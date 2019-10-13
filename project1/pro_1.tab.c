/* A Bison parser, made by GNU Bison 3.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "pro_1.y"

#include "lex.yy.c"
#include "stdlib.h"
#include "stdio.h"
#include "node.hpp"
#include "queue"
#include "stack"
#include "iostream"
#include "string"
#include "vector"
#define YYSTYPE Node
using namespace std;
void yyerror(const char*); //必须要有
extern int yylex(void);
string addLine(string,int);

Node program;

#line 89 "pro_1.tab.c"

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PRO_1_TAB_H_INCLUDED
# define YY_YY_PRO_1_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    FLOAT = 259,
    CHAR = 260,
    ID = 261,
    TYPE = 262,
    STRUCT = 263,
    IF = 264,
    ELSE = 265,
    WHILE = 266,
    RETURN = 267,
    DOT = 268,
    SEMI = 269,
    COMMA = 270,
    ASSIGN = 271,
    LT = 272,
    LE = 273,
    GT = 274,
    GE = 275,
    NE = 276,
    EQ = 277,
    PLUS = 278,
    MINUS = 279,
    MUL = 280,
    DIV = 281,
    AND = 282,
    OR = 283,
    NOT = 284,
    LP = 285,
    RP = 286,
    LB = 287,
    RB = 288,
    LC = 289,
    RC = 290,
    LINE = 291,
    ADD = 292,
    SUB = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PRO_1_TAB_H_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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


#define YY_ASSERT(E) ((void) (0 && (E)))

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   249

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  123

#define YYUNDEFTOK  2
#define YYMAXUTOK   293

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    30,    30,    36,    45,    52,    62,    71,    81,    87,
      98,   106,   114,   128,   139,   146,   160,   172,   185,   194,
     202,   211,   216,   231,   240,   247,   252,   259,   265,   275,
     288,   304,   319,   328,   335,   346,   352,   362,   368,   379,
     384,   392,   400,   408,   416,   424,   432,   440,   448,   456,
     464,   472,   480,   488,   496,   503,   510,   519,   527,   536,
     544,   550,   556,   562,   570,   578
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "CHAR", "ID", "TYPE",
  "STRUCT", "IF", "ELSE", "WHILE", "RETURN", "DOT", "SEMI", "COMMA",
  "ASSIGN", "LT", "LE", "GT", "GE", "NE", "EQ", "PLUS", "MINUS", "MUL",
  "DIV", "AND", "OR", "NOT", "LP", "RP", "LB", "RB", "LC", "RC", "LINE",
  "ADD", "SUB", "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList",
  "Specifier", "StructSpecifier", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "Exp", "Args", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293
};
# endif

#define YYPACT_NINF -66

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-66)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      10,   -66,     5,    24,   -66,    10,    34,   -66,   -19,   -66,
     -66,    14,   -66,    33,   -10,    18,    10,    12,   -66,    52,
      56,    10,   -66,    52,    25,    10,   -66,    52,    46,    63,
     -66,   -66,    53,    78,     7,    65,    70,   -66,   -66,    59,
     -66,    10,   -66,   -66,   -66,   -66,    58,    71,    73,    93,
      93,    93,    93,   -66,     6,    78,    48,    93,   -66,    52,
     -66,    89,    93,    93,   129,   217,   217,   146,   -66,   -66,
     -66,   -66,    94,   -66,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,   217,   -66,
     -66,   166,    15,   183,   200,   -66,   -66,   -66,   217,    31,
      31,    31,    31,    31,    31,   217,   217,    31,    31,    31,
      31,   108,    93,   -66,   -66,    78,    78,   -66,   -66,    95,
     -66,    78,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    10,     0,     0,     2,     4,     0,    11,    13,     1,
       3,    14,     6,     0,     8,     0,    33,     0,     5,     0,
       0,    33,     7,     0,     0,    33,    17,     0,     0,    19,
      14,     9,     0,    24,    37,     0,    35,    12,    32,    20,
      16,     0,    15,    61,    62,    63,    60,     0,     0,     0,
       0,     0,     0,    27,     0,    24,     0,     0,    34,     0,
      18,     0,     0,     0,     0,    54,    55,     0,    21,    22,
      23,    25,     0,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    36,
      57,    65,     0,     0,     0,    28,    53,    59,    40,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    41,
      42,     0,     0,    39,    56,     0,     0,    58,    64,    29,
      31,     0,    30
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -66,   -66,    99,   -66,    87,     4,   -66,   -17,   -66,    68,
     -66,    96,    55,   -65,    32,   -66,    57,   -66,   -49,     2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,    13,    23,     7,    14,    15,    28,
      29,    53,    54,    55,    24,    25,    35,    36,    56,    92
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      64,    65,    66,    67,     6,    19,    34,    68,    88,     6,
      39,     8,    91,    93,    94,    16,   113,     1,     2,     1,
       2,    27,    20,    57,     9,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,    20,
      11,    69,    34,    26,    17,    27,   114,    18,    12,    71,
     119,   120,    21,    33,    81,    82,   122,    38,    30,    32,
      37,    72,    73,    91,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    40,    41,    58,
      87,    43,    44,    45,    46,    59,    42,    47,    61,    48,
      49,    20,    43,    44,    45,    46,    43,    44,    45,    46,
      97,    62,    50,    63,    10,   121,    31,    51,    52,    60,
      70,    22,    21,    50,   118,     0,    89,    50,    51,    52,
      90,    72,    51,    52,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,     0,     0,     0,
      87,   117,    72,    95,     0,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,     0,    72,
       0,    87,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,     0,     0,    96,    87,    72,
       0,   112,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,     0,    72,     0,    87,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,     0,    72,   115,    87,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,     0,
      72,   116,    87,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,     0,     0,     0,    87
};

static const yytype_int8 yycheck[] =
{
      49,    50,    51,    52,     0,    15,    23,     1,    57,     5,
      27,     6,    61,    62,    63,    34,     1,     7,     8,     7,
       8,    17,    32,    16,     0,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    32,
       6,    35,    59,    31,    30,    41,    31,    14,    14,     1,
     115,   116,    34,    21,    23,    24,   121,    25,     6,     3,
      35,    13,    14,   112,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    31,    15,    14,
      32,     3,     4,     5,     6,    15,    33,     9,    30,    11,
      12,    32,     3,     4,     5,     6,     3,     4,     5,     6,
       6,    30,    24,    30,     5,    10,    19,    29,    30,    41,
      55,    15,    34,    24,   112,    -1,    59,    24,    29,    30,
      31,    13,    29,    30,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    33,    13,    14,    -1,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,    13,
      -1,    32,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    31,    32,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    13,    -1,    32,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    13,    31,    32,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      13,    31,    32,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    40,    41,    42,    44,    45,     6,     0,
      41,     6,    14,    43,    46,    47,    34,    30,    14,    15,
      32,    34,    50,    44,    53,    54,    31,    44,    48,    49,
       6,    43,     3,    53,    46,    55,    56,    35,    53,    46,
      31,    15,    33,     3,     4,     5,     6,     9,    11,    12,
      24,    29,    30,    50,    51,    52,    57,    16,    14,    15,
      48,    30,    30,    30,    57,    57,    57,    57,     1,    35,
      51,     1,    13,    14,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    32,    57,    55,
      31,    57,    58,    57,    57,    14,    31,     6,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    15,     1,    31,    31,    31,    33,    58,    52,
      52,    10,    52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    41,    42,    42,    42,    43,    43,
      44,    44,    45,    45,    46,    46,    47,    47,    48,    48,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    53,    53,    54,    55,    55,    56,    56,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57,    58,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     1,     3,
       1,     1,     5,     2,     1,     4,     4,     3,     3,     1,
       2,     4,     4,     2,     0,     2,     2,     1,     3,     5,
       7,     5,     2,     0,     3,     1,     3,     1,     3,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  *++yylsp = yylloc;
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
| yyreduce -- do a reduction.  |
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 30 "pro_1.y"
    {
        program.show = addLine("Program", (yyloc).first_line);
        program.subNode.push_back(yyvsp[0]);
    }
#line 1478 "pro_1.tab.c"
    break;

  case 3:
#line 36 "pro_1.y"
    {
        Node temp; 
        temp.subNode.push_back(yyvsp[-1]);
        if (! yyvsp[0].subNode.empty())
            temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("ExtDefList", (yyloc).first_line);
        yyval = temp;
    }
#line 1491 "pro_1.tab.c"
    break;

  case 4:
#line 45 "pro_1.y"
    {
        Node temp; 
        temp.show = addLine("ExtDefList", (yyloc).first_line);
        yyval = temp;
    }
#line 1501 "pro_1.tab.c"
    break;

  case 5:
#line 52 "pro_1.y"
    {
        Node temp;
        Node semi;
        semi.show = "SEMI";
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(semi);
        temp.show = addLine("ExtDef", (yyloc).first_line);
        yyval = temp;
    }
#line 1516 "pro_1.tab.c"
    break;

  case 6:
#line 62 "pro_1.y"
    {
        Node temp;
        Node semi;
        semi.show = "SEMI";
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(semi);
        temp.show = addLine("ExtDef", (yyloc).first_line);
        yyval = temp;
    }
#line 1530 "pro_1.tab.c"
    break;

  case 7:
#line 71 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("ExtDef", (yyloc).first_line);
        yyval = temp;
    }
#line 1543 "pro_1.tab.c"
    break;

  case 8:
#line 81 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("ExtDecList", (yyloc).first_line);
        yyval = temp;
    }
#line 1554 "pro_1.tab.c"
    break;

  case 9:
#line 87 "pro_1.y"
    {
        Node temp;
        Node comma;
        temp.subNode.push_back(yyvsp[-2]);
        comma.show = "COMMA";
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("ExtDecList", (yyloc).first_line);
        yyval = temp;
    }
#line 1568 "pro_1.tab.c"
    break;

  case 10:
#line 98 "pro_1.y"
    {
        Node temp;
        Node type;
        type.show = "TYPE: "+yyvsp[0].show;
        temp.subNode.push_back(type);
        temp.show = addLine("Specifier", (yyloc).first_line);
        yyval = temp;
    }
#line 1581 "pro_1.tab.c"
    break;

  case 11:
#line 106 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Specifier", (yyloc).first_line);
        yyval = temp;
    }
#line 1592 "pro_1.tab.c"
    break;

  case 12:
#line 114 "pro_1.y"
    {
        Node temp, struc, id, lc, rc;
        struc.show = "STRUCT";
        id.show = "ID: "+yyvsp[-3].show;
        lc.show = "LC";
        rc.show = "RC";
        temp.subNode.push_back(struc);
        temp.subNode.push_back(id);
        temp.subNode.push_back(lc);
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(rc);
        temp.show = addLine("StructSpecifier", (yyloc).first_line);
        yyval = temp;
    }
#line 1611 "pro_1.tab.c"
    break;

  case 13:
#line 128 "pro_1.y"
    {
        Node temp, struc, id;
        struc.show = "STRUCT";
        id.show = "ID: "+yyvsp[0].show;
        temp.subNode.push_back(struc);
        temp.subNode.push_back(id);
        temp.show = addLine("StructSpecifier", (yyloc).first_line);
        yyval = temp;
    }
#line 1625 "pro_1.tab.c"
    break;

  case 14:
#line 139 "pro_1.y"
    {
        Node temp, id;
        id.show = "ID: "+yyvsp[0].show;
        temp.subNode.push_back(id);
        temp.show = addLine("VarDec", (yyloc).first_line);
        yyval = temp;
    }
#line 1637 "pro_1.tab.c"
    break;

  case 15:
#line 146 "pro_1.y"
    {
        Node temp, lb, i, rb;
        lb.show = "LB";
        rb.show = "RB";
        i.show = "INT: "+yyvsp[-1].show;
        temp.subNode.push_back(yyvsp[-3]);
        temp.subNode.push_back(lb);
        temp.subNode.push_back(i);
        temp.subNode.push_back(rb);
        temp.show = addLine("VarDec", (yyloc).first_line);
        yyval = temp;
    }
#line 1654 "pro_1.tab.c"
    break;

  case 16:
#line 160 "pro_1.y"
    {
        Node temp, id, lp, rp;
        id.show = "ID: "+yyvsp[-3].show;
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(id);
        temp.subNode.push_back(lp);
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(rp);
        temp.show = addLine("FunDec", (yyloc).first_line);
        yyval = temp;
    }
#line 1671 "pro_1.tab.c"
    break;

  case 17:
#line 172 "pro_1.y"
    {
        Node temp, id, lp, rp;
        id.show = "ID: "+yyvsp[-2].show;
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(id);
        temp.subNode.push_back(lp);
        temp.subNode.push_back(rp);
        temp.show = addLine("FunDec", (yyloc).first_line);
        yyval = temp;
    }
#line 1687 "pro_1.tab.c"
    break;

  case 18:
#line 185 "pro_1.y"
    {
        Node temp, comma;
        comma.show ="COMMA";
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(comma);
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("VarList", (yyloc).first_line);
        yyval = temp;
    }
#line 1701 "pro_1.tab.c"
    break;

  case 19:
#line 194 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("VarList", (yyloc).first_line);
        yyval = temp;
    }
#line 1712 "pro_1.tab.c"
    break;

  case 20:
#line 202 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("ParamDec", (yyloc).first_line);
        yyval = temp;
    }
#line 1724 "pro_1.tab.c"
    break;

  case 21:
#line 211 "pro_1.y"
    {
        string e = "Error type B at Line "+to_string((yyloc).first_line)+": Missing semicolon \'}\'";
        errList.push_back(e);
    }
#line 1733 "pro_1.tab.c"
    break;

  case 22:
#line 216 "pro_1.y"
    {
        Node temp, lc, rc;
        lc.show = "LC";
        rc.show = "RC";
        temp.subNode.push_back(lc);
        if (! yyvsp[-2].subNode.empty())
            temp.subNode.push_back(yyvsp[-2]);
        if (! yyvsp[-1].subNode.empty())
            temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(rc);
        temp.show = addLine("CompSt", (yyloc).first_line);
        yyval = temp;
    }
#line 1751 "pro_1.tab.c"
    break;

  case 23:
#line 231 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-1]);
        if (! yyvsp[0].subNode.empty())
            temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("StmtList", (yyloc).first_line);
        yyval = temp;
    }
#line 1764 "pro_1.tab.c"
    break;

  case 24:
#line 240 "pro_1.y"
    {
        Node temp;
        temp.show = addLine("StmtList", (yyloc).first_line);
        yyval = temp;
    }
#line 1774 "pro_1.tab.c"
    break;

  case 25:
#line 247 "pro_1.y"
    {
        string e = "Error type B at Line "+to_string((yyloc).first_line)+": Missing semicolon \';\'";
        errList.push_back(e);
    }
#line 1783 "pro_1.tab.c"
    break;

  case 26:
#line 252 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(createNode("SEMI"));
        temp.show = addLine("Stmt", (yyloc).first_line);
        yyval = temp;
    }
#line 1795 "pro_1.tab.c"
    break;

  case 27:
#line 259 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Stmt", (yyloc).first_line);
        yyval = temp;
    }
#line 1806 "pro_1.tab.c"
    break;

  case 28:
#line 265 "pro_1.y"
    {
        Node temp, ret, semi;
        ret.show = "RETURN";
        semi.show = "SEMI";
        temp.subNode.push_back(ret);
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(semi);
        temp.show = addLine("Stmt", (yyloc).first_line);
        yyval = temp;
    }
#line 1821 "pro_1.tab.c"
    break;

  case 29:
#line 275 "pro_1.y"
    {
        Node temp, i, lp, rp;
        i.show = "IF";
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(i);
        temp.subNode.push_back(lp);
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(rp);
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Stmt", (yyloc).first_line);
        yyval = temp;
    }
#line 1839 "pro_1.tab.c"
    break;

  case 30:
#line 288 "pro_1.y"
    {
        Node temp, i, lp, rp, e;
        i.show = "IF";
        lp.show = "LP";
        rp.show = "RP";
        e.show = "ELSE";
        temp.subNode.push_back(i);
        temp.subNode.push_back(lp);
        temp.subNode.push_back(yyvsp[-4]);
        temp.subNode.push_back(rp);
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(e);
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Stmt", (yyloc).first_line);
        yyval = temp;
    }
#line 1860 "pro_1.tab.c"
    break;

  case 31:
#line 304 "pro_1.y"
    {
        Node temp, w, lp, rp;
        w.show = "WHILE";
        lp.show = "LP";
        rp.show = "RP";
        temp.subNode.push_back(w);
        temp.subNode.push_back(lp);
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(rp);
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Stmt", (yyloc).first_line);
        yyval = temp;
    }
#line 1878 "pro_1.tab.c"
    break;

  case 32:
#line 319 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-1]);
        if (! yyvsp[0].subNode.empty())
            temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("DefList", (yyloc).first_line);
        yyval = temp;
    }
#line 1891 "pro_1.tab.c"
    break;

  case 33:
#line 328 "pro_1.y"
    {
        Node temp;
        temp.show = addLine("DefList", (yyloc).first_line);
        yyval = temp;
    }
#line 1901 "pro_1.tab.c"
    break;

  case 34:
#line 335 "pro_1.y"
    {
        Node temp, semi;
        semi.show = "SEMI";
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(semi);
        temp.show = addLine("Def", (yyloc).first_line);
        yyval = temp;
    }
#line 1915 "pro_1.tab.c"
    break;

  case 35:
#line 346 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("DecList", (yyloc).first_line);
        yyval = temp;
    }
#line 1926 "pro_1.tab.c"
    break;

  case 36:
#line 352 "pro_1.y"
    {
        Node temp, comma;
        comma.show= "COMMA";
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(comma);
        temp.subNode.push_back(yyvsp[0]);
        yyval = temp;
    }
#line 1939 "pro_1.tab.c"
    break;

  case 37:
#line 362 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Dec", (yyloc).first_line);
        yyval = temp;
    }
#line 1950 "pro_1.tab.c"
    break;

  case 38:
#line 368 "pro_1.y"
    {
        Node temp, assign;
        assign.show = "ASSIGN";
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(assign);
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Dec", (yyloc).first_line);
        yyval = temp;
    }
#line 1964 "pro_1.tab.c"
    break;

  case 39:
#line 379 "pro_1.y"
    {
        string e = "Error type B at Line "+to_string((yyloc).first_line)+": Missing semicolon \')\'";
        errList.push_back(e);
    }
#line 1973 "pro_1.tab.c"
    break;

  case 40:
#line 384 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("ASSIGN"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 1986 "pro_1.tab.c"
    break;

  case 41:
#line 392 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("AND"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 1999 "pro_1.tab.c"
    break;

  case 42:
#line 400 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("OR"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2012 "pro_1.tab.c"
    break;

  case 43:
#line 408 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("LT"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2025 "pro_1.tab.c"
    break;

  case 44:
#line 416 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("LE"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2038 "pro_1.tab.c"
    break;

  case 45:
#line 424 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("GT"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2051 "pro_1.tab.c"
    break;

  case 46:
#line 432 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("GE"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2064 "pro_1.tab.c"
    break;

  case 47:
#line 440 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("NE"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2077 "pro_1.tab.c"
    break;

  case 48:
#line 448 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("EQ"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2090 "pro_1.tab.c"
    break;

  case 49:
#line 456 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("PLUS"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2103 "pro_1.tab.c"
    break;

  case 50:
#line 464 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("MINUS"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2116 "pro_1.tab.c"
    break;

  case 51:
#line 472 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("MUL"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2129 "pro_1.tab.c"
    break;

  case 52:
#line 480 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("DIV"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2142 "pro_1.tab.c"
    break;

  case 53:
#line 488 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("LP"));
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(createNode("RP"));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2155 "pro_1.tab.c"
    break;

  case 54:
#line 496 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("MINUS"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2167 "pro_1.tab.c"
    break;

  case 55:
#line 503 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("NOT"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2179 "pro_1.tab.c"
    break;

  case 56:
#line 510 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("ID: "+yyvsp[-3].show));
        temp.subNode.push_back(createNode("LP"));
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(createNode("RP"));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2193 "pro_1.tab.c"
    break;

  case 57:
#line 519 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("ID: "+yyvsp[-2].show));
        temp.subNode.push_back(createNode("LP"));
        temp.subNode.push_back(createNode("RP"));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2206 "pro_1.tab.c"
    break;

  case 58:
#line 527 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-3]);
        temp.subNode.push_back(createNode("LB"));
        temp.subNode.push_back(yyvsp[-1]);
        temp.subNode.push_back(createNode("RB"));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2220 "pro_1.tab.c"
    break;

  case 59:
#line 536 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("DOT"));
        temp.subNode.push_back(createNode("ID: "+yyvsp[0].show));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2233 "pro_1.tab.c"
    break;

  case 60:
#line 544 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("ID: "+yyvsp[0].show));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2244 "pro_1.tab.c"
    break;

  case 61:
#line 550 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("INT: "+yyvsp[0].show));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2255 "pro_1.tab.c"
    break;

  case 62:
#line 556 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("FLOAT: "+yyvsp[0].show));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2266 "pro_1.tab.c"
    break;

  case 63:
#line 562 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(createNode("CHAR: "+yyvsp[0].show));
        temp.show = addLine("Exp", (yyloc).first_line);
        yyval = temp;
    }
#line 2277 "pro_1.tab.c"
    break;

  case 64:
#line 570 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[-2]);
        temp.subNode.push_back(createNode("COMMA"));
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Args", (yyloc).first_line);
        yyval = temp;
    }
#line 2290 "pro_1.tab.c"
    break;

  case 65:
#line 578 "pro_1.y"
    {
        Node temp;
        temp.subNode.push_back(yyvsp[0]);
        temp.show = addLine("Args", (yyloc).first_line);
        yyval = temp;
    }
#line 2301 "pro_1.tab.c"
    break;


#line 2305 "pro_1.tab.c"

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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 585 "pro_1.y"

 
 
void yyerror(const char *s){
    fprintf(stderr, "%s\n", s);
}

void output(Node node, int num){
    int size = node.subNode.size();
    string tab(num,' ');
    cout<<tab<<node.show<<endl; 
    for (int i=0;i<size;i++){
        output(node.subNode[i],num+2);
    }
      
}

string addLine(string s, int line){
    return s+" ("+to_string(line)+")";
}

int main(){
    yyparse();
    // cout<<endl;
    output(program,0);
}

