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
    FOR = 273,
    DO = 274,
    TO = 275,
    ASSIGNOP = 276,
    RELOP = 277,
    EQ = 278,
    NE = 279,
    LT = 280,
    LE = 281,
    GT = 282,
    GE = 283,
    ADDOP = 284,
    PLUS = 285,
    MINUS = 286,
    OR = 287,
    MULOP = 288,
    STAR = 289,
    SLASH = 290,
    AND = 291,
    NOT = 292,
    ID = 293,
    INUM = 294,
    RNUM = 295,
    COMMA = 296,
    SEMICOLON = 297,
    ARRAY_ACCESS = 298,
    FUNCTION_CALL = 299,
    PROCEDURE_CALL = 300,
    ENTRY_NAME = 301,
    ENTRY_TYPE = 302
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
#define FOR 273
#define DO 274
#define TO 275
#define ASSIGNOP 276
#define RELOP 277
#define EQ 278
#define NE 279
#define LT 280
#define LE 281
#define GT 282
#define GE 283
#define ADDOP 284
#define PLUS 285
#define MINUS 286
#define OR 287
#define MULOP 288
#define STAR 289
#define SLASH 290
#define AND 291
#define NOT 292
#define ID 293
#define INUM 294
#define RNUM 295
#define COMMA 296
#define SEMICOLON 297
#define ARRAY_ACCESS 298
#define FUNCTION_CALL 299
#define PROCEDURE_CALL 300
#define ENTRY_NAME 301
#define ENTRY_TYPE 302

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

#line 158 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
