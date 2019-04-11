/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROGRAM = 258,
    BBEGIN = 259,
    END = 260,
    VAR = 261,
    TYPE = 262,
    PROCEDURE = 263,
    FUNCTION = 264,
    INTEGER = 265,
    REAL = 266,
    ARRAY = 267,
    OF = 268,
    DOTDOT = 269,
    IF = 270,
    THEN = 271,
    ELSE = 272,
    WHILE = 273,
    FOR = 274,
    DO = 275,
    TO = 276,
    ASSIGNOP = 277,
    RELOP = 278,
    EQ = 279,
    NE = 280,
    LT = 281,
    LE = 282,
    GT = 283,
    GE = 284,
    ADDOP = 285,
    PLUS = 286,
    MINUS = 287,
    OR = 288,
    MULOP = 289,
    STAR = 290,
    SLASH = 291,
    AND = 292,
    NOT = 293,
    ID = 294,
    INUM = 295,
    RNUM = 296,
    COMMA = 297,
    SEMICOLON = 298,
    ARRAY_ACCESS = 299,
    FUNCTION_CALL = 300,
    PROCEDURE_CALL = 301,
    ENTRY_NAME = 302,
    ENTRY_TYPE = 303
  };
#endif
/* Tokens.  */
#define PROGRAM 258
#define BBEGIN 259
#define END 260
#define VAR 261
#define TYPE 262
#define PROCEDURE 263
#define FUNCTION 264
#define INTEGER 265
#define REAL 266
#define ARRAY 267
#define OF 268
#define DOTDOT 269
#define IF 270
#define THEN 271
#define ELSE 272
#define WHILE 273
#define FOR 274
#define DO 275
#define TO 276
#define ASSIGNOP 277
#define RELOP 278
#define EQ 279
#define NE 280
#define LT 281
#define LE 282
#define GT 283
#define GE 284
#define ADDOP 285
#define PLUS 286
#define MINUS 287
#define OR 288
#define MULOP 289
#define STAR 290
#define SLASH 291
#define AND 292
#define NOT 293
#define ID 294
#define INUM 295
#define RNUM 296
#define COMMA 297
#define SEMICOLON 298
#define ARRAY_ACCESS 299
#define FUNCTION_CALL 300
#define PROCEDURE_CALL 301
#define ENTRY_NAME 302
#define ENTRY_TYPE 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "pc.y" /* yacc.c:1909  */

    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;
    node_t* nval;

#line 161 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
