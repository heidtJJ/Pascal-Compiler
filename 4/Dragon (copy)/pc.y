%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include "tree.h"
    #include "y.tab.h"

    // DRAGON PARSER

    extern int yyerror(char*);
    extern int yylex();
%}

%union {
    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;
}

%token PROGRAM   /* Keyword PROGRAM */
%token BBEGIN END
%token VAR   
%token PROCEDURE FUNCTION 
%token INTEGER REAL 
%token ARRAY OF DOTDOT
%token IF THEN ELSE WHILE DO
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

%token ARRAY_ACCESS
%token FUNCTION_CALL
%token PROCEDURE_CALL

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
%type <tval>   factor

%%

program 
    : 
    { fprintf(stderr, "BEGINING OF PROGRAM\n"); }
    PROGRAM ID '(' identifier_list ')' ';'
    declarations
    subprogram_declarations
    compound_statement
    '.'
    { fprintf(stderr, "END OF PROGRAM\n"); }
    ;

identifier_list
    : ID
        { $$ = mkid(symtab_insert($1)); }
    | identifier_list ',' ID
        { $$ = mktree(COMMA, $1, mkid(symtab_insert($3))); }
    ;

declarations
    : declarations VAR identifier_list ':' type ';'
    | /* empty */
    ;

type
    : standard_type
        { $$ = NULL; }
    | ARRAY '[' INUM DOTDOT INUM ']' OF standard_type
        { $$ = NULL; }
    ;

standard_type
    : INTEGER
    | REAL
    ;

subprogram_declarations
    :subprogram_declarations subprogram_declaration ';'
    | /* empty */
    ;

subprogram_declaration
    : subprogram_head declarations subprogram_declarations compound_statement
        { /* pop_current_scope(); */}
    ;

subprogram_head
    : FUNCTION ID { /* push_new_scope(); */  } arguments ':' standard_type ';'
    | PROCEDURE ID arguments ';'
    ;
    
arguments
    : '(' parameter_list ')'
    | /* empty */
    ;

parameter_list
    : identifier_list ':' type
    | parameter_list ';' identifier_list ':' type
    ;

compound_statement
    : BBEGIN optional_statements END 
        { 
            $$ =  $2;
            fprintf(stderr, "BEGIN TREE PRINT\n\n");
            tree_print($$);
            fprintf(stderr, "END TREE PRINT\n\n");
        }
    ;

optional_statements
    : statement_list { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

statement_list
    : statement { $$ = $1; }
    | statement_list ';' statement { $$ = mktree(COMMA, $1, $3); }
    ;

statement
    : variable ASSIGNOP expression 
        {  $$ = mktree(ASSIGNOP, $1, $3); }
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
    ;

variable
    : ID { $$ = mkid($1); }
    | ID '[' expression ']' { $$ = mktree(ARRAY_ACCESS, mkid($1), $3); }
    ;

procedure_statement
    : ID { $$ = mkid($1); }
    | ID '(' expression_list ')' { $$ = mktree(PROCEDURE_CALL, mkid($1), $3); }
    ;

expression_list
    : expression { $$ = $1; }
    | expression_list ',' expression 
        { $$ = mktree(COMMA, $1, $3); }
    ;

expression
    : simple_expression
    | simple_expression RELOP simple_expression { $$ = mktree(COMMA, $1, $3); }
    ;

simple_expression
    : term { $$ = $1; }
    | ADDOP term { $$ = mkop(ADDOP, $1, $2, NULL); }
    | simple_expression ADDOP term { $$ = mkop(ADDOP, $2, $1, $3); }
    ;

term
    : factor 
        { $$ = $1; }
    | term MULOP factor
        { $$ = mkop(MULOP, $2, $1, $3); }
    ;

factor
    : ID { $$ = mkid(symtab_search($1)); }
    | ID '[' expression ']' { $$ = mktree(ARRAY_ACCESS, mkid($1), $3); }
    | ID '(' expression_list ')' { $$ = mktree(FUNCTION_CALL, mkid($1), $3); }
    | INUM { $$ = mkinum($1); }
    | RNUM { $$ = mkrnum($1); }
    | '(' expression ')' { $$ = $2; }
    | NOT factor
        { $$ = mktree(NOT, $2, NULL); }

    ;

%%

int main(){
    yyparse();
}