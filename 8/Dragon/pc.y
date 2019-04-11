%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "node.h"
    #include "scope.h"
    #include "tree.h"
    #include "y.tab.h"

    // DRAGON PARSER

    extern int yyerror(char*);
    extern int yylex();

    scope_t* top_scope;
%}

%union {
    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;
    node_t* nval;
}

%token PROGRAM   /* Keyword PROGRAM */
%token BBEGIN END
%token VAR   
%token TYPE   
%token PROCEDURE FUNCTION 
%token INTEGER REAL 
%token ARRAY OF DOTDOT
%token IF THEN ELSE WHILE FOR DO TO
%token ASSIGNOP 

%token <opval> RELOP
%token EQ NE LT LE GT GE

%token <opval> ADDOP 
%token PLUS MINUS OR

%token <opval> MULOP
%token STAR SLASH AND

%token NOT 

%token <sval> ID
%token <ival> INUM
%token <rval> RNUM

%token COMMA
%token SEMICOLON

%token ARRAY_ACCESS
%token FUNCTION_CALL
%token PROCEDURE_CALL

%token ENTRY_NAME
%token ENTRY_TYPE

%type <ival>   INTEGER REAL

%type <tval> standard_type

%type <nval>   arguments
%type <nval>   parameter_list

%type <tval>   identifier_list
%type <tval>   compound_statement
%type <tval>   optional_statements
%type <tval>   statement_list
%type <tval>   statement
%type <tval>   variable
%type <tval>   procedure_statement
%type <tval>   expression_list
%type <tval>   simple_expression
%type <tval>   expression
%type <tval>   term
%type <tval>   type
%type <tval>   factor

%%

program 
    : 
    {
        fprintf(stderr, "BEGINING OF PROGRAM\n"); 
    }
    PROGRAM ID '(' identifier_list ')' ';'
    declarations
    subprogram_declarations
    compound_statement
    '.'
    { 
        fprintf(stderr, "END OF PROGRAM\n"); 
    }
    ;

identifier_list
    : ID
    { 
        if(scope_search(top_scope, $1) != NULL){
            /* Variable is redeclared in the current scope */
            fprintf(stderr, "Variable %s is redeclared in the current scope in identifier_list\n", $1); 
            exit(0);
        }
        $$ = mkid(scope_insert(top_scope, $1)); 
    }
    | identifier_list ',' ID
    { 
        if(scope_search(top_scope, $3) != NULL){
            /* Variable is redeclared in the current scope */
            fprintf(stderr, "Variable %s is redeclared in the current scope in identifier_list\n", $3); 
            exit(0);
        }
        $$ = mktree(COMMA, $1, mkid(scope_insert(top_scope, $3)));
    }
    ;

declarations
    : declarations VAR identifier_list ':' type ';'
    | /* empty */
    ;

type 
    /* type -> tree with root node of type TYPE, 
       left node indicates whether array or not, 
       right node indicates type (INTEGER, REAL, etc.) 
    */
    : standard_type 
    { 
        $$ = mktree(TYPE, NULL, $1); 
    }
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type 
    { 
        $$ = mktree(TYPE, mktree(ARRAY, NULL, NULL), $8); 
    }
    ;

standard_type
    : INTEGER { $$ = mktree($1, NULL, NULL); }
    | REAL { $$ = mktree($1, NULL, NULL); }
    ;

subprogram_declarations
    : subprogram_declarations subprogram_declaration ';'
    | /* empty */
    ;

subprogram_declaration
    : subprogram_head declarations subprogram_declarations compound_statement
    { 
        if(top_scope == NULL){
            fprintf(stderr, "Invalid scope in subprogram_declaration\n"); 
            exit(0);
        }
        top_scope = pop_scope(top_scope); 
    }
    ;

subprogram_head
    : FUNCTION ID
        {   
            if(scope_search(top_scope, $2) != NULL){
                /* Function with same name is redeclared in the same scope */
                fprintf(stderr, "Function %s redeclared in the same scope\n", $2); 
                exit(0);
            }
            scope_insert_function(top_scope, 0, $2, NULL);
            top_scope = push_scope(top_scope);  
        } 
        arguments ':' standard_type ';' 
        {
            /* Set the return type and argument types of the node */
            scope_t* prevScope = top_scope->next;
            node_t* functionNode = scope_search(prevScope, $2);

            functionNode->data.functionInfo.returnType = $6->type;
            functionNode->data.functionInfo.arguments = $4;
        }
    | PROCEDURE ID 
        { 
            if(scope_search(top_scope, $2) != NULL){
                /* Procedure with same name is redeclared in the same scope */
                fprintf(stderr, "Procedure %s redeclared in the same scope\n", $2); 
                exit(0);
            }
            scope_insert(top_scope, $2);
            top_scope = push_scope(top_scope);  
        }
        arguments ';'
    ;
    
arguments
    : '(' parameter_list ')' { $$ = $2; }
    | /* empty */ { $$ = NULL; }
    ;

parameter_list /* returns a node list of identifiers with their types associated */
    : identifier_list ':' type 
    {
        node_t* idList = convertToNameList($1);
        node_t* cur = idList;
        while(cur != NULL){
            cur->data.type = $3;
            cur = cur->next;
        }
        $$ = idList;
    }
    | parameter_list ';' identifier_list ':' type
    ;

compound_statement
    : BBEGIN optional_statements END 
        { 
            $$ =  $2;
            fprintf(stderr, "\nBEGIN TREE PRINT\n\n");
            tree_print($$);
            fprintf(stderr, "\nEND TREE PRINT\n\n");
        }
    ;

optional_statements
    : statement_list { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

statement_list
    : statement { $$ = $1; }
    | statement ';' optional_statements { $$ = mktree(SEMICOLON, $1, $3); }
    ;

statement
    : variable ASSIGNOP expression 
        {  
            $$ = mktree(ASSIGNOP, $1, $3);
        }
    | procedure_statement 
        { $$ = $1; }
    | compound_statement 
        { $$ = $1; }
    | IF expression THEN statement ELSE statement
        { $$ = mktree(IF, $2, mktree(THEN, $4, $6)); }
    | IF expression THEN statement
        { $$ = mktree(IF, $2, mktree(THEN, $4, NULL)); }
    | WHILE expression DO statement
        { $$ = mktree(WHILE, $2, $4); }
    | FOR variable ASSIGNOP expression TO expression DO optional_statements
        { $$ = mktree(FOR, mktree(ASSIGNOP, $2, $4), mktree(TO, $6, mktree(DO, $8, NULL))); }
    ;

variable
    : ID 
    {
        node_t* match = scope_search_all(top_scope, $1);
        if(match){
            $$ = mkid(match); 
        }
        else{
            fprintf(stderr, "Cannot find variable ID '%s' in variable\n", $1); 
            scope_print(top_scope);
            exit(0);
        }
    }
    | ID '[' expression ']' { $$ = mktree(ARRAY_ACCESS, mkid(scope_search_all(top_scope, $1)), $3); }
    ;

procedure_statement
    : ID 
    { 
        node_t* match = scope_search_all(top_scope, $1);
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in procedure_statement\n", $1); 
            scope_print(top_scope);
            exit(0);
        }
        $$ = mktree(PROCEDURE_CALL, mkid(match), NULL); 
    }
    | ID '(' expression_list ')' 
    { 
        node_t* match = scope_search_all(top_scope, $1);
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in procedure_statement\n", $1); 
            scope_print(top_scope);
            exit(0);
        }
        $$ = mktree(PROCEDURE_CALL, mkid(match), $3); 
    }
    ;

expression_list
    : expression { $$ = $1; }
    | expression_list ',' expression 
        { $$ = mktree(COMMA, $1, $3); }
    ;

expression
    : simple_expression { $$ = $1; }
    | simple_expression RELOP simple_expression { $$ = mkop(RELOP, $2, $1, $3); }
    ;

simple_expression
    : term 
    { 
        $$ = $1; 
    }
    | ADDOP term 
    { 
        $$ = mkop(ADDOP, $1, $2, NULL); 
    }
    | simple_expression ADDOP term 
    { 
        $$ = mkop(ADDOP, $2, $1, $3); 
    }
    ;

term
    : factor 
        { $$ = $1; }
    | term MULOP factor
        { $$ = mkop(MULOP, $2, $1, $3); }
    ;

factor
    : ID 
    { 
        node_t* match = scope_search_all(top_scope, $1);
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in factor\n", $1); 
            exit(0);
        }
        $$ = mkid(match); 
    }
    | ID '[' expression ']' 
    { 
        node_t* match = scope_search_all(top_scope, $1);
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in factor\n", $1); 
            exit(0);
        }
        $$ = mktree(ARRAY_ACCESS, mkid(match), $3); 
    }
    | ID '(' expression_list ')' 
    { 
        node_t* match = scope_search_all(top_scope, $1);
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in factor\n", $1); 
            exit(0);
        }
        $$ = mktree(FUNCTION_CALL, mkid(match), $3); 
    }
    | INUM { $$ = mkinum($1); }
    | RNUM { $$ = mkrnum($1); }
    | '(' expression ')' { $$ = $2; }
    | NOT factor { $$ = mktree(NOT, $2, NULL); }
    ;

%%

int main(){
    top_scope = mkscope();
    yyparse();
    free_scope(top_scope);
}