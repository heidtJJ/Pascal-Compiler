%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "treeList.h"
#include "y.tab.h"

// Scanner File
// page 746 apendix A type it in
%}
whitespace  [ \t]+
number      [0-9]+
ident       [A-Za-z][A-Za-z0-9]*

%%

{whitespace}    ;
	
"(*".*"*)" {}
"{".*"}" {}

"read"        { fprintf(stderr, "[READ]"); return READ; }
"write"        { fprintf(stderr, "[WRITE]"); return WRITE; }
"program"        { fprintf(stderr, "[PROGRAM]"); return PROGRAM; }
"var"           { fprintf(stderr, "[VAR]"); return VAR; }
"array"         { fprintf(stderr, "[ARRAY]"); return ARRAY; }
"of"            { fprintf(stderr, "[OF]"); return OF; }
"procedure"     { fprintf(stderr, "[PROCEDURE]"); return PROCEDURE; }
"function"      { fprintf(stderr, "[FUNCTION]"); return FUNCTION; }
"begin"         { fprintf(stderr, "[BBEGIN]"); return BBEGIN; }
"end"           { fprintf(stderr, "[END]"); return END; }
"integer"       { fprintf(stderr, "[INTEGER]"); return INTEGER; }
"real"          { fprintf(stderr, "[REAL]"); return REAL; }
"if"            { fprintf(stderr, "[IF]"); return IF; }
"then"          { fprintf(stderr, "[THEN]"); return THEN; }
"else"          { fprintf(stderr, "[ELSE]"); return ELSE; }
"while"         { fprintf(stderr, "[WHILE]"); return WHILE; }
"do"            { fprintf(stderr, "[DO]"); return DO; }
"for"            { fprintf(stderr, "[FOR]"); return FOR; }
"to"            { fprintf(stderr, "[TO]"); return TO; }

".."    { fprintf(stderr, "[DOTDOT]"); return DOTDOT; }

":="    { fprintf(stderr, "[ASSIGNOP]"); return ASSIGNOP; }

"="    { fprintf(stderr, "[RELOP:%d]", yylval.opval = EQ); return RELOP; }
"<>"    { fprintf(stderr, "[RELOP:%d]", yylval.opval = NE); return RELOP; }
"<"    { fprintf(stderr, "[RELOP:%d]", yylval.opval = LT); return RELOP; }
"<="    { fprintf(stderr, "[RELOP:%d]", yylval.opval = LE); return RELOP; }
">"    { fprintf(stderr, "[RELOP:%d]", yylval.opval = GT); return RELOP; }
">="    { fprintf(stderr, "[RELOP:%d]", yylval.opval = GE); return RELOP; }

"+"    { fprintf(stderr, "[ADDOP:%d]", yylval.opval = PLUS); return ADDOP; }
"-"    { fprintf(stderr, "[ADDOP:%d]", yylval.opval = MINUS); return ADDOP; }
"or"    { fprintf(stderr, "[ADDOP:%d]", yylval.opval = OR); return ADDOP; }

"*"    { fprintf(stderr, "[MULOP:%d]", yylval.opval = STAR); return MULOP; }
"/"    { fprintf(stderr, "[MULOP:%d]", yylval.opval = SLASH); return MULOP; }
"and"    { fprintf(stderr, "[MULOP:%d]", yylval.opval = AND); return MULOP; }

"not"    { fprintf(stderr, "[NOT:%d]", NOT); return NOT; }

{number}    { fprintf(stderr, "[INUM:%d]", yylval.ival = atoi(yytext)); return INUM; }
{number}"."{number} { fprintf(stderr, "[RNUM:%f]", yylval.rval = atof(yytext)); return RNUM; }
{ident}     { fprintf(stderr, "[ID:%s]", yylval.sval = strdup(yytext)); return ID; }

";"     { fprintf(stderr, "{%c}", yytext[0]); return yytext[0]; }
\n      { fprintf(stderr, "\n"); }
.       { fprintf(stderr, "{%c}\n", yytext[0]); return yytext[0]; }

%%

int yyerror(char* message){
    fprintf(stderr, "Error: %s\n", message);
    exit(1);
}