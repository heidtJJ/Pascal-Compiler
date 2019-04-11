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
#define YYLAST   126

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  127

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
       0,    88,    88,    88,   102,   110,   121,   131,   141,   145,
     152,   153,   157,   158,   162,   174,   173,   192,   191,   214,
     218,   225,   236,   251,   261,   262,   266,   267,   271,   275,
     277,   279,   281,   283,   285,   290,   300,   304,   312,   330,
     335,   344,   345,   349,   353,   357,   364,   366,   371,   379,
     387,   401,   402,   403,   404
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
  "statement", "variable", "procedure_statement", "expression_list",
  "expression", "simple_expression", "term", "factor", YY_NULLPTR
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

#define YYPACT_NINF -100

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-100)))

#define YYTABLE_NINF -36

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
    -100,    32,    40,  -100,    28,    -7,    29,  -100,   -41,     0,
      30,  -100,  -100,    57,    29,    48,     2,     1,    31,    33,
      21,  -100,    22,    19,     5,     5,    35,   -20,  -100,    75,
    -100,    26,    55,  -100,  -100,  -100,  -100,    57,  -100,  -100,
    -100,    24,    34,  -100,   -26,   -26,   -25,  -100,  -100,     5,
      63,   -13,    47,  -100,    62,    36,    61,     5,     5,  -100,
       1,     5,    37,    37,    48,    46,  -100,    47,  -100,     5,
       5,    38,     1,     5,   -26,   -26,     1,     5,    39,    42,
      41,  -100,  -100,    29,    45,    44,  -100,    77,    43,    49,
    -100,    72,    68,    47,  -100,  -100,    78,  -100,     5,  -100,
       4,    11,  -100,    56,    60,  -100,  -100,     1,     5,  -100,
      19,  -100,    29,    51,    50,  -100,    82,  -100,    13,  -100,
      90,     1,    19,    56,  -100,  -100,  -100
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,     4,     0,     0,
       0,     7,     5,    13,     0,     0,     0,    25,     0,     0,
       0,     7,     0,     0,     0,     0,     0,    37,    30,     0,
      24,    26,     0,    29,    17,    15,    12,    13,     3,    10,
      11,     0,     0,     8,     0,     0,    48,    51,    52,     0,
       0,    41,    43,    46,     0,    35,     0,     0,     0,    23,
      25,     0,    20,    20,     0,     0,     6,    44,    54,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    39,
       0,    27,    28,     0,     0,     0,    14,     0,     0,     0,
      53,    32,    42,    45,    47,    33,     0,    38,     0,    36,
       0,     0,    18,     0,     0,    50,    49,     0,     0,    40,
       0,    19,     0,     0,     0,    31,     0,    21,     0,    16,
       0,    25,     0,     0,    34,    22,     9
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -100,  -100,  -100,   -14,    91,   -99,   -94,    74,  -100,  -100,
    -100,  -100,    52,  -100,   -11,   -57,  -100,   -66,    87,  -100,
     -61,   -23,    53,   -32,   -31
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     8,    13,    42,    43,    15,    20,    21,
      63,    62,    84,   101,    28,    29,    30,    31,    32,    33,
      78,    79,    51,    52,    53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      16,    50,    54,    81,    22,    17,    91,   -35,    88,   113,
      95,   117,    67,     9,    68,    73,    10,    45,    46,    47,
      48,    24,    74,   125,    25,    26,    71,    49,    69,   126,
      39,    40,     3,    57,    70,    80,    41,   109,    82,    58,
      44,   115,    93,     4,    94,    27,     6,    89,    45,    46,
      47,    48,    17,    86,    96,    11,    18,    19,    49,    10,
      23,    10,   110,    14,   124,   111,   112,    39,    40,   100,
      10,   122,     5,     7,    12,    34,    36,    35,    38,    55,
      59,    60,    61,    65,    72,   116,    75,    76,    77,    66,
      83,    87,    90,    97,   107,    58,   104,   105,   118,    98,
     102,    99,   103,    74,   108,   114,   119,   121,   123,   106,
     120,    64,    37,    56,     0,    85,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92
};

static const yytype_int8 yycheck[] =
{
      14,    24,    25,    60,    15,     4,    72,    27,    69,   103,
      76,   110,    44,    54,    45,    28,    57,    43,    44,    45,
      46,    20,    35,   122,    23,    24,    49,    53,    53,   123,
      11,    12,     0,    53,    59,    58,    17,    98,    61,    59,
      35,   107,    74,     3,    75,    44,    53,    70,    43,    44,
      45,    46,     4,    64,    77,    55,     8,     9,    53,    57,
      58,    57,    58,     6,   121,    54,    55,    11,    12,    83,
      57,    58,    44,    44,    44,    44,    55,    44,    56,    44,
       5,    55,    27,    59,    21,   108,    39,    25,    27,    55,
      53,    45,    54,    54,    22,    59,    19,    54,   112,    57,
      55,    60,    58,    35,    26,    45,    55,    25,    18,    60,
      60,    37,    21,    26,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    62,    63,     0,     3,    44,    53,    44,    64,    54,
      57,    55,    44,    65,     6,    68,    64,     4,     8,     9,
      69,    70,    75,    58,    20,    23,    24,    44,    75,    76,
      77,    78,    79,    80,    44,    44,    55,    65,    56,    11,
      12,    17,    66,    67,    35,    43,    44,    45,    46,    53,
      82,    83,    84,    85,    82,    44,    79,    53,    59,     5,
      55,    27,    72,    71,    68,    59,    55,    84,    85,    53,
      59,    82,    21,    28,    35,    39,    25,    27,    81,    82,
      82,    76,    82,    53,    73,    73,    75,    45,    81,    82,
      54,    78,    83,    84,    85,    78,    82,    54,    57,    60,
      64,    74,    55,    58,    19,    54,    60,    22,    26,    81,
      58,    54,    55,    67,    45,    78,    82,    66,    64,    55,
      60,    25,    58,    18,    76,    66,    67
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    63,    62,    64,    64,    65,    65,    66,    66,
      67,    67,    68,    68,    69,    71,    70,    72,    70,    73,
      73,    74,    74,    75,    76,    76,    77,    77,    78,    78,
      78,    78,    78,    78,    78,    79,    79,    80,    80,    81,
      81,    82,    82,    83,    83,    83,    84,    84,    85,    85,
      85,    85,    85,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,    11,     1,     3,     6,     0,     1,     8,
       1,     1,     3,     0,     4,     0,     7,     0,     5,     3,
       0,     3,     5,     3,     1,     0,     1,     3,     3,     1,
       1,     6,     4,     4,     8,     1,     4,     1,     4,     1,
       3,     1,     3,     1,     2,     3,     1,     3,     1,     4,
       4,     1,     1,     3,     2
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
#line 88 "pc.y" /* yacc.c:1646  */
    {
        fprintf(stderr, "BEGINING OF PROGRAM\n"); 
    }
#line 1425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 96 "pc.y" /* yacc.c:1646  */
    { 
        fprintf(stderr, "END OF PROGRAM\n"); 
    }
#line 1433 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 103 "pc.y" /* yacc.c:1646  */
    { 
        if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
            /* Variable is redeclared in the current scope */
            yyerror("Variable %s is redeclared in the current scope in identifier_list\n");
        }
        (yyval.tval) = mkid(insertVarNode(NULL, NOT_SET, (yyvsp[0].sval))); 
    }
#line 1445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 111 "pc.y" /* yacc.c:1646  */
    { 
        if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
            /* Variable is redeclared in the current scope */
            yyerror("Variable %s is redeclared in the current scope in identifier_list\n");
        }
        (yyval.tval) = mktree(COMMA, (yyvsp[-2].tval), mkid(insertVarNode(NULL, NOT_SET, (yyvsp[0].sval))));
    }
#line 1457 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 122 "pc.y" /* yacc.c:1646  */
    {
            node_t* idList = convertToNameList((yyvsp[-3].tval));
            node_t* cur = idList;
            while(cur != NULL){
                cur->data.varInfo.type = getType((yyvsp[-1].nval));
                scope_insert_node(top_scope, cur); 
                cur = cur->next;
            }
        }
#line 1471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 142 "pc.y" /* yacc.c:1646  */
    {
        (yyval.nval) = insertTypeNode(NULL, (yyvsp[0].ival));
    }
#line 1479 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 146 "pc.y" /* yacc.c:1646  */
    {
        (yyval.nval) = insertArrayNode(NULL, (yyvsp[0].ival), NULL, (yyvsp[-3].ival) - (yyvsp[-5].ival));
    }
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 152 "pc.y" /* yacc.c:1646  */
    { (yyval.ival) = INTEGER; }
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "pc.y" /* yacc.c:1646  */
    { (yyval.ival) = REAL; }
#line 1499 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 163 "pc.y" /* yacc.c:1646  */
    { 
        if(top_scope == NULL){
            yyerror("Invalid scope in subprogram_declaration\n");
        }
        node_t* procNode = scope_search_all(top_scope, "boo");
        top_scope = pop_scope(top_scope); 
    }
#line 1511 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 174 "pc.y" /* yacc.c:1646  */
    {   
            if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
                /* Function with same name is redeclared in the same scope */
                yyerror("Function %s redeclared in the same scope\n");
            }
            scope_insert_function(top_scope, 0, (yyvsp[0].sval), NULL);
            top_scope = push_scope(top_scope);  
        }
#line 1524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 183 "pc.y" /* yacc.c:1646  */
    {
            /* Set the return type and argument types of the node */
            scope_t* prevScope = top_scope->next;
            node_t* functionNode = scope_search(prevScope, (yyvsp[-5].sval));

            functionNode->data.functionInfo.returnType = (yyvsp[-1].ival);
            functionNode->data.functionInfo.arguments = copyArguments((yyvsp[-3].nval));
        }
#line 1537 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 192 "pc.y" /* yacc.c:1646  */
    { 
            if(scope_search(top_scope, (yyvsp[0].sval)) != NULL){
                /* Procedure with same name is redeclared in the same scope */
                yyerror("Procedure %s redeclared in the same scope\n");
            }
            scope_insert_procedure(top_scope, (yyvsp[0].sval), NULL);
            top_scope = push_scope(top_scope);  
        }
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 201 "pc.y" /* yacc.c:1646  */
    {
            /* Set the return type and argument types of the node */
            scope_t* prevScope = top_scope->next;
            node_t* procedureNode = scope_search(prevScope, (yyvsp[-3].sval));

            if(procedureNode->nodeType != PROCEDURE){
                yyerror("PROCEDURE error in subprogram_head\n");
            }
            procedureNode->data.procedureInfo.arguments = copyArguments((yyvsp[-1].nval));
        }
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 215 "pc.y" /* yacc.c:1646  */
    { 
            (yyval.nval) = (yyvsp[-1].nval); 
        }
#line 1573 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 218 "pc.y" /* yacc.c:1646  */
    { (yyval.nval) = NULL; }
#line 1579 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 226 "pc.y" /* yacc.c:1646  */
    {
        node_t* idList = convertToNameList((yyvsp[-2].tval));
        node_t* cur = idList;
        while(cur != NULL){
            cur->data.varInfo.type = getType((yyvsp[0].nval));
            scope_insert_node(top_scope, cur); 
            cur = cur->next;
        }
        (yyval.nval) = idList;
    }
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 237 "pc.y" /* yacc.c:1646  */
    {
        node_t* idList = convertToNameList((yyvsp[-2].tval));
        node_t* cur = idList;
        while(cur != NULL){
            cur->data.type = getType((yyvsp[0].nval));
            scope_insert_node(top_scope, cur); 
            cur = cur->next;
        }
        getBottom((yyvsp[-4].nval))->next = idList;
        (yyval.nval) = (yyvsp[-4].nval);
    }
#line 1610 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 252 "pc.y" /* yacc.c:1646  */
    { 
            (yyval.tval) =  (yyvsp[-1].tval);
            fprintf(stderr, "\nBEGIN TREE PRINT\n\n");
            tree_print((yyval.tval));
            fprintf(stderr, "\nEND TREE PRINT\n\n");
        }
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 261 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 262 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = NULL; }
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 266 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 267 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(SEMICOLON, (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 272 "pc.y" /* yacc.c:1646  */
    {  
            (yyval.tval) = mktree(ASSIGNOP, (yyvsp[-2].tval), (yyvsp[0].tval));
        }
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 276 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 278 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 280 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-4].tval), mktree(THEN, (yyvsp[-2].tval), (yyvsp[0].tval))); }
#line 1671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 282 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(IF, (yyvsp[-2].tval), mktree(THEN, (yyvsp[0].tval), NULL)); }
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 284 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(WHILE, (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 286 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(FOR, mktree(ASSIGNOP, (yyvsp[-6].tval), (yyvsp[-4].tval)), mktree(TO, (yyvsp[-2].tval), mktree(DO, (yyvsp[0].tval), NULL))); }
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 291 "pc.y" /* yacc.c:1646  */
    {
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[0].sval));
        if(matchNode){
            (yyval.tval) = mkid(matchNode); 
        }
        else{
            yyerror("Cannot find variable ID '%s' in variable\n");
        }
    }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 300 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(ARRAY_ACCESS, mkid(scope_search_all(top_scope, (yyvsp[-3].sval))), (yyvsp[-1].tval)); }
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 305 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[0].sval));
        if(matchNode == NULL || matchNode->nodeType != PROCEDURE){
            yyerror("Cannot find ID '%s' match in procedure_statement\n");
        }
        (yyval.tval) = mktree(PROCEDURE_CALL, mkid(matchNode), NULL); 
    }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 313 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(matchNode == NULL || matchNode->nodeType != PROCEDURE){
            yyerror("Cannot find ID '%s' match in procedure_statement\n");
        }

        // Validate input types
        node_t* expectedArgs = matchNode->data.procedureInfo.arguments;
        node_t* actualArgs = (yyvsp[-1].nval);

        validateArguments(expectedArgs, actualArgs);

        (yyval.tval) = mktree(PROCEDURE_CALL, mkid(matchNode), mkargs((yyvsp[-1].nval))); 
    }
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 331 "pc.y" /* yacc.c:1646  */
    { 
        int expressionType = getExpressionType(top_scope, (yyvsp[0].tval));
        (yyval.nval) = insertTypeNode(NULL, expressionType); 
    }
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 336 "pc.y" /* yacc.c:1646  */
    {
            (yyval.nval) = (yyvsp[0].nval);
            int expressionType = getExpressionType(top_scope, (yyvsp[-2].tval));
            (yyval.nval) = insertTypeNode((yyval.nval), expressionType);
        }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 344 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 345 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkop(RELOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 350 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = (yyvsp[0].tval); 
    }
#line 1779 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 354 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = mkop(ADDOP, (yyvsp[-1].opval), (yyvsp[0].tval), NULL); 
    }
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 358 "pc.y" /* yacc.c:1646  */
    { 
        (yyval.tval) = mkop(ADDOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); 
    }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 365 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[0].tval); }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 367 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkop(MULOP, (yyvsp[-1].opval), (yyvsp[-2].tval), (yyvsp[0].tval)); }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 372 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[0].sval));
        if(matchNode == NULL){
            yyerror("Cannot find ID '%s' match in factor\n");
        }
        (yyval.tval) = mkid(matchNode); 
    }
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 380 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(matchNode == NULL || matchNode->nodeType != ARRAY){
            yyerror("Cannot find ID '%s' match in factor\n");
        }
        (yyval.tval) = mktree(ARRAY_ACCESS, mkid(matchNode), (yyvsp[-1].tval)); 
    }
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 388 "pc.y" /* yacc.c:1646  */
    { 
        node_t* matchNode = scope_search_all(top_scope, (yyvsp[-3].sval));
        if(matchNode == NULL || matchNode->nodeType != FUNCTION){
            yyerror("Cannot find ID '%s' match in factor\n");
        }

        node_t* expectedArgs = matchNode->data.functionInfo.arguments;
        node_t* actualArgs = (yyvsp[-1].nval);
        
        validateArguments(expectedArgs, actualArgs);

        (yyval.tval) = mktree(FUNCTION_CALL, mkid(matchNode), mkargs((yyvsp[-1].nval))); 
    }
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 401 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkinum((yyvsp[0].ival)); }
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 402 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mkrnum((yyvsp[0].rval)); }
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 403 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = (yyvsp[-1].tval); }
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 404 "pc.y" /* yacc.c:1646  */
    { (yyval.tval) = mktree(NOT, (yyvsp[0].tval), NULL); }
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1877 "y.tab.c" /* yacc.c:1646  */
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
#line 407 "pc.y" /* yacc.c:1906  */


int main(){
    top_scope = mkscope();
    yyparse();
    free_scope(top_scope);
}
