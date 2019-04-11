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
    INTEGER_ARRAY = 268,
    REAL_ARRAY = 269,
    BOOLEAN = 270,
    NOT_SET = 271,
    ARRAY = 272,
    OF = 273,
    DOTDOT = 274,
    IF = 275,
    THEN = 276,
    ELSE = 277,
    WHILE = 278,
    FOR = 279,
    DO = 280,
    TO = 281,
    ASSIGNOP = 282,
    RELOP = 283,
    EQ = 284,
    NE = 285,
    LT = 286,
    LE = 287,
    GT = 288,
    GE = 289,
    ADDOP = 290,
    PLUS = 291,
    MINUS = 292,
    OR = 293,
    MULOP = 294,
    STAR = 295,
    SLASH = 296,
    AND = 297,
    NOT = 298,
    ID = 299,
    INUM = 300,
    RNUM = 301,
    COMMA = 302,
    SEMICOLON = 303,
    ARRAY_ACCESS = 304,
    FUNCTION_CALL = 305,
    PROCEDURE_CALL = 306,
    ENTRY_TYPE = 307
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
#define INTEGER_ARRAY 268
#define REAL_ARRAY 269
#define BOOLEAN 270
#define NOT_SET 271
#define ARRAY 272
#define OF 273
#define DOTDOT 274
#define IF 275
#define THEN 276
#define ELSE 277
#define WHILE 278
#define FOR 279
#define DO 280
#define TO 281
#define ASSIGNOP 282
#define RELOP 283
#define EQ 284
#define NE 285
#define LT 286
#define LE 287
#define GT 288
#define GE 289
#define ADDOP 290
#define PLUS 291
#define MINUS 292
#define OR 293
#define MULOP 294
#define STAR 295
#define SLASH 296
#define AND 297
#define NOT 298
#define ID 299
#define INUM 300
#define RNUM 301
#define COMMA 302
#define SEMICOLON 303
#define ARRAY_ACCESS 304
#define FUNCTION_CALL 305
#define PROCEDURE_CALL 306
#define ENTRY_TYPE 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 19 "pc.y" /* yacc.c:1909  */

    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;
    node_t* nval;

#line 169 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
