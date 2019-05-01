%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "treeList.h"
#include "y.tab.h"

// Scanner File
int yyerror(char* message);

short commenting = 0;
unsigned int currentLineNumber = 1;

int printIntToken(char* token, int yval, int returnVal){
    fprintf(stderr, "[%s: %d]", token, yval); 
    return returnVal; 
}

int printFloatToken(char* token, float yval, int returnVal){
    fprintf(stderr, "[%s: %f]", token, yval); 
    return returnVal; 
}

int printIDToken(char* token, char* yval, int returnVal){
    fprintf(stderr, "[%s: %s]", token, yval); 
    return returnVal; 
}

int printCharToken(char yval){
    fprintf(stderr, "{%c}", yval); 
    return yval; 
}


%}
whitespace  [ \t]+
number      [0-9]+
ident       [A-Za-z][A-Za-z0-9]*

%%

{whitespace}    ;

"(*" { commenting = 1; }
"*)" { 
        if(commenting){ 
            commenting = 0;
        } else {
            yyerror("Invalid end-comment.");
        }
    }

"{" { commenting = 1; }
"}" { 
        if(commenting){ 
            commenting = 0;
        } else {
            yyerror("Invalid end-comment.");
        }
    }

"read"          { if(!commenting){ return printIntToken("READ", 0, READ); } }
"write"         { if(!commenting){ return printIntToken("WRITE", 0, WRITE); } }
"program"       { if(!commenting){ return printIntToken("PROGRAM", 0, PROGRAM); } }
"var"           { if(!commenting){ return printIntToken("VAR", 0, VAR); } }
"array"         { if(!commenting){ return printIntToken("ARRAY", 0, ARRAY); } }
"of"            { if(!commenting){ return printIntToken("OF", 0, OF); } }
"procedure"     { if(!commenting){ return printIntToken("PROCEDURE", 0, PROCEDURE); } }
"function"      { if(!commenting){ return printIntToken("FUNCTION", 0, FUNCTION); } }
"begin"         { if(!commenting){ return printIntToken("BBEGIN", 0, BBEGIN); } }
"end"           { if(!commenting){ return printIntToken("END", 0, END); } }
"integer"       { if(!commenting){ return printIntToken("INTEGER", 0, INTEGER); } }
"real"          { if(!commenting){ return printIntToken("REAL", 0, REAL); } }
"if"            { if(!commenting){ return printIntToken("IF", 0, IF); } }
"then"          { if(!commenting){ return printIntToken("THEN", 0, THEN); } }
"else"          { if(!commenting){ return printIntToken("ELSE", 0, ELSE); } }
"while"         { if(!commenting){ return printIntToken("WHILE", 0, WHILE); } }
"do"            { if(!commenting){ return printIntToken("DO", 0, DO); } }
"for"           { if(!commenting){ return printIntToken("FOR", 0, FOR); } }
"to"            { if(!commenting){ return printIntToken("TO", 0, TO); } }

".."            { if(!commenting){ return printIntToken("DOTDOT", 0, DOTDOT); } }

":="            { if(!commenting){ return printIntToken("ASSIGNOP", 0, ASSIGNOP); } }

"="             { if(!commenting){ return printIntToken("RELOP", yylval.opval = EQ, RELOP); } }
"<>"            { if(!commenting){ return printIntToken("RELOP", yylval.opval = NE, RELOP); } }
"<"             { if(!commenting){ return printIntToken("RELOP", yylval.opval = LT, RELOP); } }
"<="            { if(!commenting){ return printIntToken("RELOP", yylval.opval = LE, RELOP); } }
">"             { if(!commenting){ return printIntToken("RELOP", yylval.opval = GT, RELOP); } }
">="            { if(!commenting){ return printIntToken("RELOP", yylval.opval = GE, RELOP); } }

"+"             { if(!commenting){ return printIntToken("ADDOP", yylval.opval = PLUS, ADDOP); } }
"-"             { if(!commenting){ return printIntToken("ADDOP", yylval.opval = MINUS, ADDOP); } }
"or"            { if(!commenting){ return printIntToken("ADDOP", yylval.opval = OR, ADDOP); } }

"*"             { if(!commenting){ return printIntToken("MULOP", yylval.opval = STAR, MULOP); } }
"div"           { if(!commenting){ return printIntToken("MULOP", yylval.opval = SLASH, MULOP); } }
"/"             { if(!commenting){ return printIntToken("MULOP", yylval.opval = SLASH, MULOP); } }
"mod"           { if(!commenting){ return printIntToken("MULOP", yylval.opval = MOD, MULOP); } }
"%"             { if(!commenting){ return printIntToken("MULOP", yylval.opval = MOD, MULOP); } }
"and"           { if(!commenting){ return printIntToken("MULOP", yylval.opval = AND, MULOP); } }

"not"           { if(!commenting){ return printIntToken("NOT", 0, NOT); } }

{number}        { if(!commenting){ return printIntToken("INUM", yylval.ival = atoi(yytext), INUM); } }
{number}"."{number} { if(!commenting){ return printFloatToken("RNUM", yylval.rval = atof(yytext), RNUM);  } }
{ident}         { if(!commenting){ return printIDToken("ID",  yylval.sval = strdup(yytext), ID); } }

";"             { if(!commenting){ return printCharToken(yytext[0]); } }
\n              { currentLineNumber++; fprintf(stderr, "\n"); }
.               { if(!commenting){ return printCharToken(yytext[0]); } }

%%

int yyerror(char* message){
    fprintf(stderr, "\n\nError: %s\n", message);
    fprintf(stderr, "Line number: %d\n", currentLineNumber);
    exit(1);
}