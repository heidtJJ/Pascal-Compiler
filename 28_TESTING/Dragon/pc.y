%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <string.h>
    #include "node.h"
    #include "scope.h"
    #include "tree.h"
    #include "util.h"
    #include "codeGeneration.h"
    #include "treeList.h"
    #include "y.tab.h"

    // DRAGON PARSER

    extern int yyerror(char*);
    extern int yylex();

    scope_t* top_scope = NULL;
    
    FILE* outFile;

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
    TreeList* treeListVal;
}

%token PROGRAM   /* Keyword PROGRAM */
%token BBEGIN END
%token VAR   
%token TYPE   
%token READ WRITE   
%token PROCEDURE FUNCTION ARGS
%token INTEGER REAL BOOLEAN NOT_SET
%token ARRAY OF DOTDOT
%token IF THEN ELSE WHILE FOR DO TO
%token ASSIGNOP 

%token <opval> RELOP
%token EQ NE LT LE GT GE

%token <opval> ADDOP 
%token PLUS MINUS OR

%token <opval> MULOP
%token STAR SLASH AND MOD

%token NOT 

%token <sval> ID
%token <ival> INUM
%token <rval> RNUM

%token COMMA
%token SEMICOLON

%token ARRAY_ACCESS
%token FUNCTION_CALL
%token PROCEDURE_CALL
%token COMPOUND_STATEMENT

%type <ival>   INTEGER REAL BOOLEAN
%type <ival>   standard_type
%type <ival>   subprogram_declaration subprogram_declarations

%type <nval>   arguments
%type <nval>   parameter_list
%type <nval>   type
%type <nval>   identifier_list
%type <nval>   subprogram_head

%type <tval>   statement
%type <tval>   matched
%type <tval>   unmatched
%type <tval>   variable
%type <tval>   procedure_statement
%type <tval>   simple_expression
%type <tval>   expression
%type <tval>   term
%type <tval>   factor
%type <tval>   compound_statement

%type <treeListVal>   statement_list
%type <treeListVal>   optional_statements
%type <treeListVal>   expression_list

%%

/* TO-DO; Function with variable declared with same name as function (different type? same type? ) */

program 
    : 
    {
        setupRegisterStack();
        fprintf(stderr, "BEGINING OF PROGRAM\n"); 
    }
    PROGRAM ID 
    {
        char* fileName = getFileName($3);
        fprintf(stderr, "fileName %s\n", fileName);
        outFile = fopen(fileName, "w+");
        if(outFile == NULL){
            yyerror("Could not open the desired file!");
        }
        genCodePrintHeader(outFile);
        
        node_t* programNode = insertProcedureNode(NULL, $3, NULL);

        top_scope = push_scope(NULL, programNode);
    }
    '(' identifier_list ')' ';'
    {
        top_scope->scopeOwner->data.procedureInfo.arguments = NULL;
    }
    declarations
    subprogram_declarations
    compound_statement
    '.'
    { 
        tree_t* compoundStmtTree = $12;
        genCode(outFile, compoundStmtTree, top_scope, 0);

        free_scope(top_scope);
        fprintf(stderr, "END OF PROGRAM\n"); 

        genCodePrintMain(outFile, $3);
        fclose(outFile);
        freeRegisters();
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

declarations /* Purely for defining variables. Variable cannot have same name as parent subprogram. */
    : declarations VAR identifier_list ':' type ';'
        {
            node_t* idListHead = $3;
            node_t* curId = idListHead;
            node_t* typeNode = $5;

            print_list(idListHead);
            
            /* Iterate through identifier_list and set type information */
            while(curId != NULL){
                char* name = curId->name;

                /* Check if variable name is redeclared in the current scope */
                if(scope_search(top_scope, name) != NULL){
                    yyerror("Variable is redeclared in the current scope in identifier_list\n");
                }
                if(top_scope->scopeOwner != NULL){
                    /* Check if variable is being declared has same name as the current function. */
                    if(strcmp(top_scope->scopeOwner->name, name) == 0){
                        yyerror("Variable is redeclared with same name as owning subprogram name in identifier_list\n");
                    }
                }

                node_t* next = curId->next;

                /* copyNode does not affect *next attribute. But it does set name. */
                copyNode(typeNode, curId);
                curId->name = name;

                /* Handle the frame offset of this variable. */
                if(curId->data.varInfo.isArray){
                    VarInfo nodeInfo = curId->data.varInfo;
                    int arrayLength = nodeInfo.end - nodeInfo.start + 1;
                    curId->frameOffset = addVariableToScope(top_scope, sizeof(int)*arrayLength);
                }
                else{
                    /* Size of float is same as size of int */
                    curId->frameOffset = addVariableToScope(top_scope, sizeof(int));
                }
                
                scope_insert_node(top_scope, curId); 
                curId = next;
            }
            fprintf(stderr, "Scope print\n");
            scope_print(top_scope);
            free_list(typeNode);
        }
    | /* empty */
    ;

type 
    /* 
        Returns a node_t* which indicates the type information
        associated with the current value. Returned name is NULL.
    */
    : standard_type 
    {
        $$ = insertVarNode(NULL, $1, NULL);
    }
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type 
    {
        /* TO-DO: VERIFY THAT FIRST INUM is LESS THAN SECOND INUM. OR SUPPORT IT */
        $$ = insertArrayNode(NULL, $8, NULL, $3, $5);
    }
    ;

standard_type
    : INTEGER { $$ = INTEGER; }
    | REAL { $$ = REAL; }
    ;

subprogram_declarations
    : subprogram_declarations subprogram_declaration ';'
    {
        $$ = $1 || $2;
    }
    | /* empty */ { $$ = 0; }
    ;

subprogram_declaration 
    /* 
        Returns a boolean of whether or not a side effect 
        has occured in this subprogram_declaration.
    */
    : subprogram_head declarations subprogram_declarations compound_statement
    {
        /* Value indicating whether subprogram_declarations have side effects. */
        short subContainsSideEffects = $3;

        /* Retrieve the list of statements. */
        tree_t* compoundStmtTree = $4;
        
        $$ = genCode(outFile, compoundStmtTree, top_scope, subContainsSideEffects);

        top_scope = pop_scope(top_scope); 
        tree_free(compoundStmtTree);
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
            node_t* functionNode = top_scope->scopeOwner;

            if(functionNode->nodeType != FUNCTION){
                yyerror("FUNCTION error in subprogram_head\n");
            }
            functionNode->data.functionInfo.returnType = $6;
            functionNode->data.functionInfo.arguments = $4;
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
            node_t* procedureNode = top_scope->scopeOwner;

            if(procedureNode->nodeType != PROCEDURE){
                yyerror("PROCEDURE error in subprogram_head\n");
            }
            procedureNode->data.procedureInfo.arguments = $4;
            $$ = procedureNode;
        }
    ;
    
arguments
    : '(' parameter_list ')' 
        { 
            node_t* cur = $2;
            print_list(cur);

            while(cur != NULL){
                node_t* copy = insertVarNode(NULL, NOT_SET, cur->name);
                fprintf(stderr, "fasd\n");
                copyNode(cur, copy);

                /* Handle the frame offset of this variable. */
                if(isArrayNode(cur)){
                    int startIndex = cur->data.varInfo.start;
                    int endIndex = cur->data.varInfo.end;
                    int size = endIndex - startIndex + 1;
                    copy->frameOffset = cur->frameOffset = addVariableToScope(top_scope, size*sizeof(int));
                }
                else{
                    copy->frameOffset = cur->frameOffset = addVariableToScope(top_scope, sizeof(int));
                }

                scope_insert_node(top_scope, copy); 

                cur = cur->next;
            }
            $$ = $2;
            print_list($2);
        }
    | /* empty */ { $$ = NULL; }
    ;

parameter_list 
    /*
        Used for inputs to functions. Returns a node list of 
        VAR nodes with their types and identifiers associated.
    */
    : identifier_list ':' type 
    {
        node_t* idList = $1;
        node_t* cur = idList;
        node_t* typeNode = $3;
        while(cur != NULL){
            char* name = cur->name;
            copyNode(typeNode, cur);
            cur->name = name;
            cur = cur->next;
        }
        free_list(typeNode);
        $$ = idList;
        print_list(idList);

    }
    | identifier_list ':' type ';' parameter_list
    {
        node_t* typeNode = $3;
        node_t* idList = $1;
        node_t* cur = idList;
        node_t* prev = NULL;


        /* 
            Iterate through identifiers setting their 
            types to type. Then re-copy the name. 
        */
        while(cur != NULL){
            char* name = cur->name;
            copyNode(typeNode, cur);
            cur->name = name;
            prev = cur;
            cur = cur->next;
        }
        prev->next = $5;
        free_list(typeNode);
        $$ = idList;
        print_list(idList);
    }
    | /* empty */ { $$ = NULL; }
    ;

compound_statement
    : BBEGIN optional_statements END 
        { 
            /* Do semantic checking on statements. */
            if(top_scope == NULL){
                yyerror("Invalid scope in subprogram_declaration\n");
            }
            
            $$ = mktree(COMPOUND_STATEMENT, mktreeList($2), NULL);
        }
    ;

optional_statements
    : statement_list 
    { 
        $$ = $1; 
    }
    | /* empty */ { $$ = NULL; }
    ;

statement_list
    : statement 
    { 
        $$ = insertTree(NULL, $1);
 
    }
    | statement ';' optional_statements 
    {
        $$ = insertTree($3, $1); 
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
    | WRITE '(' expression ')' 
        { 
            $$ = mktree(WRITE, $3, NULL); 
        }
    | READ '(' variable ')'
    {
        $$ = mktree(READ, $3, NULL);
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
        node_t* varNode = scope_search_all(top_scope, $1);
        if(!varNode){
            fprintf(stderr, "\n%s\n", $1);
            yyerror("Cannot find variable ID in variable\n");
        }
        if(strcmp($1, top_scope->scopeOwner->name)){
            /* ID is not the same as scope owner name. */
            if(varNode->nodeType != VAR){
                fprintf(stderr, "\n%d      %s\n", varNode->nodeType, top_scope->scopeOwner->name);
                yyerror("Accesed identifier is not a variable\n");
            }
            if(varNode->data.varInfo.isArray == IS_ARRAY){
                //yyerror("Accesed variable is an array in variable\n");
            }
        }

        $$ = mkid(varNode); 
    }
    | ID '[' simple_expression ']' 
    { 
        node_t* arrayNode = scope_search_all(top_scope, $1);
        if(!arrayNode || arrayNode->nodeType != VAR){
            yyerror("Cannot find array variable ID in variable\n");
        }
        if(arrayNode->data.varInfo.isArray == NOT_ARRAY){
            fprintf(stderr, "%s\n", arrayNode->name);
            yyerror("Accesed variable is not an array in variable\n");
        }
        $$ = mktree(ARRAY_ACCESS, mkid(arrayNode), $3);
    }
    ;

procedure_statement
    : ID 
    { 
        node_t* procedureNode = scope_search_all(top_scope, $1);
        if(procedureNode == NULL){
            fprintf(stderr, "ID is %s\n", $1);
            yyerror("Cannot find procedure ID match 1 in procedure_statement\n");
        }
        if(procedureNode->nodeType != PROCEDURE){
            yyerror("Cannot find procedure ID match 2 in procedure_statement\n");
        }
        $$ = mktree(PROCEDURE_CALL, mkid(procedureNode), NULL); 
    }
    | ID '(' expression_list ')' 
    { 
        node_t* procedureNode = scope_search_all(top_scope, $1);
        if(procedureNode == NULL){
            fprintf(stderr, "ID is %s\n", $1);
            yyerror("Cannot find procedure ID match 3 in procedure_statement\n");
        }
        if(procedureNode->nodeType != PROCEDURE){
            yyerror("Cannot find procedure ID match 4 in procedure_statement\n");
        }

        /* Validate input types (arguments) */
        node_t* expectedArgs = procedureNode->data.procedureInfo.arguments;
        validateArguments(top_scope, expectedArgs, $3);

        

        $$ = mktree(PROCEDURE_CALL, mkid(procedureNode), mktreeList($3)); 
    }
    ;

expression_list /* Returns a list of the types returned from each expression */
    : expression 
    { 
        /*int expressionType = getExpressionType(top_scope, $1);*/
        $$ = insertTree(NULL, $1); 
    }
    | expression ',' expression_list
    {
        /*int expressionType = getExpressionType(top_scope, $1);*/
        
        /*fprintf(stderr, "expressionType = %d expression location = %d  expression_list location = %d\n", expressionType, $1, $3);*/
        
        $$ = insertTree($3, $1); 
        /*fprintf(stderr, "AFTER insertVarNode %d\n", $$);*/
    }
    | { $$ = NULL; }/* empty */
    ;

expression
    : simple_expression 
    { 
        $$ = $1; 
    }
    | simple_expression RELOP simple_expression { $$ = mkop(RELOP, $2, $1, $3); }
    ;

simple_expression
    : term 
    { 
        $$ = $1; 
    }
    | ADDOP term 
    { 
        $$ = mkop(ADDOP, $1, mkinum(0), $2); 
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
    : ID '(' expression_list ')' /* Function call */
    { 
        node_t* matchNode = scope_search_all(top_scope, $1);
        if(matchNode == NULL || matchNode->nodeType != FUNCTION){
            yyerror("Cannot find function ID match in factor\n");
        }

        /* Validate input types (arguments) */
        node_t* expectedArgs = matchNode->data.functionInfo.arguments;
        validateArguments(top_scope, expectedArgs, $3);

        $$ = mktree(FUNCTION_CALL, mkid(matchNode), mktreeList($3)); 
    }
    | variable { $$ = $1; }
    | INUM { $$ = mkinum($1); }
    | RNUM { $$ = mkrnum($1); }
    | '(' expression ')' { $$ = $2; }
    | NOT factor { $$ = mktree(NOT, $2, NULL); }
    ;

%%

int main(){
    yyparse();
}