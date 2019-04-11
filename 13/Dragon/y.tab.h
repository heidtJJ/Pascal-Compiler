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
    ARGS = 265,
    INTEGER = 266,
    REAL = 267,
    BOOLEAN = 268,
    NOT_SET = 269,
    ARRAY = 270,
    OF = 271,
    DOTDOT = 272,
    IF = 273,
    THEN = 274,
    ELSE = 275,
    WHILE = 276,
    FOR = 277,
    DO = 278,
    TO = 279,
    ASSIGNOP = 280,
    RELOP = 281,
    EQ = 282,
    NE = 283,
    LT = 284,
    LE = 285,
    GT = 286,
    GE = 287,
    ADDOP = 288,
    PLUS = 289,
    MINUS = 290,
    OR = 291,
    MULOP = 292,
    STAR = 293,
    SLASH = 294,
    AND = 295,
    NOT = 296,
    ID = 297,
    INUM = 298,
    RNUM = 299,
    COMMA = 300,
    SEMICOLON = 301,
    ARRAY_ACCESS = 302,
    FUNCTION_CALL = 303,
    PROCEDURE_CALL = 304,
    COMPOUND_STATEMENT = 305,
    ARGUMENT_TYPE = 306
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
#define ARGS 265
#define INTEGER 266
#define REAL 267
#define BOOLEAN 268
#define NOT_SET 269
#define ARRAY 270
#define OF 271
#define DOTDOT 272
#define IF 273
#define THEN 274
#define ELSE 275
#define WHILE 276
#define FOR 277
#define DO 278
#define TO 279
#define ASSIGNOP 280
#define RELOP 281
#define EQ 282
#define NE 283
#define LT 284
#define LE 285
#define GT 286
#define GE 287
#define ADDOP 288
#define PLUS 289
#define MINUS 290
#define OR 291
#define MULOP 292
#define STAR 293
#define SLASH 294
#define AND 295
#define NOT 296
#define ID 297
#define INUM 298
#define RNUM 299
#define COMMA 300
#define SEMICOLON 301
#define ARRAY_ACCESS 302
#define FUNCTION_CALL 303
#define PROCEDURE_CALL 304
#define COMPOUND_STATEMENT 305
#define ARGUMENT_TYPE 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "pc.y" /* yacc.c:1909  */

    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;
    node_t* nval;

#line 167 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
