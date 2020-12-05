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
#line 1 "parser.y" /* yacc.c:339  */

	//PROLOGOS
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include "symtable.h"
	#include "tcode.h"

	int yyerror(const char* yaccProvidedMessage);
	int yylex(void);

	extern FILE* yyin;
	extern FILE* yyout;
	extern char* yytext;
	extern int yylineno;

	int scope = 0;
	int loop_depth = 0; //elegxei mesa se poses epanaliptikes methodous eimaste
	char *name;	//used for id and func names.
	int in_func = 0; //used to check if i am in a function.
	Type type;
	Node_T node;
	Arg_T arg;

	char anonymous[100];
	int uknownfunc = 0;
	char *fname;

	expr *tmpexpr = NULL;
	int funcQuadNo = 0;

	int whileQuadNo = 0;
	int specialflag = 0; // gia ta break kai continue
	SymTable_T oSymTable;

#line 103 "parser.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    ID = 258,
    STRING = 259,
    INTEGER = 260,
    TRUE = 261,
    FALSE = 262,
    REAL = 263,
    WHILE = 264,
    FOR = 265,
    IF = 266,
    ELSE = 267,
    FUNCTION = 268,
    RETURN = 269,
    BREAK = 270,
    CONTINUE = 271,
    AND = 272,
    OR = 273,
    NOT = 274,
    NIL = 275,
    PLUS = 276,
    MINUS = 277,
    UMINUS = 278,
    ASSERTION = 279,
    MULT = 280,
    MOD = 281,
    DIV = 282,
    EQUALS = 283,
    DIFF = 284,
    PLUS1 = 285,
    MINUS1 = 286,
    GREATER_OR_EQUAL = 287,
    LESS_OR_EQUAL = 288,
    GREATER_THAN = 289,
    LESS_THAN = 290,
    LEFT_SQUARE_BRACKET = 291,
    RIGHT_SQUARE_BRACKET = 292,
    LEFT_BRACKET = 293,
    RIGHT_BRACKET = 294,
    LEFT_PARENTHESIS = 295,
    RIGHT_PARENTHESIS = 296,
    COMMA = 297,
    SEMICOLON = 298,
    COLON = 299,
    DOUBLE_COLON = 300,
    DOT = 301,
    DOUBLE_DOT = 302,
    LOCAL = 303
  };
#endif
/* Tokens.  */
#define ID 258
#define STRING 259
#define INTEGER 260
#define TRUE 261
#define FALSE 262
#define REAL 263
#define WHILE 264
#define FOR 265
#define IF 266
#define ELSE 267
#define FUNCTION 268
#define RETURN 269
#define BREAK 270
#define CONTINUE 271
#define AND 272
#define OR 273
#define NOT 274
#define NIL 275
#define PLUS 276
#define MINUS 277
#define UMINUS 278
#define ASSERTION 279
#define MULT 280
#define MOD 281
#define DIV 282
#define EQUALS 283
#define DIFF 284
#define PLUS1 285
#define MINUS1 286
#define GREATER_OR_EQUAL 287
#define LESS_OR_EQUAL 288
#define GREATER_THAN 289
#define LESS_THAN 290
#define LEFT_SQUARE_BRACKET 291
#define RIGHT_SQUARE_BRACKET 292
#define LEFT_BRACKET 293
#define RIGHT_BRACKET 294
#define LEFT_PARENTHESIS 295
#define RIGHT_PARENTHESIS 296
#define COMMA 297
#define SEMICOLON 298
#define COLON 299
#define DOUBLE_COLON 300
#define DOT 301
#define DOUBLE_DOT 302
#define LOCAL 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 43 "parser.y" /* yacc.c:355  */

	char* strVal;
	int intVal;
	double doubleVal;
	struct forval *forVal;
	struct stmt_t *stmtVal;
	struct expr *exprVal;
	struct node *symVal; // ST node
	//struct method_t *methodVal; //maybe later

#line 250 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 267 "parser.c" /* yacc.c:358  */

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
#define YYLAST   597

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  189

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    86,    86,    89,    94,    95,    96,    97,   106,   120,
     135,   136,   137,   140,   153,   156,   160,   164,   168,   172,
     176,   180,   184,   188,   192,   196,   200,   204,   208,   212,
     218,   222,   229,   235,   253,   272,   290,   309,   314,   314,
     336,   338,   340,   344,   348,   351,   408,   436,   446,   452,
     456,   463,   464,   467,   482,   514,   532,   535,   540,   547,
     557,   564,   567,   572,   575,   601,   606,   613,   620,   626,
     630,   635,   635,   645,   650,   667,   690,   704,   722,   729,
     737,   741,   745,   749,   753,   757,   763,   766,   785,   788,
     789,   792,   798,   805,   812,   818,   824,   831,   855,   857,
     859,   859,   868,   868,   892,   896
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "STRING", "INTEGER", "TRUE",
  "FALSE", "REAL", "WHILE", "FOR", "IF", "ELSE", "FUNCTION", "RETURN",
  "BREAK", "CONTINUE", "AND", "OR", "NOT", "NIL", "PLUS", "MINUS",
  "UMINUS", "ASSERTION", "MULT", "MOD", "DIV", "EQUALS", "DIFF", "PLUS1",
  "MINUS1", "GREATER_OR_EQUAL", "LESS_OR_EQUAL", "GREATER_THAN",
  "LESS_THAN", "LEFT_SQUARE_BRACKET", "RIGHT_SQUARE_BRACKET",
  "LEFT_BRACKET", "RIGHT_BRACKET", "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS",
  "COMMA", "SEMICOLON", "COLON", "DOUBLE_COLON", "DOT", "DOUBLE_DOT",
  "LOCAL", "$accept", "program", "stmt", "stmts", "expr", "term",
  "assignexpr", "$@1", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "exprs", "objectdef", "index",
  "indexed", "indexedelem", "indexedelems", "block", "$@2", "blstmts",
  "funcdef", "funcname", "funprefix", "funcargs", "funcbody", "const",
  "idlist", "id", "ids", "ifstmt", "ifprefix", "elseprefix", "whilestart",
  "whilecond", "whilestmt", "N", "M", "forprefix", "$@3", "forstmt", "$@4",
  "returnstmt", YY_NULLPTR
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
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -168

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-168)))

#define YYTABLE_NINF -39

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-39)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -168,    10,   150,  -168,  -168,  -168,  -168,  -168,  -168,  -168,
    -168,  -168,   -24,    27,     1,   -19,    -5,   288,  -168,   288,
       8,     8,   196,  -168,   242,  -168,    36,    39,  -168,   313,
    -168,  -168,  -168,    21,  -168,   -11,  -168,  -168,  -168,     3,
    -168,  -168,   150,    15,  -168,  -168,  -168,  -168,    19,   288,
    -168,  -168,  -168,   332,  -168,  -168,  -168,  -168,    37,    18,
     -11,    18,   288,   370,  -168,    25,  -168,    24,  -168,   389,
      28,  -168,  -168,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,  -168,  -168,  -168,   288,
     288,    67,    81,    61,  -168,  -168,  -168,   288,   288,    85,
      91,    55,    84,   288,   150,   288,   288,   410,  -168,    56,
      90,   288,  -168,  -168,    60,  -168,   150,    64,  -168,    59,
     547,   532,    65,    65,  -168,  -168,  -168,   562,   562,   106,
     106,   106,   106,   471,    63,  -168,    70,   288,   492,    72,
    -168,  -168,    79,    58,  -168,  -168,  -168,   150,   431,  -168,
      80,    62,  -168,    59,   288,   370,    24,  -168,   288,  -168,
    -168,   288,   513,  -168,  -168,  -168,    91,  -168,  -168,  -168,
    -168,  -168,   452,  -168,  -168,    88,    89,    58,   150,   288,
    -168,  -168,  -168,  -168,  -168,   351,  -168,  -168,  -168
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      14,     0,     2,     1,    45,    82,    80,    84,    85,    81,
      95,   100,     0,    76,     0,     0,     0,     0,    83,     0,
       0,     0,    61,    71,     0,    12,     0,     0,    13,     0,
      29,    15,    37,    40,    48,    41,    42,    10,    11,     0,
      44,     4,     0,     0,     5,    98,     6,     7,     0,     0,
      75,    77,   104,     0,     8,     9,    32,    31,     0,    33,
       0,    35,     0,    63,    65,     0,    66,    70,    14,     0,
       0,    47,    46,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,    34,    36,     0,
      61,     0,     0,     0,    54,    56,    57,     0,    61,     0,
      88,     0,    91,     0,     0,    61,    61,     0,   105,     0,
       0,     0,    60,    64,     0,    67,    73,     0,    30,    43,
      27,    28,    16,    17,    18,    20,    19,    22,    21,    24,
      26,    23,    25,     0,     0,    49,     0,     0,     0,     0,
      51,    87,     0,    90,    79,    74,    94,     0,     0,    97,
       0,     0,    93,     0,     0,    63,    70,    72,    61,    50,
      58,    61,    39,    52,    53,    78,    88,    86,    92,    96,
      98,    99,     0,    62,    69,     0,     0,    90,     0,     0,
      68,    55,    59,    89,   102,     0,    98,   101,   103
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -168,  -168,   -41,    68,    -2,  -168,  -168,  -168,  -168,    -7,
    -168,     7,  -168,  -168,  -168,   -72,   -29,  -168,  -168,  -168,
      29,   -14,    43,  -168,  -168,   -22,  -168,  -168,  -168,  -168,
    -168,  -168,   -20,   -30,  -168,  -168,  -168,  -168,  -168,  -168,
    -167,  -168,  -168,  -168,  -168,  -168,  -168
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    28,     2,    63,    30,    31,    93,    32,    33,
      34,    35,    94,    95,    96,    64,   112,    36,    65,    66,
      67,   115,    37,    68,   117,    38,    51,    39,   101,   145,
      40,   142,   143,   167,    41,    42,   147,    43,   104,    44,
     105,   179,    45,    48,    46,   186,    47
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,   102,    70,   178,     4,     5,     6,     7,     8,     9,
       3,     4,    53,    59,    61,    56,    49,    57,   134,   188,
      17,    18,    69,    19,    54,    97,   139,    60,    60,    98,
      50,    20,    21,   150,   151,    99,   109,    22,    55,    71,
      29,    24,    72,   100,    52,   -38,    26,   107,    58,    27,
      13,    87,    88,    26,    89,   103,    27,    89,    90,   106,
     110,    90,   113,   149,    91,    92,   114,    91,    92,   119,
     135,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   136,   137,   175,   133,   140,   176,
      77,    78,    79,    23,   141,   138,   146,   153,    62,   158,
     166,   148,    29,   157,   160,   171,   168,    73,    74,   155,
     161,    75,    76,   164,    29,    77,    78,    79,    80,    81,
     165,   170,    82,    83,    84,    85,   173,    75,    76,   181,
     182,    77,    78,    79,   154,   162,   116,   184,   -39,   -39,
     -39,   -39,   174,   156,   144,    29,   177,   183,     0,     0,
       0,     0,   172,     4,     5,     6,     7,     8,     9,    10,
      11,    12,     0,    13,    14,    15,    16,     0,     0,    17,
      18,     0,    19,     0,     0,     0,    29,   185,     0,     0,
      20,    21,     0,     0,     0,     0,    22,     0,    23,     0,
      24,     0,     0,    25,     0,    26,     0,     0,    27,     4,
       5,     6,     7,     8,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    17,    18,     0,    19,     0,
       0,     0,     0,     0,     0,     0,    20,    21,     0,     0,
       0,     0,    22,     0,    62,     0,    24,     0,     0,     0,
       0,    26,     0,     0,    27,     4,     5,     6,     7,     8,
       9,     0,     0,     0,     0,    13,     0,     0,     0,     0,
       0,    17,    18,     0,    19,     0,     0,     0,     0,     0,
       0,     0,    20,    21,     0,     0,     0,     0,    22,     0,
       0,     0,    24,     0,     0,     0,     0,    26,     0,     0,
      27,     4,     5,     6,     7,     8,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    18,     0,
      19,     0,     0,     0,     0,     0,     0,     0,    20,    21,
       0,     0,     0,     0,    22,     0,     0,     0,    24,     0,
      73,    74,     0,    26,    75,    76,    27,     0,    77,    78,
      79,    80,    81,     0,     0,    82,    83,    84,    85,    73,
      74,     0,     0,    75,    76,     0,    86,    77,    78,    79,
      80,    81,     0,     0,    82,    83,    84,    85,    73,    74,
       0,     0,    75,    76,     0,   108,    77,    78,    79,    80,
      81,     0,     0,    82,    83,    84,    85,    73,    74,     0,
       0,    75,    76,     0,   187,    77,    78,    79,    80,    81,
       0,     0,    82,    83,    84,    85,    73,    74,     0,     0,
      75,    76,   111,     0,    77,    78,    79,    80,    81,     0,
       0,    82,    83,    84,    85,     0,     0,    73,    74,     0,
     118,    75,    76,     0,     0,    77,    78,    79,    80,    81,
       0,     0,    82,    83,    84,    85,     0,     0,    73,    74,
       0,   152,    75,    76,     0,     0,    77,    78,    79,    80,
      81,     0,     0,    82,    83,    84,    85,     0,     0,    73,
      74,     0,   169,    75,    76,     0,     0,    77,    78,    79,
      80,    81,     0,     0,    82,    83,    84,    85,    73,    74,
       0,   180,    75,    76,     0,     0,    77,    78,    79,    80,
      81,     0,     0,    82,    83,    84,    85,     0,   159,    73,
      74,     0,     0,    75,    76,     0,     0,    77,    78,    79,
      80,    81,     0,     0,    82,    83,    84,    85,     0,   163,
      73,    74,     0,     0,    75,    76,     0,     0,    77,    78,
      79,    80,    81,     0,     0,    82,    83,    84,    85,    73,
       0,     0,     0,    75,    76,     0,     0,    77,    78,    79,
      80,    81,     0,     0,    82,    83,    84,    85,    75,    76,
       0,     0,    77,    78,    79,    80,    81,     0,     0,    82,
      83,    84,    85,    75,    76,     0,     0,    77,    78,    79,
     -39,   -39,     0,     0,    82,    83,    84,    85
};

static const yytype_int16 yycheck[] =
{
       2,    42,    24,   170,     3,     4,     5,     6,     7,     8,
       0,     3,    14,    20,    21,    17,    40,    19,    90,   186,
      19,    20,    24,    22,    43,    36,    98,    20,    21,    40,
       3,    30,    31,   105,   106,    46,    58,    36,    43,     3,
      42,    40,     3,    40,    43,    24,    45,    49,    40,    48,
      13,    30,    31,    45,    36,    40,    48,    36,    40,    40,
      62,    40,    37,   104,    46,    47,    42,    46,    47,    41,
       3,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,     3,    24,   158,    89,     3,   161,
      25,    26,    27,    38,     3,    97,    12,    41,    38,    40,
      42,   103,   104,    39,    41,    43,   147,    17,    18,   111,
      40,    21,    22,    41,   116,    25,    26,    27,    28,    29,
      41,    41,    32,    33,    34,    35,   155,    21,    22,    41,
      41,    25,    26,    27,    44,   137,    68,   178,    32,    33,
      34,    35,   156,   114,   101,   147,   166,   177,    -1,    -1,
      -1,    -1,   154,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    13,    14,    15,    16,    -1,    -1,    19,
      20,    -1,    22,    -1,    -1,    -1,   178,   179,    -1,    -1,
      30,    31,    -1,    -1,    -1,    -1,    36,    -1,    38,    -1,
      40,    -1,    -1,    43,    -1,    45,    -1,    -1,    48,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    20,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      -1,    -1,    36,    -1,    38,    -1,    40,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,     3,     4,     5,     6,     7,
       8,    -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,    -1,
      -1,    19,    20,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    -1,    40,    -1,
      17,    18,    -1,    45,    21,    22,    48,    -1,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    17,
      18,    -1,    -1,    21,    22,    -1,    43,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    17,    18,
      -1,    -1,    21,    22,    -1,    43,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    17,    18,    -1,
      -1,    21,    22,    -1,    43,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    17,    18,    -1,    -1,
      21,    22,    42,    -1,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    -1,    -1,    17,    18,    -1,
      41,    21,    22,    -1,    -1,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    -1,    -1,    17,    18,
      -1,    41,    21,    22,    -1,    -1,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    -1,    -1,    17,
      18,    -1,    41,    21,    22,    -1,    -1,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    17,    18,
      -1,    39,    21,    22,    -1,    -1,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    -1,    37,    17,
      18,    -1,    -1,    21,    22,    -1,    -1,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    -1,    37,
      17,    18,    -1,    -1,    21,    22,    -1,    -1,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    17,
      -1,    -1,    -1,    21,    22,    -1,    -1,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    21,    22,
      -1,    -1,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    21,    22,    -1,    -1,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    52,     0,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    13,    14,    15,    16,    19,    20,    22,
      30,    31,    36,    38,    40,    43,    45,    48,    51,    53,
      54,    55,    57,    58,    59,    60,    66,    71,    74,    76,
      79,    83,    84,    86,    88,    91,    93,    95,    92,    40,
       3,    75,    43,    53,    43,    43,    53,    53,    40,    58,
      60,    58,    38,    53,    64,    67,    68,    69,    72,    53,
      74,     3,     3,    17,    18,    21,    22,    25,    26,    27,
      28,    29,    32,    33,    34,    35,    43,    30,    31,    36,
      40,    46,    47,    56,    61,    62,    63,    36,    40,    46,
      40,    77,    51,    40,    87,    89,    40,    53,    43,    74,
      53,    42,    65,    37,    42,    70,    52,    73,    41,    41,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    64,     3,     3,    24,    53,    64,
       3,     3,    80,    81,    71,    78,    12,    85,    53,    51,
      64,    64,    41,    41,    44,    53,    69,    39,    40,    37,
      41,    40,    53,    37,    41,    41,    42,    82,    51,    41,
      41,    43,    53,    65,    70,    64,    64,    81,    89,    90,
      39,    41,    41,    82,    51,    53,    94,    43,    89
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    54,    54,    54,    54,    54,    56,    55,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    62,    63,
      64,    64,    65,    65,    66,    67,    67,    68,    69,    70,
      70,    72,    71,    73,    74,    75,    75,    76,    77,    78,
      79,    79,    79,    79,    79,    79,    80,    81,    81,    82,
      82,    83,    83,    84,    85,    86,    87,    88,    89,    90,
      92,    91,    94,    93,    95,    95
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     2,     0,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     0,     4,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       2,     0,     3,     0,     3,     1,     1,     2,     5,     3,
       0,     0,     4,     1,     3,     1,     0,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     0,     3,
       0,     2,     4,     4,     1,     1,     3,     3,     0,     0,
       0,     8,     0,     8,     2,     3
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
#line 86 "parser.y" /* yacc.c:1646  */
    {printf("Start Program\n");}
#line 1565 "parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 89 "parser.y" /* yacc.c:1646  */
    {
					(yyval.stmtVal) = newstmt(); //$$ = malloc(sizeof(stmt_t));
					resettemp(); // midenizw ta temporaries
					printf("stmt -> expr;\n\n");
				}
#line 1575 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 94 "parser.y" /* yacc.c:1646  */
    {(yyval.stmtVal) = (yyvsp[0].stmtVal); printf("stmt -> ifstmt\n");}
#line 1581 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 95 "parser.y" /* yacc.c:1646  */
    {(yyval.stmtVal) = (yyvsp[0].stmtVal); printf("stmt -> whilestmt\n");}
#line 1587 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 96 "parser.y" /* yacc.c:1646  */
    {(yyval.stmtVal) = (yyvsp[0].stmtVal); printf("stmt -> forstmt\n");}
#line 1593 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 97 "parser.y" /* yacc.c:1646  */
    {
				(yyval.stmtVal) = newstmt();
				printf("stmt -> returnstmt\n");
				if(in_func == 0) {
					printf("\033[0;31m");
					printf("Error: return out of function at line %d\n",yylineno);
					printf("\033[0m");
				}
			}
#line 1607 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 106 "parser.y" /* yacc.c:1646  */
    {
				if(loop_depth == 0) {
					printf("\033[0;31m");
					printf("Error: break out of loop at line %d\n",yylineno);
					printf("\033[0m");
				}else{
					specialflag = 1;
					(yyval.stmtVal) = newstmt();
					(yyval.stmtVal)->next = initList(nextquadlabel());
					(yyval.stmtVal)->next->isbreak = 1;
					emit(jump,NULL,NULL,NULL,0,yylineno);
				}
				printf("stmt -> break;\n\n");
			}
#line 1626 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 120 "parser.y" /* yacc.c:1646  */
    {
					(yyval.stmtVal) = newstmt();
					if(loop_depth == 0) {
						printf("\033[0;31m");
						printf("Error: continue out of loop at line %d\n",yylineno);
						printf("\033[0m");
					}else{
						(yyval.stmtVal) = newstmt();
						specialflag = 1;
						(yyval.stmtVal)->next = initList(nextquadlabel());
						(yyval.stmtVal)->next->isbreak = 0;
						emit(jump,NULL,NULL,NULL,0,yylineno);
					}
				printf("stmt -> continue;\n\n");
			}
#line 1646 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 135 "parser.y" /* yacc.c:1646  */
    {(yyval.stmtVal) = (yyvsp[0].stmtVal); printf("stmt -> block\n");}
#line 1652 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 136 "parser.y" /* yacc.c:1646  */
    {(yyval.stmtVal) = newstmt(); printf("stmt -> funcdef\n");}
#line 1658 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 137 "parser.y" /* yacc.c:1646  */
    {(yyval.stmtVal) = newstmt(); printf("stmt -> ;\n\n");}
#line 1664 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 140 "parser.y" /* yacc.c:1646  */
    {
				if((yyvsp[-1].stmtVal) && (yyvsp[0].stmtVal) && specialflag){
					(yyval.stmtVal)->next = mergeLists((yyvsp[-1].stmtVal)->next,(yyvsp[0].stmtVal)->next);
					//$$->contlist = mergeLists($1->contlist,$2->contlist,0);
				}else if(!(yyvsp[-1].stmtVal)) {
					(yyval.stmtVal) = (yyvsp[0].stmtVal);
				}
				else {
					(yyval.stmtVal) = (yyvsp[-1].stmtVal);
				}
				//specialflag = 0;
				printf("stmts -> stmt stmts\n");
				printf("stmts -> stmt stmts\n");}
#line 1682 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 153 "parser.y" /* yacc.c:1646  */
    {(yyval.stmtVal) = newstmt(); printf("stmts -> empty \n");}
#line 1688 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 156 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[0].exprVal);
				printf("expr -> assignexpr\n");
			}
#line 1697 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 160 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = arith_emit(add,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr + expr, %.2lf ADD %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);	
			}
#line 1706 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 164 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = arith_emit(sub,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr - expr, %.2lf SUB %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);				
			}
#line 1715 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 168 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = arith_emit(mul,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr * expr, %.2lf MULT %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);				
			}
#line 1724 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 172 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = arith_emit(divide,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr / expr, %.2lf DIV %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);			
			}
#line 1733 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 176 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = arith_emit(mod,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr mod expr, %.2lf MOD %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);		
			}
#line 1742 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 180 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = relop_emit(if_noteq,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr != expr, %.2lf != %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);				
			}
#line 1751 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 184 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = relop_emit(if_eq,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr == expr, %.2lf == %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);			
			}
#line 1760 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 188 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = relop_emit(if_greater,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr > expr, %.2lf > %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);	
			}
#line 1769 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 192 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = relop_emit(if_greatereq,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr >= expr, %.2lf >= %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);	
			}
#line 1778 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 196 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = relop_emit(if_less,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr < expr, %.2lf < %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);	
			}
#line 1787 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 200 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = relop_emit(if_lesseq,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr <= expr, %.2lf <= %.2lf\n",(yyvsp[-2].exprVal)->numConst,(yyvsp[0].exprVal)->numConst);	
			}
#line 1796 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 204 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = boolop_emit(and,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr and expr, %u AND %u\n",(yyvsp[-2].exprVal)->boolConst,(yyvsp[0].exprVal)->boolConst);	
			}
#line 1805 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 208 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = boolop_emit(or,(yyvsp[-2].exprVal),(yyvsp[0].exprVal),yylineno,scope);
				printf("expr -> expr or expr, %u OR %u\n",(yyvsp[-2].exprVal)->boolConst,(yyvsp[0].exprVal)->boolConst);	
			}
#line 1814 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 212 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[0].exprVal);
				printf("expr -> term\n");
			}
#line 1823 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 218 "parser.y" /* yacc.c:1646  */
    {
						(yyval.exprVal) = (yyvsp[-1].exprVal);
						printf("term -> (expr)\n");
					}
#line 1832 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 222 "parser.y" /* yacc.c:1646  */
    {
						arith_typecheck((yyvsp[0].exprVal));
						(yyval.exprVal) = newexpr(arithexpr_e);
						(yyval.exprVal)->sym = newtemp(yylineno,scope);
						emit(uminus,(yyvsp[0].exprVal),NULL,(yyval.exprVal),0,yylineno);
						printf("term -> -expr\n");
					}
#line 1844 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 229 "parser.y" /* yacc.c:1646  */
    {
						(yyval.exprVal) = newexpr(boolexpr_e);
						(yyval.exprVal)->sym = newtemp(yylineno,scope);
						emit(not,(yyvsp[0].exprVal),NULL,(yyval.exprVal),0,yylineno);
						printf("term -> !expr\n");}
#line 1854 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 235 "parser.y" /* yacc.c:1646  */
    {	
						if ( Scope_lookup((yyvsp[0].exprVal)->sym->name, userfunc, scope) || Scope_lookup((yyvsp[0].exprVal)->sym->name, libfunc, scope) ){
							printf("\033[0;31m");
							printf("Error: (line %d) cannot increase value of a function\n", yylineno);
							printf("\033[0m");
						}
						if((yyvsp[0].exprVal)->type == tableitem_e){
							(yyval.exprVal) = emit_iftableitem((yyvsp[0].exprVal),scope,yylineno);
							emit(add,(yyval.exprVal),numConst_expr(1),(yyval.exprVal),0,yylineno);
							emit(tablesetelem,(yyvsp[0].exprVal),(yyvsp[0].exprVal)->index,(yyval.exprVal),0,yylineno);
						} else {
							emit(add,(yyvsp[0].exprVal),numConst_expr(1),(yyvsp[0].exprVal),0,yylineno);
							(yyval.exprVal) = newexpr(arithexpr_e);
							(yyval.exprVal)->sym = newtemp(yylineno,scope);
							emit(assign,(yyvsp[0].exprVal),NULL,(yyval.exprVal),0,yylineno);
						}
						printf("term -> ++lvalue\n");
					}
#line 1877 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 253 "parser.y" /* yacc.c:1646  */
    {
						if ( Scope_lookup((yyvsp[-1].exprVal)->sym->name, userfunc, scope) || Scope_lookup((yyvsp[-1].exprVal)->sym->name, libfunc, scope) ){
							printf("\033[0;31m");
							printf("Error: (line %d) cannot increase value of a function\n", yylineno);
							printf("\033[0m");
						}
						(yyval.exprVal) = newexpr(var_e);
						(yyval.exprVal)->sym = newtemp(yylineno,scope);
						if((yyvsp[-1].exprVal)->type == tableitem_e)  {
							expr *e = emit_iftableitem((yyvsp[-1].exprVal),scope,yylineno);
							emit(assign,e,NULL,(yyval.exprVal),0,yylineno);
							emit(add,e,numConst_expr(1),e,0,yylineno);
							emit(tablesetelem,(yyvsp[-1].exprVal),(yyvsp[-1].exprVal)->index,e,0,yylineno);
						} else {
							emit(assign,(yyvsp[-1].exprVal),NULL,(yyval.exprVal),0,yylineno);
							emit(add,(yyvsp[-1].exprVal),numConst_expr(1),(yyvsp[-1].exprVal),0,yylineno);
						}
						printf("term -> lvalue++\n");
					}
#line 1901 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 272 "parser.y" /* yacc.c:1646  */
    {
						if ( Scope_lookup((yyvsp[0].exprVal)->sym->name, userfunc, scope) || Scope_lookup((yyvsp[0].exprVal)->sym->name, libfunc, scope) ){
							printf("\033[0;31m");
							printf("Error: (line %d) cannot decrease value of a function\n", yylineno);
							printf("\033[0m");
						}
						if((yyvsp[0].exprVal)->type == tableitem_e){
							(yyval.exprVal) = emit_iftableitem((yyvsp[0].exprVal),scope,yylineno);
							emit(sub,(yyval.exprVal),numConst_expr(1),(yyval.exprVal),0,yylineno);
							emit(tablesetelem,(yyvsp[0].exprVal),(yyvsp[0].exprVal)->index,(yyval.exprVal),0,yylineno);
						} else {
							emit(sub,(yyvsp[0].exprVal),numConst_expr(1),(yyvsp[0].exprVal),0,yylineno);
							(yyval.exprVal) = newexpr(arithexpr_e);
							(yyval.exprVal)->sym = newtemp(yylineno,scope);
							emit(assign,(yyvsp[0].exprVal),NULL,(yyval.exprVal),0,yylineno);
						}
						printf("term -> --lvalue\n");
					}
#line 1924 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 290 "parser.y" /* yacc.c:1646  */
    {
						if ( Scope_lookup((yyvsp[-1].exprVal)->sym->name, userfunc, scope) || Scope_lookup((yyvsp[-1].exprVal)->sym->name, libfunc, scope) ){
							printf("\033[0;31m");
							printf("Error: (line %d) cannot decrease value of a function\n", yylineno);
							printf("\033[0m");
						}
						(yyval.exprVal) = newexpr(var_e);
						(yyval.exprVal)->sym = newtemp(yylineno,scope);
						if((yyvsp[-1].exprVal)->type == tableitem_e)  {
							expr *e = emit_iftableitem((yyvsp[-1].exprVal),scope,yylineno);
							emit(assign,e,NULL,(yyval.exprVal),0,yylineno);
							emit(sub,e,numConst_expr(1),e,0,yylineno);
							emit(tablesetelem,(yyvsp[-1].exprVal),(yyvsp[-1].exprVal)->index,e,0,yylineno);
						} else {
							emit(assign,(yyvsp[-1].exprVal),NULL,(yyval.exprVal),0,yylineno);
							emit(sub,(yyvsp[-1].exprVal),numConst_expr(1),(yyvsp[-1].exprVal),0,yylineno);
						}
						printf("term -> lvalue--\n");
					}
#line 1948 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 309 "parser.y" /* yacc.c:1646  */
    {
							(yyval.exprVal) = (yyvsp[0].exprVal);
							printf("term -> primary\n");}
#line 1956 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 314 "parser.y" /* yacc.c:1646  */
    {
				if ( Scope_lookup((yyvsp[0].exprVal)->sym->name, userfunc, scope) || Scope_lookup((yyvsp[0].exprVal)->sym->name, libfunc, scope) )
				{
						printf("\033[0;31m");
						printf("Error: (line %d) cannot assign a value to a function\n", yylineno);
						printf("\033[0m");
				}
			}
#line 1969 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 322 "parser.y" /* yacc.c:1646  */
    {
				printf("assignexpr -> lvalue = expr\n");
				if((yyvsp[-3].exprVal)->type == tableitem_e){
					emit(tablesetelem,(yyval.exprVal)->index,(yyvsp[0].exprVal),(yyval.exprVal),0,yylineno);
					(yyval.exprVal) = emit_iftableitem((yyval.exprVal),scope,yylineno);				
				}else{	
					(yyval.exprVal) = newexpr(assignexpr_e);
					(yyval.exprVal)->sym = newtemp(yylineno,scope);
					emit(assign,(yyvsp[0].exprVal),NULL,(yyvsp[-3].exprVal),0,yylineno);
					emit(assign,(yyvsp[-3].exprVal),NULL,(yyval.exprVal),0,yylineno);
				}
			}
#line 1986 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 336 "parser.y" /* yacc.c:1646  */
    { 
				(yyval.exprVal) = emit_iftableitem((yyvsp[0].exprVal),scope,yylineno); printf("primary -> lvalue\n");}
#line 1993 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 338 "parser.y" /* yacc.c:1646  */
    { (yyval.exprVal) = (yyvsp[0].exprVal);
				printf("primary -> call\n");}
#line 2000 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 340 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[0].exprVal);
				printf("primary -> objectdef\n");
			}
#line 2009 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 344 "parser.y" /* yacc.c:1646  */
    {printf("primary -> (funcdef)\n");
				(yyval.exprVal) = newexpr(programfunc_e);
				(yyval.exprVal)->sym = (yyvsp[-1].symVal);
				}
#line 2018 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 348 "parser.y" /* yacc.c:1646  */
    { (yyval.exprVal) = (yyvsp[0].exprVal); printf("primary -> const\n");}
#line 2024 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 351 "parser.y" /* yacc.c:1646  */
    {

				Node_T sym;
				int i;
				/* an h metavliti den yparxei sto symtable se opoiodipote scope */
				sym = SymTable_lookup(oSymTable, (yyvsp[0].strVal));
				if(!sym){
					if(scope == 0) type = global;
					else type = local;
					/* tin eisagoume sto trexon scope */
					SymTable_insert(oSymTable, (yyvsp[0].strVal), type, yylineno, scope);

					sym = newsymbol(var_s,(yyvsp[0].strVal),scope,yylineno);
					sym->space = currscopespace();
					sym->offset = currscopeoffset();
					incurrscopeoffset();

				} else { 
						if(Scope_lookup((yyvsp[0].strVal), libfunc, 0)){
							printf("Calling libfunc %s\n", (yyvsp[0].strVal));
						}else {					
							for(i=scope; i>=0; i--){
								sym = Scope_lookup((yyvsp[0].strVal), unknown, i);

								if(Scope_lookup((yyvsp[0].strVal), userfunc, i)){
									printf("Calling userfunc %s\n",(yyvsp[0].strVal));
									break;
								}
								/* an vrethei ekxwrhsh sto ST sto idio h ekswterikotero scope*/
								if(sym){
									if(sym->isActive == 1 && sym->scope != 0){
										/* an mesolavei function anamesa sto current scope kai se afto pou vrethike 
												metavliti me to idio onoma */
										if ( FuncBetween(i, scope-1) && sym->scope != 0){ 
											printf("\033[0;31m");
											printf("Error: (line %d) ID %s is not visible\n",yylineno,(yyvsp[0].strVal));
											printf("\033[0m");
										}
										break;							
									} else {
										if(sym->scope != 0){
											SymTable_insert(oSymTable, (yyvsp[0].strVal), type, yylineno, scope);
											break;
										}
									}
								} else {
									if(i==0){
										SymTable_insert(oSymTable, (yyvsp[0].strVal), global, yylineno, scope); // local ??
										break;
									}
								}
							}
						}
				}
				(yyval.exprVal) = lvalue_expr(SymTable_lookup(oSymTable, (yyvsp[0].strVal)));
				printf("lvalue -> ID\n");
			}
#line 2086 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 408 "parser.y" /* yacc.c:1646  */
    {
					 	Node_T sym;
						sym = Scope_lookup((yyvsp[0].strVal),unknown,scope);
						if(!sym){
							if(!Scope_lookup((yyvsp[0].strVal),libfunc,0)){
								if(scope == 0) type = global;
								else type = local;
								SymTable_insert(oSymTable,(yyvsp[0].strVal),type,yylineno,scope);

								sym = newsymbol(var_s,(yyvsp[0].strVal),scope,yylineno);
								sym->space = currscopespace();
								sym->offset = currscopeoffset();
								incurrscopeoffset();
							}else{
								printf("\033[0;31m");
								printf("Error: (line %d) trying to shadow library function %s\n",yylineno,(yyvsp[0].strVal));
								printf("\033[0m");
							}
						}else{
							if(Scope_lookup((yyvsp[0].strVal),userfunc,scope)){
								printf("Warning: (line %d) Trying to define local ID %s which is a function name\n",yylineno,(yyvsp[0].strVal));
							}else{
								(yyval.exprVal) = lvalue_expr(sym);
							}
						}
						(yyval.exprVal) = lvalue_expr(SymTable_lookup(oSymTable, (yyvsp[0].strVal)));
						printf("lvalue -> local ID\n");
			}
#line 2119 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 436 "parser.y" /* yacc.c:1646  */
    {
				node = Scope_lookup((yyvsp[0].strVal), unknown, 0);
				if(node == NULL){	
					printf("\033[0;31m");
					printf("Error: (line:%d) trying to access (global) ID: %s, which is not defined\n",yylineno,(yyvsp[0].strVal));
					printf("\033[0m");
				}
				(yyval.exprVal) = lvalue_expr(SymTable_lookup(oSymTable, (yyvsp[0].strVal)));
				printf("lvalue -> ::ID\n");
			}
#line 2134 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 446 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[0].exprVal);
				printf("lvalue -> member\n");
			}
#line 2143 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 452 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = member_item((yyvsp[-2].exprVal),(yyvsp[0].strVal), yylineno,scope);
				printf("member -> lvalue.ID\n");
			}
#line 2152 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 456 "parser.y" /* yacc.c:1646  */
    {
				(yyvsp[-3].exprVal) = emit_iftableitem((yyvsp[-3].exprVal),scope,yylineno);
				(yyval.exprVal) = newexpr(tableitem_e);
				(yyval.exprVal)->sym = (yyvsp[-3].exprVal)->sym;
				(yyval.exprVal)->index = (yyvsp[-1].exprVal);
				printf("member -> lvalue[expr]\n");
			}
#line 2164 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 463 "parser.y" /* yacc.c:1646  */
    {printf("member -> call.ID\n");}
#line 2170 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 464 "parser.y" /* yacc.c:1646  */
    {printf("member -> call[expr]\n");}
#line 2176 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 467 "parser.y" /* yacc.c:1646  */
    {
				expr *tmp = (yyvsp[-1].exprVal);
				while(tmp){
					emit(param ,tmp, NULL, NULL, -1, yylineno);
					tmp = tmp->next;
				}
				expr *e = newexpr(programfunc_e);
				e->sym = (yyvsp[-3].exprVal)->sym;
				emit(call ,e, NULL, NULL, -1, yylineno);
				expr* d = newexpr(var_e);
				d->sym = newtemp(yylineno,scope);
				emit(getretval,d,NULL,NULL,0,yylineno);
				(yyval.exprVal) = d;
				printf("call -> (elist)\n");
			}
#line 2196 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 482 "parser.y" /* yacc.c:1646  */
    {

				expr *tmp = (yyvsp[0].exprVal);
				expr *tobecalled = (yyvsp[0].exprVal);
				if((yyvsp[0].exprVal) && (yyvsp[0].exprVal)->isMethodcall){
					expr *e2 = malloc(sizeof(expr));
					memcpy(e2,(yyvsp[-1].exprVal),sizeof(expr));
					expr *tmp2 = (yyvsp[0].exprVal);
					while(tmp2->next){
						tmp2 = tmp2->next;
					}
					tmp2->next = e2;
					tmp = tmp->next;
					expr *e = newexpr(tableitem_e);
					e->sym = newtemp(yylineno,scope);
					emit(tablegetelem,(yyvsp[-1].exprVal),tobecalled,e,-1,yylineno);
				}
				while(tmp){
					emit(param ,tmp, NULL, NULL, -1, yylineno);
					tmp = tmp->next;
				}
				if((yyvsp[0].exprVal) && (yyvsp[0].exprVal)->isMethodcall){		
					emit(call ,tobecalled, NULL, NULL, -1, yylineno);
				}else{
					emit(call ,(yyvsp[-1].exprVal), NULL, NULL, -1, yylineno);
				}
				expr *e = newexpr(var_e);
				e->sym = newtemp(yylineno,scope);
				emit(getretval,e,NULL,NULL,0,yylineno);
				(yyval.exprVal) = e;
				printf("call -> lvalue callsuffix\n");
			}
#line 2233 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 515 "parser.y" /* yacc.c:1646  */
    {
					expr *tmp = (yyvsp[-1].exprVal);
					while(tmp){
						emit(param ,tmp, NULL, NULL, -1, yylineno);
						tmp = tmp->next;
					}
					expr *e = newexpr(programfunc_e);
					e->sym = (yyvsp[-4].symVal);
					emit(call ,e, NULL, NULL, -1, yylineno);
					expr* d = newexpr(var_e);
					d->sym = newtemp(yylineno,scope);
					emit(getretval,d,NULL,NULL,0,yylineno);
					(yyval.exprVal) = d;
					printf("call -> (funcdef)(elist)\n");
				}
#line 2253 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 532 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[0].exprVal);
				printf("callsuffix -> normcall\n");}
#line 2261 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 535 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[0].exprVal);
				printf("callsyffix -> methodcall\n");}
#line 2269 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 540 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[-1].exprVal);
				if((yyval.exprVal))
					(yyval.exprVal)->isMethodcall = 0;
				printf("normacall -> (elist)\n");}
#line 2279 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 548 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = newexpr(programfunc_e);
				(yyval.exprVal)->sym = SymTable_lookup(oSymTable,(yyvsp[-3].strVal));
				(yyval.exprVal)->next = (yyvsp[-1].exprVal);
				(yyval.exprVal)->isMethodcall = 1;
				printf("methodcall -> ..ID(elist)\n");
				}
#line 2291 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 557 "parser.y" /* yacc.c:1646  */
    {
						(yyval.exprVal) = (yyvsp[-1].exprVal);
						(yyvsp[-1].exprVal)->next = (yyvsp[0].exprVal);
						if((yyval.exprVal)->next)
							(yyval.exprVal) = reverseList((yyval.exprVal));
						printf("elist -> expr exprs\n");
			}
#line 2303 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 564 "parser.y" /* yacc.c:1646  */
    {(yyval.exprVal) = NULL;printf("elist -> empty\n");}
#line 2309 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 567 "parser.y" /* yacc.c:1646  */
    {
			(yyval.exprVal) = (yyvsp[-1].exprVal);
			(yyvsp[-1].exprVal)->next = (yyvsp[0].exprVal);
			printf("exprs -> ,expr exprs\n");
		}
#line 2319 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 572 "parser.y" /* yacc.c:1646  */
    {(yyval.exprVal) = NULL; printf("exprs -> empty\n");}
#line 2325 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 575 "parser.y" /* yacc.c:1646  */
    {
				expr *e = newexpr(newtable_e);
				e->sym = newtemp(yylineno,scope);
				emit(tablecreate,e,NULL,NULL,-1,yylineno);
				if((yyvsp[-1].exprVal) && (yyvsp[-1].exprVal)->iselist){
					expr *tmp = (yyvsp[-1].exprVal);
					int i = 0;
					tmp = reverseList(tmp);
					while(tmp){
						//expr *toemit = numConst_expr(i);
						emit(tablesetelem,e,tmp,numConst_expr(i),-1,yylineno);
						i++;
						tmp = tmp->next;
					}
				}else if((yyvsp[-1].exprVal)){
					expr *tmp = (yyvsp[-1].exprVal);
					while(tmp){
						emit(tablesetelem,e,tmp,tmp->index,-1,yylineno);
						tmp = tmp->next;
					}
				}
				(yyval.exprVal) = e;
				printf("objectdef -> [index]");
			}
#line 2354 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 601 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[0].exprVal);
				if((yyval.exprVal))
					(yyval.exprVal)->iselist = 1;
				printf("index-> elist");}
#line 2364 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 606 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[0].exprVal);
				if((yyval.exprVal))
					(yyval.exprVal)->iselist = 0;
				printf("index -> indexed\n");}
#line 2374 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 613 "parser.y" /* yacc.c:1646  */
    {
				(yyvsp[-1].exprVal)->next = (yyvsp[0].exprVal);
				(yyval.exprVal) = (yyvsp[-1].exprVal);
				printf("indexed -> indexedelem indexedelems\n");
			}
#line 2384 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 620 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = (yyvsp[-1].exprVal);
				(yyval.exprVal)->index = (yyvsp[-3].exprVal);
				printf("indexedelem -> {expr : expr}\n");}
#line 2393 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 626 "parser.y" /* yacc.c:1646  */
    {
					(yyvsp[-1].exprVal)->next = (yyvsp[0].exprVal);
					(yyval.exprVal) = (yyvsp[-1].exprVal);
					printf("indexedelems -> ,indexedelem indexedelems\n");}
#line 2402 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 630 "parser.y" /* yacc.c:1646  */
    {
					(yyval.exprVal) = NULL;
					printf("indexedelems -> empty\n");}
#line 2410 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 635 "parser.y" /* yacc.c:1646  */
    {
				scope++;
			}
#line 2418 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 637 "parser.y" /* yacc.c:1646  */
    {
				(yyval.stmtVal) = (yyvsp[-1].stmtVal);
				SymTable_hide(oSymTable, scope);
				printf("block -> [blstmts]\n");
				scope--;
			}
#line 2429 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 645 "parser.y" /* yacc.c:1646  */
    {
				(yyval.stmtVal) = (yyvsp[0].stmtVal);
				printf("blstmts -> stmts\n");}
#line 2437 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 651 "parser.y" /* yacc.c:1646  */
    {
				//exitscopespace(); // -1 gia locals (func definition)
				Node_T sym = Scope_lookup((yyvsp[-2].symVal)->name,userfunc,scope);
				(yyvsp[-2].symVal)->totallocals = currscopeoffset();

				unsigned offset = popOffsetStack();
				restorecurrscopeoffset(offset);

				(yyval.symVal) = (yyvsp[-2].symVal);
				emit(funcend ,lvalue_expr((yyvsp[-2].symVal)), NULL, NULL, -1, yylineno);

				patchlabel(sym->funcQuadNo,nextquadlabel());
				printf("funcdef -> function funcname (idlist) block\n");
			}
#line 2456 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 667 "parser.y" /* yacc.c:1646  */
    {					
					node = Scope_lookup((yyvsp[0].strVal), libfunc, 0); //elegxos gia shadowing twn libfunc
					if(node != NULL){
						printf("\033[0;31m");
						printf("Error: (line %d) trying to shadow library function %s\n",yylineno,(yyvsp[0].strVal));
						printf("\033[0m");
					}else{
						node = Scope_lookup((yyvsp[0].strVal), unknown, scope); //elegxos gia function/ variable me to idio onoma sto idio scope
						/* an yparxei */
						if(node != NULL /* && node->isActive == 1 */){
							printf("\033[0;31m");
							printf("Error: (line %d) ID %s already exists in scope %d\n",yylineno,(yyvsp[0].strVal),scope);
							printf("\033[0m");
						}else{
							fname = strdup((yyvsp[0].strVal));
							SymTable_insert(oSymTable, (yyvsp[0].strVal), userfunc, yylineno, scope);
						}
					}
					(yyval.symVal) = Scope_lookup((yyvsp[0].strVal),userfunc,scope);
					if((yyval.symVal))
						(yyval.symVal)->funcQuadNo = nextquadlabel();
					printf("funcname -> ID\n");
				}
#line 2484 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 690 "parser.y" /* yacc.c:1646  */
    {

					sprintf(anonymous,"_f%d",uknownfunc);
					fname = strdup(anonymous);

					SymTable_insert(oSymTable, anonymous, userfunc, yylineno, scope);
					(yyval.symVal) = Scope_lookup(anonymous,userfunc,scope);
					if((yyval.symVal))
						(yyval.symVal)->funcQuadNo = nextquadlabel();
					uknownfunc++;
					printf("funcname -> empty\n");
				}
#line 2501 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 704 "parser.y" /* yacc.c:1646  */
    {

				Node_T sym = Scope_lookup((yyvsp[0].symVal)->name,userfunc,scope);
				fname = strdup(sym->name);
	
				emit(jump ,NULL, NULL, NULL, -1, yylineno);

				sym->iaddress = nextquadlabel();
				emit(funcstart ,lvalue_expr(sym), NULL, NULL, -1, yylineno);
				(yyval.symVal) = sym;
				if(in_func) pushOffsetStack();

				enterscopespace(); // scopespacecount++;
				resetformalargsoffset(); // ormalargsoffset = 0;
				scope++;
			}
#line 2522 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 722 "parser.y" /* yacc.c:1646  */
    {
				scope--; in_func++;
				enterscopespace();
				resetfunctionlocaloffset();
			}
#line 2532 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 729 "parser.y" /* yacc.c:1646  */
    {
				//exitscopespace(); // -1 gia formals
				Node_T sym = Scope_lookup(fname,userfunc,scope);
				SymTable_hide(oSymTable, scope);
				in_func--;
			}
#line 2543 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 737 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = numConst_expr((double)(yyvsp[0].intVal));
				printf("const -> INTEGER\n");
			}
#line 2552 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 741 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = numConst_expr((yyvsp[0].doubleVal));
				printf("const -> REAL\n");
			}
#line 2561 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 745 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = strConst_expr((yyvsp[0].strVal));
				printf("const -> STRING\n");
			}
#line 2570 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 749 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = nilConst_expr();
				printf("const -> NIL\n");
			}
#line 2579 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 753 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = boolConst_expr('1');
				printf("const -> TRUE\n");
			}
#line 2588 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 757 "parser.y" /* yacc.c:1646  */
    {
				(yyval.exprVal) = boolConst_expr('0');
				printf("const -> FALSE\n");
			}
#line 2597 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 763 "parser.y" /* yacc.c:1646  */
    {printf("idlist -> id ids\n");}
#line 2603 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 766 "parser.y" /* yacc.c:1646  */
    {
				struct argument *tmparg;
				tmparg = ArgumentSearch(fname, (yyvsp[0].strVal),scope);
				node = Scope_lookup((yyvsp[0].strVal), libfunc, 0);
				if(tmparg != NULL){
					printf("\033[0;31m");
					printf("Error: (line %d) argument %s already defined in function %s\n",yylineno,(yyvsp[0].strVal),fname);
					printf("\033[0m");
				}else if(node != NULL){
					printf("\033[0;31m");
					printf("Error: (line %d) trying to shadow library function %s\n",yylineno,(yyvsp[0].strVal));
					printf("\033[0m");
				}else{
					ArgumentInsert(fname,(yyvsp[0].strVal),scope,oSymTable);
					SymTable_insert(oSymTable, (yyvsp[0].strVal), formal, yylineno, scope);
					incurrscopeoffset();
				}
				printf("id -> ID\n");
			}
#line 2627 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 785 "parser.y" /* yacc.c:1646  */
    {printf("id -> empty\n");}
#line 2633 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 788 "parser.y" /* yacc.c:1646  */
    {printf("ids -> ,id ids\n");}
#line 2639 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 789 "parser.y" /* yacc.c:1646  */
    {printf("ids -> empty\n");}
#line 2645 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 793 "parser.y" /* yacc.c:1646  */
    {
				(yyval.stmtVal) = (yyvsp[0].stmtVal);
				patchlabel((yyvsp[-1].intVal),nextquadlabel());
				printf("ifstmt -> if (expr) stmt elsestmt\n");
			}
#line 2655 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 799 "parser.y" /* yacc.c:1646  */
    {
				patchlabel((yyvsp[-3].intVal),(yyvsp[-1].intVal)+1);
				patchlabel((yyvsp[-1].intVal),nextquadlabel());
			}
#line 2664 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 805 "parser.y" /* yacc.c:1646  */
    {
				emit(if_eq,(yyvsp[-1].exprVal),boolConst_expr(1),NULL,nextquadlabel()+2,yylineno);
				(yyval.intVal) = nextquadlabel();
				emit(jump,NULL,NULL,NULL,0,yylineno);
			}
#line 2674 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 812 "parser.y" /* yacc.c:1646  */
    {
				(yyval.intVal) = nextquadlabel();
				emit(jump,NULL,NULL,NULL,0,yylineno);
			}
#line 2683 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 818 "parser.y" /* yacc.c:1646  */
    {
				loop_depth++;
				(yyval.intVal) = nextquadlabel();
			}
#line 2692 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 825 "parser.y" /* yacc.c:1646  */
    {
				emit(if_eq,(yyvsp[-1].exprVal),boolConst_expr(1),NULL,nextquadlabel()+2,yylineno);
				(yyval.intVal) = nextquadlabel();
				emit(jump,NULL,NULL,NULL,0,yylineno);
			}
#line 2702 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 831 "parser.y" /* yacc.c:1646  */
    {
					stmt_t* tmp;
					emit(jump,NULL,NULL,NULL,(yyvsp[-2].intVal),yylineno);
					patchlabel((yyvsp[-1].intVal),nextquadlabel());
					(yyval.stmtVal) = newstmt();

					if(specialflag){
						stmt_t *tmp = (yyvsp[0].stmtVal)->next;
						while(tmp){
							if(tmp->isbreak){
								patchlabel(tmp->quadno, nextquadlabel());
							}
							else{
								patchlabel(tmp->quadno, (yyvsp[-2].intVal));
							}
							tmp = tmp->next;
						}
					}
					loop_depth--;
					specialflag = 0;
					printf("whilestmt -> while (expr) stmt\n");
				}
#line 2729 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 855 "parser.y" /* yacc.c:1646  */
    { (yyval.intVal) = nextquadlabel(); emit(jump,NULL,NULL,NULL,0,yylineno); }
#line 2735 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 857 "parser.y" /* yacc.c:1646  */
    { (yyval.intVal) = nextquadlabel(); }
#line 2741 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 859 "parser.y" /* yacc.c:1646  */
    {loop_depth++;}
#line 2747 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 860 "parser.y" /* yacc.c:1646  */
    {
				(yyval.forVal) = malloc(sizeof(forval));
				(yyval.forVal)->test = (yyvsp[-2].intVal);
				(yyval.forVal)->enter = nextquadlabel();
				emit(if_eq,(yyvsp[-1].exprVal),boolConst_expr(1),NULL,0,yylineno);
			}
#line 2758 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 868 "parser.y" /* yacc.c:1646  */
    {loop_depth--;}
#line 2764 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 869 "parser.y" /* yacc.c:1646  */
    {
				patchlabel((yyvsp[-7].forVal)->enter,(yyvsp[-3].intVal)+1);
				patchlabel((yyvsp[-6].intVal),nextquadlabel());
				patchlabel((yyvsp[-3].intVal),(yyvsp[-7].forVal)->test);
				patchlabel((yyvsp[0].intVal),(yyvsp[-6].intVal)+1);

				(yyval.stmtVal) = newstmt();
				if(specialflag){
						stmt_t *tmp = (yyvsp[-2].stmtVal)->next;
						while(tmp){
							if(tmp->isbreak){
								patchlabel(tmp->quadno, nextquadlabel());
							}
							else{
								patchlabel(tmp->quadno, (yyvsp[-6].intVal)+1);
							}
							tmp = tmp->next;
						}
					}
				printf("forstmt -> for (elist; expr; elist) stmt\n");}
#line 2789 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 892 "parser.y" /* yacc.c:1646  */
    {
				emit(ret,NULL,NULL,NULL,-1,yylineno);
				printf("returnstmt -> return;\n\n");
			}
#line 2798 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 896 "parser.y" /* yacc.c:1646  */
    {
				emit(ret,(yyvsp[-1].exprVal),NULL,NULL,-1,yylineno);
				printf("returnstmt -> return expr;\n\n");
			}
#line 2807 "parser.c" /* yacc.c:1646  */
    break;


#line 2811 "parser.c" /* yacc.c:1646  */
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
#line 902 "parser.y" /* yacc.c:1906  */

//EPILOGOS

int yyerror (const char* yaccProvidedMessage){
	fprintf(stderr,"%s: at line %d, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
	fprintf(stderr,"INPUT NOT VALID\n");
}

int main(int argc, char** argv){

	int i;
	
	if(argc > 1){
		if(!(yyin = fopen(argv[1],"r"))){
			fprintf(stderr,"Cannot read file: %s\n",argv[1]);
		}
	}else
		yyin = stdin;

	oSymTable = SymTable_new();

	SymTable_insert(oSymTable, "print", libfunc, 0, 0);
	SymTable_insert(oSymTable, "input", libfunc, 0, 0);
	SymTable_insert(oSymTable, "objectmemberkeys", libfunc, 0, 0);
	SymTable_insert(oSymTable, "objecttotalmembers", libfunc, 0, 0);
	SymTable_insert(oSymTable, "objectcopy", libfunc, 0, 0);
	SymTable_insert(oSymTable, "totalarguments", libfunc, 0, 0);
	SymTable_insert(oSymTable, "argument", libfunc, 0, 0);
	SymTable_insert(oSymTable, "typeof", libfunc, 0, 0);
	SymTable_insert(oSymTable, "strtonum", libfunc, 0, 0);
	SymTable_insert(oSymTable, "sqrt", libfunc, 0, 0);
	SymTable_insert(oSymTable, "cos", libfunc, 0, 0);
	SymTable_insert(oSymTable, "sin", libfunc, 0, 0);

	yyparse();

	printf("\n");

	for(i=0; i < ScopelinkSize(); i++){
		Scope_print(oSymTable, i);
	}
	printQuads();

	init_constTables();

	produce_tcode();

	generateText();
	generateBinary();

	return 0;
 }
