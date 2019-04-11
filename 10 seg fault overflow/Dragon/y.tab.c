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
    #include "node.h"
    #include "scope.h"
    #include "tree.h"
    #include "util.h"
    #include "y.tab.h"

    // DRAGON PARSER

    extern int yyerror(char*);
    extern int yylex();

    scope_t* top_scope;

#line 84 "y.tab.c" /* yacc.c:339  */

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
#line 19 "pc.y" /* yacc.c:355  */

    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;
    node_t* nval;

#line 239 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 256 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   127

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  136

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

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
      53,    54,     2,     2,    57,     2,    56,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    55,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    60,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    93,    93,    93,   107,   111,   119,   141,   151,   155,
     162,   163,   167,   168,   172,   188,   187,   210,   209,   233,
     237,   244,   262,   278,   288,   293,   297,   301,   308,   309,
     313,   315,   319,   321,   323,   325,   339,   341,   346,   354,
     365,   373,   391,   396,   407,   408,   412,   416,   420,   427,
     429,   434,   442,   450,   464,   465,   466,   467
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "BBEGIN", "END", "VAR",
  "TYPE", "PROCEDURE", "FUNCTION", "ARGS", "INTEGER", "REAL",
  "INTEGER_ARRAY", "REAL_ARRAY", "BOOLEAN", "NOT_SET", "ARRAY", "OF",
  "DOTDOT", "IF", "THEN", "ELSE", "WHILE", "FOR", "DO", "TO", "ASSIGNOP",
  "RELOP", "EQ", "NE", "LT", "LE", "GT", "GE", "ADDOP", "PLUS", "MINUS",
  "OR", "MULOP", "STAR", "SLASH", "AND", "NOT", "ID", "INUM", "RNUM",
  "COMMA", "SEMICOLON", "ARRAY_ACCESS", "FUNCTION_CALL", "PROCEDURE_CALL",
  "ENTRY_TYPE", "'('", "')'", "';'", "'.'", "','", "':'", "'['", "']'",
  "$accept", "program", "$@1", "identifier_list", "declarations", "type",
  "standard_type", "subprogram_declarations", "subprogram_declaration",
  "subprogram_head", "$@2", "$@3", "arguments", "parameter_list",
  "compound_statement", "optional_statements", "statement_list",
  "statement", "matched", "unmatched", "variable", "procedure_statement",
  "expression_list", "expression", "simple_expression", "term", "factor", YY_NULLPTR
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
     305,   306,   307,    40,    41,    59,    46,    44,    58,    91,
      93
};
# endif

#define YYPACT_NINF -98

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-98)))

#define YYTABLE_NINF -39

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -98,    15,    18,   -98,   -26,   -29,   -15,   -25,   -18,   -15,
     -17,   -98,   -98,    36,   -15,    70,   -13,     2,     4,     6,
      27,   -98,     1,    42,    20,    20,    39,   -20,   -98,    56,
     -98,    29,   -98,   -98,    58,   -98,   -98,   -98,   -98,    36,
     -98,   -98,   -98,    28,    31,   -98,    24,    24,   -40,   -98,
     -98,    20,    67,   -12,    50,   -98,    66,    33,    68,    20,
      20,   -98,     2,    20,    40,    40,    70,    49,   -98,    50,
     -98,    20,    20,    43,     2,    20,    24,    24,     7,    20,
      44,    45,    41,   -98,   -98,   -15,    48,    38,   -98,    80,
      46,    47,   -98,   -98,    82,    71,    50,   -98,    20,   -98,
      79,   -98,    20,   -98,    51,    17,   -98,    69,    65,   -98,
     -98,     2,    90,    20,   -98,    42,   -98,   -15,    57,    53,
     -98,   -98,     7,    89,   -98,    59,   -98,    97,    94,     2,
      42,    69,     7,   -98,   -98,   -98
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     4,     0,     0,
       0,     5,     7,    13,     0,     0,     0,    25,     0,     0,
       0,     7,     0,     0,     0,     0,     0,    40,    33,     0,
      24,    26,    28,    29,     0,    32,    17,    15,    12,    13,
       3,    10,    11,     0,     0,     8,     0,     0,    51,    54,
      55,     0,     0,    44,    46,    49,     0,    38,     0,     0,
       0,    23,    25,     0,    20,    20,     0,     0,     6,    47,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,     0,    27,    31,     0,     0,     0,    14,     0,
       0,     0,    56,    36,    28,    45,    48,    50,     0,    34,
       0,    41,     0,    39,     0,     0,    18,     0,     0,    53,
      52,     0,     0,     0,    43,     0,    19,     0,     0,     0,
      30,    37,     0,     0,    21,     0,    16,     0,     0,     0,
       0,     0,     0,    35,    22,     9
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -98,   -98,   -98,    -9,    98,   -95,   -97,    81,   -98,   -98,
     -98,   -98,    60,   -98,    -6,    61,   -98,   -71,   -70,    10,
      92,   -98,   -59,   -23,    52,   -32,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     8,    13,    44,    45,    15,    20,    21,
      65,    64,    86,   105,    28,    29,    30,    31,    32,    33,
      34,    35,    80,    81,    53,    54,    55
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      11,    52,    56,    93,    94,    16,    17,   -38,    99,    22,
     118,    17,    90,    71,    69,     3,    75,    70,     5,    72,
     124,     4,    24,    76,     6,    25,    26,    98,    73,     7,
      25,    26,     9,    59,   135,   134,    10,    82,    12,    60,
      84,   120,    14,   114,    96,    23,    27,    97,    36,    91,
      37,    27,   128,    41,    42,    46,   100,    40,   133,    43,
      88,    61,   120,    47,    48,    49,    50,    47,    48,    49,
      50,   116,   117,    51,    17,   112,   104,    51,    18,    19,
      41,    42,    38,    57,    62,    63,    68,    67,    74,    77,
     123,    78,    60,    85,    89,    79,   107,    92,   101,   108,
     109,   103,   102,   106,   111,   113,    76,   110,   125,   115,
     119,   122,   126,   127,   129,   131,   132,   130,    58,    39,
      66,   121,     0,    83,     0,    87,     0,    95
};

static const yytype_int16 yycheck[] =
{
       9,    24,    25,    74,    74,    14,     4,    27,    78,    15,
     107,     4,    71,    53,    46,     0,    28,    47,    44,    59,
     115,     3,    20,    35,    53,    23,    24,    20,    51,    44,
      23,    24,    57,    53,   131,   130,    54,    60,    55,    59,
      63,   111,     6,   102,    76,    58,    44,    77,    44,    72,
      44,    44,   122,    11,    12,    35,    79,    56,   129,    17,
      66,     5,   132,    43,    44,    45,    46,    43,    44,    45,
      46,    54,    55,    53,     4,    98,    85,    53,     8,     9,
      11,    12,    55,    44,    55,    27,    55,    59,    21,    39,
     113,    25,    59,    53,    45,    27,    58,    54,    54,    19,
      54,    60,    57,    55,    22,    26,    35,    60,   117,    58,
      45,    21,    55,    60,    25,    18,    22,    58,    26,    21,
      39,   111,    -1,    62,    -1,    65,    -1,    75
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    62,    63,     0,     3,    44,    53,    44,    64,    57,
      54,    64,    55,    65,     6,    68,    64,     4,     8,     9,
      69,    70,    75,    58,    20,    23,    24,    44,    75,    76,
      77,    78,    79,    80,    81,    82,    44,    44,    55,    65,
      56,    11,    12,    17,    66,    67,    35,    43,    44,    45,
      46,    53,    84,    85,    86,    87,    84,    44,    81,    53,
      59,     5,    55,    27,    72,    71,    68,    59,    55,    86,
      87,    53,    59,    84,    21,    28,    35,    39,    25,    27,
      83,    84,    84,    76,    84,    53,    73,    73,    75,    45,
      83,    84,    54,    78,    79,    85,    86,    87,    20,    79,
      84,    54,    57,    60,    64,    74,    55,    58,    19,    54,
      60,    22,    84,    26,    83,    58,    54,    55,    67,    45,
      79,    80,    21,    84,    66,    64,    55,    60,    79,    25,
      58,    18,    22,    78,    66,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    63,    62,    64,    64,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    71,    70,    72,    70,    73,
      73,    74,    74,    75,    76,    76,    77,    77,    78,    78,
      79,    79,    79,    79,    79,    79,    80,    80,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    86,
      86,    87,    87,    87,    87,    87,    87,    87
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,    11,     1,     3,     6,     0,     1,     8,
       1,     1,     3,     0,     4,     0,     7,     0,     5,     3,
       0,     3,     5,     3,     1,     0,     1,     3,     1,     1,
       6,     3,     1,     1,     4,     8,     4,     6,     1,     4,
       1,     4,     1,     3,     1,     3,     1,     2,     3,     1,
       3,     1,     4,     4,     1,     1,     3,     2
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
#line 93 "pc.y" /* yacc.c:1646  */
    {
        fprintf(stderr, "BEGINING OF PROGRAM\n"); 
    }
#line 1428 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 101 "pc.y" /* yacc.c:1646  */
    { 
        fprintf(stderr, "END OF PROGRAM\n"); 
    }
#line 1436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 108 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.nval) = insertVarNode(NULL, NOT_SET, (yyvsp[0].sval)); 
    }
#line 1444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 112 "pc.y" /* yacc.c:1646  */
    { 
        node_t* newTop = insertVarNode((yyvsp[0].nval), NOT_SET, (yyvsp[-2].sval)); 
        (yyval.nval) = newTop;
    }
#line 1453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 120 "pc.y" /* yacc.c:1646  */
    {
            int type = getType((yyvsp[-1].nval));
            node_t* idList = (yyvsp[-3].nval);
            node_t* cur = idList;

            while(cur != NULL){
                if(scope_search(top_scope, cur->name) != NULL){
                    /* Variable is redeclared in the current scope */
                    yyerror("Variable is redeclared in the current scope in identifier_list\n");
                }
                if((yyvsp[-1].nval)->nodeType == ARRAY){
                    cur->data.arrayInfo.type = type; 
                }
                else{
                    cur->data.varInfo.type = type; 
                }
                node_t* next = cur->next;
                scope_insert_node(top_scope, cur); 
                cur = next;
            }
        }
#line 1479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 152 "pc.y" /* yacc.c:1646  */
    {
        (yyval.nval) = insertTypeNode(NULL, (yyvsp[0].ival));
    }
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 156 "pc.y" /* yacc.c:1646  */
    {
        (yyval.nval) = insertArrayNode(NULL, (yyvsp[0].ival), NULL, (yyvsp[-3].ival) - (yyvsp[-5].ival));
    }
#line 1495 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 162 "pc.y" /* yacc.c:1646  */
    { (yyval.ival) = INTEGER; }
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 163 "pc.y" /* yacc.c:1646  */
    { (yyval.ival) = REAL; }
#line 1507 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 173 "pc.y" /* yacc.c:1646  */
    { 
        if(top_scope == NULL){
            yyerror("Invalid scope in subprogram_declaration\n");
        }
        node_t* subprogramHead = (yyvsp[-3].nval);
        if(subprogramHead->nodeType == FUNCTION){
            /* Ensure no side effects in subprogram_declarations or compound_statement */
            /* Ensure a return statement. */
        }
        top_scope = pop_scope(top_scope); 
    }
#line 1523 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 188 "pc.y" /* yacc.c:1646  */
    {   
            if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
                /* Function with same name is redeclared in the same scope */
                yyerror("Function redeclared in the same scope\n");
            }
            scope_insert_function(top_scope, 0, (yyvsp[0].sval), NULL);
            top_scope = push_scope(top_scope);  
        }
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 197 "pc.y" /* yacc.c:1646  */
    {
            /* Set the return type and argument types of the node */
            scope_t* prevScope = top_scope->next;
            node_t* functionNode = scope_search(prevScope, (yyvsp[-5].sval));

            if(functionNode->nodeType != FUNCTION){
                yyerror("FUNCTION error in subprogram_head\n");
            }
            functionNode->data.functionInfo.returnType = (yyvsp[-1].ival);
            functionNode->data.functionInfo.arguments = copyArguments((yyvsp[-3].nval));
            (yyval.nval) = functionNode;
        }
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 210 "pc.y" /* yacc.c:1646  */
    { 
            if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
                /* Procedure with same name is redeclared in the same scope */
                yyerror("Procedure redeclared in the same scope\n");
            }
            scope_insert_procedure(top_scope, (yyvsp[0].sval), NULL);
            top_scope = push_scope(top_scope);  
        }
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 219 "pc.y" /* yacc.c:1646  */
    {
            /* Set the return type and argument types of the node */
            scope_t* prevScope = top_scope->next;
            node_t* procedureNode = scope_search(prevScope, (yyvsp[-3].sval));

            if(procedureNode->nodeType != PROCEDURE){
                yyerror("PROCEDURE error in subprogram_head\n");
            }
            procedureNode->data.procedureInfo.arguments = copyArguments((yyvsp[-1].nval));
            (yyval.nval) = procedureNode;
        }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 234 "pc.y" /* yacc.c:1646  */
    { 
            (yyval.nval) = (yyvsp[-1].nval); 
        }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 237 "pc.y" /* yacc.c:1646  */
    { (yyval.nval) = NULL; }
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 245 "pc.y" /* yacc.c:1646  */
    {
        int type = getType((yyvsp[0].nval));
        node_t* idList = (yyvsp[-2].nval);
        node_t* cur = idList;
        while(cur != NULL){
            if((yyvsp[0].nval)->nodeType == ARRAY){
                cur->data.arrayInfo.type = type; 
            }
            else {
                cur->data.varInfo.type = type; 
            }
            node_t* next = cur->next;
            scope_insert_node(top_scope, cur); 
            cur = next;
        }
        (yyval.nval) = idList;
    }
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 263 "pc.y" /* yacc.c:1646  */
    {
        node_t* idList = (yyvsp[-2].nval);
        node_t* cur = idList;
        while(cur != NULL){
            cur->data.type = getType((yyvsp[0].nval));
            node_t* next = cur->next;
            scope_insert_node(top_scope, cur); 
            cur = next;
        }
        getBottom((yyvsp[-4].nval))->next = idList;
        (yyval.nval) = (yyvsp[-4].nval);
    }
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 279 "pc.y" /* yacc.c:1646  */
    { 
            (yyval.tval) =  (yyvsp[-1].tval);
            fprintf(stderr, "\nBEGIN TREE PRINT\n\n");
            tree_print((yyval.tval));
            fprintf(stderr, "\nEND TREE PRINT\n\n");
        }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 289 "pc.y" /* yacc.c:1646  */
    { 
        validateStatement(top_scope, (yyvsp[0].tval));
        (yyval.tval) = (yyvsp[0].tval); 
    }
#line 1655 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 293 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL; }
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 298 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = (yyvsp[0].tval); 
    }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 302 "pc.y" /* yacc.c:1646  */
    {
        (yyval.tval) = mktree(SEMICOLON, (yyvsp[-2].tval), (yyvsp[0].tval)); 
    }
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 308 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 309 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 314 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-4].tval), mktree(THEN, (yyvsp[-2].tval), (yyvsp[0].tval))); }
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 316 "pc.y" /* yacc.c:1646  */
    {  
            (yyval.tval) = mktree(ASSIGNOP, (yyvsp[-2].tval), (yyvsp[0].tval));
        }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 320 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 322 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 324 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(WHILE, (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 326 "pc.y" /* yacc.c:1646  */
    { 
            int variableType = getExpressionType(top_scope, (yyvsp[-6].tval));
            int expression1 = getExpressionType(top_scope, (yyvsp[-4].tval));
            int expression2 = getExpressionType(top_scope, (yyvsp[-2].tval));
            if(variableType != expression1 || expression1 != expression2){
                yyerror("For loop assignment types do not match.");
            }
            (yyval.tval) = mktree(FOR, mktree(ASSIGNOP, (yyvsp[-6].tval), (yyvsp[-4].tval)), mktree(TO, (yyvsp[-2].tval), mktree(DO, (yyvsp[0].tval), NULL))); 

        }
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 340 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-2].tval), mktree(THEN, (yyvsp[0].tval), NULL)); }
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 342 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-4].tval), mktree(THEN, (yyvsp[-2].tval), (yyvsp[0].tval))); }
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 347 "pc.y" /* yacc.c:1646  */
    {
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[0].sval));
        if(!matchNode){
            yyerror("Cannot find variable ID in variable\n");
        }
        (yyval.tval) = mkid(matchNode); 
    }
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 355 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(!matchNode){
            yyerror("Cannot find array variable ID in variable\n");
        }
        (yyval.tval) = mktree(ARRAY_ACCESS, mkid(matchNode), (yyvsp[-1].tval));
    }
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 366 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[0].sval));
        if(matchNode == NULL || matchNode->nodeType != PROCEDURE){
            yyerror("Cannot find procedure ID match 1 in procedure_statement\n");
        }
        (yyval.tval) = mktree(PROCEDURE_CALL, mkid(matchNode), NULL); 
    }
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 374 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(matchNode == NULL || matchNode->nodeType != PROCEDURE){
            yyerror("Cannot find procedure ID match 2 in procedure_statement\n");
        }

        // Validate input types
        node_t* expectedArgs = matchNode->data.procedureInfo.arguments;
        node_t* actualArgs = (yyvsp[-1].nval);

        validateArguments(expectedArgs, actualArgs);

        (yyval.tval) = mktree(PROCEDURE_CALL, mkid(matchNode), mkargs((yyvsp[-1].nval))); 
    }
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 392 "pc.y" /* yacc.c:1646  */
    { 
        int expressionType = getExpressionType(top_scope, (yyvsp[0].tval));
        (yyval.nval) = insertTypeNode(NULL, expressionType); 
    }
#line 1812 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 397 "pc.y" /* yacc.c:1646  */
    {
            int expressionType = getExpressionType(top_scope, (yyvsp[-2].tval));
            fprintf(stderr, "AFTERGOOOO BILLS\n");
            fprintf(stderr, "$$ = %d    %d\n", expressionType, (yyvsp[0].nval));
            node_t* newTop = insertTypeNode((yyvsp[0].nval), expressionType); 
            (yyval.nval) = newTop;
        }
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 407 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 408 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkop(RELOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1836 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 413 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = (yyvsp[0].tval); 
    }
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 417 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = mkop(ADDOP, (yyvsp[-1].opval), (yyvsp[0].tval), NULL); 
    }
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 421 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = mkop(ADDOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); 
    }
#line 1860 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 428 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 430 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkop(MULOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1872 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 435 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[0].sval));
        if(matchNode == NULL || matchNode->nodeType != VAR){
            yyerror("Cannot find ID match in factor\n");
        }
        (yyval.tval) = mkid(matchNode); 
    }
#line 1884 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 443 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(matchNode == NULL || matchNode->nodeType != ARRAY){
            yyerror("Cannot find array ID match in factor\n");
        }
        (yyval.tval) = mktree(ARRAY_ACCESS, mkid(matchNode), (yyvsp[-1].tval)); 
    }
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 451 "pc.y" /* yacc.c:1646  */
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
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 464 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkinum((yyvsp[0].ival)); }
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 465 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkrnum((yyvsp[0].rval)); }
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 466 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[-1].tval); }
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 467 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(NOT, (yyvsp[0].tval), NULL); }
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1942 "y.tab.c" /* yacc.c:1646  */
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
#line 470 "pc.y" /* yacc.c:1906  */


int main(){
    top_scope = mkscope();
    yyparse();
    free_scope(top_scope);
}
