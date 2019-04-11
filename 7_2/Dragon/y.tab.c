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
    #include "y.tab.h"

    // DRAGON PARSER

    extern int yyerror(char*);
    extern int yylex();

    scope_t* top_scope;

#line 83 "y.tab.c" /* yacc.c:339  */

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
#line 18 "pc.y" /* yacc.c:355  */

    // This is yylval
    int ival; /* NUM */
    float rval; /* RNUM */
    int opval; /* RELOP ADDOP MULOP */
    char* sval; /* ID */
    /********************************/
    tree_t* tval;

#line 227 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 244 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   121

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

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
      48,    49,     2,     2,    52,     2,    51,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    50,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    54,     2,    55,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    81,    81,    81,    95,   104,   116,   117,   121,   122,
     126,   127,   131,   132,   136,   147,   157,   170,   171,   175,
     176,   180,   190,   191,   195,   196,   200,   204,   206,   208,
     210,   212,   214,   219,   231,   235,   245,   258,   259,   264,
     265,   269,   273,   277,   284,   286,   291,   300,   309,   318,
     319,   320,   321
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROGRAM", "BBEGIN", "END", "VAR",
  "PROCEDURE", "FUNCTION", "INTEGER", "REAL", "ARRAY", "OF", "DOTDOT",
  "IF", "THEN", "ELSE", "WHILE", "FOR", "DO", "TO", "ASSIGNOP", "RELOP",
  "EQ", "NE", "LT", "LE", "GT", "GE", "ADDOP", "PLUS", "MINUS", "OR",
  "MULOP", "STAR", "SLASH", "AND", "NOT", "ID", "INUM", "RNUM", "COMMA",
  "SEMICOLON", "ARRAY_ACCESS", "FUNCTION_CALL", "PROCEDURE_CALL",
  "ENTRY_NAME", "ENTRY_TYPE", "'('", "')'", "';'", "'.'", "','", "':'",
  "'['", "']'", "$accept", "program", "$@1", "identifier_list",
  "declarations", "type", "standard_type", "subprogram_declarations",
  "subprogram_declaration", "subprogram_head", "arguments",
  "parameter_list", "compound_statement", "optional_statements",
  "statement_list", "statement", "variable", "procedure_statement",
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
     295,   296,   297,   298,   299,   300,   301,   302,    40,    41,
      59,    46,    44,    58,    91,    93
};
# endif

#define YYPACT_NINF -93

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-93)))

#define YYTABLE_NINF -34

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -93,     8,    12,   -93,   -21,   -17,    -9,   -93,   -19,   -15,
      -1,   -93,   -93,    40,    -9,    43,    11,     2,    15,    41,
      30,   -93,    31,    60,   -16,   -16,    45,   -10,   -93,    76,
     -93,    34,    64,   -93,    38,    38,   -93,    40,   -93,   -93,
     -93,    33,    39,   -93,    20,    20,   -20,   -93,   -93,   -16,
      77,    -4,    58,   -93,    74,    42,    73,   -16,   -16,   -93,
       2,   -16,    -9,    47,    46,    43,    56,   -93,    58,   -93,
     -16,   -16,    49,     2,   -16,    20,    20,     2,   -16,     3,
     -93,    48,   -93,   -93,    14,    23,   -93,    65,   -93,    87,
      13,    50,   -93,    85,    75,    58,   -93,   -93,    82,   -93,
     -16,   -93,    60,   -93,    -9,    57,    67,   -93,   -93,     2,
     -16,   -93,   -93,    24,   -93,    53,   -93,    90,    60,    98,
       2,   -93,    65,   -93,   -93
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     4,     0,     0,
       0,     7,     5,    13,     0,     0,     0,    23,     0,     0,
       0,     7,     0,     0,     0,     0,     0,    35,    28,     0,
      22,    24,     0,    27,    18,    18,    12,    13,     3,    10,
      11,     0,     0,     8,     0,     0,    46,    49,    50,     0,
       0,    39,    41,    44,     0,    33,     0,     0,     0,    21,
      23,     0,     0,     0,     0,     0,     0,     6,    42,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      37,     0,    25,    26,     0,     0,    16,     0,    14,     0,
       0,     0,    51,    30,    40,    43,    45,    31,     0,    36,
       0,    34,     0,    17,     0,     0,     0,    48,    47,     0,
       0,    38,    19,     0,    15,     0,    29,     0,     0,     0,
      23,    20,     0,    32,     9
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -93,   -93,   -93,   -14,    91,   -92,   -80,    78,   -93,   -93,
      79,   -93,   -11,   -59,   -93,   -68,    92,   -93,    51,   -22,
      37,   -32,   -31
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     8,    13,    42,    43,    15,    20,    21,
      63,    85,    28,    29,    30,    31,    32,    33,    79,    80,
      51,    52,    53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      16,    82,    50,    54,    22,    93,    17,   105,     3,    97,
     112,   -33,    68,    44,    69,     4,    24,     5,    74,    25,
      26,    45,    46,    47,    48,    75,   121,    72,    70,     7,
       9,     6,    49,    10,    71,    11,    81,    12,    57,    83,
      27,   116,   124,    95,    58,    96,    14,    17,    84,    91,
      18,    19,    99,    34,    88,   100,    98,    45,    46,    47,
      48,   123,   107,    10,    23,   100,    10,   102,    49,    39,
      40,    41,   103,   104,    39,    40,    10,   118,   111,    35,
      36,    59,    38,    55,    60,    61,    62,    66,   117,    67,
     113,    76,    73,    77,    78,    89,    58,    86,    92,    87,
     106,   109,   110,   101,    75,   108,   115,   114,   119,   120,
     122,    94,    37,     0,    64,    65,     0,     0,    56,     0,
       0,    90
};

static const yytype_int8 yycheck[] =
{
      14,    60,    24,    25,    15,    73,     4,    87,     0,    77,
     102,    21,    44,    29,    45,     3,    14,    38,    22,    17,
      18,    37,    38,    39,    40,    29,   118,    49,    48,    38,
      49,    48,    48,    52,    54,    50,    58,    38,    48,    61,
      38,   109,   122,    75,    54,    76,     6,     4,    62,    71,
       7,     8,    49,    38,    65,    52,    78,    37,    38,    39,
      40,   120,    49,    52,    53,    52,    52,    53,    48,     9,
      10,    11,    49,    50,     9,    10,    52,    53,   100,    38,
      50,     5,    51,    38,    50,    21,    48,    54,   110,    50,
     104,    33,    15,    19,    21,    39,    54,    50,    49,    53,
      13,    16,    20,    55,    29,    55,    39,    50,    55,    19,
      12,    74,    21,    -1,    35,    37,    -1,    -1,    26,    -1,
      -1,    70
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,    58,     0,     3,    38,    48,    38,    59,    49,
      52,    50,    38,    60,     6,    63,    59,     4,     7,     8,
      64,    65,    68,    53,    14,    17,    18,    38,    68,    69,
      70,    71,    72,    73,    38,    38,    50,    60,    51,     9,
      10,    11,    61,    62,    29,    37,    38,    39,    40,    48,
      75,    76,    77,    78,    75,    38,    72,    48,    54,     5,
      50,    21,    48,    66,    66,    63,    54,    50,    77,    78,
      48,    54,    75,    15,    22,    29,    33,    19,    21,    74,
      75,    75,    69,    75,    59,    67,    50,    53,    68,    39,
      74,    75,    49,    71,    76,    77,    78,    71,    75,    49,
      52,    55,    53,    49,    50,    62,    13,    49,    55,    16,
      20,    75,    61,    59,    50,    39,    71,    75,    53,    55,
      19,    61,    12,    69,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    58,    57,    59,    59,    60,    60,    61,    61,
      62,    62,    63,    63,    64,    65,    65,    66,    66,    67,
      67,    68,    69,    69,    70,    70,    71,    71,    71,    71,
      71,    71,    71,    72,    72,    73,    73,    74,    74,    75,
      75,    76,    76,    76,    77,    77,    78,    78,    78,    78,
      78,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,    11,     1,     3,     6,     0,     1,     8,
       1,     1,     3,     0,     4,     6,     4,     3,     0,     3,
       5,     3,     1,     0,     1,     3,     3,     1,     1,     6,
       4,     4,     8,     1,     4,     1,     4,     1,     3,     1,
       3,     1,     2,     3,     1,     3,     1,     4,     4,     1,
       1,     3,     2
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
#line 81 "pc.y" /* yacc.c:1646  */
    {
        fprintf(stderr, "BEGINING OF PROGRAM\n"); 
    }
#line 1411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 89 "pc.y" /* yacc.c:1646  */
    { 
        fprintf(stderr, "END OF PROGRAM\n"); 
    }
#line 1419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 96 "pc.y" /* yacc.c:1646  */
    { 
        if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
            /* Variable is redeclared in the current scope */
            fprintf(stderr, "Variable %s is redeclared in the current scope in identifier_list\n", (yyvsp[0].sval)); 
            exit(0);
        }
        (yyval.tval) = mkid(scope_insert(top_scope, (yyvsp[0].sval))); 
    }
#line 1432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 105 "pc.y" /* yacc.c:1646  */
    { 
        if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
            /* Variable is redeclared in the current scope */
            fprintf(stderr, "Variable %s is redeclared in the current scope in identifier_list\n", (yyvsp[0].sval)); 
            exit(0);
        }
        (yyval.tval) = mktree(COMMA, (yyvsp[-2].tval), mkid(scope_insert(top_scope, (yyvsp[0].sval)))); 
    }
#line 1445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 121 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL; }
#line 1451 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 122 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL; }
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 137 "pc.y" /* yacc.c:1646  */
    { 
        if(top_scope == NULL){
            fprintf(stderr, "Invalid scope in subprogram_declaration\n"); 
            exit(0);
        }
        top_scope = pop_scope(top_scope); 
    }
#line 1469 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 148 "pc.y" /* yacc.c:1646  */
    {   
            if(scope_search(top_scope, (yyvsp[-4].sval)) != NULL){
                /* Function with same name is redeclared in the same scope */
                fprintf(stderr, "Function %s redeclared in the same scope\n", (yyvsp[-4].sval)); 
                exit(0);
            }
            scope_insert(top_scope, (yyvsp[-4].sval));
            top_scope = push_scope(top_scope);  
        }
#line 1483 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 158 "pc.y" /* yacc.c:1646  */
    { 
            if(scope_search(top_scope, (yyvsp[-2].sval)) != NULL){
                /* Procedure with same name is redeclared in the same scope */
                fprintf(stderr, "Procedure %s redeclared in the same scope\n", (yyvsp[-2].sval)); 
                exit(0);
            }
            scope_insert(top_scope, (yyvsp[-2].sval));
            top_scope = push_scope(top_scope);  
        }
#line 1497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 181 "pc.y" /* yacc.c:1646  */
    { 
            (yyval.tval) =  (yyvsp[-1].tval);
            fprintf(stderr, "\nBEGIN TREE PRINT\n\n");
            tree_print((yyval.tval));
            fprintf(stderr, "\nEND TREE PRINT\n\n");
        }
#line 1508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 190 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 191 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL; }
#line 1520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 195 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 196 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(SEMICOLON, (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 201 "pc.y" /* yacc.c:1646  */
    {  
            (yyval.tval) = mktree(ASSIGNOP, (yyvsp[-2].tval), (yyvsp[0].tval));
        }
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 205 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 207 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 209 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-4].tval), mktree(THEN, (yyvsp[-2].tval), (yyvsp[0].tval))); }
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 211 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-2].tval), mktree(THEN, (yyvsp[0].tval), NULL)); }
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 213 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(WHILE, (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 215 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(FOR, mktree(ASSIGNOP, (yyvsp[-6].tval), (yyvsp[-4].tval)), mktree(TO, (yyvsp[-2].tval), mktree(DO, (yyvsp[0].tval), NULL))); }
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 220 "pc.y" /* yacc.c:1646  */
    {
        node_t* match = scope_search_all(top_scope, (yyvsp[0].sval));
        if(match){
            (yyval.tval) = mkid(match); 
        }
        else{
            fprintf(stderr, "Cannot find variable ID '%s' in variable\n", (yyvsp[0].sval)); 
            scope_print(top_scope);
            exit(0);
        }
    }
#line 1592 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 231 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(ARRAY_ACCESS, mkid(scope_search_all(top_scope, (yyvsp[-3].sval))), (yyvsp[-1].tval)); }
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 236 "pc.y" /* yacc.c:1646  */
    { 
        node_t* match = scope_search_all(top_scope, (yyvsp[0].sval));
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in procedure_statement\n", (yyvsp[0].sval)); 
            scope_print(top_scope);
            exit(0);
        }
        (yyval.tval) = mktree(PROCEDURE_CALL, mkid(match), NULL); 
    }
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 246 "pc.y" /* yacc.c:1646  */
    { 
        node_t* match = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in procedure_statement\n", (yyvsp[-3].sval)); 
            scope_print(top_scope);
            exit(0);
        }
        (yyval.tval) = mktree(PROCEDURE_CALL, mkid(match), (yyvsp[-1].tval)); 
    }
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 258 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 260 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(COMMA, (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 264 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 265 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkop(RELOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 270 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = (yyvsp[0].tval); 
    }
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 274 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = mkop(ADDOP, (yyvsp[-1].opval), (yyvsp[0].tval), NULL); 
    }
#line 1666 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 278 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = mkop(ADDOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); 
    }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 285 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 287 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkop(MULOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 292 "pc.y" /* yacc.c:1646  */
    { 
        node_t* match = scope_search_all(top_scope, (yyvsp[0].sval));
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in factor\n", (yyvsp[0].sval)); 
            exit(0);
        }
        (yyval.tval) = mkid(match); 
    }
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 301 "pc.y" /* yacc.c:1646  */
    { 
        node_t* match = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in factor\n", (yyvsp[-3].sval)); 
            exit(0);
        }
        (yyval.tval) = mktree(ARRAY_ACCESS, mkid(match), (yyvsp[-1].tval)); 
    }
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 310 "pc.y" /* yacc.c:1646  */
    { 
        node_t* match = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(match == NULL){
            fprintf(stderr, "Cannot find ID '%s' match in factor\n", (yyvsp[-3].sval)); 
            exit(0);
        }
        (yyval.tval) = mktree(FUNCTION_CALL, mkid(match), (yyvsp[-1].tval)); 
    }
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 318 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkinum((yyvsp[0].ival)); }
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 319 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkrnum((yyvsp[0].rval)); }
#line 1737 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 320 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[-1].tval); }
#line 1743 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 321 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(NOT, (yyvsp[0].tval), NULL); }
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1753 "y.tab.c" /* yacc.c:1646  */
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
#line 324 "pc.y" /* yacc.c:1906  */


int main(){
    top_scope = mkscope();
    yyparse();
    free_scope(top_scope);
}
