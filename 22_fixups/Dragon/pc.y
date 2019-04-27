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

    unsigned int NO_FUNCTION_RETURN = 0x1;
    unsigned int NO_SIDE_EFFECTS = 0x2;

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
                copyNode(typeNode, curId);/* Does not affect *next attribute. Does affect ->name. */
                curId->name = name;
                node_t* copy = insertVarNode(NULL, NOT_SET, name);

                /* Handle the frame offset of this variable. */
                copy->frameOffset = addVariableToScope(top_scope, sizeof(int));
                
                scope_insert_node(top_scope, copy); 
                copyNode(curId, copy);
                curId = curId->next;
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
        tree_t* cpmdStatement = $4;
        unsigned int subContainsSideEffects = $3;
        if(cpmdStatement == NULL){
            $$ = subContainsSideEffects;
        }
        else{
            /* compound_statement already checked for side effects */
            assert(cpmdStatement->type == INUM);/* Indicates side effects or not */

            node_t* subpgmHeadNode = $1;
            int cpndStmtSideEffects = cpmdStatement->attribute.ival;
            if(subpgmHeadNode->nodeType == FUNCTION && subContainsSideEffects){
                /* No side effects allowed in compound_statement or subprogram_declarations. */
                fprintf(stderr, "In function name %s\n", subpgmHeadNode->name);
                yyerror("subprogram_declarations contain side effects in subprogram_declaration\n");
            }
            subContainsSideEffects = subContainsSideEffects || cpndStmtSideEffects;

            $$ = subContainsSideEffects; 
            
            top_scope = pop_scope(top_scope); 
            tree_free(cpmdStatement);
        }
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
            node_t* procedureNode = top_scope->scopeOwner;;

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
                copy->frameOffset = cur->frameOffset = addVariableToScope(top_scope, sizeof(int));

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
    ;

compound_statement
    : BBEGIN optional_statements END 
        { 
            /* Do semantic checking on statements. */
            if(top_scope == NULL){
                yyerror("Invalid scope in subprogram_declaration\n");
            }
            node_t* scopeOwner = top_scope->scopeOwner;
            TreeList* statementList = $2;

            /* Setup flags to check for side effects. */
            int flags = NO_SIDE_EFFECTS;
            if(scopeOwner->nodeType == FUNCTION){
                flags = flags | NO_FUNCTION_RETURN;
            }
            int maxNumArguments = 0;
            findMaxNumArguments(statementList, &maxNumArguments);
            for(int i = 0; i < maxNumArguments; ++i){
                addVariableToScope(top_scope, sizeof(int));
            }
            /* Add space to scope for temp variables */
            top_scope->tempsAddress = addVariableToScope(top_scope, sizeof(int));
            addVariableToScope(top_scope, sizeof(int));
            
            /* Do code generation */
            genCodePrintProcBegin(outFile, top_scope);

            TreeList* curStmt = statementList;
            while(curStmt != NULL){
                fprintf(stderr, "\n\nBefore validateStatement flags=%d\n", flags);
                validateStatement(top_scope, curStmt->statementTree, &flags);
                fprintf(stderr, "After validateStatement flags=%d\n", flags);
                
                /* Output code for the statement */
                genStatement(outFile, curStmt->statementTree, top_scope);

                fprintf(stderr, "\nBEGIN STATEMENT PRINT\n\n");
                tree_print(curStmt->statementTree);
                fprintf(stderr, "\nEND STATEMENT PRINT\n\n");
                
                curStmt = popStatement(curStmt);
            }
            int containsSideEffects = hasSideEffects(flags);
            /*fprintf(stderr, "\n\n\n HAS %d SIDE in %s\n", containsSideEffects,scopeOwner->name);*/

            if(scopeOwner->nodeType == FUNCTION){
                if(hasNoReturnStmt(flags)){
                    yyerror("Function return has no return statement in subprogram_declaration\n");
                }
                if(containsSideEffects){
                    yyerror("Function return has SIDE EFFECT in subprogram_declaration\n");
                }
            }
            else{ /* scopeOwner->nodeType == PROCEDURE */
                assert(scopeOwner->nodeType == PROCEDURE);
                scopeOwner->data.procedureInfo.hasSideEffects = containsSideEffects;
            }        

            genCodePrintProcEnd(outFile, top_scope->scopeName);
            $$ = mkinum(containsSideEffects);

            fprintf(stderr, "RETURNING SIDE EFFECT %d %d\n\n", containsSideEffects, flags);
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
            if(varNode->nodeType != VAR){
                fprintf(stderr, "\n%d\n", varNode->nodeType);
                yyerror("Accesed identifier is not a variable\n");
            }
            if(varNode->data.varInfo.isArray == IS_ARRAY){
                yyerror("Accesed variable is an array in variable\n");
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