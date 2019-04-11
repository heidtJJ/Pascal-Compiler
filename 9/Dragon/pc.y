%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "node.h"
    #include "scope.h"
    #include "tree.h"
    #include "util.h"
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
%token PROCEDURE FUNCTION ARGS
%token INTEGER REAL INTEGER_ARRAY REAL_ARRAY BOOLEAN NOT_SET
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

%token ENTRY_TYPE

%type <ival>   INTEGER REAL BOOLEAN
%type <ival>   standard_type

%type <nval>   arguments
%type <nval>   parameter_list
%type <nval>   type
%type <nval>   expression_list

%type <tval>   identifier_list
%type <tval>   compound_statement
%type <tval>   optional_statements
%type <tval>   statement_list
%type <tval>   statement
%type <tval>   variable
%type <tval>   procedure_statement
%type <tval>   simple_expression
%type <tval>   expression
%type <tval>   term
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

identifier_list /* Returns a tree of identifier names */
    : ID
    { 
        if(scope_search(top_scope, $1) != NULL){
            /* Variable is redeclared in the current scope */
            yyerror("Variable %s is redeclared in the current scope in identifier_list\n");
        }
        $$ = mkid(insertVarNode(NULL, NOT_SET, $1)); 
    }
    | identifier_list ',' ID
    { 
        if(scope_search(top_scope, $3) != NULL){
            /* Variable is redeclared in the current scope */
            yyerror("Variable %s is redeclared in the current scope in identifier_list\n");
        }
        $$ = mktree(COMMA, $1, mkid(insertVarNode(NULL, NOT_SET, $3)));
    }
    ;

declarations
    : declarations VAR identifier_list ':' type ';'
        {
            node_t* idList = convertToNameList($3);
            node_t* cur = idList;
            while(cur != NULL){
                cur->data.varInfo.type = getType($5);
                scope_insert_node(top_scope, cur); 
                cur = cur->next;
            }
        }
    | /* empty */
    ;

type 
    /* 
        Returns a node_t* which indicates the type information
        associated with the current value. A ENTRY_TYPE node returned 
        indicates a REAL or INTEGER (not array). An ARRAY type node
        indicates an array of type, node->data.type
    */
    : standard_type 
    {
        $$ = insertTypeNode(NULL, $1);
    }
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type 
    {
        $$ = insertArrayNode(NULL, $8, NULL, $5 - $3);
    }
    ;

standard_type
    : INTEGER { $$ = INTEGER; }
    | REAL { $$ = REAL; }
    ;

subprogram_declarations
    : subprogram_declarations subprogram_declaration ';'
    | /* empty */
    ;

subprogram_declaration
    : subprogram_head declarations subprogram_declarations compound_statement
    { 
        if(top_scope == NULL){
            yyerror("Invalid scope in subprogram_declaration\n");
        }
        node_t* procNode = scope_search_all(top_scope, "boo");
        top_scope = pop_scope(top_scope); 
    }
    ;

subprogram_head
    : FUNCTION ID
        {   
            if(scope_search(top_scope, $2) != NULL){
                /* Function with same name is redeclared in the same scope */
                yyerror("Function %s redeclared in the same scope\n");
            }
            scope_insert_function(top_scope, 0, $2, NULL);
            top_scope = push_scope(top_scope);  
        } 
        arguments ':' standard_type ';' 
        {
            /* Set the return type and argument types of the node */
            scope_t* prevScope = top_scope->next;
            node_t* functionNode = scope_search(prevScope, $2);

            functionNode->data.functionInfo.returnType = $6;
            functionNode->data.functionInfo.arguments = copyArguments($4);
        }
    | PROCEDURE ID 
        { 
            if(scope_search(top_scope, $2) != NULL){
                /* Procedure with same name is redeclared in the same scope */
                yyerror("Procedure %s redeclared in the same scope\n");
            }
            scope_insert_procedure(top_scope, $2, NULL);
            top_scope = push_scope(top_scope);  
        }
        arguments ';'
        {
            /* Set the return type and argument types of the node */
            scope_t* prevScope = top_scope->next;
            node_t* procedureNode = scope_search(prevScope, $2);

            if(procedureNode->nodeType != PROCEDURE){
                yyerror("PROCEDURE error in subprogram_head\n");
            }
            procedureNode->data.procedureInfo.arguments = copyArguments($4);
        }
    ;
    
arguments
    : '(' parameter_list ')' 
        { 
            $$ = $2; 
        }
    | /* empty */ { $$ = NULL; }
    ;

parameter_list 
    /*
        returns a node list of VAR node identifiers with their types associated
    */
    : identifier_list ':' type 
    {
        node_t* idList = convertToNameList($1);
        node_t* cur = idList;
        while(cur != NULL){
            cur->data.varInfo.type = getType($3);
            scope_insert_node(top_scope, cur); 
            cur = cur->next;
        }
        $$ = idList;
    }
    | parameter_list ';' identifier_list ':' type
    {
        node_t* idList = convertToNameList($3);
        node_t* cur = idList;
        while(cur != NULL){
            cur->data.type = getType($5);
            scope_insert_node(top_scope, cur); 
            cur = cur->next;
        }
        getBottom($1)->next = idList;
        $$ = $1;
    }
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
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode){
            $$ = mkid(matchNode); 
        }
        else{
            yyerror("Cannot find variable ID '%s' in variable\n");
        }
    }
    | ID '[' expression ']' { $$ = mktree(ARRAY_ACCESS, mkid(scope_search_all(top_scope, $1)), $3); }
    ;

procedure_statement
    : ID 
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != PROCEDURE){
            yyerror("Cannot find ID '%s' match in procedure_statement\n");
        }
        $$ = mktree(PROCEDURE_CALL, mkid(matchNode), NULL); 
    }
    | ID '(' expression_list ')' 
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != PROCEDURE){
            yyerror("Cannot find ID '%s' match in procedure_statement\n");
        }

        // Validate input types
        node_t* expectedArgs = matchNode->data.procedureInfo.arguments;
        node_t* actualArgs = $3;

        validateArguments(expectedArgs, actualArgs);

        $$ = mktree(PROCEDURE_CALL, mkid(matchNode), mkargs($3)); 
    }
    ;

expression_list /* Returns a list of the types returned from each expression */
    : expression 
    { 
        int expressionType = getExpressionType(top_scope, $1);
        $$ = insertTypeNode(NULL, expressionType); 
    }
    | expression ',' expression_list
        {
            $$ = $3;
            int expressionType = getExpressionType(top_scope, $1);
            $$ = insertTypeNode($$, expressionType);
        }
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
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL){
            yyerror("Cannot find ID '%s' match in factor\n");
        }
        $$ = mkid(matchNode); 
    }
    | ID '[' expression ']' 
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != ARRAY){
            yyerror("Cannot find ID '%s' match in factor\n");
        }
        $$ = mktree(ARRAY_ACCESS, mkid(matchNode), $3); 
    }
    | ID '(' expression_list ')' /* Function call */
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != FUNCTION){
            yyerror("Cannot find ID '%s' match in factor\n");
        }

        node_t* expectedArgs = matchNode->data.functionInfo.arguments;
        node_t* actualArgs = $3;
        
        validateArguments(expectedArgs, actualArgs);

        $$ = mktree(FUNCTION_CALL, mkid(matchNode), mkargs($3)); 
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