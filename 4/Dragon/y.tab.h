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
    PROCEDURE = 262,
    FUNCTION = 263,
    INTEGER = 264,
    REAL = 265,
    ARRAY = 266,
    OF = 267,
    DOTDOT = 268,
    IF = 269,
    THEN = 270,
    ELSE = 271,
    WHILE = 272,
    DO = 273,
    ASSIGNOP = 274,
    RELOP = 275,
    EQ = 276,
    NE = 277,
    LT = 278,
    LE = 279,
    GT = 280,
    GE = 281,
    ADDOP = 282,
    PLUS = 283,
    MINUS = 284,
    OR = 285,
    MULOP = 286,
    STAR = 287,
    SLASH = 288,
    AND = 289,
    NOT = 290,
    ID = 291,
    INUM = 292,
    RNUM = 293,
    COMMA = 294,
    SEMICOLON = 295,
    ARRAY_ACCESS = 296,
    FUNCTION_CALL = 297,
    PROCEDURE_CALL = 298
  };
#endif
/* Tokens.  */
#define PROGRAM 258
#define BBEGIN 259
#define END 260
#define VAR 261
#define PROCEDURE 262
#define FUNCTION 263
#define INTEGER 264
#define REAL 265
#define ARRAY 266
#define OF 267
#define DOTDOT 268
#define IF 269
#define THEN 270
#define ELSE 271
#define WHILE 272
#define DO 273
#define ASSIGNOP 274
#define RELOP 275
#define EQ 276
#define NE 277
#define LT 278
#define LE 279
#define GT 280
#define GE 281
#define ADDOP 282
#define PLUS 283
#define MINUS 284
#define OR 285
#define MULOP 286
#define STAR 287
#define SLASH 288
#define AND 289
#define NOT 290
#define ID 291
#define INUM 292
#define RNUM 293
#define COMMA 294
#define SEMICOLON 295
#define ARRAY_ACCESS 296
#define FUNCTION_CALL 297
#define PROCEDURE_CALL 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "pc.y" /* yacc.c:1909  */

    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;

#line 150 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
