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
    READ = 263,
    WRITE = 264,
    PROCEDURE = 265,
    FUNCTION = 266,
    ARGS = 267,
    INTEGER = 268,
    REAL = 269,
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
    MOD = 298,
    NOT = 299,
    ID = 300,
    INUM = 301,
    RNUM = 302,
    COMMA = 303,
    SEMICOLON = 304,
    ARRAY_ACCESS = 305,
    FUNCTION_CALL = 306,
    PROCEDURE_CALL = 307,
    COMPOUND_STATEMENT = 308
  };
#endif
/* Tokens.  */
#define PROGRAM 258
#define BBEGIN 259
#define END 260
#define VAR 261
#define TYPE 262
#define READ 263
#define WRITE 264
#define PROCEDURE 265
#define FUNCTION 266
#define ARGS 267
#define INTEGER 268
#define REAL 269
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
#define MOD 298
#define NOT 299
#define ID 300
#define INUM 301
#define RNUM 302
#define COMMA 303
#define SEMICOLON 304
#define ARRAY_ACCESS 305
#define FUNCTION_CALL 306
#define PROCEDURE_CALL 307
#define COMPOUND_STATEMENT 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 28 "pc.y" /* yacc.c:1909  */

    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;
    node_t* nval;
    TreeList* treeListVal;

#line 172 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
