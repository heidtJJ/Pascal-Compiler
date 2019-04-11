/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "pc.y" /* yacc.c:339  */

    #include <stdio.h>
    #include <stdlib.h>
    #include <assert.h>
    #include <string.h>
    #include "node.h"
    #include "scope.h"
    #include "tree.h"
    #include "util.h"
    #include "y.tab.h"

    // DRAGON PARSER

    extern int yyerror(char*);
    extern int yylex();

    scope_t* top_scope;

    unsigned int NO_FUNCTION_RETURN = 0x1;
    unsigned int NO_SIDE_EFFECTS = 0x2;


#line 89 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 24 "pc.y" /* yacc.c:355  */

    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;
    node_t* nval;

#line 242 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 259 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   133

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   306

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,    53,     2,     2,    56,     2,    55,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    57,    54,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   100,   100,   104,   109,   100,   123,   127,   135,   170,
     180,   184,   191,   192,   196,   200,   208,   240,   239,   261,
     260,   283,   299,   307,   323,   346,   390,   394,   398,   402,
     409,   410,   414,   416,   420,   422,   424,   426,   440,   442,
     447,   465,   480,   492,   514,   524,   537,   538,   542,   546,
     550,   557,   559,   564,   578,   579,   580,   581,   582
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "BBEGIN", "END", "VAR",
  "TYPE", "PROCEDURE", "FUNCTION", "ARGS", "INTEGER", "REAL", "BOOLEAN",
  "NOT_SET", "ARRAY", "OF", "DOTDOT", "IF", "THEN", "ELSE", "WHILE", "FOR",
  "DO", "TO", "ASSIGNOP", "RELOP", "EQ", "NE", "LT", "LE", "GT", "GE",
  "ADDOP", "PLUS", "MINUS", "OR", "MULOP", "STAR", "SLASH", "AND", "NOT",
  "ID", "INUM", "RNUM", "COMMA", "SEMICOLON", "ARRAY_ACCESS",
  "FUNCTION_CALL", "PROCEDURE_CALL", "COMPOUND_STATEMENT", "ARGUMENT_TYPE",
  "'('", "')'", "';'", "'.'", "','", "':'", "'['", "']'", "$accept",
  "program", "$@1", "$@2", "$@3", "identifier_list", "declarations",
  "type", "standard_type", "subprogram_declarations",
  "subprogram_declaration", "subprogram_head", "$@4", "$@5", "arguments",
  "parameter_list", "compound_statement", "optional_statements",
  "statement_list", "statement", "matched", "unmatched", "variable",
  "procedure_statement", "expression_list", "expression",
  "simple_expression", "term", "factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,    40,    41,    59,    46,    44,    58,    91,    93
};
# endif

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -41

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -96,    14,    30,   -96,    18,   -96,    12,    21,     9,    13,
      21,    17,   -96,   -96,   -96,    66,    21,    23,    16,     1,
      33,    34,    29,   -96,    22,    39,    26,    26,    42,   -10,
     -96,    80,   -96,    32,   -96,   -96,    62,   -96,   -96,   -96,
     -96,    66,   -96,   -96,   -96,    31,    37,   -96,    38,    38,
     -23,   -96,   -96,    26,   -96,    74,    11,    57,   -96,    72,
      40,    71,    26,    26,   -96,     1,    26,    45,    45,    23,
      56,   -96,    57,   -96,    26,    47,     1,    26,    38,    38,
       3,    26,    48,    49,   -21,   -96,   -96,    21,    50,    46,
     -96,    89,    54,   -96,   -96,    90,    76,    57,   -96,    26,
     -96,    88,   -96,    26,   -96,    58,    60,   -96,    41,    73,
     -96,     1,    95,    26,   -96,    39,   -96,    63,    59,   -96,
     -96,     3,    96,    67,   -96,   104,   102,     1,    21,    41,
       3,   -96,   -96,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     3,     0,     0,     6,     0,
       0,     0,     7,     4,     9,    15,     0,     0,     0,    27,
       0,     0,     0,     9,     0,     0,     0,     0,     0,    42,
      35,     0,    26,    28,    30,    31,     0,    34,    19,    17,
      14,    15,     5,    12,    13,     0,     0,    10,     0,     0,
      40,    55,    56,     0,    54,     0,    46,    48,    51,     0,
      40,     0,     0,     0,    25,    27,     0,    22,    22,     0,
       0,     8,    49,    58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,     0,    29,    33,     0,     0,     0,
      16,     0,     0,    57,    38,    30,    47,    50,    52,     0,
      36,     0,    43,     0,    41,     0,     0,    20,     0,     0,
      53,     0,     0,     0,    45,     0,    21,     0,     0,    32,
      39,     0,     0,    23,    18,     0,     0,     0,     0,     0,
       0,    37,    24,    11
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   -96,   -96,   -96,    10,   100,    15,   -95,    83,
     -96,   -96,   -96,   -96,    61,    -3,   -14,    68,   -96,   -65,
     -72,    20,   -19,   -96,   -56,   -25,   -47,   -42,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     6,    14,   105,    15,    46,    47,    17,
      22,    23,    68,    67,    88,   106,    30,    31,    32,    33,
      34,    35,    54,    37,    82,    83,    56,    57,    58
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    55,    59,    24,    95,    19,    72,    19,   100,    61,
      73,    94,    78,   117,     3,   -40,    84,     9,    92,    26,
      12,    99,    27,    28,    27,    28,    18,    19,    75,    74,
      96,    20,    21,     4,   133,    63,    97,    77,   104,   119,
      98,    86,    62,    29,    78,    29,    36,   114,    63,   126,
      43,    44,    43,    44,    45,    90,   101,    36,   119,    48,
       5,    36,   131,     8,     7,    10,    11,    49,    50,    51,
      52,    13,    16,    25,   112,    38,    39,    42,    53,    49,
      50,    51,    52,    40,    60,    64,    65,    66,   122,    70,
      53,    71,    36,    76,    79,    80,    81,    87,    63,    91,
      93,   102,    36,   108,   107,   103,   109,   110,    36,    78,
     111,    36,   113,   116,   121,   115,   118,   124,   125,   127,
     129,   128,   130,    41,    69,   132,     0,     0,     0,    89,
     123,   120,     0,    85
};

static const yytype_int16 yycheck[] =
{
      19,    26,    27,    17,    76,     4,    48,     4,    80,    28,
      49,    76,    33,   108,     0,    25,    63,     7,    74,    18,
      10,    18,    21,    22,    21,    22,    16,     4,    53,    52,
      77,     8,     9,     3,   129,    58,    78,    26,    59,   111,
      79,    66,    52,    42,    33,    42,    65,   103,    58,   121,
      11,    12,    11,    12,    15,    69,    81,    76,   130,    33,
      42,    80,   127,    42,    52,    56,    53,    41,    42,    43,
      44,    54,     6,    57,    99,    42,    42,    55,    52,    41,
      42,    43,    44,    54,    42,     5,    54,    25,   113,    58,
      52,    54,   111,    19,    37,    23,    25,    52,    58,    43,
      53,    53,   121,    57,    54,    56,    17,    53,   127,    33,
      20,   130,    24,    53,    19,    57,    43,    54,    59,    23,
      16,    54,    20,    23,    41,   128,    -1,    -1,    -1,    68,
     115,   111,    -1,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    61,    62,     0,     3,    42,    63,    52,    42,    65,
      56,    53,    65,    54,    64,    66,     6,    69,    65,     4,
       8,     9,    70,    71,    76,    57,    18,    21,    22,    42,
      76,    77,    78,    79,    80,    81,    82,    83,    42,    42,
      54,    66,    55,    11,    12,    15,    67,    68,    33,    41,
      42,    43,    44,    52,    82,    85,    86,    87,    88,    85,
      42,    82,    52,    58,     5,    54,    25,    73,    72,    69,
      58,    54,    87,    88,    52,    85,    19,    26,    33,    37,
      23,    25,    84,    85,    86,    77,    85,    52,    74,    74,
      76,    43,    84,    53,    79,    80,    86,    87,    88,    18,
      80,    85,    53,    56,    59,    65,    75,    54,    57,    17,
      53,    20,    85,    24,    84,    57,    53,    68,    43,    80,
      81,    19,    85,    67,    54,    59,    80,    23,    54,    16,
      20,    79,    75,    68
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    60,    62,    63,    64,    61,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    72,    71,    73,
      71,    74,    74,    75,    75,    76,    77,    77,    78,    78,
      79,    79,    80,    80,    80,    80,    80,    80,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      86,    87,    87,    88,    88,    88,    88,    88,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,    13,     1,     3,     6,     0,
       1,     8,     1,     1,     3,     0,     4,     0,     7,     0,
       5,     3,     0,     3,     5,     3,     1,     0,     1,     3,
       1,     1,     6,     3,     1,     1,     4,     8,     4,     6,
       1,     4,     1,     4,     1,     3,     1,     3,     1,     2,
       3,     1,     3,     4,     1,     1,     1,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 100 "pc.y" /* yacc.c:1646  */
    {
        fprintf(stderr, "BEGINING OF PROGRAM\n"); 
    }
#line 1433 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 104 "pc.y" /* yacc.c:1646  */
    {
        node_t* programNode = insertProcedureNode(NULL, (yyvsp[0].sval), NULL);
        top_scope = push_scope(NULL, programNode);
    }
#line 1442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 109 "pc.y" /* yacc.c:1646  */
    {
        top_scope->scopeOwner->data.procedureInfo.arguments = (yyvsp[-2].nval);
    }
#line 1450 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 116 "pc.y" /* yacc.c:1646  */
    { 
        free_scope(top_scope);
        fprintf(stderr, "END OF PROGRAM\n"); 
    }
#line 1459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 124 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.nval) = insertVarNode(NULL, NOT_SET, (yyvsp[0].sval));
    }
#line 1467 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 128 "pc.y" /* yacc.c:1646  */
    { 
        node_t* newTop = insertVarNode((yyvsp[0].nval), NOT_SET, (yyvsp[-2].sval)); 
        (yyval.nval) = newTop;
    }
#line 1476 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 136 "pc.y" /* yacc.c:1646  */
    {
            node_t* idListHead = (yyvsp[-3].nval);
            node_t* curId = idListHead;
            node_t* typeNode = (yyvsp[-1].nval);

            fprintf(stderr, "Before identifier_list print22222222222222222222\n");
            print_list(idListHead);
            
            while(curId != NULL){

                /* Check if variable name is redeclared in the current scope */
                if(scope_search(top_scope, curId->name) != NULL){
                    yyerror("Variable is redeclared in the current scope in identifier_list\n");
                }
                if(top_scope->scopeOwner != NULL){
                    /* Check if variable is being declared has same name as the current function. */
                    if(strcmp(top_scope->scopeOwner->name, curId->name) == 0){
                        yyerror("Variable is redeclared with same name as owning subprogram name in identifier_list\n");
                    }
                }

                char* name = curId->name;
                copyNode(typeNode, curId);/* Does not affect *next attribute */
                curId->name = name;
                node_t* copy = insertVarNode(NULL, NOT_SET, name);
                scope_insert_node(top_scope, copy); 
                copyNode(curId, copy);
                fprintf(stderr, "111111111111111111111111 Name %s\n", curId->name);
                curId = curId->next;
            }
            fprintf(stderr, "Scope print\n");
            scope_print(top_scope);
            free_list(typeNode);
        }
#line 1515 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 181 "pc.y" /* yacc.c:1646  */
    {
        (yyval.nval) = insertVarNode(NULL, (yyvsp[0].ival), NULL);
    }
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 185 "pc.y" /* yacc.c:1646  */
    {
        (yyval.nval) = insertArrayNode(NULL, (yyvsp[0].ival), NULL, (yyvsp[-5].ival), (yyvsp[-3].ival));
    }
#line 1531 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 191 "pc.y" /* yacc.c:1646  */
    { (yyval.ival) = INTEGER; }
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 192 "pc.y" /* yacc.c:1646  */
    { (yyval.ival) = REAL; }
#line 1543 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 197 "pc.y" /* yacc.c:1646  */
    {
        (yyval.ival) = (yyvsp[-2].ival) || (yyvsp[-1].ival);
    }
#line 1551 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 200 "pc.y" /* yacc.c:1646  */
    { (yyval.ival) = 0; }
#line 1557 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 209 "pc.y" /* yacc.c:1646  */
    {
        tree_t* cpmdStatement = (yyvsp[0].tval);
        unsigned int subContainsSideEffects = (yyvsp[-1].ival);
        if(cpmdStatement == NULL){
            (yyval.ival) = subContainsSideEffects;
        }
        else{
            /* compound_statement already checked for side effects */
            assert(cpmdStatement->type == COMPOUND_STATEMENT);

            node_t* subpgmHeadNode = (yyvsp[-3].nval);
            int cpndStmtSideEffects = cpmdStatement->rightChild->attribute.ival;
            fprintf(stderr, "\n\ncpndStmtSideEffects %d  subContainsSideEffects %d\n\n", cpndStmtSideEffects,subContainsSideEffects);
            
            if(subpgmHeadNode->nodeType == FUNCTION && subContainsSideEffects){
                /* No side effects allowed in compound_statement or subprogram_declarations. */
                fprintf(stderr, "In function name %s\n", subpgmHeadNode->name);
                yyerror("subprogram_declarations contain side effects in subprogram_declaration\n");
            }
            subContainsSideEffects = subContainsSideEffects || cpndStmtSideEffects;

            (yyval.ival) = subContainsSideEffects; 
            
            top_scope = pop_scope(top_scope); 
            tree_free(cpmdStatement);
        }
    }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 240 "pc.y" /* yacc.c:1646  */
    {   
            if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
                /* Function with same name is redeclared in the same scope */
                yyerror("Function redeclared in the same scope\n");
            }
            node_t* functionNode = scope_insert_function(top_scope, 0, (yyvsp[0].sval), NULL);
            top_scope = push_scope(top_scope, functionNode);  
        }
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 249 "pc.y" /* yacc.c:1646  */
    {
            /* Set the return type and argument types of the node */
            node_t* functionNode = top_scope->scopeOwner;

            if(functionNode->nodeType != FUNCTION){
                yyerror("FUNCTION error in subprogram_head\n");
            }
            functionNode->data.functionInfo.returnType = (yyvsp[-1].ival);
            functionNode->data.functionInfo.arguments = (yyvsp[-3].nval);
            (yyval.nval) = functionNode;
        }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 261 "pc.y" /* yacc.c:1646  */
    { 
            if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
                /* Procedure with same name is redeclared in the same scope */
                yyerror("Procedure redeclared in the same scope\n");
            }
            node_t* procedureNode = scope_insert_procedure(top_scope, (yyvsp[0].sval), NULL);
            top_scope = push_scope(top_scope, procedureNode);  
        }
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 270 "pc.y" /* yacc.c:1646  */
    {
            /* Set the return type and argument types of the node */
            node_t* procedureNode = top_scope->scopeOwner;;

            if(procedureNode->nodeType != PROCEDURE){
                yyerror("PROCEDURE error in subprogram_head\n");
            }
            procedureNode->data.procedureInfo.arguments = (yyvsp[-1].nval);
            (yyval.nval) = procedureNode;
        }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 284 "pc.y" /* yacc.c:1646  */
    { 
            node_t* cur = (yyvsp[-1].nval);
            fprintf(stderr, "\nFUFUFUSADJDSFSADJJDASJFDSAJJFSADAFD111\n");
            print_list(cur);

            while(cur != NULL){
                node_t* copy = insertVarNode(NULL, NOT_SET, cur->name);
                fprintf(stderr, "fasd\n");
                copyNode(cur, copy);
                scope_insert_node(top_scope, copy); 
                cur = cur->next;
            }
            (yyval.nval) = (yyvsp[-1].nval);
            print_list((yyvsp[-1].nval));
        }
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 299 "pc.y" /* yacc.c:1646  */
    { (yyval.nval) = NULL; }
#line 1672 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 308 "pc.y" /* yacc.c:1646  */
    {
        node_t* idList = (yyvsp[-2].nval);
        node_t* cur = idList;
        node_t* typeNode = (yyvsp[0].nval);
        while(cur != NULL){
            char* name = cur->name;
            copyNode(typeNode, cur);
            cur->name = name;
            cur = cur->next;
        }
        free_list(typeNode);
        (yyval.nval) = idList;
        print_list(idList);

    }
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 324 "pc.y" /* yacc.c:1646  */
    {
        node_t* idList = (yyvsp[-4].nval);
        node_t* cur = idList;
        node_t* prev = NULL;

        node_t* typeNode = (yyvsp[-2].nval);

        while(cur != NULL){
            char* name = cur->name;
            copyNode(typeNode, cur);
            cur->name = name;
            prev = cur;
            cur = cur->next;
        }
        prev->next = (yyvsp[0].nval);
        free_list(typeNode);
        (yyval.nval) = idList;
        print_list(idList);
    }
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 347 "pc.y" /* yacc.c:1646  */
    { 
            if(top_scope == NULL){
                yyerror("Invalid scope in subprogram_declaration\n");
            }
            node_t* scopeOwner = top_scope->scopeOwner;
            tree_t* statementTree = (yyvsp[-1].tval);
            int flags = NO_SIDE_EFFECTS;
            if(scopeOwner->nodeType == FUNCTION){
                flags = flags | NO_FUNCTION_RETURN;
            }
            
            fprintf(stderr, "\n\nBefore validateStatement flags=%d\n", flags);
            validateStatement(top_scope, statementTree, &flags);
            fprintf(stderr, "After validateStatement flags=%d\n", flags);
            

            int containsSideEffects = hasSideEffects(flags);
            fprintf(stderr, "\n\n\n HAS %d SIDE in %s\n", containsSideEffects,scopeOwner->name);

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

            fprintf(stderr, "\nBEGIN TREE PRINT\n\n");
            tree_print(statementTree);
            fprintf(stderr, "\nEND TREE PRINT\n\n");
            
            
            (yyval.tval) = mktree(COMPOUND_STATEMENT, statementTree, mkinum(containsSideEffects));
            fprintf(stderr, "RETURNING SIDE EFFECT %d %d\n\n", containsSideEffects, flags);
        }
#line 1761 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 391 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = (yyvsp[0].tval); 
    }
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 394 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL; }
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 399 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = (yyvsp[0].tval); 
    }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 403 "pc.y" /* yacc.c:1646  */
    {
        (yyval.tval) = mktree(SEMICOLON, (yyvsp[-2].tval), (yyvsp[0].tval)); 
    }
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 409 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 410 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 415 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-4].tval), mktree(THEN, (yyvsp[-2].tval), (yyvsp[0].tval))); }
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 417 "pc.y" /* yacc.c:1646  */
    {  
            (yyval.tval) = mktree(ASSIGNOP, (yyvsp[-2].tval), (yyvsp[0].tval));
        }
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 421 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 423 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 425 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(WHILE, (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 427 "pc.y" /* yacc.c:1646  */
    { 
            int variableType = getExpressionType(top_scope, (yyvsp[-6].tval));
            int expression1 = getExpressionType(top_scope, (yyvsp[-4].tval));
            int expression2 = getExpressionType(top_scope, (yyvsp[-2].tval));
            if(variableType != expression1 || expression1 != expression2){
                yyerror("For loop assignment types do not match.");
            }
            (yyval.tval) = mktree(FOR, mktree(ASSIGNOP, (yyvsp[-6].tval), (yyvsp[-4].tval)), mktree(TO, (yyvsp[-2].tval), mktree(DO, (yyvsp[0].tval), NULL))); 

        }
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 441 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-2].tval), mktree(THEN, (yyvsp[0].tval), NULL)); }
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 443 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-4].tval), mktree(THEN, (yyvsp[-2].tval), (yyvsp[0].tval))); }
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 448 "pc.y" /* yacc.c:1646  */
    {
        node_t* varNode = scope_search_all(top_scope, (yyvsp[0].sval));
        if(!varNode){
            fprintf(stderr, "\n%s\n", (yyvsp[0].sval));
            yyerror("Cannot find variable ID in variable\n");
        }
        if(strcmp((yyvsp[0].sval), top_scope->scopeOwner->name)){
            if(varNode->nodeType != VAR){
                fprintf(stderr, "\n%d\n", varNode->nodeType);
                yyerror("Accesed identifier is not a variable\n");
            }
            if(varNode->data.varInfo.isArray == IS_ARRAY){
                yyerror("Accesed variable is an array in variable\n");
            }
        }
        (yyval.tval) = mkid(varNode); 
    }
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 466 "pc.y" /* yacc.c:1646  */
    { 
        node_t* arrayNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(!arrayNode || arrayNode->nodeType != VAR){
            yyerror("Cannot find array variable ID in variable\n");
        }
        if(arrayNode->data.varInfo.isArray == NOT_ARRAY){
            fprintf(stderr, "%s\n", arrayNode->name);
            yyerror("Accesed variable is not an array in variable\n");
        }
        (yyval.tval) = mktree(ARRAY_ACCESS, mkid(arrayNode), (yyvsp[-1].tval));
    }
#line 1900 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 481 "pc.y" /* yacc.c:1646  */
    { 
        node_t* procedureNode = scope_search_all(top_scope, (yyvsp[0].sval));
        if(procedureNode == NULL){
            fprintf(stderr, "ID is %s\n", (yyvsp[0].sval));
            yyerror("Cannot find procedure ID match 1 in procedure_statement\n");
        }
        if(procedureNode->nodeType != PROCEDURE){
            yyerror("Cannot find procedure ID match 2 in procedure_statement\n");
        }
        (yyval.tval) = mktree(PROCEDURE_CALL, mkid(procedureNode), NULL); 
    }
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 493 "pc.y" /* yacc.c:1646  */
    { 
        node_t* procedureNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(procedureNode == NULL){
            fprintf(stderr, "ID is %s\n", (yyvsp[-3].sval));
            yyerror("Cannot find procedure ID match 3 in procedure_statement\n");
        }
        if(procedureNode->nodeType != PROCEDURE){
            yyerror("Cannot find procedure ID match 4 in procedure_statement\n");
        }

        // Validate input types
        node_t* expectedArgs = procedureNode->data.procedureInfo.arguments;
        node_t* actualArgs = (yyvsp[-1].nval);

        validateArguments(expectedArgs, actualArgs);

        (yyval.tval) = mktree(PROCEDURE_CALL, mkid(procedureNode), mkargs((yyvsp[-1].nval))); 
    }
#line 1939 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 515 "pc.y" /* yacc.c:1646  */
    { 
        int expressionType = getExpressionType(top_scope, (yyvsp[0].tval));
        
        tree_free((yyvsp[0].tval));/* If this line is deleted, seg fault! Why?? */
        
        (yyval.nval) = insertVarNode(NULL, expressionType, NULL); 

        /*fprintf(stderr, "expressionType = %d  expression location = %d $$ = %d\n", expressionType, $1, $$);*/
    }
#line 1953 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 525 "pc.y" /* yacc.c:1646  */
    {
        int expressionType = getExpressionType(top_scope, (yyvsp[-2].tval));
        tree_free((yyvsp[-2].tval));/* If this line is deleted, seg fault! Why?? */
        
        /*fprintf(stderr, "expressionType = %d expression location = %d  expression_list location = %d\n", expressionType, $1, $3);*/
        
        (yyval.nval) = insertVarNode((yyvsp[0].nval), expressionType, NULL); 
        /*fprintf(stderr, "AFTER insertVarNode %d\n", $$);*/
    }
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 537 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 538 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkop(RELOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 543 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = (yyvsp[0].tval); 
    }
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 547 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = mkop(ADDOP, (yyvsp[-1].opval), (yyvsp[0].tval), NULL); 
    }
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 551 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = mkop(ADDOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); 
    }
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 558 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 560 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkop(MULOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 565 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(matchNode == NULL || matchNode->nodeType != FUNCTION){
            yyerror("Cannot find function ID match in factor\n");
        }

        node_t* expectedArgs = matchNode->data.functionInfo.arguments;
        node_t* actualArgs = (yyvsp[-1].nval);
        
        validateArguments(expectedArgs, actualArgs);

        (yyval.tval) = mktree(FUNCTION_CALL, mkid(matchNode), mkargs((yyvsp[-1].nval))); 
    }
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 579 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkinum((yyvsp[0].ival)); }
#line 2039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 580 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkrnum((yyvsp[0].rval)); }
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 581 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[-1].tval); }
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 582 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(NOT, (yyvsp[0].tval), NULL); }
#line 2057 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2061 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 585 "pc.y" /* yacc.c:1906  */


int main(){
    yyparse();
}
