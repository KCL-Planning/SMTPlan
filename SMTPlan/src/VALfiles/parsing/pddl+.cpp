/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 17 "pddl+.yacc"

/*
Error reporting:
Intention is to provide error token on most bracket expressions,
so synchronisation can occur on next CLOSE_BRAC.
Hence error should be generated for innermost expression containing error.
Expressions which cause errors return a NULL values, and parser
always attempts to carry on.
This won't behave so well if CLOSE_BRAC is missing.

Naming conventions:
Generally, the names should be similar to the PDDL2.1 spec.
During development, they have also been based on older PDDL specs,
older PDDL+ and TIM parsers, and this shows in places.

All the names of fields in the semantic value type begin with t_
Corresponding categories in the grammar begin with c_
Corresponding classes have no prefix.

PDDL grammar       yacc grammar      type of corresponding semantic val.

thing+             c_things          thing_list
(thing+)           c_thing_list      thing_list

*/

#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <ctype.h>

// This is now copied locally to avoid relying on installation
// of flex++.

//#include "FlexLexer.h"
//#include <FlexLexer.h>

#include "ptree.h"
#include "parse_error.h"

#define YYDEBUG 1

int yyerror(char *);

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", ((char *)msgid))
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) ((char *) msgid)
# endif
#endif

extern int yylex();

using namespace VAL;



/* Line 189 of yacc.c  */
#line 135 "pddl+.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OPEN_BRAC = 258,
     CLOSE_BRAC = 259,
     MODULES = 260,
     OPEN_SQ = 261,
     CLOSE_SQ = 262,
     DOT = 263,
     CLASSES = 264,
     CLASS = 265,
     DEFINE = 266,
     PDDLDOMAIN = 267,
     REQS = 268,
     EQUALITY = 269,
     STRIPS = 270,
     ADL = 271,
     NEGATIVE_PRECONDITIONS = 272,
     TYPING = 273,
     DISJUNCTIVE_PRECONDS = 274,
     EXT_PRECS = 275,
     UNIV_PRECS = 276,
     QUANT_PRECS = 277,
     COND_EFFS = 278,
     FLUENTS = 279,
     OBJECTFLUENTS = 280,
     NUMERICFLUENTS = 281,
     ACTIONCOSTS = 282,
     TIME = 283,
     DURATIVE_ACTIONS = 284,
     DURATION_INEQUALITIES = 285,
     CONTINUOUS_EFFECTS = 286,
     DERIVED_PREDICATES = 287,
     TIMED_INITIAL_LITERALS = 288,
     PREFERENCES = 289,
     CONSTRAINTS = 290,
     ACTION = 291,
     PROCESS = 292,
     EVENT = 293,
     DURATIVE_ACTION = 294,
     DERIVED = 295,
     CONSTANTS = 296,
     PREDS = 297,
     FUNCTIONS = 298,
     TYPES = 299,
     ARGS = 300,
     PRE = 301,
     CONDITION = 302,
     PREFERENCE = 303,
     START_PRE = 304,
     END_PRE = 305,
     EFFECTS = 306,
     INITIAL_EFFECT = 307,
     FINAL_EFFECT = 308,
     INVARIANT = 309,
     DURATION = 310,
     AT_START = 311,
     AT_END = 312,
     OVER_ALL = 313,
     AND = 314,
     OR = 315,
     EXISTS = 316,
     FORALL = 317,
     IMPLY = 318,
     NOT = 319,
     WHEN = 320,
     WHENEVER = 321,
     EITHER = 322,
     PROBLEM = 323,
     FORDOMAIN = 324,
     INITIALLY = 325,
     OBJECTS = 326,
     GOALS = 327,
     EQ = 328,
     LENGTH = 329,
     SERIAL = 330,
     PARALLEL = 331,
     METRIC = 332,
     MINIMIZE = 333,
     MAXIMIZE = 334,
     HASHT = 335,
     DURATION_VAR = 336,
     TOTAL_TIME = 337,
     INCREASE = 338,
     DECREASE = 339,
     SCALE_UP = 340,
     SCALE_DOWN = 341,
     ASSIGN = 342,
     GREATER = 343,
     GREATEQ = 344,
     LESS = 345,
     LESSEQ = 346,
     Q = 347,
     COLON = 348,
     NUMBER = 349,
     ALWAYS = 350,
     SOMETIME = 351,
     WITHIN = 352,
     ATMOSTONCE = 353,
     SOMETIMEAFTER = 354,
     SOMETIMEBEFORE = 355,
     ALWAYSWITHIN = 356,
     HOLDDURING = 357,
     HOLDAFTER = 358,
     ISVIOLATED = 359,
     BOGUS = 360,
     CONTROL = 361,
     NAME = 362,
     FUNCTION_SYMBOL = 363,
     INTVAL = 364,
     FLOATVAL = 365,
     AT_TIME = 366,
     PLUS = 367,
     HYPHEN = 368,
     DIV = 369,
     MUL = 370,
     UMINUS = 371
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 79 "pddl+.yacc"

    parse_category* t_parse_category;

    effect_lists* t_effect_lists;
    effect* t_effect;
    simple_effect* t_simple_effect;
    cond_effect*   t_cond_effect;
    forall_effect* t_forall_effect;
    timed_effect* t_timed_effect;

    quantifier t_quantifier;
    metric_spec*  t_metric;
    optimization t_optimization;

    symbol* t_symbol;
    var_symbol*   t_var_symbol;
    pddl_type*    t_type;
    pred_symbol*  t_pred_symbol;
    func_symbol*  t_func_symbol;
    const_symbol* t_const_symbol;
    class_symbol* t_class;

    parameter_symbol_list* t_parameter_symbol_list;
    var_symbol_list* t_var_symbol_list;
    const_symbol_list* t_const_symbol_list;
    pddl_type_list* t_type_list;

    proposition* t_proposition;
    pred_decl* t_pred_decl;
    pred_decl_list* t_pred_decl_list;
    func_decl* t_func_decl;
    func_decl_list* t_func_decl_list;

    goal* t_goal;
    con_goal * t_con_goal;
    goal_list* t_goal_list;

    func_term* t_func_term;
    assignment* t_assignment;
    expression* t_expression;
    num_expression* t_num_expression;
    assign_op t_assign_op;
    comparison_op t_comparison_op;

    structure_def* t_structure_def;
    structure_store* t_structure_store;

    action* t_action_def;
    event* t_event_def;
    process* t_process_def;
    durative_action* t_durative_action_def;
    derivation_rule* t_derivation_rule;

    problem* t_problem;
    length_spec* t_length_spec;

    domain* t_domain;

    pddl_req_flag t_pddl_req_flag;

    plan* t_plan;
    plan_step* t_step;

    int ival;
    double fval;

    char* cp;
    int t_dummy;

    var_symbol_table * vtab;

  class_def * t_class_def;
  //  classes_list* t_classes;




/* Line 214 of yacc.c  */
#line 365 "pddl+.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 377 "pddl+.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   984

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  117
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  131
/* YYNRULES -- Number of rules.  */
#define YYNRULES  356
/* YYNRULES -- Number of states.  */
#define YYNSTATES  822

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   371

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    15,    20,    23,    26,
      29,    32,    35,    38,    41,    43,    48,    50,    52,    57,
      60,    61,    66,    71,    74,    75,    78,    80,    85,    89,
      91,    93,    95,    97,   100,   101,   107,   111,   114,   115,
     117,   122,   127,   129,   134,   135,   139,   140,   145,   150,
     152,   155,   156,   159,   160,   165,   170,   172,   175,   179,
     180,   182,   184,   186,   188,   193,   195,   197,   200,   201,
     204,   205,   212,   215,   218,   221,   222,   227,   230,   233,
     236,   237,   239,   241,   243,   245,   247,   252,   254,   256,
     258,   260,   263,   266,   269,   270,   275,   280,   285,   293,
     299,   305,   307,   309,   312,   313,   318,   323,   329,   335,
     339,   345,   351,   355,   360,   368,   374,   376,   379,   380,
     385,   387,   389,   391,   393,   396,   399,   402,   403,   409,
     415,   421,   427,   433,   439,   445,   450,   453,   454,   456,
     459,   461,   463,   466,   472,   478,   484,   490,   495,   502,
     512,   522,   524,   526,   528,   530,   533,   534,   539,   541,
     546,   548,   556,   562,   568,   574,   580,   586,   592,   597,
     603,   609,   615,   621,   623,   626,   628,   634,   640,   642,
     644,   646,   651,   656,   658,   665,   670,   675,   677,   679,
     681,   683,   685,   687,   689,   694,   702,   706,   709,   714,
     720,   725,   733,   735,   740,   746,   751,   759,   762,   764,
     769,   775,   777,   780,   782,   787,   795,   800,   805,   810,
     816,   821,   827,   833,   840,   847,   853,   855,   860,   865,
     870,   876,   884,   892,   898,   901,   903,   906,   908,   910,
     912,   917,   922,   927,   932,   937,   942,   947,   952,   957,
     962,   967,   970,   972,   974,   976,   978,   980,   982,   984,
     990,   992,   998,  1011,  1016,  1029,  1034,  1047,  1052,  1057,
    1058,  1071,  1076,  1080,  1084,  1085,  1087,  1092,  1095,  1096,
    1101,  1106,  1111,  1117,  1122,  1124,  1126,  1128,  1130,  1132,
    1134,  1136,  1138,  1140,  1142,  1144,  1146,  1148,  1150,  1152,
    1154,  1156,  1158,  1160,  1162,  1164,  1166,  1168,  1170,  1172,
    1177,  1182,  1195,  1201,  1204,  1207,  1210,  1213,  1216,  1219,
    1222,  1223,  1228,  1233,  1235,  1240,  1246,  1251,  1259,  1265,
    1271,  1273,  1275,  1279,  1281,  1283,  1285,  1290,  1294,  1298,
    1302,  1306,  1310,  1312,  1315,  1317,  1320,  1323,  1327,  1331,
    1332,  1336,  1338,  1343,  1345,  1350,  1352
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     118,     0,    -1,   119,    -1,   230,    -1,   243,    -1,     3,
      11,   121,   120,     4,    -1,     3,    11,   121,     1,    -1,
     126,   120,    -1,   229,   120,    -1,   228,   120,    -1,   208,
     120,    -1,   209,   120,    -1,   210,   120,    -1,   124,   120,
      -1,   212,    -1,     3,    12,   107,     4,    -1,   107,    -1,
     107,    -1,     3,     9,   125,     4,    -1,   122,   125,    -1,
      -1,     3,    13,   127,     4,    -1,     3,    13,     1,     4,
      -1,   127,   227,    -1,    -1,   129,   128,    -1,   129,    -1,
       3,   130,   137,     4,    -1,     3,     1,     4,    -1,   107,
      -1,    73,    -1,   107,    -1,   107,    -1,   133,   134,    -1,
      -1,     3,   136,   137,     4,   135,    -1,     3,     1,     4,
      -1,   113,    94,    -1,    -1,   107,    -1,   139,   113,   151,
     137,    -1,   139,   113,   149,   137,    -1,   139,    -1,   139,
     113,    94,   138,    -1,    -1,    92,   145,   139,    -1,    -1,
     142,   113,   151,   140,    -1,   142,   113,   149,   140,    -1,
     142,    -1,   147,   141,    -1,    -1,   148,   142,    -1,    -1,
     152,   113,   151,   143,    -1,   152,   113,   149,   143,    -1,
     152,    -1,   144,   147,    -1,   144,    92,   146,    -1,    -1,
     107,    -1,   107,    -1,   107,    -1,   107,    -1,     3,    67,
     153,     4,    -1,   107,    -1,   107,    -1,   152,   150,    -1,
      -1,   153,   151,    -1,    -1,   154,     3,    73,   190,   189,
       4,    -1,   154,   183,    -1,   154,   182,    -1,   154,   155,
      -1,    -1,     3,   111,   154,     4,    -1,   158,   156,    -1,
     185,   156,    -1,   184,   156,    -1,    -1,   161,    -1,   181,
      -1,   180,    -1,   185,    -1,   184,    -1,     3,    59,   160,
       4,    -1,   159,    -1,   180,    -1,   181,    -1,   186,    -1,
     160,   180,    -1,   160,   181,    -1,   160,   186,    -1,    -1,
       3,    59,   156,     4,    -1,     3,    59,     1,     4,    -1,
       3,    59,   163,     4,    -1,     3,   203,     3,   137,     4,
     162,     4,    -1,     3,    65,   223,   162,     4,    -1,     3,
      66,   200,   166,     4,    -1,   164,    -1,   186,    -1,   163,
     162,    -1,    -1,     3,    56,   168,     4,    -1,     3,    57,
     168,     4,    -1,     3,    83,   190,   188,     4,    -1,     3,
      84,   190,   188,     4,    -1,     3,     1,     4,    -1,     3,
      83,   190,   188,     4,    -1,     3,    84,   190,   188,     4,
      -1,     3,     1,     4,    -1,     3,    59,   167,     4,    -1,
       3,   203,     3,   137,     4,   166,     4,    -1,     3,    66,
     200,   166,     4,    -1,   165,    -1,   167,   166,    -1,    -1,
       3,    59,   170,     4,    -1,   169,    -1,   180,    -1,   181,
      -1,   171,    -1,   170,   180,    -1,   170,   181,    -1,   170,
     171,    -1,    -1,     3,    87,   190,   174,     4,    -1,     3,
      83,   190,   174,     4,    -1,     3,    84,   190,   174,     4,
      -1,     3,    85,   190,   174,     4,    -1,     3,    86,   190,
     174,     4,    -1,     3,    83,   190,   188,     4,    -1,     3,
      84,   190,   188,     4,    -1,     3,    59,   173,     4,    -1,
     173,   172,    -1,    -1,   175,    -1,    92,    81,    -1,   189,
      -1,   190,    -1,    92,   107,    -1,     3,   112,   174,   174,
       4,    -1,     3,   113,   174,   174,     4,    -1,     3,   115,
     174,   174,     4,    -1,     3,   114,   174,   174,     4,    -1,
       3,    59,   179,     4,    -1,     3,   177,    92,    81,   178,
       4,    -1,     3,    56,     3,   177,    92,    81,   178,     4,
       4,    -1,     3,    57,     3,   177,    92,    81,   178,     4,
       4,    -1,    91,    -1,    89,    -1,    73,    -1,   187,    -1,
     179,   176,    -1,    -1,     3,    64,   205,     4,    -1,   205,
      -1,     3,    64,   207,     4,    -1,   207,    -1,     3,   203,
       3,   137,     4,   157,     4,    -1,     3,    65,   200,   156,
       4,    -1,     3,    87,   190,   187,     4,    -1,     3,    83,
     190,   187,     4,    -1,     3,    84,   190,   187,     4,    -1,
       3,    85,   190,   187,     4,    -1,     3,    86,   190,   187,
       4,    -1,     3,   113,   187,     4,    -1,     3,   112,   187,
     187,     4,    -1,     3,   113,   187,   187,     4,    -1,     3,
     115,   187,   187,     4,    -1,     3,   114,   187,   187,     4,
      -1,   189,    -1,    92,   107,    -1,   190,    -1,     3,   115,
      80,   187,     4,    -1,     3,   115,   187,    80,     4,    -1,
      80,    -1,   109,    -1,   110,    -1,     3,   108,   144,     4,
      -1,     3,   107,   144,     4,    -1,   108,    -1,     3,   123,
       8,   108,   144,     4,    -1,     3,   108,   144,     4,    -1,
       3,   107,   144,     4,    -1,   108,    -1,    88,    -1,    89,
      -1,    90,    -1,    91,    -1,    73,    -1,   197,    -1,     3,
      59,   201,     4,    -1,     3,   203,     3,   137,     4,   193,
       4,    -1,     3,    59,     4,    -1,     3,     4,    -1,     3,
      48,   199,     4,    -1,     3,    48,   107,   199,     4,    -1,
       3,    59,   196,     4,    -1,     3,   203,     3,   137,     4,
     195,     4,    -1,   199,    -1,     3,    48,   199,     4,    -1,
       3,    48,   107,   199,     4,    -1,     3,    59,   196,     4,
      -1,     3,   203,     3,   137,     4,   195,     4,    -1,   196,
     194,    -1,   194,    -1,     3,    48,   200,     4,    -1,     3,
      48,   107,   200,     4,    -1,   200,    -1,   198,   199,    -1,
     199,    -1,     3,    59,   198,     4,    -1,     3,   203,     3,
     137,     4,   199,     4,    -1,     3,    57,   200,     4,    -1,
       3,    95,   200,     4,    -1,     3,    96,   200,     4,    -1,
       3,    97,   189,   200,     4,    -1,     3,    98,   200,     4,
      -1,     3,    99,   200,   200,     4,    -1,     3,   100,   200,
     200,     4,    -1,     3,   101,   189,   200,   200,     4,    -1,
       3,   102,   189,   189,   200,     4,    -1,     3,   103,   189,
     200,     4,    -1,   205,    -1,     3,    64,   200,     4,    -1,
       3,    59,   202,     4,    -1,     3,    60,   202,     4,    -1,
       3,    63,   200,   200,     4,    -1,     3,   203,     3,   137,
       4,   200,     4,    -1,     3,   204,     3,   137,     4,   200,
       4,    -1,     3,   192,   187,   187,     4,    -1,   201,   193,
      -1,   193,    -1,   202,   200,    -1,   200,    -1,    62,    -1,
      61,    -1,     3,   131,   144,     4,    -1,     3,   131,   137,
       4,    -1,     3,   132,   144,     4,    -1,     3,    42,   128,
       4,    -1,     3,    42,     1,     4,    -1,     3,    43,   133,
       4,    -1,     3,    43,     1,     4,    -1,     3,    35,   199,
       4,    -1,     3,    35,     1,     4,    -1,     3,    35,   194,
       4,    -1,     3,    35,     1,     4,    -1,   212,   213,    -1,
     213,    -1,   217,    -1,   218,    -1,   219,    -1,   221,    -1,
     216,    -1,   214,    -1,     3,    10,   123,   209,     4,    -1,
      40,    -1,     3,   215,   206,   200,     4,    -1,     3,    36,
     107,   226,     3,   137,     4,    46,   193,    51,   157,     4,
      -1,     3,    36,     1,     4,    -1,     3,    38,   107,   226,
       3,   137,     4,    46,   200,    51,   157,     4,    -1,     3,
      38,     1,     4,    -1,     3,    37,   107,   226,     3,   137,
       4,    46,   200,    51,   172,     4,    -1,     3,    37,     1,
       4,    -1,   106,     3,   138,     4,    -1,    -1,     3,    39,
     107,   226,     3,   137,     4,   220,    55,   176,   222,     4,
      -1,     3,    39,     1,     4,    -1,   222,    51,   162,    -1,
     222,    47,   223,    -1,    -1,   225,    -1,     3,    59,   224,
       4,    -1,   224,   223,    -1,    -1,     3,    56,   200,     4,
      -1,     3,    57,   200,     4,    -1,     3,    58,   200,     4,
      -1,     3,    48,   107,   225,     4,    -1,     3,    48,   225,
       4,    -1,    45,    -1,    14,    -1,    15,    -1,    18,    -1,
      17,    -1,    19,    -1,    20,    -1,    21,    -1,    23,    -1,
      24,    -1,    29,    -1,    28,    -1,    27,    -1,    25,    -1,
      26,    -1,     5,    -1,    16,    -1,    22,    -1,    30,    -1,
      31,    -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,
     107,    -1,     3,    41,   140,     4,    -1,     3,    44,   143,
       4,    -1,     3,    11,     3,    68,   107,     4,     3,    69,
     107,     4,   231,     4,    -1,     3,    11,     3,    68,     1,
      -1,   126,   231,    -1,   232,   231,    -1,   233,   231,    -1,
     235,   231,    -1,   211,   231,    -1,   236,   231,    -1,   237,
     231,    -1,    -1,     3,    71,   140,     4,    -1,     3,    70,
     154,     4,    -1,    72,    -1,     3,   234,   193,     4,    -1,
       3,    77,   238,   239,     4,    -1,     3,    77,     1,     4,
      -1,     3,    74,    75,   109,    76,   109,     4,    -1,     3,
      74,    75,   109,     4,    -1,     3,    74,    76,   109,     4,
      -1,    78,    -1,    79,    -1,     3,   240,     4,    -1,   191,
      -1,   189,    -1,    82,    -1,     3,   104,   107,     4,    -1,
       3,    82,     4,    -1,   112,   239,   241,    -1,   113,   239,
     239,    -1,   115,   239,   242,    -1,   114,   239,   239,    -1,
     239,    -1,   239,   241,    -1,   239,    -1,   239,   242,    -1,
     244,   243,    -1,    28,   110,   243,    -1,    28,   109,   243,
      -1,    -1,   247,    93,   245,    -1,   245,    -1,   246,     6,
     247,     7,    -1,   246,    -1,     3,   107,   141,     4,    -1,
     110,    -1,   109,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   260,   260,   261,   262,   266,   272,   279,   280,   281,
     282,   284,   286,   288,   289,   292,   296,   299,   301,   303,
     304,   308,   315,   322,   323,   328,   330,   335,   337,   345,
     353,   355,   363,   368,   370,   374,   376,   383,   383,   386,
     399,   408,   417,   424,   430,   437,   439,   445,   454,   464,
     469,   470,   474,   475,   483,   490,   499,   505,   507,   509,
     516,   522,   526,   530,   534,   539,   546,   551,   553,   557,
     559,   563,   576,   578,   580,   583,   587,   593,   594,   596,
     598,   607,   608,   609,   610,   611,   615,   616,   620,   622,
     624,   631,   632,   633,   635,   639,   641,   649,   651,   659,
     664,   669,   672,   679,   680,   684,   686,   688,   692,   696,
     702,   706,   710,   716,   718,   726,   731,   737,   738,   742,
     743,   747,   749,   751,   758,   759,   760,   762,   767,   769,
     771,   773,   775,   780,   786,   792,   797,   798,   802,   803,
     805,   806,   807,   811,   813,   815,   817,   822,   824,   827,
     830,   836,   837,   838,   846,   850,   853,   857,   862,   869,
     874,   879,   884,   889,   891,   893,   895,   897,   902,   904,
     906,   908,   910,   912,   913,   914,   918,   920,   922,   928,
     929,   932,   935,   937,   940,   957,   959,   961,   967,   968,
     969,   970,   971,   983,   990,   992,   996,   997,  1001,  1003,
    1005,  1007,  1011,  1016,  1018,  1020,  1022,  1029,  1031,  1036,
    1038,  1042,  1047,  1049,  1054,  1056,  1059,  1061,  1063,  1065,
    1067,  1069,  1071,  1073,  1075,  1077,  1082,  1084,  1088,  1090,
    1093,  1096,  1099,  1102,  1108,  1110,  1115,  1117,  1127,  1134,
    1141,  1146,  1151,  1156,  1158,  1165,  1167,  1174,  1176,  1183,
    1185,  1192,  1193,  1197,  1198,  1199,  1200,  1201,  1202,  1205,
    1214,  1220,  1229,  1240,  1247,  1258,  1264,  1274,  1280,  1282,
    1285,  1303,  1310,  1312,  1314,  1318,  1320,  1325,  1328,  1332,
    1334,  1336,  1338,  1343,  1348,  1353,  1354,  1356,  1357,  1359,
    1361,  1362,  1363,  1364,  1365,  1367,  1370,  1373,  1374,  1375,
    1377,  1386,  1389,  1392,  1394,  1396,  1398,  1400,  1402,  1408,
    1412,  1417,  1429,  1436,  1437,  1438,  1439,  1440,  1442,  1444,
    1445,  1448,  1451,  1454,  1457,  1461,  1463,  1470,  1473,  1477,
    1484,  1485,  1490,  1491,  1492,  1493,  1494,  1496,  1500,  1501,
    1502,  1503,  1507,  1508,  1513,  1514,  1520,  1523,  1525,  1528,
    1532,  1536,  1542,  1546,  1552,  1560,  1561
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OPEN_BRAC", "CLOSE_BRAC", "MODULES",
  "OPEN_SQ", "CLOSE_SQ", "DOT", "CLASSES", "CLASS", "DEFINE", "PDDLDOMAIN",
  "REQS", "EQUALITY", "STRIPS", "ADL", "NEGATIVE_PRECONDITIONS", "TYPING",
  "DISJUNCTIVE_PRECONDS", "EXT_PRECS", "UNIV_PRECS", "QUANT_PRECS",
  "COND_EFFS", "FLUENTS", "OBJECTFLUENTS", "NUMERICFLUENTS", "ACTIONCOSTS",
  "TIME", "DURATIVE_ACTIONS", "DURATION_INEQUALITIES",
  "CONTINUOUS_EFFECTS", "DERIVED_PREDICATES", "TIMED_INITIAL_LITERALS",
  "PREFERENCES", "CONSTRAINTS", "ACTION", "PROCESS", "EVENT",
  "DURATIVE_ACTION", "DERIVED", "CONSTANTS", "PREDS", "FUNCTIONS", "TYPES",
  "ARGS", "PRE", "CONDITION", "PREFERENCE", "START_PRE", "END_PRE",
  "EFFECTS", "INITIAL_EFFECT", "FINAL_EFFECT", "INVARIANT", "DURATION",
  "AT_START", "AT_END", "OVER_ALL", "AND", "OR", "EXISTS", "FORALL",
  "IMPLY", "NOT", "WHEN", "WHENEVER", "EITHER", "PROBLEM", "FORDOMAIN",
  "INITIALLY", "OBJECTS", "GOALS", "EQ", "LENGTH", "SERIAL", "PARALLEL",
  "METRIC", "MINIMIZE", "MAXIMIZE", "HASHT", "DURATION_VAR", "TOTAL_TIME",
  "INCREASE", "DECREASE", "SCALE_UP", "SCALE_DOWN", "ASSIGN", "GREATER",
  "GREATEQ", "LESS", "LESSEQ", "Q", "COLON", "NUMBER", "ALWAYS",
  "SOMETIME", "WITHIN", "ATMOSTONCE", "SOMETIMEAFTER", "SOMETIMEBEFORE",
  "ALWAYSWITHIN", "HOLDDURING", "HOLDAFTER", "ISVIOLATED", "BOGUS",
  "CONTROL", "NAME", "FUNCTION_SYMBOL", "INTVAL", "FLOATVAL", "AT_TIME",
  "PLUS", "HYPHEN", "DIV", "MUL", "UMINUS", "$accept", "mystartsymbol",
  "c_domain", "c_preamble", "c_domain_name", "c_new_class", "c_class",
  "c_classes", "c_class_seq", "c_domain_require_def", "c_reqs",
  "c_pred_decls", "c_pred_decl", "c_new_pred_symbol", "c_pred_symbol",
  "c_init_pred_symbol", "c_func_decls", "c_func_decl", "c_ntype",
  "c_new_func_symbol", "c_typed_var_list", "c_control_params_list",
  "c_var_symbol_list", "c_typed_consts", "c_const_symbols",
  "c_new_const_symbols", "c_typed_types", "c_parameter_symbols",
  "c_declaration_var_symbol", "c_var_symbol", "c_const_symbol",
  "c_new_const_symbol", "c_either_type", "c_new_primitive_type",
  "c_primitive_type", "c_new_primitive_types", "c_primitive_types",
  "c_init_els", "c_timed_initial_literal", "c_effects", "c_effect",
  "c_a_effect", "c_p_effect", "c_p_effects", "c_conj_effect",
  "c_da_effect", "c_da_effects", "c_timed_effect",
  "c_cts_only_timed_effect", "c_da_cts_only_effect",
  "c_da_cts_only_effects", "c_a_effect_da", "c_p_effect_da",
  "c_p_effects_da", "c_f_assign_da", "c_proc_effect", "c_proc_effects",
  "c_f_exp_da", "c_binary_expr_da", "c_duration_constraint", "c_d_op",
  "c_d_value", "c_duration_constraints", "c_neg_simple_effect",
  "c_pos_simple_effect", "c_init_neg_simple_effect",
  "c_init_pos_simple_effect", "c_forall_effect", "c_cond_effect",
  "c_assignment", "c_f_exp", "c_f_exp_t", "c_number", "c_f_head",
  "c_ground_f_head", "c_comparison_op", "c_pre_goal_descriptor",
  "c_pref_con_goal", "c_pref_goal", "c_pref_con_goal_list",
  "c_pref_goal_descriptor", "c_constraint_goal_list", "c_constraint_goal",
  "c_goal_descriptor", "c_pre_goal_descriptor_list", "c_goal_list",
  "c_forall", "c_exists", "c_proposition", "c_derived_proposition",
  "c_init_proposition", "c_predicates", "c_functions_def",
  "c_constraints_def", "c_constraints_probdef", "c_structure_defs",
  "c_structure_def", "c_class_def", "c_rule_head", "c_derivation_rule",
  "c_action_def", "c_event_def", "c_process_def", "c_control",
  "c_durative_action_def", "c_da_def_body", "c_da_gd", "c_da_gds",
  "c_timed_gd", "c_args_head", "c_require_key", "c_domain_constants",
  "c_type_names", "c_problem", "c_problem_body", "c_objects",
  "c_initial_state", "c_goals", "c_goal_spec", "c_metric_spec",
  "c_length_spec", "c_optimization", "c_ground_f_exp",
  "c_binary_ground_f_exp", "c_binary_ground_f_pexps",
  "c_binary_ground_f_mexps", "c_plan", "c_step_t_d", "c_step_d", "c_step",
  "c_float", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   117,   118,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   120,   120,   120,   121,   122,   123,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     131,   131,   132,   133,   133,   134,   134,   135,   135,   136,
     137,   137,   137,   138,   138,   139,   139,   140,   140,   140,
     141,   141,   142,   142,   143,   143,   143,   144,   144,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   152,   153,
     153,   154,   154,   154,   154,   154,   155,   156,   156,   156,
     156,   157,   157,   157,   157,   157,   158,   158,   159,   159,
     159,   160,   160,   160,   160,   161,   161,   162,   162,   162,
     162,   162,   162,   163,   163,   164,   164,   164,   164,   164,
     165,   165,   165,   166,   166,   166,   166,   167,   167,   168,
     168,   169,   169,   169,   170,   170,   170,   170,   171,   171,
     171,   171,   171,   172,   172,   172,   173,   173,   174,   174,
     174,   174,   174,   175,   175,   175,   175,   176,   176,   176,
     176,   177,   177,   177,   178,   179,   179,   180,   181,   182,
     183,   184,   185,   186,   186,   186,   186,   186,   187,   187,
     187,   187,   187,   187,   187,   187,   188,   188,   188,   189,
     189,   190,   190,   190,   190,   191,   191,   191,   192,   192,
     192,   192,   192,   193,   193,   193,   193,   193,   194,   194,
     194,   194,   194,   195,   195,   195,   195,   196,   196,   197,
     197,   197,   198,   198,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   199,   200,   200,   200,   200,
     200,   200,   200,   200,   201,   201,   202,   202,   203,   204,
     205,   206,   207,   208,   208,   209,   209,   210,   210,   211,
     211,   212,   212,   213,   213,   213,   213,   213,   213,   214,
     215,   216,   217,   217,   218,   218,   219,   219,   220,   220,
     221,   221,   222,   222,   222,   223,   223,   224,   224,   225,
     225,   225,   225,   225,   226,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   228,
     229,   230,   230,   231,   231,   231,   231,   231,   231,   231,
     231,   232,   233,   234,   235,   236,   236,   237,   237,   237,
     238,   238,   239,   239,   239,   239,   239,   239,   240,   240,
     240,   240,   241,   241,   242,   242,   243,   243,   243,   243,
     244,   244,   245,   245,   246,   247,   247
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     5,     4,     2,     2,     2,
       2,     2,     2,     2,     1,     4,     1,     1,     4,     2,
       0,     4,     4,     2,     0,     2,     1,     4,     3,     1,
       1,     1,     1,     2,     0,     5,     3,     2,     0,     1,
       4,     4,     1,     4,     0,     3,     0,     4,     4,     1,
       2,     0,     2,     0,     4,     4,     1,     2,     3,     0,
       1,     1,     1,     1,     4,     1,     1,     2,     0,     2,
       0,     6,     2,     2,     2,     0,     4,     2,     2,     2,
       0,     1,     1,     1,     1,     1,     4,     1,     1,     1,
       1,     2,     2,     2,     0,     4,     4,     4,     7,     5,
       5,     1,     1,     2,     0,     4,     4,     5,     5,     3,
       5,     5,     3,     4,     7,     5,     1,     2,     0,     4,
       1,     1,     1,     1,     2,     2,     2,     0,     5,     5,
       5,     5,     5,     5,     5,     4,     2,     0,     1,     2,
       1,     1,     2,     5,     5,     5,     5,     4,     6,     9,
       9,     1,     1,     1,     1,     2,     0,     4,     1,     4,
       1,     7,     5,     5,     5,     5,     5,     5,     4,     5,
       5,     5,     5,     1,     2,     1,     5,     5,     1,     1,
       1,     4,     4,     1,     6,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     4,     7,     3,     2,     4,     5,
       4,     7,     1,     4,     5,     4,     7,     2,     1,     4,
       5,     1,     2,     1,     4,     7,     4,     4,     4,     5,
       4,     5,     5,     6,     6,     5,     1,     4,     4,     4,
       5,     7,     7,     5,     2,     1,     2,     1,     1,     1,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     5,
       1,     5,    12,     4,    12,     4,    12,     4,     4,     0,
      12,     4,     3,     3,     0,     1,     4,     2,     0,     4,
       4,     4,     5,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       4,    12,     5,     2,     2,     2,     2,     2,     2,     2,
       0,     4,     4,     1,     4,     5,     4,     7,     5,     5,
       1,     1,     3,     1,     1,     1,     4,     3,     3,     3,
       3,     3,     1,     2,     1,     2,     2,     3,     3,     0,
       3,     1,     4,     1,     4,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     349,     0,     0,   356,   355,     0,     2,     3,     4,   349,
     351,   353,     0,     0,    51,   349,   349,     1,     0,   346,
       0,     0,     0,     0,    62,     0,    51,   348,   347,     0,
     350,     0,     0,     6,     0,     0,     0,     0,     0,     0,
       0,    14,   252,   258,   257,   253,   254,   255,   256,     0,
       0,   354,    50,   352,     0,   312,     0,    20,     0,     0,
       0,     0,     0,     0,     0,   260,    53,     0,     0,    68,
       0,     5,    13,     7,    10,    11,    12,     0,   251,     9,
       8,    15,     0,    16,    20,     0,    17,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    63,     0,    49,    53,     0,     0,     0,    26,     0,
       0,     0,    56,     0,     0,     0,    19,    18,     0,     0,
      22,    21,   299,   285,   286,   300,   288,   287,   289,   290,
     291,   301,   292,   293,   297,   298,   296,   295,   294,   302,
     303,   304,   305,   306,   307,   308,    23,   248,     0,     0,
     238,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   247,   263,   284,     0,   267,     0,   265,     0,   271,
       0,   309,     0,    52,   244,     0,    29,    46,   243,    25,
     246,     0,   245,    33,   310,    65,     0,    67,    30,    31,
      46,     0,     0,   226,     0,   259,     0,     0,   213,     0,
       0,   179,   180,     0,     0,     0,     0,     0,     0,     0,
      46,    46,    46,    46,    46,     0,    66,    53,    53,    28,
       0,     0,    42,     0,    39,    46,    68,    68,     0,     0,
       0,   239,     0,     0,   192,   188,   189,   190,   191,    59,
       0,     0,     0,   261,     0,   216,   214,   212,   217,   218,
       0,   220,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    48,    47,    60,    46,    27,     0,    36,
       0,    55,    54,   241,   237,     0,     0,     0,     0,     0,
       0,     0,   183,     0,   173,   175,    46,    46,   320,   219,
     221,   222,     0,     0,   225,     0,     0,     0,     0,   269,
       0,    45,    46,    46,    38,   228,   236,   229,     0,   227,
     240,     0,    57,    59,    59,     0,     0,     0,     0,     0,
     174,     0,     0,     0,     0,   320,   320,     0,   320,   320,
     320,   320,   320,   223,   224,     0,     0,     0,     0,     0,
       0,    64,    69,    41,    40,     0,    35,   230,    61,    58,
       0,     0,     0,     0,     0,     0,     0,   233,     0,     0,
       0,    75,    53,   323,     0,     0,     0,   313,   317,   311,
     314,   315,   316,   318,   319,   215,     0,     0,   193,   211,
       0,     0,    44,     0,    37,   182,   181,     0,   168,     0,
       0,     0,    59,     0,     0,     0,     0,     0,   202,     0,
       0,     0,     0,     0,   330,   331,     0,     0,   197,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   274,   169,
     170,   172,   171,     0,   231,   232,   250,     0,     0,     0,
     249,     0,   322,    74,    73,    72,   160,   321,     0,     0,
     326,     0,   335,   187,   334,   333,     0,   324,     0,     0,
     196,   235,   211,     0,    46,     0,     0,    81,    83,    82,
      85,    84,   158,     0,     0,     0,   268,     0,     0,     0,
     156,   153,   152,   151,     0,     0,   184,     0,     0,   208,
       0,   202,    46,     0,     0,    32,    75,    59,   328,     0,
     329,     0,     0,    59,    59,     0,     0,     0,     0,     0,
     325,     0,   209,   194,   234,     0,     0,     0,     0,     0,
     262,   137,     0,     0,   266,   264,    44,     0,     0,     0,
       0,   270,     0,     0,     0,   198,   200,   207,     0,     0,
       0,     0,     0,     0,     0,     0,   337,     0,     0,     0,
       0,     0,     0,     0,   332,   210,     0,     0,     0,     0,
      80,    87,    88,    89,    80,    80,    90,     0,     0,    80,
      46,     0,     0,     0,    43,     0,     0,   147,   155,     0,
       0,   273,   275,     0,   272,   101,   102,   199,     0,   159,
       0,    76,   242,   327,   336,   186,   185,   342,   338,   339,
     341,   344,   340,     0,     0,    96,    94,     0,     0,     0,
       0,     0,    95,    77,    79,    78,   157,     0,     0,   135,
     136,     0,   178,     0,     0,     0,     0,     0,   154,     0,
       0,     0,     0,   278,     0,     0,     0,   104,     0,     0,
       0,     0,     0,     0,     0,    71,   343,   345,   195,     0,
       0,     0,     0,     0,     0,   162,     0,     0,   133,   134,
       0,     0,   148,     0,     0,     0,     0,     0,     0,     0,
     109,     0,     0,   120,   123,   121,   122,     0,     0,     0,
       0,     0,     0,    46,     0,     0,     0,   201,     0,    86,
      91,    92,    93,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   283,   279,   280,   281,   276,   277,
     127,     0,     0,     0,     0,     0,   105,   106,    97,   103,
       0,     0,   116,     0,     0,     0,     0,     0,     0,     0,
       0,    46,   164,   165,   166,   167,   163,   161,     0,     0,
       0,     0,   282,     0,     0,     0,     0,     0,     0,    99,
       0,   118,     0,     0,     0,     0,   100,     0,   107,   108,
       0,     0,   203,   205,     0,   176,   177,   149,   150,     0,
     119,   126,   124,   125,     0,     0,     0,   138,   140,   141,
       0,     0,     0,     0,   112,     0,     0,     0,     0,    46,
       0,     0,   204,     0,     0,     0,     0,     0,   139,   142,
     129,   130,   131,   132,   128,   113,   117,     0,     0,     0,
       0,    98,     0,     0,     0,     0,     0,   115,   110,   111,
       0,   206,     0,     0,     0,     0,     0,   143,   144,   146,
     145,   114
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,    35,    23,    84,   319,    36,    85,    37,
      89,   107,   108,   177,   239,   487,   110,   183,   346,   225,
     221,   415,   222,   102,    25,   103,   111,   279,   266,   349,
     312,   104,   217,   187,   218,   112,   300,   399,   433,   549,
     456,   550,   551,   639,   457,   574,   668,   575,   712,   713,
     775,   662,   663,   733,   664,   464,   561,   766,   767,   418,
     474,   617,   519,   552,   553,   434,   435,   554,   555,   556,
     618,   613,   284,   285,   445,   240,   377,   479,   634,   480,
     378,   197,   335,   379,   453,   275,   509,   242,   193,   114,
     436,    38,    39,    40,   326,    41,    42,    43,    70,    44,
      45,    46,    47,   340,    48,   475,   571,   659,   572,   164,
     146,    49,    50,     7,   327,   328,   329,   366,   330,   331,
     332,   406,   587,   499,   588,   592,     8,     9,    10,    11,
      12
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -700
static const yytype_int16 yypact[] =
{
      68,    39,   150,  -700,  -700,    26,  -700,  -700,  -700,    71,
    -700,    61,   -23,    72,   -29,    71,    71,  -700,   -24,  -700,
     231,    84,    13,   201,  -700,   108,   -29,  -700,  -700,   184,
    -700,    88,    29,  -700,   746,   199,   215,   215,   215,   215,
     215,   226,  -700,  -700,  -700,  -700,  -700,  -700,  -700,   215,
     215,  -700,  -700,  -700,   260,  -700,   262,   136,   164,   449,
     277,    40,    44,    47,    51,  -700,   172,   319,   269,  -700,
     293,  -700,  -700,  -700,  -700,  -700,  -700,   763,  -700,  -700,
    -700,  -700,   301,  -700,   136,   306,  -700,   326,   330,   651,
     333,   669,   346,   350,   316,   359,   316,   361,   316,   399,
     316,  -700,   404,   299,   172,   411,    59,   417,   430,   447,
     368,   488,    27,   -19,   493,   434,  -700,  -700,   464,   507,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,  -700,   493,   511,
    -700,   493,   493,   275,   493,   493,   493,   275,   275,   275,
     518,  -700,  -700,  -700,   527,  -700,   529,  -700,   550,  -700,
     552,  -700,    55,  -700,  -700,   556,  -700,   424,  -700,  -700,
    -700,    64,  -700,  -700,  -700,  -700,    55,  -700,  -700,  -700,
     424,   628,   583,  -700,   482,  -700,   589,   402,  -700,   592,
     594,  -700,  -700,   493,   608,   493,   493,   493,   275,   493,
     424,   424,   424,   424,   424,   546,  -700,   172,   172,  -700,
     510,   614,   508,   618,  -700,   424,  -700,  -700,   624,   493,
     493,  -700,   493,   493,   195,  -700,  -700,  -700,  -700,  -700,
     176,   626,   633,  -700,   642,  -700,  -700,  -700,  -700,  -700,
     643,  -700,   644,   645,   493,   493,   646,   653,   655,   657,
     658,   659,  -700,  -700,  -700,  -700,   424,  -700,    55,  -700,
     660,  -700,  -700,  -700,  -700,   428,   433,   493,   689,   207,
     703,   587,  -700,   176,  -700,  -700,   424,   424,   692,  -700,
    -700,  -700,   694,   695,  -700,   511,   650,   661,   662,   598,
      78,  -700,   424,   424,   593,  -700,  -700,  -700,   701,  -700,
    -700,   603,  -700,   704,  -700,   176,   176,   176,   176,   705,
    -700,   710,   723,   726,   480,   692,   692,   728,   692,   692,
     692,   692,   692,  -700,  -700,   729,   731,   493,   493,   733,
     682,  -700,  -700,  -700,  -700,   654,  -700,  -700,  -700,  -700,
     209,   246,   176,   106,   176,   176,   630,  -700,   493,   493,
     327,  -700,   172,  -700,   349,    60,   731,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,   338,   693,  -700,  -700,
     706,   709,   -28,   751,  -700,  -700,  -700,   757,  -700,   758,
     772,   774,  -700,   775,   776,   793,   474,   794,  -700,   457,
     800,   699,   713,   808,  -700,  -700,   239,   809,  -700,    65,
     486,   811,   818,   820,   818,   826,   719,   718,  -700,  -700,
    -700,  -700,  -700,   259,  -700,  -700,  -700,    66,   828,   834,
    -700,   245,  -700,  -700,  -700,  -700,  -700,  -700,    49,   836,
    -700,   512,  -700,  -700,  -700,  -700,   842,  -700,   493,   843,
    -700,  -700,  -700,   498,   424,   345,   844,  -700,  -700,  -700,
    -700,  -700,  -700,   138,   845,   846,  -700,   759,   848,   849,
    -700,  -700,  -700,  -700,   762,   145,  -700,   511,   851,  -700,
     502,  -700,   424,   853,    19,  -700,  -700,  -700,  -700,   748,
    -700,   854,   752,  -700,  -700,   239,   239,   239,   239,   856,
    -700,   857,  -700,  -700,  -700,   858,   356,   860,   493,   861,
    -700,  -700,    19,    19,  -700,  -700,   -28,   121,   121,   516,
     784,  -700,   863,   864,   865,  -700,  -700,  -700,   866,   761,
     867,   416,   275,   522,   263,   868,  -700,   869,   270,   272,
     239,   239,   239,   239,  -700,  -700,   731,   870,   638,   871,
     873,  -700,  -700,  -700,   873,   873,  -700,   -19,   874,   873,
     424,   525,    46,    46,  -700,   785,   787,  -700,  -700,   176,
     390,  -700,  -700,   357,  -700,  -700,  -700,  -700,   877,  -700,
     878,  -700,  -700,  -700,  -700,  -700,  -700,   239,  -700,  -700,
    -700,   239,  -700,   879,   775,  -700,  -700,    19,    19,    19,
      19,    19,  -700,  -700,  -700,  -700,  -700,   880,   881,  -700,
    -700,   766,  -700,   882,   883,   807,   810,   885,  -700,    76,
     493,   493,   493,  -700,   886,   889,   889,  -700,   863,   493,
      19,    19,   890,   542,   891,  -700,  -700,  -700,  -700,   531,
     176,   176,   176,   176,   176,  -700,   818,   125,  -700,  -700,
     176,   176,  -700,   182,   893,   894,   895,   896,   897,   540,
    -700,   656,   898,  -700,  -700,  -700,  -700,   899,   555,   864,
     901,   173,   173,   424,    77,   828,   902,  -700,   454,  -700,
    -700,  -700,  -700,   903,   904,   905,   906,   907,   908,   176,
     814,   909,   910,   911,  -700,  -700,  -700,  -700,  -700,  -700,
    -700,    19,    19,    19,    19,    19,  -700,  -700,  -700,  -700,
     912,   429,  -700,   913,   712,   914,   915,   916,   511,   917,
     560,   424,  -700,  -700,  -700,  -700,  -700,  -700,   918,   919,
     920,   921,  -700,   575,   203,   203,   203,   203,   203,  -700,
     922,  -700,   493,    19,    19,   924,  -700,   125,  -700,  -700,
     864,   925,  -700,  -700,   926,  -700,  -700,  -700,  -700,   524,
    -700,  -700,  -700,  -700,   721,   -15,   927,  -700,  -700,  -700,
     928,   929,   930,   931,  -700,   577,   901,    46,    46,   424,
     197,   932,  -700,   877,   203,   203,   203,   203,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -700,   933,   934,   935,
     936,  -700,   937,   203,   203,   203,   203,  -700,  -700,  -700,
     901,  -700,   938,   939,   940,   941,   942,  -700,  -700,  -700,
    -700,  -700
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -700,  -700,  -700,   756,  -700,  -700,   839,  -700,   822,   421,
    -700,   840,  -700,  -700,   815,  -700,  -700,  -700,  -700,  -700,
    -179,   431,  -247,  -180,   923,   847,   365,  -286,  -700,  -700,
      58,  -700,  -127,  -700,  -178,  -700,  -700,   466,  -700,  -172,
    -410,  -700,  -700,  -700,  -700,  -606,  -700,  -700,  -700,  -699,
    -700,   324,  -700,  -700,   220,   393,  -700,  -238,  -700,   436,
      85,   -45,  -700,  -398,  -394,  -700,  -700,  -397,  -391,  -494,
    -185,  -516,  -152,  -411,  -700,  -700,  -353,  -351,   174,   281,
    -700,  -700,   -60,  -112,  -700,   730,   -88,  -700,  -402,  -700,
     475,  -700,   872,  -700,  -700,  -700,   943,  -700,  -700,  -700,
    -700,  -700,  -700,  -700,  -700,  -700,  -509,  -700,  -568,   219,
    -700,  -700,  -700,  -700,   513,  -700,  -700,  -700,  -700,  -700,
    -700,  -700,  -382,  -700,   374,   371,   242,  -700,   944,  -700,
     946
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -81
static const yytype_int16 yytable[] =
{
      92,   203,   192,   160,   465,   207,   208,   209,   227,   397,
     462,   228,   462,   407,   458,   460,   458,   460,   459,   301,
     459,   461,   531,   461,   446,    31,    17,   350,   351,   576,
      55,   257,   258,   259,   260,   261,   196,   263,   264,   199,
     200,    93,   204,   205,   206,    95,   270,   614,    97,   611,
      13,   655,    99,   488,   188,   283,   255,   451,   215,   226,
     175,   403,   709,   710,   220,   223,   788,    20,   191,    91,
      21,     1,    26,   532,    18,    22,   796,   797,    24,   653,
      91,    32,   341,    14,    26,   -46,   693,    18,   189,   198,
     303,   250,   789,   252,   253,   254,     2,   256,   321,     2,
     504,   562,   563,   241,   462,   558,   423,   322,   323,   280,
     388,   816,    51,   540,   541,   542,   543,   274,   274,   669,
     277,   278,   342,   343,   344,   489,   612,   282,   280,   527,
     352,   353,   354,   355,   185,   416,    56,   247,   404,   405,
     186,   302,   292,   293,   781,   682,    14,    94,   462,   521,
     699,    96,   462,   462,    98,   715,   716,   462,   100,   589,
     590,   591,   216,   306,   306,   308,   176,   387,   389,   390,
     391,   224,   448,   477,   576,   576,   714,     3,     4,   280,
       3,     4,   400,   654,   718,   216,   640,   641,   642,   643,
     644,    53,   522,   593,   471,    54,   523,   511,   281,   -30,
     280,   534,    33,    71,    34,   689,   764,   538,   539,   591,
     472,   310,   473,   385,   282,   201,   202,   281,    34,   671,
     672,   512,   513,   462,   462,   380,   381,   665,   665,    77,
     619,   666,   666,   282,   201,   202,   688,   462,   620,   621,
     622,   680,   441,    83,   462,   681,   393,   394,   458,   460,
     386,    19,   459,   612,   444,   461,   576,    27,    28,    15,
      16,   798,   799,   476,    81,   281,    82,   582,   281,   416,
     109,    86,   -34,   -34,   585,   505,   586,   729,    90,   101,
      91,   282,   201,   202,   282,   201,   202,   -30,   411,   281,
     734,   735,   736,   737,   738,   765,   113,   449,   452,   311,
     398,   311,   -30,   528,   115,   282,   201,   202,   429,   483,
     117,   282,   201,   202,    24,   166,    24,   168,   484,   170,
     105,   442,   106,   769,   769,   769,   769,   769,   395,   118,
     396,   462,   777,   778,   120,   762,   501,   147,   311,   763,
       3,     4,   408,   444,   444,   444,   444,   443,   201,   202,
     161,   311,   485,    24,   162,   311,   486,   547,   624,   548,
     -80,   163,   311,   165,   311,   167,    24,   478,   481,   527,
      24,   181,   182,   769,   769,   769,   769,    24,   603,    24,
     580,   608,   604,   605,   201,   202,   409,   607,   444,   444,
     444,   444,   769,   769,   769,   769,   559,   410,   230,   231,
     150,   232,   233,   169,   506,    91,   246,   150,   171,   507,
     508,   234,   172,   625,   626,   174,   627,   524,   188,   150,
     398,   178,   628,   629,   401,   402,   235,   236,   237,   238,
     740,   191,   305,   106,   594,   444,   191,   307,   619,   444,
     630,   631,   599,   600,   601,   189,   620,   621,   622,   623,
      88,   180,   189,   -24,   -24,   683,   684,   685,   686,   687,
     431,   432,   690,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   632,   683,   684,   741,   376,
     450,   150,   184,    59,   717,   742,   191,   770,   771,   772,
     773,   376,   503,   194,   728,   396,   526,    68,   656,   657,
     658,   195,   743,   744,    91,   360,   220,   670,   507,   417,
     567,   210,   427,   313,   314,   431,   581,   188,   463,   609,
     211,   148,   212,   428,   678,   679,   150,   597,   598,   599,
     600,   601,   754,   570,   698,   676,   803,   804,   805,   806,
     361,   362,   363,   213,   364,   214,   -24,   365,   573,   708,
     219,   189,   780,   396,   753,   812,   813,   814,   815,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   759,   760,
     711,   795,   768,   768,   768,   768,   768,   243,   507,   244,
     674,   271,   272,   245,   491,   391,   248,   188,   249,   148,
     800,   675,   565,   566,   150,   691,   692,   701,   702,   703,
     704,   705,   251,   262,   719,   481,   492,   265,   267,   493,
     494,   268,   269,   745,   495,   496,   497,   498,   273,   286,
     776,   189,   768,   768,   768,   768,   287,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   288,   289,   290,   291,
     294,   768,   768,   768,   768,   121,   122,   295,   751,   296,
     398,   297,   298,   299,   304,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   229,   230,   231,
     150,   232,   233,   309,   320,   324,   336,   596,   333,   334,
     150,   234,   507,   508,   339,   347,   345,   337,   338,   325,
     348,   188,   -17,   356,   357,   700,   235,   236,   237,   238,
     507,   597,   598,   599,   600,   601,   148,   358,   149,   188,
     359,   150,   369,   375,   376,   189,   382,   383,   392,   701,
     702,   703,   704,   705,   412,   189,   325,   325,   384,   325,
     325,   325,   325,   325,   417,    57,    58,   413,   145,    59,
     414,   419,   420,   189,   151,   152,   153,   154,   155,   156,
     157,   158,   159,    58,   468,   469,   421,   470,   422,   424,
     425,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,   471,    72,    73,    74,    75,    76,   426,   430,    61,
      62,    63,    64,    65,   437,    79,    80,   472,   438,   473,
     313,   314,   440,   447,   454,   315,   316,   317,   318,   313,
     314,   455,   439,   463,   315,   316,   317,   747,   313,   314,
     466,   396,   467,   784,   785,   786,   787,   482,   367,   368,
     490,   370,   371,   372,   373,   374,   500,   502,   510,   514,
     515,   517,   518,   516,   520,   525,   529,   535,   536,   537,
     544,   545,   546,   557,   560,   569,   570,   573,   485,   577,
     578,   579,   583,   584,   595,   602,   548,   615,   606,   616,
     633,   647,   635,   638,   645,   646,   648,   649,   650,   652,
     660,   651,   661,   673,   729,   677,   653,    87,   694,   695,
     696,   697,   706,   707,   711,   721,   116,   722,   723,   724,
     725,   726,   727,   730,   731,   732,   739,   746,   748,   749,
     750,   752,   755,   756,   757,   758,   774,   779,   190,   782,
     783,   790,   791,   792,   793,   794,   801,   807,   808,   809,
     810,   811,   817,   818,   819,   820,   821,   564,   179,    52,
     667,   173,   533,   761,   610,   568,   720,   802,   530,   119,
     276,   636,   637,     0,     0,    30,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    78
};

static const yytype_int16 yycheck[] =
{
      60,   153,   114,    91,   414,   157,   158,   159,   186,   360,
     412,   190,   414,   366,   412,   412,   414,   414,   412,   266,
     414,   412,     3,   414,   406,    12,     0,   313,   314,   523,
       1,   210,   211,   212,   213,   214,   148,   217,   218,   151,
     152,     1,   154,   155,   156,     1,   225,   563,     1,     3,
      11,   619,     1,     4,    73,   240,   208,   410,     3,   186,
       1,     1,   668,   669,    92,     1,    81,     6,     3,     3,
      93,     3,    14,   484,     3,     3,   775,   776,   107,     3,
       3,    68,     4,   107,    26,   113,   654,     3,   107,   149,
     268,   203,   107,   205,   206,   207,    28,   209,   283,    28,
     453,   512,   513,   191,   506,   507,   392,   286,   287,     3,
       4,   810,     4,   495,   496,   497,   498,   229,   230,   628,
     232,   233,   300,   302,   303,    76,    80,   108,     3,   480,
     315,   316,   317,   318,   107,   382,   107,   197,    78,    79,
     113,   268,   254,   255,   750,   639,   107,   107,   550,     4,
     659,   107,   554,   555,   107,   671,   672,   559,   107,   541,
     542,   543,   107,   275,   276,   277,   107,   352,   353,   354,
     355,   107,   107,   107,   668,   669,     3,   109,   110,     3,
     109,   110,   362,   107,   107,   107,   597,   598,   599,   600,
     601,     7,    47,   546,    73,   107,    51,    59,    92,     4,
       3,   487,     1,     4,     3,    80,     3,   493,   494,   591,
      89,     4,    91,     4,   108,   109,   110,    92,     3,   630,
     631,    83,    84,   625,   626,   337,   338,   625,   626,     3,
      48,   625,   626,   108,   109,   110,   646,   639,    56,    57,
      58,   639,     3,   107,   646,   639,   358,   359,   646,   646,
       4,     9,   646,    80,   406,   646,   750,    15,    16,   109,
     110,   777,   778,     4,     4,    92,     4,     4,    92,   516,
       1,   107,     3,     4,     4,   454,     4,    80,     1,   107,
       3,   108,   109,   110,   108,   109,   110,    92,   376,    92,
     701,   702,   703,   704,   705,    92,     3,   409,   410,    92,
     360,    92,   107,   482,     3,   108,   109,   110,   396,    64,
       4,   108,   109,   110,   107,    96,   107,    98,    73,   100,
       1,    82,     3,   734,   735,   736,   737,   738,     1,     3,
       3,   733,   743,   744,     4,   733,   448,     4,    92,   733,
     109,   110,     4,   495,   496,   497,   498,   108,   109,   110,
       4,    92,   107,   107,     4,    92,   111,     1,     1,     3,
       4,    45,    92,     4,    92,     4,   107,   427,   428,   720,
     107,     3,     4,   784,   785,   786,   787,   107,   550,   107,
     532,   560,   554,   555,   109,   110,    48,   559,   540,   541,
     542,   543,   803,   804,   805,   806,   508,    59,    60,    61,
      62,    63,    64,     4,    59,     3,     4,    62,     4,    64,
      65,    73,   113,    56,    57,     4,    59,   477,    73,    62,
     480,     4,    65,    66,    75,    76,    88,    89,    90,    91,
       1,     3,     4,     3,   546,   587,     3,     4,    48,   591,
      83,    84,    85,    86,    87,   107,    56,    57,    58,    59,
       1,     4,   107,     4,     5,   640,   641,   642,   643,   644,
       3,     4,   647,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,   573,   671,   672,    59,     3,
       4,    62,     4,    13,   673,    66,     3,   735,   736,   737,
     738,     3,     4,    69,   689,     3,     4,    43,   620,   621,
     622,     4,    83,    84,     3,    35,    92,   629,    64,     3,
       4,     3,    48,   107,   108,     3,     4,    73,     3,     4,
       3,    57,     3,    59,     3,     4,    62,    83,    84,    85,
      86,    87,   721,     3,     4,   633,   784,   785,   786,   787,
      70,    71,    72,     3,    74,     3,   107,    77,     3,     4,
       4,   107,   747,     3,     4,   803,   804,   805,   806,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     3,     4,
       3,     4,   734,   735,   736,   737,   738,     4,    64,   107,
      48,   226,   227,     4,    82,   780,     4,    73,     4,    57,
     779,    59,   517,   518,    62,   650,   651,    83,    84,    85,
      86,    87,     4,    67,   674,   675,   104,   107,     4,   107,
     108,   113,     4,   711,   112,   113,   114,   115,     4,     3,
     742,   107,   784,   785,   786,   787,     3,    95,    96,    97,
      98,    99,   100,   101,   102,   103,     4,     4,     4,     4,
       4,   803,   804,   805,   806,     4,     5,     4,   718,     4,
     720,     4,     4,     4,     4,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    59,    60,    61,
      62,    63,    64,     4,   107,     3,    46,    59,     4,     4,
      62,    73,    64,    65,   106,     4,   113,    46,    46,   288,
     107,    73,     8,     8,     4,    59,    88,    89,    90,    91,
      64,    83,    84,    85,    86,    87,    57,     4,    59,    73,
       4,    62,     4,     4,     3,   107,     3,    55,   108,    83,
      84,    85,    86,    87,    51,   107,   325,   326,    94,   328,
     329,   330,   331,   332,     3,     9,    10,    51,   107,    13,
      51,     4,     4,   107,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    10,    56,    57,     4,    59,     4,     4,
       4,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    73,    36,    37,    38,    39,    40,     4,     4,    36,
      37,    38,    39,    40,     4,    49,    50,    89,   109,    91,
     107,   108,     4,     4,     3,   112,   113,   114,   115,   107,
     108,     3,   109,     3,   112,   113,   114,   115,   107,   108,
       4,     3,   113,   112,   113,   114,   115,     3,   325,   326,
       4,   328,   329,   330,   331,   332,     4,     4,     4,     4,
       4,     3,     3,    94,    92,     4,     3,   109,     4,   107,
       4,     4,     4,     3,     3,    81,     3,     3,   107,     4,
       4,     4,     4,     4,     4,     4,     3,    92,     4,    92,
       3,   115,     4,     4,     4,     4,     4,     4,    81,     4,
       4,    81,     3,     3,    80,     4,     3,    58,     4,     4,
       4,     4,     4,     4,     3,     3,    84,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   113,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   516,   108,    26,
     626,   104,   486,   733,   561,   519,   675,   783,   483,    87,
     230,   587,   591,    -1,    -1,    21,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    28,   109,   110,   118,   119,   230,   243,   244,
     245,   246,   247,    11,   107,   109,   110,     0,     3,   243,
       6,    93,     3,   121,   107,   141,   147,   243,   243,   247,
     245,    12,    68,     1,     3,   120,   124,   126,   208,   209,
     210,   212,   213,   214,   216,   217,   218,   219,   221,   228,
     229,     4,   141,     7,   107,     1,   107,     9,    10,    13,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
     215,     4,   120,   120,   120,   120,   120,     3,   213,   120,
     120,     4,     4,   107,   122,   125,   107,   123,     1,   127,
       1,     3,   199,     1,   107,     1,   107,     1,   107,     1,
     107,   107,   140,   142,   148,     1,     3,   128,   129,     1,
     133,   143,   152,     3,   206,     3,   125,     4,     3,   209,
       4,     4,     5,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,   107,   227,     4,    57,    59,
      62,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     203,     4,     4,    45,   226,     4,   226,     4,   226,     4,
     226,     4,   113,   142,     4,     1,   107,   130,     4,   128,
       4,     3,     4,   134,     4,   107,   113,   150,    73,   107,
     131,     3,   200,   205,    69,     4,   200,   198,   199,   200,
     200,   109,   110,   189,   200,   200,   200,   189,   189,   189,
       3,     3,     3,     3,     3,     3,   107,   149,   151,     4,
      92,   137,   139,     1,   107,   136,   149,   151,   137,    59,
      60,    61,    63,    64,    73,    88,    89,    90,    91,   131,
     192,   203,   204,     4,   107,     4,     4,   199,     4,     4,
     200,     4,   200,   200,   200,   189,   200,   137,   137,   137,
     137,   137,    67,   140,   140,   107,   145,     4,   113,     4,
     137,   143,   143,     4,   200,   202,   202,   200,   200,   144,
       3,    92,   108,   187,   189,   190,     3,     3,     4,     4,
       4,     4,   200,   200,     4,     4,     4,     4,     4,     4,
     153,   139,   149,   151,     4,     4,   200,     4,   200,     4,
       4,    92,   147,   107,   108,   112,   113,   114,   115,   123,
     107,   187,   137,   137,     3,   126,   211,   231,   232,   233,
     235,   236,   237,     4,     4,   199,    46,    46,    46,   106,
     220,     4,   151,   137,   137,   113,   135,     4,   107,   146,
     144,   144,   187,   187,   187,   187,     8,     4,     4,     4,
      35,    70,    71,    72,    74,    77,   234,   231,   231,     4,
     231,   231,   231,   231,   231,     4,     3,   193,   197,   200,
     200,   200,     3,    55,    94,     4,     4,   187,     4,   187,
     187,   187,   108,   200,   200,     1,     3,   194,   199,   154,
     140,    75,    76,     1,    78,    79,   238,   193,     4,    48,
      59,   203,    51,    51,    51,   138,   139,     3,   176,     4,
       4,     4,     4,   144,     4,     4,     4,    48,    59,   203,
       4,     3,     4,   155,   182,   183,   207,     4,   109,   109,
       4,     3,    82,   108,   189,   191,   239,     4,   107,   200,
       4,   193,   200,   201,     3,     3,   157,   161,   180,   181,
     184,   185,   205,     3,   172,   157,     4,   113,    56,    57,
      59,    73,    89,    91,   177,   222,     4,   107,   199,   194,
     196,   199,     3,    64,    73,   107,   111,   132,     4,    76,
       4,    82,   104,   107,   108,   112,   113,   114,   115,   240,
       4,   200,     4,     4,   193,   137,    59,    64,    65,   203,
       4,    59,    83,    84,     4,     4,    94,     3,     3,   179,
      92,     4,    47,    51,   199,     4,     4,   194,   137,     3,
     207,     3,   190,   154,   144,   109,     4,   107,   144,   144,
     239,   239,   239,   239,     4,     4,     4,     1,     3,   156,
     158,   159,   180,   181,   184,   185,   186,     3,   205,   200,
       3,   173,   190,   190,   138,   177,   177,     4,   176,    81,
       3,   223,   225,     3,   162,   164,   186,     4,     4,     4,
     189,     4,     4,     4,     4,     4,     4,   239,   241,   239,
     239,   239,   242,   193,   200,     4,    59,    83,    84,    85,
      86,    87,     4,   156,   156,   156,     4,   156,   137,     4,
     172,     3,    80,   188,   188,    92,    92,   178,   187,    48,
      56,    57,    58,    59,     1,    56,    57,    59,    65,    66,
      83,    84,   203,     3,   195,     4,   241,   242,     4,   160,
     190,   190,   190,   190,   190,     4,     4,   115,     4,     4,
      81,    81,     4,     3,   107,   225,   200,   200,   200,   224,
       4,     3,   168,   169,   171,   180,   181,   168,   163,   223,
     200,   190,   190,     3,    48,    59,   203,     4,     3,     4,
     180,   181,   186,   187,   187,   187,   187,   187,   157,    80,
     187,   178,   178,   225,     4,     4,     4,     4,     4,   223,
      59,    83,    84,    85,    86,    87,     4,     4,     4,   162,
     162,     3,   165,   166,     3,   188,   188,   137,   107,   199,
     196,     3,     4,     4,     4,     4,     4,     4,   187,    80,
       4,     4,     4,   170,   190,   190,   190,   190,   190,     4,
       1,    59,    66,    83,    84,   203,     4,   115,     4,     4,
       4,   199,     4,     4,   137,     4,     4,     4,     4,     3,
       4,   171,   180,   181,     3,    92,   174,   175,   189,   190,
     174,   174,   174,   174,     4,   167,   200,   190,   190,     3,
     187,   162,     4,     4,   112,   113,   114,   115,    81,   107,
       4,     4,     4,     4,     4,     4,   166,   166,   188,   188,
     137,     4,   195,   174,   174,   174,   174,     4,     4,     4,
       4,     4,   174,   174,   174,   174,   166,     4,     4,     4,
       4,     4
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

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

/* Line 1464 of yacc.c  */
#line 260 "pddl+.yacc"
    {top_thing= (yyvsp[(1) - (1)].t_domain); current_analysis->the_domain= (yyvsp[(1) - (1)].t_domain);;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 261 "pddl+.yacc"
    {top_thing= (yyvsp[(1) - (1)].t_problem); current_analysis->the_problem= (yyvsp[(1) - (1)].t_problem);;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 262 "pddl+.yacc"
    {top_thing= (yyvsp[(1) - (1)].t_plan); ;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 267 "pddl+.yacc"
    {(yyval.t_domain)= (yyvsp[(4) - (5)].t_domain); (yyval.t_domain)->name= (yyvsp[(3) - (5)].cp);delete [] (yyvsp[(3) - (5)].cp);
	if (types_used && !types_defined) {
		yyerrok; log_error(E_FATAL,"Syntax error in domain - no :types section, but types used in definitions.");
	}
	;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 273 "pddl+.yacc"
    {yyerrok; (yyval.t_domain)=static_cast<domain*>(NULL);
       	log_error(E_FATAL,"Syntax error in domain"); ;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 279 "pddl+.yacc"
    {(yyval.t_domain)= (yyvsp[(2) - (2)].t_domain); (yyval.t_domain)->req= (yyvsp[(1) - (2)].t_pddl_req_flag);;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 280 "pddl+.yacc"
    {types_defined = true; (yyval.t_domain)= (yyvsp[(2) - (2)].t_domain); (yyval.t_domain)->types= (yyvsp[(1) - (2)].t_type_list);;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 281 "pddl+.yacc"
    {(yyval.t_domain)= (yyvsp[(2) - (2)].t_domain); (yyval.t_domain)->constants= (yyvsp[(1) - (2)].t_const_symbol_list);;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 282 "pddl+.yacc"
    {(yyval.t_domain)= (yyvsp[(2) - (2)].t_domain);
                                       (yyval.t_domain)->predicates= (yyvsp[(1) - (2)].t_pred_decl_list); ;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 284 "pddl+.yacc"
    {(yyval.t_domain)= (yyvsp[(2) - (2)].t_domain);
                                       (yyval.t_domain)->functions= (yyvsp[(1) - (2)].t_func_decl_list); ;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 286 "pddl+.yacc"
    {(yyval.t_domain)= (yyvsp[(2) - (2)].t_domain);
   				       (yyval.t_domain)->constraints = (yyvsp[(1) - (2)].t_con_goal);;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 288 "pddl+.yacc"
    {(yyval.t_domain) = (yyvsp[(2) - (2)].t_domain);;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 289 "pddl+.yacc"
    {(yyval.t_domain)= new domain((yyvsp[(1) - (1)].t_structure_store)); ;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 292 "pddl+.yacc"
    {(yyval.cp)=(yyvsp[(3) - (4)].cp);;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 296 "pddl+.yacc"
    { (yyval.t_class)=current_analysis->classes_tab.new_symbol_put((yyvsp[(1) - (1)].cp));
       delete [] (yyvsp[(1) - (1)].cp); ;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 299 "pddl+.yacc"
    { (yyval.t_class) = current_analysis->classes_tab.symbol_get((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp);;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 301 "pddl+.yacc"
    {(yyval.t_dummy) = 0;;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 303 "pddl+.yacc"
    {(yyval.t_dummy) = 0;;}
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 304 "pddl+.yacc"
    {(yyval.t_dummy) = 0;;}
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 309 "pddl+.yacc"
    {
	// Stash in analysis object --- we need to refer to it during parse
	//   but domain object is not created yet,
	current_analysis->req |= (yyvsp[(3) - (4)].t_pddl_req_flag);
	(yyval.t_pddl_req_flag)=(yyvsp[(3) - (4)].t_pddl_req_flag);
    ;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 316 "pddl+.yacc"
    {yyerrok;
       log_error(E_FATAL,"Syntax error in requirements declaration.");
       (yyval.t_pddl_req_flag)= 0; ;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 322 "pddl+.yacc"
    { (yyval.t_pddl_req_flag)= (yyvsp[(1) - (2)].t_pddl_req_flag) | (yyvsp[(2) - (2)].t_pddl_req_flag); ;}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 323 "pddl+.yacc"
    { (yyval.t_pddl_req_flag)= 0; ;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 329 "pddl+.yacc"
    {(yyval.t_pred_decl_list)=(yyvsp[(2) - (2)].t_pred_decl_list); (yyval.t_pred_decl_list)->push_front((yyvsp[(1) - (2)].t_pred_decl));;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 331 "pddl+.yacc"
    {  (yyval.t_pred_decl_list)=new pred_decl_list;
           (yyval.t_pred_decl_list)->push_front((yyvsp[(1) - (1)].t_pred_decl)); ;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 336 "pddl+.yacc"
    {(yyval.t_pred_decl)= new pred_decl((yyvsp[(2) - (4)].t_pred_symbol),(yyvsp[(3) - (4)].t_var_symbol_list),current_analysis->var_tab_stack.pop());;}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 338 "pddl+.yacc"
    {yyerrok;
        // hope someone makes this error someday
        log_error(E_FATAL,"Syntax error in predicate declaration.");
	(yyval.t_pred_decl)= static_cast<pred_decl*>(NULL); ;}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 346 "pddl+.yacc"
    { (yyval.t_pred_symbol)=current_analysis->pred_tab.new_symbol_put((yyvsp[(1) - (1)].cp));
           current_analysis->var_tab_stack.push(
           				current_analysis->buildPredTab());
           delete [] (yyvsp[(1) - (1)].cp); ;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 353 "pddl+.yacc"
    { (yyval.t_pred_symbol)=current_analysis->pred_tab.symbol_ref("=");
	      requires(E_EQUALITY); ;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 355 "pddl+.yacc"
    { (yyval.t_pred_symbol)=current_analysis->pred_tab.symbol_get((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp); ;}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 363 "pddl+.yacc"
    { (yyval.t_pred_symbol)=current_analysis->pred_tab.symbol_get((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp);;}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 369 "pddl+.yacc"
    {(yyval.t_func_decl_list)=(yyvsp[(1) - (2)].t_func_decl_list); (yyval.t_func_decl_list)->push_back((yyvsp[(2) - (2)].t_func_decl));;}
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 370 "pddl+.yacc"
    { (yyval.t_func_decl_list)=new func_decl_list; ;}
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 375 "pddl+.yacc"
    {(yyval.t_func_decl)= new func_decl((yyvsp[(2) - (5)].t_func_symbol),(yyvsp[(3) - (5)].t_var_symbol_list),current_analysis->var_tab_stack.pop());;}
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 377 "pddl+.yacc"
    {yyerrok;
	 log_error(E_FATAL,"Syntax error in functor declaration.");
	 (yyval.t_func_decl)= (int) NULL; ;}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 383 "pddl+.yacc"
    {(yyval.t_dummy) = (int) NULL;;}
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 383 "pddl+.yacc"
    {(yyval.t_dummy)= (int) NULL;;}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 387 "pddl+.yacc"
    { (yyval.t_func_symbol)=current_analysis->func_tab.new_symbol_put((yyvsp[(1) - (1)].cp));
           current_analysis->var_tab_stack.push(
           		current_analysis->buildFuncTab());
           delete [] (yyvsp[(1) - (1)].cp); ;}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 400 "pddl+.yacc"
    {
      (yyval.t_var_symbol_list)= (yyvsp[(1) - (4)].t_var_symbol_list);
      (yyval.t_var_symbol_list)->set_types((yyvsp[(3) - (4)].t_type));           /* Set types for variables */
      (yyval.t_var_symbol_list)->splice((yyval.t_var_symbol_list)->end(),*(yyvsp[(4) - (4)].t_var_symbol_list));   /* Join lists */
      delete (yyvsp[(4) - (4)].t_var_symbol_list);                   /* Delete (now empty) list */
      requires(E_TYPING);
      types_used = true;
   ;}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 409 "pddl+.yacc"
    {
      (yyval.t_var_symbol_list)= (yyvsp[(1) - (4)].t_var_symbol_list);
      (yyval.t_var_symbol_list)->set_either_types((yyvsp[(3) - (4)].t_type_list));    /* Set types for variables */
      (yyval.t_var_symbol_list)->splice((yyval.t_var_symbol_list)->end(),*(yyvsp[(4) - (4)].t_var_symbol_list));   /* Join lists */
      delete (yyvsp[(4) - (4)].t_var_symbol_list);                   /* Delete (now empty) list */
      requires(E_TYPING);
      types_used = true;
   ;}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 418 "pddl+.yacc"
    {
       (yyval.t_var_symbol_list)= (yyvsp[(1) - (1)].t_var_symbol_list);
   ;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 425 "pddl+.yacc"
    {
      (yyval.t_var_symbol_list)= (yyvsp[(1) - (4)].t_var_symbol_list);
      (yyval.t_var_symbol_list)->set_types(0);           /* Set types for variables */
      (yyval.t_var_symbol_list)->splice((yyval.t_var_symbol_list)->end(),*(yyvsp[(4) - (4)].t_var_symbol_list));   /* Join lists */
      delete (yyvsp[(4) - (4)].t_var_symbol_list);                   /* Delete (now empty) list */
   ;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 430 "pddl+.yacc"
    {(yyval.t_var_symbol_list) = new var_symbol_list;;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 438 "pddl+.yacc"
    {(yyval.t_var_symbol_list)=(yyvsp[(3) - (3)].t_var_symbol_list); (yyvsp[(3) - (3)].t_var_symbol_list)->push_front((yyvsp[(2) - (3)].t_var_symbol)); ;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 439 "pddl+.yacc"
    {(yyval.t_var_symbol_list)= new var_symbol_list; ;}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 446 "pddl+.yacc"
    {
      (yyval.t_const_symbol_list)= (yyvsp[(1) - (4)].t_const_symbol_list);
      (yyvsp[(1) - (4)].t_const_symbol_list)->set_types((yyvsp[(3) - (4)].t_type));           /* Set types for constants */
      (yyvsp[(1) - (4)].t_const_symbol_list)->splice((yyvsp[(1) - (4)].t_const_symbol_list)->end(),*(yyvsp[(4) - (4)].t_const_symbol_list)); /* Join lists */
      delete (yyvsp[(4) - (4)].t_const_symbol_list);                   /* Delete (now empty) list */
      requires(E_TYPING);
      types_used = true;
   ;}
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 455 "pddl+.yacc"
    {
      (yyval.t_const_symbol_list)= (yyvsp[(1) - (4)].t_const_symbol_list);
      (yyvsp[(1) - (4)].t_const_symbol_list)->set_either_types((yyvsp[(3) - (4)].t_type_list));
      (yyvsp[(1) - (4)].t_const_symbol_list)->splice((yyvsp[(1) - (4)].t_const_symbol_list)->end(),*(yyvsp[(4) - (4)].t_const_symbol_list));
      delete (yyvsp[(4) - (4)].t_const_symbol_list);
      requires(E_TYPING);
      types_used = true;
   ;}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 464 "pddl+.yacc"
    {(yyval.t_const_symbol_list)= (yyvsp[(1) - (1)].t_const_symbol_list);;}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 469 "pddl+.yacc"
    {(yyval.t_const_symbol_list)=(yyvsp[(2) - (2)].t_const_symbol_list); (yyvsp[(2) - (2)].t_const_symbol_list)->push_front((yyvsp[(1) - (2)].t_const_symbol));;}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 470 "pddl+.yacc"
    {(yyval.t_const_symbol_list)=new const_symbol_list;;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 474 "pddl+.yacc"
    {(yyval.t_const_symbol_list)=(yyvsp[(2) - (2)].t_const_symbol_list); (yyvsp[(2) - (2)].t_const_symbol_list)->push_front((yyvsp[(1) - (2)].t_const_symbol));;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 475 "pddl+.yacc"
    {(yyval.t_const_symbol_list)=new const_symbol_list;;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 484 "pddl+.yacc"
    {
       (yyval.t_type_list)= (yyvsp[(1) - (4)].t_type_list);
       (yyval.t_type_list)->set_types((yyvsp[(3) - (4)].t_type));           /* Set types for constants */
       (yyval.t_type_list)->splice((yyval.t_type_list)->end(),*(yyvsp[(4) - (4)].t_type_list)); /* Join lists */
       delete (yyvsp[(4) - (4)].t_type_list);                   /* Delete (now empty) list */
   ;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 491 "pddl+.yacc"
    {
   // This parse needs to be excluded, we think (DPL&MF: 6/9/01)
       (yyval.t_type_list)= (yyvsp[(1) - (4)].t_type_list);
       (yyval.t_type_list)->set_either_types((yyvsp[(3) - (4)].t_type_list));
       (yyval.t_type_list)->splice((yyvsp[(1) - (4)].t_type_list)->end(),*(yyvsp[(4) - (4)].t_type_list));
       delete (yyvsp[(4) - (4)].t_type_list);
   ;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 500 "pddl+.yacc"
    { (yyval.t_type_list)= (yyvsp[(1) - (1)].t_type_list); ;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 506 "pddl+.yacc"
    {(yyval.t_parameter_symbol_list)=(yyvsp[(1) - (2)].t_parameter_symbol_list); (yyval.t_parameter_symbol_list)->push_back((yyvsp[(2) - (2)].t_const_symbol)); ;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 508 "pddl+.yacc"
    {(yyval.t_parameter_symbol_list)=(yyvsp[(1) - (3)].t_parameter_symbol_list); (yyval.t_parameter_symbol_list)->push_back((yyvsp[(3) - (3)].t_var_symbol)); ;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 509 "pddl+.yacc"
    {(yyval.t_parameter_symbol_list)= new parameter_symbol_list;;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 516 "pddl+.yacc"
    { (yyval.t_var_symbol)= current_analysis->var_tab_stack.top()->symbol_put((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp); ;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 522 "pddl+.yacc"
    { (yyval.t_var_symbol)= current_analysis->var_tab_stack.symbol_get((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp); ;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 526 "pddl+.yacc"
    { (yyval.t_const_symbol)= current_analysis->const_tab.symbol_get((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp); ;}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 530 "pddl+.yacc"
    { (yyval.t_const_symbol)= current_analysis->const_tab.new_symbol_put((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp);;}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 535 "pddl+.yacc"
    { (yyval.t_type_list)= (yyvsp[(3) - (4)].t_type_list); ;}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 540 "pddl+.yacc"
    { (yyval.t_type)= current_analysis->pddl_type_tab.symbol_ref((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp);;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 547 "pddl+.yacc"
    { (yyval.t_type)= current_analysis->pddl_type_tab.symbol_ref((yyvsp[(1) - (1)].cp)); delete [] (yyvsp[(1) - (1)].cp);;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 552 "pddl+.yacc"
    {(yyval.t_type_list)= (yyvsp[(1) - (2)].t_type_list); (yyval.t_type_list)->push_back((yyvsp[(2) - (2)].t_type));;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 553 "pddl+.yacc"
    {(yyval.t_type_list)= new pddl_type_list;;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 558 "pddl+.yacc"
    {(yyval.t_type_list)= (yyvsp[(1) - (2)].t_type_list); (yyval.t_type_list)->push_back((yyvsp[(2) - (2)].t_type));;}
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 559 "pddl+.yacc"
    {(yyval.t_type_list)= new pddl_type_list;;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 564 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(1) - (6)].t_effect_lists);
	  (yyval.t_effect_lists)->assign_effects.push_back(new assignment((yyvsp[(4) - (6)].t_func_term),E_ASSIGN,(yyvsp[(5) - (6)].t_num_expression)));
          if((yyvsp[(4) - (6)].t_func_term)->getFunction()->getName()=="total-cost")
          {
          	requires(E_ACTIONCOSTS);
          	// Should also check that $5 is 0...
		  }
          else
          {
          	requires(E_NFLUENTS);
          }
	;}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 577 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->add_effects.push_back((yyvsp[(2) - (2)].t_simple_effect)); ;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 579 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->del_effects.push_back((yyvsp[(2) - (2)].t_simple_effect)); ;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 581 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->timed_effects.push_back((yyvsp[(2) - (2)].t_timed_effect)); ;}
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 583 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists;;}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 588 "pddl+.yacc"
    { requires(E_TIMED_INITIAL_LITERALS);
   		(yyval.t_timed_effect)=new timed_initial_literal((yyvsp[(3) - (4)].t_effect_lists),(yyvsp[(2) - (4)].fval));;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 593 "pddl+.yacc"
    {(yyval.t_effect_lists)=(yyvsp[(2) - (2)].t_effect_lists); (yyval.t_effect_lists)->append_effects((yyvsp[(1) - (2)].t_effect_lists)); delete (yyvsp[(1) - (2)].t_effect_lists);;}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 594 "pddl+.yacc"
    {(yyval.t_effect_lists)=(yyvsp[(2) - (2)].t_effect_lists); (yyval.t_effect_lists)->cond_effects.push_front((yyvsp[(1) - (2)].t_cond_effect));
                                      requires(E_COND_EFFS);;}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 596 "pddl+.yacc"
    {(yyval.t_effect_lists)=(yyvsp[(2) - (2)].t_effect_lists); (yyval.t_effect_lists)->forall_effects.push_front((yyvsp[(1) - (2)].t_forall_effect));
                                      requires(E_COND_EFFS);;}
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 598 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists(); ;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 607 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (1)].t_effect_lists);;}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 608 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->add_effects.push_front((yyvsp[(1) - (1)].t_simple_effect));;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 609 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->del_effects.push_front((yyvsp[(1) - (1)].t_simple_effect));;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 610 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->cond_effects.push_front((yyvsp[(1) - (1)].t_cond_effect));;}
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 611 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->forall_effects.push_front((yyvsp[(1) - (1)].t_forall_effect));;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 615 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(3) - (4)].t_effect_lists);;}
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 616 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (1)].t_effect_lists);;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 621 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->del_effects.push_front((yyvsp[(1) - (1)].t_simple_effect));;}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 623 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->add_effects.push_front((yyvsp[(1) - (1)].t_simple_effect));;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 625 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->assign_effects.push_front((yyvsp[(1) - (1)].t_assignment));
         requires(E_NFLUENTS);;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 631 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->del_effects.push_back((yyvsp[(2) - (2)].t_simple_effect));;}
    break;

  case 92:

/* Line 1464 of yacc.c  */
#line 632 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->add_effects.push_back((yyvsp[(2) - (2)].t_simple_effect));;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 633 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->assign_effects.push_back((yyvsp[(2) - (2)].t_assignment));
                                     requires(E_NFLUENTS); ;}
    break;

  case 94:

/* Line 1464 of yacc.c  */
#line 635 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists; ;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 640 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(3) - (4)].t_effect_lists); ;}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 642 "pddl+.yacc"
    {yyerrok; (yyval.t_effect_lists)=NULL;
	 log_error(E_FATAL,"Syntax error in (and ...)");
	;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 650 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(3) - (4)].t_effect_lists); ;}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 655 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists;
          (yyval.t_effect_lists)->forall_effects.push_back(
	       new forall_effect((yyvsp[(6) - (7)].t_effect_lists), (yyvsp[(4) - (7)].t_var_symbol_list), current_analysis->var_tab_stack.pop()));
          requires(E_COND_EFFS);;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 660 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists;
	  (yyval.t_effect_lists)->cond_effects.push_back(
	       new cond_effect((yyvsp[(3) - (5)].t_goal),(yyvsp[(4) - (5)].t_effect_lists)));
          requires(E_COND_EFFS); ;}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 665 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists;
	  (yyval.t_effect_lists)->cond_assign_effects.push_back(
	       new cond_effect((yyvsp[(3) - (5)].t_goal),(yyvsp[(4) - (5)].t_effect_lists)));
          requires(E_COND_EFFS); ;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 670 "pddl+.yacc"
    { (yyval.t_effect_lists)=new effect_lists;
          (yyval.t_effect_lists)->timed_effects.push_back((yyvsp[(1) - (1)].t_timed_effect)); ;}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 673 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists;
	  (yyval.t_effect_lists)->assign_effects.push_front((yyvsp[(1) - (1)].t_assignment));
          requires(E_NFLUENTS); ;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 679 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(1) - (2)].t_effect_lists); (yyvsp[(1) - (2)].t_effect_lists)->append_effects((yyvsp[(2) - (2)].t_effect_lists)); delete (yyvsp[(2) - (2)].t_effect_lists); ;}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 680 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists; ;}
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 685 "pddl+.yacc"
    {(yyval.t_timed_effect)=new timed_effect((yyvsp[(3) - (4)].t_effect_lists),E_AT_START);;}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 687 "pddl+.yacc"
    {(yyval.t_timed_effect)=new timed_effect((yyvsp[(3) - (4)].t_effect_lists),E_AT_END);;}
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 689 "pddl+.yacc"
    {(yyval.t_timed_effect)=new timed_effect(new effect_lists,E_CONTINUOUS);
         (yyval.t_timed_effect)->effs->assign_effects.push_front(
	     new assignment((yyvsp[(3) - (5)].t_func_term),E_INCREASE,(yyvsp[(4) - (5)].t_expression))); ;}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 693 "pddl+.yacc"
    {(yyval.t_timed_effect)=new timed_effect(new effect_lists,E_CONTINUOUS);
         (yyval.t_timed_effect)->effs->assign_effects.push_front(
	     new assignment((yyvsp[(3) - (5)].t_func_term),E_DECREASE,(yyvsp[(4) - (5)].t_expression))); ;}
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 697 "pddl+.yacc"
    {yyerrok; (yyval.t_timed_effect)=NULL;
	log_error(E_FATAL,"Syntax error in timed effect"); ;}
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 703 "pddl+.yacc"
    {(yyval.t_timed_effect)=new timed_effect(new effect_lists,E_CONTINUOUS);
         (yyval.t_timed_effect)->effs->assign_effects.push_front(
	     new assignment((yyvsp[(3) - (5)].t_func_term),E_INCREASE,(yyvsp[(4) - (5)].t_expression))); ;}
    break;

  case 111:

/* Line 1464 of yacc.c  */
#line 707 "pddl+.yacc"
    {(yyval.t_timed_effect)=new timed_effect(new effect_lists,E_CONTINUOUS);
         (yyval.t_timed_effect)->effs->assign_effects.push_front(
	     new assignment((yyvsp[(3) - (5)].t_func_term),E_DECREASE,(yyvsp[(4) - (5)].t_expression))); ;}
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 711 "pddl+.yacc"
    {yyerrok; (yyval.t_timed_effect)=NULL;
	log_error(E_FATAL,"Syntax error in conditional continuous effect"); ;}
    break;

  case 113:

/* Line 1464 of yacc.c  */
#line 717 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(3) - (4)].t_effect_lists); ;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 722 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists;
          (yyval.t_effect_lists)->forall_effects.push_back(
	       new forall_effect((yyvsp[(6) - (7)].t_effect_lists), (yyvsp[(4) - (7)].t_var_symbol_list), current_analysis->var_tab_stack.pop()));
          requires(E_COND_EFFS);;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 727 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists;
	  (yyval.t_effect_lists)->cond_assign_effects.push_back(
	       new cond_effect((yyvsp[(3) - (5)].t_goal),(yyvsp[(4) - (5)].t_effect_lists)));
          requires(E_COND_EFFS); ;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 732 "pddl+.yacc"
    { (yyval.t_effect_lists)=new effect_lists;
          (yyval.t_effect_lists)->timed_effects.push_back((yyvsp[(1) - (1)].t_timed_effect)); ;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 737 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(1) - (2)].t_effect_lists); (yyvsp[(1) - (2)].t_effect_lists)->append_effects((yyvsp[(2) - (2)].t_effect_lists)); delete (yyvsp[(2) - (2)].t_effect_lists); ;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 738 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists; ;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 742 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(3) - (4)].t_effect_lists);;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 743 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (1)].t_effect_lists);;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 748 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->del_effects.push_front((yyvsp[(1) - (1)].t_simple_effect));;}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 750 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->add_effects.push_front((yyvsp[(1) - (1)].t_simple_effect));;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 752 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists; (yyval.t_effect_lists)->assign_effects.push_front((yyvsp[(1) - (1)].t_assignment));
         requires(E_NFLUENTS);;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 758 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->del_effects.push_back((yyvsp[(2) - (2)].t_simple_effect));;}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 759 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->add_effects.push_back((yyvsp[(2) - (2)].t_simple_effect));;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 760 "pddl+.yacc"
    {(yyval.t_effect_lists)= (yyvsp[(1) - (2)].t_effect_lists); (yyval.t_effect_lists)->assign_effects.push_back((yyvsp[(2) - (2)].t_assignment));
                                     requires(E_NFLUENTS); ;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 762 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists; ;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 768 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_ASSIGN,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 770 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_INCREASE,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 772 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_DECREASE,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 774 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_SCALE_UP,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 776 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_SCALE_DOWN,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 781 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists;
         timed_effect * te = new timed_effect(new effect_lists,E_CONTINUOUS);
         (yyval.t_effect_lists)->timed_effects.push_front(te);
         te->effs->assign_effects.push_front(
	     new assignment((yyvsp[(3) - (5)].t_func_term),E_INCREASE,(yyvsp[(4) - (5)].t_expression))); ;}
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 787 "pddl+.yacc"
    {(yyval.t_effect_lists)=new effect_lists;
         timed_effect * te = new timed_effect(new effect_lists,E_CONTINUOUS);
         (yyval.t_effect_lists)->timed_effects.push_front(te);
         te->effs->assign_effects.push_front(
	     new assignment((yyvsp[(3) - (5)].t_func_term),E_DECREASE,(yyvsp[(4) - (5)].t_expression))); ;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 793 "pddl+.yacc"
    {(yyval.t_effect_lists) = (yyvsp[(3) - (4)].t_effect_lists);;}
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 797 "pddl+.yacc"
    { (yyval.t_effect_lists)=(yyvsp[(1) - (2)].t_effect_lists); (yyvsp[(1) - (2)].t_effect_lists)->append_effects((yyvsp[(2) - (2)].t_effect_lists)); delete (yyvsp[(2) - (2)].t_effect_lists); ;}
    break;

  case 137:

/* Line 1464 of yacc.c  */
#line 798 "pddl+.yacc"
    { (yyval.t_effect_lists)= new effect_lists; ;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 802 "pddl+.yacc"
    {(yyval.t_expression)= (yyvsp[(1) - (1)].t_expression);;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 803 "pddl+.yacc"
    {(yyval.t_expression)= new special_val_expr(E_DURATION_VAR);
                    requires( E_DURATION_INEQUALITIES );;}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 805 "pddl+.yacc"
    { (yyval.t_expression)=(yyvsp[(1) - (1)].t_num_expression); ;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 806 "pddl+.yacc"
    { (yyval.t_expression)= (yyvsp[(1) - (1)].t_func_term); ;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 807 "pddl+.yacc"
    { (yyval.t_expression) = current_analysis->getControlParam((yyvsp[(2) - (2)].cp)); delete [] (yyvsp[(2) - (2)].cp);;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 812 "pddl+.yacc"
    { (yyval.t_expression)= new plus_expression((yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 814 "pddl+.yacc"
    { (yyval.t_expression)= new minus_expression((yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 816 "pddl+.yacc"
    { (yyval.t_expression)= new mul_expression((yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 818 "pddl+.yacc"
    { (yyval.t_expression)= new div_expression((yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 823 "pddl+.yacc"
    { (yyval.t_goal)= new conj_goal((yyvsp[(3) - (4)].t_goal_list)); ;}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 825 "pddl+.yacc"
    { (yyval.t_goal)= new timed_goal(new comparison((yyvsp[(2) - (6)].t_comparison_op),
        			new special_val_expr(E_DURATION_VAR),(yyvsp[(5) - (6)].t_expression)),E_AT_START); ;}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 828 "pddl+.yacc"
    { (yyval.t_goal) = new timed_goal(new comparison((yyvsp[(4) - (9)].t_comparison_op),
					new special_val_expr(E_DURATION_VAR),(yyvsp[(7) - (9)].t_expression)),E_AT_START);;}
    break;

  case 150:

/* Line 1464 of yacc.c  */
#line 831 "pddl+.yacc"
    { (yyval.t_goal) = new timed_goal(new comparison((yyvsp[(4) - (9)].t_comparison_op),
					new special_val_expr(E_DURATION_VAR),(yyvsp[(7) - (9)].t_expression)),E_AT_END);;}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 836 "pddl+.yacc"
    {(yyval.t_comparison_op)= E_LESSEQ; requires(E_DURATION_INEQUALITIES);;}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 837 "pddl+.yacc"
    {(yyval.t_comparison_op)= E_GREATEQ; requires(E_DURATION_INEQUALITIES);;}
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 838 "pddl+.yacc"
    {(yyval.t_comparison_op)= E_EQUALS; ;}
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 846 "pddl+.yacc"
    {(yyval.t_expression)= (yyvsp[(1) - (1)].t_expression); ;}
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 851 "pddl+.yacc"
    { (yyval.t_goal_list)=(yyvsp[(1) - (2)].t_goal_list); (yyval.t_goal_list)->push_back((yyvsp[(2) - (2)].t_goal)); ;}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 853 "pddl+.yacc"
    { (yyval.t_goal_list)= new goal_list; ;}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 858 "pddl+.yacc"
    { (yyval.t_simple_effect)= new simple_effect((yyvsp[(3) - (4)].t_proposition)); ;}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 863 "pddl+.yacc"
    { (yyval.t_simple_effect)= new simple_effect((yyvsp[(1) - (1)].t_proposition)); ;}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 870 "pddl+.yacc"
    { (yyval.t_simple_effect)= new simple_effect((yyvsp[(3) - (4)].t_proposition)); ;}
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 875 "pddl+.yacc"
    { (yyval.t_simple_effect)= new simple_effect((yyvsp[(1) - (1)].t_proposition)); ;}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 880 "pddl+.yacc"
    { (yyval.t_forall_effect)= new forall_effect((yyvsp[(6) - (7)].t_effect_lists), (yyvsp[(4) - (7)].t_var_symbol_list), current_analysis->var_tab_stack.pop());;}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 885 "pddl+.yacc"
    { (yyval.t_cond_effect)= new cond_effect((yyvsp[(3) - (5)].t_goal),(yyvsp[(4) - (5)].t_effect_lists)); ;}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 890 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_ASSIGN,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 892 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_INCREASE,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 894 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_DECREASE,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 896 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_SCALE_UP,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 898 "pddl+.yacc"
    { (yyval.t_assignment)= new assignment((yyvsp[(3) - (5)].t_func_term),E_SCALE_DOWN,(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 903 "pddl+.yacc"
    { (yyval.t_expression)= new uminus_expression((yyvsp[(3) - (4)].t_expression)); requires(E_NFLUENTS); ;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 905 "pddl+.yacc"
    { (yyval.t_expression)= new plus_expression((yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression)); requires(E_NFLUENTS); ;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 907 "pddl+.yacc"
    { (yyval.t_expression)= new minus_expression((yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression)); requires(E_NFLUENTS); ;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 909 "pddl+.yacc"
    { (yyval.t_expression)= new mul_expression((yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression)); requires(E_NFLUENTS); ;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 911 "pddl+.yacc"
    { (yyval.t_expression)= new div_expression((yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression)); requires(E_NFLUENTS); ;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 912 "pddl+.yacc"
    { (yyval.t_expression)=(yyvsp[(1) - (1)].t_num_expression); ;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 913 "pddl+.yacc"
    { (yyval.t_expression) = current_analysis->getControlParam((yyvsp[(2) - (2)].cp)); delete [] (yyvsp[(2) - (2)].cp);;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 914 "pddl+.yacc"
    { (yyval.t_expression)= (yyvsp[(1) - (1)].t_func_term); requires(E_NFLUENTS); ;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 919 "pddl+.yacc"
    { (yyval.t_expression)= new mul_expression(new special_val_expr(E_HASHT),(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 921 "pddl+.yacc"
    { (yyval.t_expression)= new mul_expression((yyvsp[(3) - (5)].t_expression), new special_val_expr(E_HASHT)); ;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 923 "pddl+.yacc"
    { (yyval.t_expression)= new special_val_expr(E_HASHT); ;}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 928 "pddl+.yacc"
    { (yyval.t_num_expression)=new int_expression((yyvsp[(1) - (1)].ival));   ;}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 929 "pddl+.yacc"
    { (yyval.t_num_expression)=new float_expression((yyvsp[(1) - (1)].fval)); ;}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 933 "pddl+.yacc"
    { (yyval.t_func_term)=new func_term( current_analysis->func_tab.symbol_get((yyvsp[(2) - (4)].cp)), (yyvsp[(3) - (4)].t_parameter_symbol_list)); delete [] (yyvsp[(2) - (4)].cp); ;}
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 936 "pddl+.yacc"
    { (yyval.t_func_term)=new func_term( current_analysis->func_tab.symbol_get((yyvsp[(2) - (4)].cp)), (yyvsp[(3) - (4)].t_parameter_symbol_list)); delete [] (yyvsp[(2) - (4)].cp); ;}
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 938 "pddl+.yacc"
    { (yyval.t_func_term)=new func_term( current_analysis->func_tab.symbol_get((yyvsp[(1) - (1)].cp)),
                            new parameter_symbol_list); delete [] (yyvsp[(1) - (1)].cp);;}
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 941 "pddl+.yacc"
    { (yyval.t_func_term) = new class_func_term( (yyvsp[(2) - (6)].t_class), current_analysis->func_tab.symbol_get((yyvsp[(4) - (6)].cp)), (yyvsp[(5) - (6)].t_parameter_symbol_list)); delete [] (yyvsp[(4) - (6)].cp);;}
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 958 "pddl+.yacc"
    { (yyval.t_func_term)=new func_term( current_analysis->func_tab.symbol_get((yyvsp[(2) - (4)].cp)), (yyvsp[(3) - (4)].t_parameter_symbol_list)); delete [] (yyvsp[(2) - (4)].cp); ;}
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 960 "pddl+.yacc"
    { (yyval.t_func_term)=new func_term( current_analysis->func_tab.symbol_get((yyvsp[(2) - (4)].cp)), (yyvsp[(3) - (4)].t_parameter_symbol_list)); delete [] (yyvsp[(2) - (4)].cp); ;}
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 962 "pddl+.yacc"
    { (yyval.t_func_term)=new func_term( current_analysis->func_tab.symbol_get((yyvsp[(1) - (1)].cp)),
                            new parameter_symbol_list); delete [] (yyvsp[(1) - (1)].cp);;}
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 967 "pddl+.yacc"
    { (yyval.t_comparison_op)= E_GREATER; ;}
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 968 "pddl+.yacc"
    { (yyval.t_comparison_op)= E_GREATEQ; ;}
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 969 "pddl+.yacc"
    { (yyval.t_comparison_op)= E_LESS; ;}
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 970 "pddl+.yacc"
    { (yyval.t_comparison_op)= E_LESSEQ; ;}
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 971 "pddl+.yacc"
    { (yyval.t_comparison_op)= E_EQUALS; ;}
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 984 "pddl+.yacc"
    {(yyval.t_goal)= (yyvsp[(1) - (1)].t_goal);;}
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 991 "pddl+.yacc"
    {(yyval.t_goal) = new conj_goal((yyvsp[(3) - (4)].t_goal_list));;}
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 994 "pddl+.yacc"
    {(yyval.t_goal)= new qfied_goal(E_FORALL,(yyvsp[(4) - (7)].t_var_symbol_list),(yyvsp[(6) - (7)].t_goal),current_analysis->var_tab_stack.pop());
        requires(E_UNIV_PRECS);;}
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 996 "pddl+.yacc"
    {(yyval.t_goal) = new conj_goal(new goal_list);;}
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 997 "pddl+.yacc"
    {(yyval.t_goal) = new conj_goal(new goal_list);;}
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1002 "pddl+.yacc"
    {(yyval.t_con_goal) = new preference((yyvsp[(3) - (4)].t_con_goal));requires(E_PREFERENCES);;}
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1004 "pddl+.yacc"
    {(yyval.t_con_goal) = new preference((yyvsp[(3) - (5)].cp),(yyvsp[(4) - (5)].t_con_goal));requires(E_PREFERENCES);;}
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1006 "pddl+.yacc"
    {(yyval.t_con_goal) = new conj_goal((yyvsp[(3) - (4)].t_goal_list));;}
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1009 "pddl+.yacc"
    {(yyval.t_con_goal)= new qfied_goal(E_FORALL,(yyvsp[(4) - (7)].t_var_symbol_list),(yyvsp[(6) - (7)].t_con_goal),current_analysis->var_tab_stack.pop());
                requires(E_UNIV_PRECS);;}
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1012 "pddl+.yacc"
    {(yyval.t_con_goal) = (yyvsp[(1) - (1)].t_con_goal);;}
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1017 "pddl+.yacc"
    {(yyval.t_con_goal) = new preference((yyvsp[(3) - (4)].t_con_goal));requires(E_PREFERENCES);;}
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1019 "pddl+.yacc"
    {(yyval.t_con_goal) = new preference((yyvsp[(3) - (5)].cp),(yyvsp[(4) - (5)].t_con_goal));requires(E_PREFERENCES);;}
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1021 "pddl+.yacc"
    {(yyval.t_con_goal) = new conj_goal((yyvsp[(3) - (4)].t_goal_list));;}
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1024 "pddl+.yacc"
    {(yyval.t_con_goal)= new qfied_goal(E_FORALL,(yyvsp[(4) - (7)].t_var_symbol_list),(yyvsp[(6) - (7)].t_con_goal),current_analysis->var_tab_stack.pop());
                requires(E_UNIV_PRECS);;}
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1030 "pddl+.yacc"
    {(yyval.t_goal_list)=(yyvsp[(1) - (2)].t_goal_list); (yyvsp[(1) - (2)].t_goal_list)->push_back((yyvsp[(2) - (2)].t_con_goal));;}
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1032 "pddl+.yacc"
    {(yyval.t_goal_list)= new goal_list; (yyval.t_goal_list)->push_back((yyvsp[(1) - (1)].t_con_goal));;}
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1037 "pddl+.yacc"
    {(yyval.t_goal)= new preference((yyvsp[(3) - (4)].t_goal)); requires(E_PREFERENCES);;}
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1039 "pddl+.yacc"
    {(yyval.t_goal)= new preference((yyvsp[(3) - (5)].cp),(yyvsp[(4) - (5)].t_goal)); requires(E_PREFERENCES);;}
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1043 "pddl+.yacc"
    {(yyval.t_goal)=(yyvsp[(1) - (1)].t_goal);;}
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1048 "pddl+.yacc"
    {(yyval.t_goal_list) = (yyvsp[(1) - (2)].t_goal_list); (yyval.t_goal_list)->push_back((yyvsp[(2) - (2)].t_con_goal));;}
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1050 "pddl+.yacc"
    {(yyval.t_goal_list) = new goal_list; (yyval.t_goal_list)->push_back((yyvsp[(1) - (1)].t_con_goal));;}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1055 "pddl+.yacc"
    {(yyval.t_con_goal)= new conj_goal((yyvsp[(3) - (4)].t_goal_list));;}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1057 "pddl+.yacc"
    {(yyval.t_con_goal) = new qfied_goal(E_FORALL,(yyvsp[(4) - (7)].t_var_symbol_list),(yyvsp[(6) - (7)].t_con_goal),current_analysis->var_tab_stack.pop());
        requires(E_UNIV_PRECS);;}
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1060 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_ATEND,(yyvsp[(3) - (4)].t_goal));;}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1062 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_ALWAYS,(yyvsp[(3) - (4)].t_goal));;}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1064 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_SOMETIME,(yyvsp[(3) - (4)].t_goal));;}
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1066 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_WITHIN,(yyvsp[(4) - (5)].t_goal),NULL,(yyvsp[(3) - (5)].t_num_expression)->double_value(),0.0);delete (yyvsp[(3) - (5)].t_num_expression);;}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1068 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_ATMOSTONCE,(yyvsp[(3) - (4)].t_goal));;}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1070 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_SOMETIMEAFTER,(yyvsp[(4) - (5)].t_goal),(yyvsp[(3) - (5)].t_goal));;}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1072 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_SOMETIMEBEFORE,(yyvsp[(4) - (5)].t_goal),(yyvsp[(3) - (5)].t_goal));;}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1074 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_ALWAYSWITHIN,(yyvsp[(5) - (6)].t_goal),(yyvsp[(4) - (6)].t_goal),(yyvsp[(3) - (6)].t_num_expression)->double_value(),0.0);delete (yyvsp[(3) - (6)].t_num_expression);;}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1076 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_HOLDDURING,(yyvsp[(5) - (6)].t_goal),NULL,(yyvsp[(4) - (6)].t_num_expression)->double_value(),(yyvsp[(3) - (6)].t_num_expression)->double_value());delete (yyvsp[(3) - (6)].t_num_expression);delete (yyvsp[(4) - (6)].t_num_expression);;}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1078 "pddl+.yacc"
    {(yyval.t_con_goal) = new constraint_goal(E_HOLDAFTER,(yyvsp[(4) - (5)].t_goal),NULL,0.0,(yyvsp[(3) - (5)].t_num_expression)->double_value());delete (yyvsp[(3) - (5)].t_num_expression);;}
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 1083 "pddl+.yacc"
    {(yyval.t_goal)= new simple_goal((yyvsp[(1) - (1)].t_proposition),E_POS);;}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1085 "pddl+.yacc"
    {(yyval.t_goal)= new neg_goal((yyvsp[(3) - (4)].t_goal));simple_goal * s = dynamic_cast<simple_goal *>((yyvsp[(3) - (4)].t_goal));
       if(s && s->getProp()->head->getName()=="=") {requires(E_EQUALITY);}
       else{requires(E_NEGATIVE_PRECONDITIONS);};;}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1089 "pddl+.yacc"
    {(yyval.t_goal)= new conj_goal((yyvsp[(3) - (4)].t_goal_list));;}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 1091 "pddl+.yacc"
    {(yyval.t_goal)= new disj_goal((yyvsp[(3) - (4)].t_goal_list));
        requires(E_DISJUNCTIVE_PRECONDS);;}
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 1094 "pddl+.yacc"
    {(yyval.t_goal)= new imply_goal((yyvsp[(3) - (5)].t_goal),(yyvsp[(4) - (5)].t_goal));
        requires(E_DISJUNCTIVE_PRECONDS);;}
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 1098 "pddl+.yacc"
    {(yyval.t_goal)= new qfied_goal((yyvsp[(2) - (7)].t_quantifier),(yyvsp[(4) - (7)].t_var_symbol_list),(yyvsp[(6) - (7)].t_goal),current_analysis->var_tab_stack.pop());;}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 1101 "pddl+.yacc"
    {(yyval.t_goal)= new qfied_goal((yyvsp[(2) - (7)].t_quantifier),(yyvsp[(4) - (7)].t_var_symbol_list),(yyvsp[(6) - (7)].t_goal),current_analysis->var_tab_stack.pop());;}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 1103 "pddl+.yacc"
    {(yyval.t_goal)= new comparison((yyvsp[(2) - (5)].t_comparison_op),(yyvsp[(3) - (5)].t_expression),(yyvsp[(4) - (5)].t_expression));
        requires(E_NFLUENTS);;}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 1109 "pddl+.yacc"
    {(yyval.t_goal_list)=(yyvsp[(1) - (2)].t_goal_list); (yyvsp[(1) - (2)].t_goal_list)->push_back((yyvsp[(2) - (2)].t_goal));;}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1111 "pddl+.yacc"
    {(yyval.t_goal_list)= new goal_list; (yyval.t_goal_list)->push_back((yyvsp[(1) - (1)].t_goal));;}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 1116 "pddl+.yacc"
    {(yyval.t_goal_list)=(yyvsp[(1) - (2)].t_goal_list); (yyvsp[(1) - (2)].t_goal_list)->push_back((yyvsp[(2) - (2)].t_goal));;}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1118 "pddl+.yacc"
    {(yyval.t_goal_list)= new goal_list; (yyval.t_goal_list)->push_back((yyvsp[(1) - (1)].t_goal));;}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 1128 "pddl+.yacc"
    {(yyval.t_quantifier)=E_FORALL;
        current_analysis->var_tab_stack.push(
        		current_analysis->buildForallTab());;}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 1135 "pddl+.yacc"
    {(yyval.t_quantifier)=E_EXISTS;
        current_analysis->var_tab_stack.push(
        	current_analysis->buildExistsTab());;}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 1142 "pddl+.yacc"
    {(yyval.t_proposition)=new proposition((yyvsp[(2) - (4)].t_pred_symbol),(yyvsp[(3) - (4)].t_parameter_symbol_list));;}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 1147 "pddl+.yacc"
    {(yyval.t_proposition) = new proposition((yyvsp[(2) - (4)].t_pred_symbol),(yyvsp[(3) - (4)].t_var_symbol_list));;}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 1152 "pddl+.yacc"
    {(yyval.t_proposition)=new proposition((yyvsp[(2) - (4)].t_pred_symbol),(yyvsp[(3) - (4)].t_parameter_symbol_list));;}
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 1157 "pddl+.yacc"
    {(yyval.t_pred_decl_list)= (yyvsp[(3) - (4)].t_pred_decl_list);;}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 1159 "pddl+.yacc"
    {yyerrok; (yyval.t_pred_decl_list)=NULL;
	 log_error(E_FATAL,"Syntax error in (:predicates ...)");
	;}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 1166 "pddl+.yacc"
    {(yyval.t_func_decl_list)= (yyvsp[(3) - (4)].t_func_decl_list);;}
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 1168 "pddl+.yacc"
    {yyerrok; (yyval.t_func_decl_list)=NULL;
	 log_error(E_FATAL,"Syntax error in (:functions ...)");
	;}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 1175 "pddl+.yacc"
    {(yyval.t_con_goal) = (yyvsp[(3) - (4)].t_con_goal);;}
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 1177 "pddl+.yacc"
    {yyerrok; (yyval.t_con_goal)=NULL;
      log_error(E_FATAL,"Syntax error in (:constraints ...)");
      ;}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 1184 "pddl+.yacc"
    {(yyval.t_con_goal) = (yyvsp[(3) - (4)].t_con_goal);;}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 1186 "pddl+.yacc"
    {yyerrok; (yyval.t_con_goal)=NULL;
      log_error(E_FATAL,"Syntax error in (:constraints ...)");
      ;}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 1192 "pddl+.yacc"
    { (yyval.t_structure_store)=(yyvsp[(1) - (2)].t_structure_store); (yyval.t_structure_store)->push_back((yyvsp[(2) - (2)].t_structure_def)); ;}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 1193 "pddl+.yacc"
    { (yyval.t_structure_store)= new structure_store; (yyval.t_structure_store)->push_back((yyvsp[(1) - (1)].t_structure_def)); ;}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 1197 "pddl+.yacc"
    { (yyval.t_structure_def)= (yyvsp[(1) - (1)].t_action_def); ;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1198 "pddl+.yacc"
    { (yyval.t_structure_def)= (yyvsp[(1) - (1)].t_event_def); requires(E_TIME); ;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 1199 "pddl+.yacc"
    { (yyval.t_structure_def)= (yyvsp[(1) - (1)].t_process_def); requires(E_TIME); ;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1200 "pddl+.yacc"
    { (yyval.t_structure_def)= (yyvsp[(1) - (1)].t_durative_action_def); requires(E_DURATIVE_ACTIONS); ;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1201 "pddl+.yacc"
    { (yyval.t_structure_def)= (yyvsp[(1) - (1)].t_derivation_rule); requires(E_DERIVED_PREDICATES);;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1202 "pddl+.yacc"
    { (yyval.t_structure_def) = (yyvsp[(1) - (1)].t_class_def); requires(E_MODULES);;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1210 "pddl+.yacc"
    {(yyval.t_class_def) = new class_def((yyvsp[(3) - (5)].t_class),(yyvsp[(4) - (5)].t_func_decl_list));;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1214 "pddl+.yacc"
    {(yyval.t_dummy)= 0;
    	current_analysis->var_tab_stack.push(
    					current_analysis->buildRuleTab());;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1225 "pddl+.yacc"
    {(yyval.t_derivation_rule) = new derivation_rule((yyvsp[(3) - (5)].t_proposition),(yyvsp[(4) - (5)].t_goal),current_analysis->var_tab_stack.pop());;}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1237 "pddl+.yacc"
    { (yyval.t_action_def)= current_analysis->buildAction(current_analysis->op_tab.new_symbol_put((yyvsp[(3) - (12)].cp)),
			(yyvsp[(6) - (12)].t_var_symbol_list),(yyvsp[(9) - (12)].t_goal),(yyvsp[(11) - (12)].t_effect_lists),
			current_analysis->var_tab_stack.pop()); delete [] (yyvsp[(3) - (12)].cp); ;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1241 "pddl+.yacc"
    {yyerrok;
	 log_error(E_FATAL,"Syntax error in action declaration.");
	 (yyval.t_action_def)= NULL; ;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1254 "pddl+.yacc"
    {(yyval.t_event_def)= current_analysis->buildEvent(current_analysis->op_tab.new_symbol_put((yyvsp[(3) - (12)].cp)),
		   (yyvsp[(6) - (12)].t_var_symbol_list),(yyvsp[(9) - (12)].t_goal),(yyvsp[(11) - (12)].t_effect_lists),
		   current_analysis->var_tab_stack.pop()); delete [] (yyvsp[(3) - (12)].cp);;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1259 "pddl+.yacc"
    {yyerrok;
	 log_error(E_FATAL,"Syntax error in event declaration.");
	 (yyval.t_event_def)= NULL; ;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1271 "pddl+.yacc"
    {(yyval.t_process_def)= current_analysis->buildProcess(current_analysis->op_tab.new_symbol_put((yyvsp[(3) - (12)].cp)),
		     (yyvsp[(6) - (12)].t_var_symbol_list),(yyvsp[(9) - (12)].t_goal),(yyvsp[(11) - (12)].t_effect_lists),
                     current_analysis->var_tab_stack.pop()); delete [] (yyvsp[(3) - (12)].cp);;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1275 "pddl+.yacc"
    {yyerrok;
	 log_error(E_FATAL,"Syntax error in process declaration.");
	 (yyval.t_process_def)= NULL; ;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1281 "pddl+.yacc"
    {(yyval.t_var_symbol_list) = (yyvsp[(3) - (4)].t_var_symbol_list); current_analysis->setControlParams((yyval.t_var_symbol_list));;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1282 "pddl+.yacc"
    {(yyval.t_var_symbol_list) = NULL; current_analysis->setControlParams((yyval.t_var_symbol_list));;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1293 "pddl+.yacc"
    { (yyval.t_durative_action_def)= (yyvsp[(11) - (12)].t_durative_action_def);
      (yyval.t_durative_action_def)->name= current_analysis->op_tab.new_symbol_put((yyvsp[(3) - (12)].cp));
      (yyval.t_durative_action_def)->symtab= current_analysis->var_tab_stack.pop();
      (yyval.t_durative_action_def)->control_parameters = current_analysis->getControlParams();
      (yyval.t_durative_action_def)->parameters= (yyvsp[(6) - (12)].t_var_symbol_list);
      (yyval.t_durative_action_def)->dur_constraint= (yyvsp[(10) - (12)].t_goal);
      delete [] (yyvsp[(3) - (12)].cp);
      delete (yyvsp[(8) - (12)].t_var_symbol_list);
    ;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1304 "pddl+.yacc"
    {yyerrok;
	 log_error(E_FATAL,"Syntax error in durative-action declaration.");
	 (yyval.t_durative_action_def)= NULL; ;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1311 "pddl+.yacc"
    {(yyval.t_durative_action_def)=(yyvsp[(1) - (3)].t_durative_action_def); (yyval.t_durative_action_def)->effects=(yyvsp[(3) - (3)].t_effect_lists);;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1313 "pddl+.yacc"
    {(yyval.t_durative_action_def)=(yyvsp[(1) - (3)].t_durative_action_def); (yyval.t_durative_action_def)->precondition=(yyvsp[(3) - (3)].t_goal);;}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 1314 "pddl+.yacc"
    {(yyval.t_durative_action_def)= current_analysis->buildDurativeAction();;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 1319 "pddl+.yacc"
    { (yyval.t_goal)=(yyvsp[(1) - (1)].t_goal); ;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 1321 "pddl+.yacc"
    { (yyval.t_goal)= new conj_goal((yyvsp[(3) - (4)].t_goal_list)); ;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 1326 "pddl+.yacc"
    { (yyval.t_goal_list)=(yyvsp[(1) - (2)].t_goal_list); (yyval.t_goal_list)->push_back((yyvsp[(2) - (2)].t_goal)); ;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 1328 "pddl+.yacc"
    { (yyval.t_goal_list)= new goal_list; ;}
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 1333 "pddl+.yacc"
    {(yyval.t_goal)= new timed_goal((yyvsp[(3) - (4)].t_goal),E_AT_START);;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 1335 "pddl+.yacc"
    {(yyval.t_goal)= new timed_goal((yyvsp[(3) - (4)].t_goal),E_AT_END);;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 1337 "pddl+.yacc"
    {(yyval.t_goal)= new timed_goal((yyvsp[(3) - (4)].t_goal),E_OVER_ALL);;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 1339 "pddl+.yacc"
    {timed_goal * tg = dynamic_cast<timed_goal *>((yyvsp[(4) - (5)].t_goal));
		(yyval.t_goal) = new timed_goal(new preference((yyvsp[(3) - (5)].cp),tg->clearGoal()),tg->getTime());
			delete tg;
			requires(E_PREFERENCES);;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 1344 "pddl+.yacc"
    {(yyval.t_goal) = new preference((yyvsp[(3) - (4)].t_goal));requires(E_PREFERENCES);;}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 1348 "pddl+.yacc"
    {(yyval.t_dummy)= 0; current_analysis->var_tab_stack.push(
    				current_analysis->buildOpTab());;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 1353 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_EQUALITY;;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 1354 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_STRIPS;;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 1356 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_TYPING;;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 1358 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_NEGATIVE_PRECONDITIONS;;}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 1360 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_DISJUNCTIVE_PRECONDS;;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 1361 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_EXT_PRECS;;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 1362 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_UNIV_PRECS;;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 1363 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_COND_EFFS;;}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 1364 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_NFLUENTS | E_OFLUENTS;;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 1366 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_DURATIVE_ACTIONS;;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 1367 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_TIME |
                      E_NFLUENTS |
                      E_DURATIVE_ACTIONS; ;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 1370 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)=E_ACTIONCOSTS | E_NFLUENTS;;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 1373 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)=E_OFLUENTS;;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 1374 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)=E_NFLUENTS;;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 1375 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)=E_MODULES;;}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 1377 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_STRIPS |
		      E_TYPING |
		      E_NEGATIVE_PRECONDITIONS |
		      E_DISJUNCTIVE_PRECONDS |
		      E_EQUALITY |
		      E_EXT_PRECS |
		      E_UNIV_PRECS |
		      E_COND_EFFS;;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 1386 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_EXT_PRECS |
		      E_UNIV_PRECS;;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 1390 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_DURATION_INEQUALITIES;;}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 1393 "pddl+.yacc"
    {(yyval.t_pddl_req_flag)= E_CONTINUOUS_EFFECTS;;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 1395 "pddl+.yacc"
    {(yyval.t_pddl_req_flag) = E_DERIVED_PREDICATES;;}
    break;

  case 305:

/* Line 1464 of yacc.c  */
#line 1397 "pddl+.yacc"
    {(yyval.t_pddl_req_flag) = E_TIMED_INITIAL_LITERALS;;}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 1399 "pddl+.yacc"
    {(yyval.t_pddl_req_flag) = E_PREFERENCES;;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 1401 "pddl+.yacc"
    {(yyval.t_pddl_req_flag) = E_CONSTRAINTS;;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 1403 "pddl+.yacc"
    {log_error(E_WARNING,"Unrecognised requirements declaration ");
       (yyval.t_pddl_req_flag)= 0; delete [] (yyvsp[(1) - (1)].cp);;}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 1409 "pddl+.yacc"
    {(yyval.t_const_symbol_list)=(yyvsp[(3) - (4)].t_const_symbol_list);;}
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 1413 "pddl+.yacc"
    {(yyval.t_type_list)=(yyvsp[(3) - (4)].t_type_list); requires(E_TYPING);;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 1423 "pddl+.yacc"
    {(yyval.t_problem)=(yyvsp[(11) - (12)].t_problem); (yyval.t_problem)->name = (yyvsp[(5) - (12)].cp); (yyval.t_problem)->domain_name = (yyvsp[(9) - (12)].cp);
		if (types_used && !types_defined) {
			yyerrok; log_error(E_FATAL,"Syntax error in problem file - types used, but no :types section in domain file.");
		}

	;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 1430 "pddl+.yacc"
    {yyerrok; (yyval.t_problem)=NULL;
       	log_error(E_FATAL,"Syntax error in problem definition."); ;}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 1436 "pddl+.yacc"
    {(yyval.t_problem)=(yyvsp[(2) - (2)].t_problem); (yyval.t_problem)->req= (yyvsp[(1) - (2)].t_pddl_req_flag);;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 1437 "pddl+.yacc"
    {(yyval.t_problem)=(yyvsp[(2) - (2)].t_problem); (yyval.t_problem)->objects= (yyvsp[(1) - (2)].t_const_symbol_list);;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 1438 "pddl+.yacc"
    {(yyval.t_problem)=(yyvsp[(2) - (2)].t_problem); (yyval.t_problem)->initial_state= (yyvsp[(1) - (2)].t_effect_lists);;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 1439 "pddl+.yacc"
    {(yyval.t_problem)=(yyvsp[(2) - (2)].t_problem); (yyval.t_problem)->the_goal= (yyvsp[(1) - (2)].t_goal);;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 1441 "pddl+.yacc"
    {(yyval.t_problem)=(yyvsp[(2) - (2)].t_problem); (yyval.t_problem)->constraints = (yyvsp[(1) - (2)].t_con_goal);;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 1442 "pddl+.yacc"
    {(yyval.t_problem)=(yyvsp[(2) - (2)].t_problem); if((yyval.t_problem)->metric == 0) {(yyval.t_problem)->metric= (yyvsp[(1) - (2)].t_metric);}
											else {(yyval.t_problem)->metric->add((yyvsp[(1) - (2)].t_metric));};}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 1444 "pddl+.yacc"
    {(yyval.t_problem)=(yyvsp[(2) - (2)].t_problem); (yyval.t_problem)->length= (yyvsp[(1) - (2)].t_length_spec);;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 1445 "pddl+.yacc"
    {(yyval.t_problem)=new problem;;}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 1448 "pddl+.yacc"
    {(yyval.t_const_symbol_list)=(yyvsp[(3) - (4)].t_const_symbol_list);;}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 1451 "pddl+.yacc"
    {(yyval.t_effect_lists)=(yyvsp[(3) - (4)].t_effect_lists);;}
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 1454 "pddl+.yacc"
    {(yyval.vtab) = current_analysis->buildOpTab();;}
    break;

  case 324:

/* Line 1464 of yacc.c  */
#line 1457 "pddl+.yacc"
    {(yyval.t_goal)=(yyvsp[(3) - (4)].t_goal);delete (yyvsp[(2) - (4)].vtab);;}
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 1462 "pddl+.yacc"
    { (yyval.t_metric)= new metric_spec((yyvsp[(3) - (5)].t_optimization),(yyvsp[(4) - (5)].t_expression)); ;}
    break;

  case 326:

/* Line 1464 of yacc.c  */
#line 1464 "pddl+.yacc"
    {yyerrok;
        log_error(E_FATAL,"Syntax error in metric declaration.");
        (yyval.t_metric)= NULL; ;}
    break;

  case 327:

/* Line 1464 of yacc.c  */
#line 1471 "pddl+.yacc"
    {(yyval.t_length_spec)= new length_spec(E_BOTH,(yyvsp[(4) - (7)].ival),(yyvsp[(6) - (7)].ival));;}
    break;

  case 328:

/* Line 1464 of yacc.c  */
#line 1474 "pddl+.yacc"
    {(yyval.t_length_spec) = new length_spec(E_SERIAL,(yyvsp[(4) - (5)].ival));;}
    break;

  case 329:

/* Line 1464 of yacc.c  */
#line 1478 "pddl+.yacc"
    {(yyval.t_length_spec) = new length_spec(E_PARALLEL,(yyvsp[(4) - (5)].ival));;}
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 1484 "pddl+.yacc"
    {(yyval.t_optimization)= E_MINIMIZE;;}
    break;

  case 331:

/* Line 1464 of yacc.c  */
#line 1485 "pddl+.yacc"
    {(yyval.t_optimization)= E_MAXIMIZE;;}
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 1490 "pddl+.yacc"
    {(yyval.t_expression)= (yyvsp[(2) - (3)].t_expression);;}
    break;

  case 333:

/* Line 1464 of yacc.c  */
#line 1491 "pddl+.yacc"
    {(yyval.t_expression)= (yyvsp[(1) - (1)].t_func_term);;}
    break;

  case 334:

/* Line 1464 of yacc.c  */
#line 1492 "pddl+.yacc"
    {(yyval.t_expression)= (yyvsp[(1) - (1)].t_num_expression);;}
    break;

  case 335:

/* Line 1464 of yacc.c  */
#line 1493 "pddl+.yacc"
    { (yyval.t_expression)= new special_val_expr(E_TOTAL_TIME); ;}
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 1495 "pddl+.yacc"
    {(yyval.t_expression) = new violation_term((yyvsp[(3) - (4)].cp));;}
    break;

  case 337:

/* Line 1464 of yacc.c  */
#line 1496 "pddl+.yacc"
    { (yyval.t_expression)= new special_val_expr(E_TOTAL_TIME); ;}
    break;

  case 338:

/* Line 1464 of yacc.c  */
#line 1500 "pddl+.yacc"
    { (yyval.t_expression)= new plus_expression((yyvsp[(2) - (3)].t_expression),(yyvsp[(3) - (3)].t_expression)); ;}
    break;

  case 339:

/* Line 1464 of yacc.c  */
#line 1501 "pddl+.yacc"
    { (yyval.t_expression)= new minus_expression((yyvsp[(2) - (3)].t_expression),(yyvsp[(3) - (3)].t_expression)); ;}
    break;

  case 340:

/* Line 1464 of yacc.c  */
#line 1502 "pddl+.yacc"
    { (yyval.t_expression)= new mul_expression((yyvsp[(2) - (3)].t_expression),(yyvsp[(3) - (3)].t_expression)); ;}
    break;

  case 341:

/* Line 1464 of yacc.c  */
#line 1503 "pddl+.yacc"
    { (yyval.t_expression)= new div_expression((yyvsp[(2) - (3)].t_expression),(yyvsp[(3) - (3)].t_expression)); ;}
    break;

  case 342:

/* Line 1464 of yacc.c  */
#line 1507 "pddl+.yacc"
    {(yyval.t_expression) = (yyvsp[(1) - (1)].t_expression);;}
    break;

  case 343:

/* Line 1464 of yacc.c  */
#line 1509 "pddl+.yacc"
    {(yyval.t_expression) = new plus_expression((yyvsp[(1) - (2)].t_expression),(yyvsp[(2) - (2)].t_expression));;}
    break;

  case 344:

/* Line 1464 of yacc.c  */
#line 1513 "pddl+.yacc"
    {(yyval.t_expression) = (yyvsp[(1) - (1)].t_expression);;}
    break;

  case 345:

/* Line 1464 of yacc.c  */
#line 1515 "pddl+.yacc"
    {(yyval.t_expression) = new mul_expression((yyvsp[(1) - (2)].t_expression),(yyvsp[(2) - (2)].t_expression));;}
    break;

  case 346:

/* Line 1464 of yacc.c  */
#line 1521 "pddl+.yacc"
    {(yyval.t_plan)= (yyvsp[(2) - (2)].t_plan);
         (yyval.t_plan)->push_front((yyvsp[(1) - (2)].t_step)); ;}
    break;

  case 347:

/* Line 1464 of yacc.c  */
#line 1524 "pddl+.yacc"
    {(yyval.t_plan) = (yyvsp[(3) - (3)].t_plan);(yyval.t_plan)->insertTime((yyvsp[(2) - (3)].fval));;}
    break;

  case 348:

/* Line 1464 of yacc.c  */
#line 1526 "pddl+.yacc"
    {(yyval.t_plan) = (yyvsp[(3) - (3)].t_plan);(yyval.t_plan)->insertTime((yyvsp[(2) - (3)].ival));;}
    break;

  case 349:

/* Line 1464 of yacc.c  */
#line 1528 "pddl+.yacc"
    {(yyval.t_plan)= new plan;;}
    break;

  case 350:

/* Line 1464 of yacc.c  */
#line 1533 "pddl+.yacc"
    {(yyval.t_step)=(yyvsp[(3) - (3)].t_step);
         (yyval.t_step)->start_time_given=1;
         (yyval.t_step)->start_time=(yyvsp[(1) - (3)].fval);;}
    break;

  case 351:

/* Line 1464 of yacc.c  */
#line 1537 "pddl+.yacc"
    {(yyval.t_step)=(yyvsp[(1) - (1)].t_step);
	 (yyval.t_step)->start_time_given=0;;}
    break;

  case 352:

/* Line 1464 of yacc.c  */
#line 1543 "pddl+.yacc"
    {(yyval.t_step)= (yyvsp[(1) - (4)].t_step);
	 (yyval.t_step)->duration_given=1;
         (yyval.t_step)->duration= (yyvsp[(3) - (4)].fval);;}
    break;

  case 353:

/* Line 1464 of yacc.c  */
#line 1547 "pddl+.yacc"
    {(yyval.t_step)= (yyvsp[(1) - (1)].t_step);
         (yyval.t_step)->duration_given=0;;}
    break;

  case 354:

/* Line 1464 of yacc.c  */
#line 1553 "pddl+.yacc"
    {(yyval.t_step)= new plan_step(
              current_analysis->op_tab.symbol_get((yyvsp[(2) - (4)].cp)),
	      (yyvsp[(3) - (4)].t_const_symbol_list)); delete [] (yyvsp[(2) - (4)].cp);
      ;}
    break;

  case 355:

/* Line 1464 of yacc.c  */
#line 1560 "pddl+.yacc"
    {(yyval.fval)= (yyvsp[(1) - (1)].fval);;}
    break;

  case 356:

/* Line 1464 of yacc.c  */
#line 1561 "pddl+.yacc"
    {(yyval.fval)= (float) (yyvsp[(1) - (1)].ival);;}
    break;



/* Line 1464 of yacc.c  */
#line 5088 "pddl+.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1684 of yacc.c  */
#line 1564 "pddl+.yacc"


#include <cstdio>
#include <iostream>
int line_no= 1;
using std::istream;
#include "lex.yy.h"

namespace VAL {
extern yyFlexLexer* yfl;
};


int yyerror(char * s)
{
    return 0;
}

int yylex()
{
    return yfl->yylex();
}

