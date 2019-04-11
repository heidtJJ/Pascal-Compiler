%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <string.h>
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

%token ARGUMENT_TYPE /* Used for node nodeType to indicate an argument type*/

%type <ival>   INTEGER REAL BOOLEAN
%type <ival>   standard_type

%type <nval>   arguments
%type <nval>   parameter_list
%type <nval>   type
%type <nval>   expression_list
%type <nval>   identifier_list
%type <nval>   subprogram_head

%type <tval>   compound_statement
%type <tval>   optional_statements
%type <tval>   statement_list
%type <tval>   statement
%type <tval>   matched
%type <tval>   unmatched
%type <tval>   variable
%type <tval>   procedure_statement
%type <tval>   simple_expression
%type <tval>   expression
%type <tval>   term
%type <tval>   factor

%%

/* TO-DO; Function with variable declared with same name as function (different type? same type? ) */

program 
    : 
    {
        fprintf(stderr, "BEGINING OF PROGRAM\n"); 
    }
    PROGRAM ID 
    {
        top_scope = push_scope(NULL, insertVarNode(NULL, NOT_SET, $3));
    }
    '(' identifier_list ')' ';'
    declarations
    subprogram_declarations
    compound_statement
    '.'
    { 
        free_scope(top_scope);
        fprintf(stderr, "END OF PROGRAM\n"); 
    }
    ;

identifier_list /* Returns a list of identifier names. NOT_SET is nodeType */
    : ID
    { 
        $$ = insertVarNode(NULL, NOT_SET, $1); 
    }
    | ID ',' identifier_list 
    { 
        node_t* newTop = insertVarNode($3, NOT_SET, $1); 
        $$ = newTop;
    }
    ;

declarations
    : declarations VAR identifier_list ':' type ';'
        {
            int type = getType($5);
            node_t* idList = $3;
            node_t* cur = idList;

            while(cur != NULL){
                if(scope_search(top_scope, cur->name) != NULL){
                    /* Variable is redeclared in the current scope */
                    yyerror("Variable is redeclared in the current scope in identifier_list\n");
                }
                if(top_scope->scopeOwner != NULL){
                    if(strcmp(top_scope->scopeOwner->name, cur->name) == 0){
                        // Variable is being declared with same name as the current function.
                        yyerror("Variable is redeclared with same name as owning subprogram name in identifier_list\n");
                    }
                }
                if($5->nodeType == ARRAY){
                    cur->data.arrayInfo.type = type; 
                }
                else{
                    cur->data.varInfo.type = type; 
                }
                node_t* next = cur->next;
                scope_insert_node(top_scope, cur); 
                cur = next;
            }
            free_list($5);
        }
    | /* empty */
    ;

type 
    /* 
        Returns a node_t* which indicates the type information
        associated with the current value. A nodeType ARGUMENT_TYPE node  
        returned indicates a REAL or INTEGER (not array). An nodeType ARRAY  
        type node indicates an array of node->data.type
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
        node_t* subprogramHead = $1;
        if(subprogramHead->nodeType == FUNCTION){
            /* Ensure no side effects in subprogram_declarations or compound_statement */
            /* Ensure a return statement. */
        }
        top_scope = pop_scope(top_scope); 
    }
    ;

subprogram_head
    : FUNCTION ID
        {   
            if(scope_search(top_scope, $2) != NULL){
                /* Function with same name is redeclared in the same scope */
                yyerror("Function redeclared in the same scope\n");
            }
            node_t* functionNode = scope_insert_function(top_scope, 0, $2, NULL);
            top_scope = push_scope(top_scope, functionNode);  
        } 
        arguments ':' standard_type ';' 
        {
            /* Set the return type and argument types of the node */
            scope_t* prevScope = top_scope->next;
            node_t* functionNode = scope_search(prevScope, $2);

            if(functionNode->nodeType != FUNCTION){
                yyerror("FUNCTION error in subprogram_head\n");
            }
            functionNode->data.functionInfo.returnType = $6;
            functionNode->data.functionInfo.arguments = copyArguments($4);
            $$ = functionNode;
        }
    | PROCEDURE ID 
        { 
            if(scope_search(top_scope, $2) != NULL){
                /* Procedure with same name is redeclared in the same scope */
                yyerror("Procedure redeclared in the same scope\n");
            }
            node_t* procedureNode = scope_insert_procedure(top_scope, $2, NULL);
            top_scope = push_scope(top_scope, procedureNode);  
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
            $$ = procedureNode;
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
        int type = getType($3);
        node_t* idList = $1;
        node_t* cur = idList;
        while(cur != NULL){
            if($3->nodeType == ARRAY){
                cur->data.arrayInfo.type = type; 
            }
            else {
                cur->data.varInfo.type = type; 
            }
            node_t* next = cur->next;
            scope_insert_node(top_scope, cur); 
            cur = next;
        }
        $$ = idList;
    }
    | parameter_list ';' identifier_list ':' type
    {
        node_t* idList = $3;
        node_t* cur = idList;
        while(cur != NULL){
            cur->data.type = getType($5);
            node_t* next = cur->next;
            scope_insert_node(top_scope, cur); 
            cur = next;
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
            tree_free($$);
        }
    ;

optional_statements
    : statement_list 
    { 
        validateStatement(top_scope, $1);
        $$ = $1; 
    }
    | /* empty */ { $$ = NULL; }
    ;

statement_list
    : statement 
    { 
        $$ = $1; 
    }
    | statement ';' optional_statements 
    {
        $$ = mktree(SEMICOLON, $1, $3); 
    }
    ;

statement
    : matched { $$ = $1; }
    | unmatched { $$ = $1; }
    ;

matched
    : IF expression THEN matched ELSE matched
        { $$ = mktree(IF, $2, mktree(THEN, $4, $6)); }
    | variable ASSIGNOP expression 
        {  
            $$ = mktree(ASSIGNOP, $1, $3);
        }    
    | procedure_statement 
        { $$ = $1; }
    | compound_statement 
        { $$ = $1; }
    | WHILE expression DO matched
        { $$ = mktree(WHILE, $2, $4); }
    | FOR variable ASSIGNOP expression TO expression DO statement
        { 
            int variableType = getExpressionType(top_scope, $2);
            int expression1 = getExpressionType(top_scope, $4);
            int expression2 = getExpressionType(top_scope, $6);
            if(variableType != expression1 || expression1 != expression2){
                yyerror("For loop assignment types do not match.");
            }
            $$ = mktree(FOR, mktree(ASSIGNOP, $2, $4), mktree(TO, $6, mktree(DO, $8, NULL))); 

        }
    ;

unmatched 
    : IF expression THEN statement
        { $$ = mktree(IF, $2, mktree(THEN, $4, NULL)); }
    | IF expression THEN matched ELSE unmatched
        { $$ = mktree(IF, $2, mktree(THEN, $4, $6)); }
    ;

variable
    : ID 
    {
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(!matchNode){
            yyerror("Cannot find variable ID in variable\n");
        }
        $$ = mkid(matchNode); 
    }
    | ID '[' expression ']' 
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(!matchNode){
            yyerror("Cannot find array variable ID in variable\n");
        }
        $$ = mktree(ARRAY_ACCESS, mkid(matchNode), $3);
    }
    ;

procedure_statement
    : ID 
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != PROCEDURE){
            yyerror("Cannot find procedure ID match 1 in procedure_statement\n");
        }
        $$ = mktree(PROCEDURE_CALL, mkid(matchNode), NULL); 
    }
    | ID '(' expression_list ')' 
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != PROCEDURE){
            yyerror("Cannot find procedure ID match 2 in procedure_statement\n");
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
        
        tree_free($1);/* If this line is deleted, seg fault! Why?? */
        
        $$ = insertTypeNode(NULL, expressionType); 

        fprintf(stderr, "expressionType = %d  expression location = %d $$ = %d\n", 
            expressionType, $1, $$);
    }
    | expression ',' expression_list
    {
        int expressionType = getExpressionType(top_scope, $1);
        tree_free($1);/* If this line is deleted, seg fault! Why?? */
        
        fprintf(stderr, "expressionType = %d expression location = %d  expression_list location = %d\n",
                expressionType, $1, $3);
        
        $$ = insertTypeNode($3, expressionType); 
        fprintf(stderr, "AFTER insertTypeNode %d\n", $$);
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
        if(matchNode == NULL || matchNode->nodeType != VAR){
            yyerror("Cannot find ID match in factor\n");
        }
        $$ = mkid(matchNode); 
    }
    | ID '[' expression ']' 
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != ARRAY){
            yyerror("Cannot find array ID match in factor\n");
        }
        $$ = mktree(ARRAY_ACCESS, mkid(matchNode), $3); 
    }
    | ID '(' expression_list ')' /* Function call */
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != FUNCTION){
            yyerror("Cannot find function ID match in factor\n");
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
    yyparse();
}