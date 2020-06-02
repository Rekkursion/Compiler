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
#line 1 "xxx.y" /* yacc.c:339  */

	#include <stdio.h>
	#include "symbol_table.hpp"
	#include "e_stack.hpp"
	#include "v_stack.hpp"
	
	
	// a node of a single hash-table
	typedef struct hnode {
		// the hash-table to store identifiers in a certain scope
		HashTable table;
		// the pointer points to the previous Hnode
		struct hnode* prev;
	}Hnode;
	
	// the linked-list of hash-tables for scoping
	Hnode* hhead = NULL;
	Hnode* htail = NULL;
	
	
	/* function definitions */
	
	// handle warnings during parsing
	int warn(const char*);
	
	// construct the warning message and print it out to warn the user (f stands for formatted)
	int fwarn(const char*, const char*, const char*, const char*, const char*, const char*);
	
	// append a new hash-table when entering a new scope
	void appendHashTable();
	
	// remove a hash-table from the tail when leaving a scope
	void removeHashTable();
	
	// insert an identifier into the currently-scoped hash-table
	int insertIntoHashTable(const char*, ItemType, DataType);
	
	// search for a certain identifier in the currently-scoped hash-table
	Item* lookupInHashTable(const char*);
	
	// initialize the new identifier and insert it into the currently-scoped hash-table
	int initNewId(const char*, ItemType, DataType, DataType);

	// check if the usage of a/an variable/constant/array is correct or not
	int checkUsageOfValVarArr(const char*, int);
	
	// set the assignee, i.e., the identifier which is about to be assigned
	void setAssignee();
	
	// check the return type of a method when analyzing a RETURN statement
	int checkReturnType();
	
	// check if the expression is a boolean expression or not (for IF & WHILE statements)
	int checkBooleanExpr(const char*);
	
	// check if the expression is a numeric (int & float) expression or not
	int checkNumExpr();
	
	
	/* helper variables */
	
	// the temporally-saved identifier
	char* ident = NULL;
	
	// the temporally-saved assignee, i.e., the identifier which is about to be assigned
	char* assignee = NULL;
	
	// the temporally-saved the method when defining one
	Item* methItem = NULL;
	
	// the counter of actual arguments when invocating a certain method
	int actualArguCounter = 0;
	
	// the flag to check if there's a pair of squared-brackets after an identifier or not
	int squaredFlag = 0;
	
	// the flag to check if the expression is the return value of a method or not
	int returnFlag = 0;
	
	// the flag to check if the expression is inside a PRINT or a PRINTLN command
	/* 0 = NOT inside, 1 = in PRINT, 2 = in PRINTLN */
	int printFlag = 0;

#line 150 "y.tab.c" /* yacc.c:339  */

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
    OR = 258,
    AND = 259,
    NOT = 260,
    LT = 261,
    LE = 262,
    EQ = 263,
    GE = 264,
    GT = 265,
    NE = 266,
    MOD = 267,
    UMINUS = 268,
    ASSIGNMENT = 269,
    EXPR = 270,
    STMT = 271,
    PRINT = 272,
    PRINTLN = 273,
    READ = 274,
    COMMA = 275,
    COLON = 276,
    PERIOD = 277,
    SEMICOLON = 278,
    OPEN_PAR = 279,
    CLOSE_PAR = 280,
    OPEN_SQB = 281,
    CLOSE_SQB = 282,
    OPEN_BRA = 283,
    CLOSE_BRA = 284,
    ARROW_IN_FOR = 285,
    BOOLEAN = 286,
    BREAK = 287,
    CHAR = 288,
    CASE = 289,
    CLASS = 290,
    CONTINUE = 291,
    DEF = 292,
    DO = 293,
    ELSE = 294,
    EXIT = 295,
    FALSE = 296,
    FLOAT = 297,
    FOR = 298,
    IF = 299,
    INT = 300,
    NULLS = 301,
    OBJECT = 302,
    REPEAT = 303,
    RETURN = 304,
    STRING = 305,
    TO = 306,
    TRUE = 307,
    TYPE = 308,
    VAL = 309,
    VAR = 310,
    WHILE = 311,
    ID = 312,
    LITERAL_CHAR = 313,
    LITERAL_STRING = 314,
    LITERAL_INTEGER = 315,
    LITERAL_FLOAT = 316
  };
#endif
/* Tokens.  */
#define OR 258
#define AND 259
#define NOT 260
#define LT 261
#define LE 262
#define EQ 263
#define GE 264
#define GT 265
#define NE 266
#define MOD 267
#define UMINUS 268
#define ASSIGNMENT 269
#define EXPR 270
#define STMT 271
#define PRINT 272
#define PRINTLN 273
#define READ 274
#define COMMA 275
#define COLON 276
#define PERIOD 277
#define SEMICOLON 278
#define OPEN_PAR 279
#define CLOSE_PAR 280
#define OPEN_SQB 281
#define CLOSE_SQB 282
#define OPEN_BRA 283
#define CLOSE_BRA 284
#define ARROW_IN_FOR 285
#define BOOLEAN 286
#define BREAK 287
#define CHAR 288
#define CASE 289
#define CLASS 290
#define CONTINUE 291
#define DEF 292
#define DO 293
#define ELSE 294
#define EXIT 295
#define FALSE 296
#define FLOAT 297
#define FOR 298
#define IF 299
#define INT 300
#define NULLS 301
#define OBJECT 302
#define REPEAT 303
#define RETURN 304
#define STRING 305
#define TO 306
#define TRUE 307
#define TYPE 308
#define VAL 309
#define VAR 310
#define WHILE 311
#define ID 312
#define LITERAL_CHAR 313
#define LITERAL_STRING 314
#define LITERAL_INTEGER 315
#define LITERAL_FLOAT 316

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 86 "xxx.y" /* yacc.c:355  */

	char c;
	char s[2002];
	int i;
	int b;
	double f;
	DataType dataType;

#line 321 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 338 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   369

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  179

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

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
       2,     2,    15,    13,     2,    14,     2,    16,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   127,   132,   137,   138,   139,   144,   149,
     152,   144,   162,   163,   168,   169,   174,   185,   186,   187,
     192,   197,   198,   199,   204,   205,   206,   207,   208,   213,
     218,   219,   224,   224,   233,   233,   238,   238,   247,   248,
     253,   254,   264,   265,   266,   266,   267,   267,   268,   268,
     268,   269,   270,   275,   276,   281,   282,   283,   283,   284,
     289,   289,   308,   309,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   329,   330,   331,   332,
     333,   335,   336,   338,   340,   342,   351,   353,   363,   363,
     387,   388,   393,   394,   399,   417,   418,   423,   435,   439
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "OR", "AND", "NOT", "LT", "LE",
  "EQ", "GE", "GT", "NE", "'+'", "'-'", "'*'", "'/'", "MOD", "UMINUS",
  "ASSIGNMENT", "EXPR", "STMT", "PRINT", "PRINTLN", "READ", "COMMA",
  "COLON", "PERIOD", "SEMICOLON", "OPEN_PAR", "CLOSE_PAR", "OPEN_SQB",
  "CLOSE_SQB", "OPEN_BRA", "CLOSE_BRA", "ARROW_IN_FOR", "BOOLEAN", "BREAK",
  "CHAR", "CASE", "CLASS", "CONTINUE", "DEF", "DO", "ELSE", "EXIT",
  "FALSE", "FLOAT", "FOR", "IF", "INT", "NULLS", "OBJECT", "REPEAT",
  "RETURN", "STRING", "TO", "TRUE", "TYPE", "VAL", "VAR", "WHILE", "ID",
  "LITERAL_CHAR", "LITERAL_STRING", "LITERAL_INTEGER", "LITERAL_FLOAT",
  "$accept", "program", "$@1", "object_body", "object_body_first_part",
  "method_def", "$@2", "$@3", "$@4", "opt_formal_argus",
  "more_formal_argus", "one_formal_argu", "def_body", "block_body",
  "block_body_first_part", "data_type", "declaration", "dclr", "val_dclr",
  "$@5", "var_dclr", "$@6", "$@7", "opt_type_dclr", "opt_init",
  "statement", "$@8", "$@9", "$@10", "$@11", "opt_else", "stmt", "$@12",
  "assignment", "$@13", "opt_squared_brackets", "expr", "func_invoc",
  "$@14", "opt_actual_argus", "more_actual_argu", "one_actual_argu",
  "opt_semi", "identifier", "new_symtab", "rem_symtab", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    61,   258,   259,   260,   261,   262,   263,
     264,   265,   266,    43,    45,    42,    47,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316
};
# endif

#define YYPACT_NINF -144

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-144)))

#define YYTABLE_NINF -37

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -48,  -144,     5,   -54,  -144,  -144,   -17,  -144,  -144,    23,
     -35,  -144,   -54,   -54,   -54,    25,  -144,    32,  -144,  -144,
    -144,    33,    37,    38,  -144,  -144,  -144,    20,  -144,    20,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,    65,    35,
      66,   -54,    90,    40,    90,  -144,    42,    61,    58,    90,
      90,    90,  -144,  -144,  -144,  -144,  -144,  -144,   325,  -144,
       8,    90,   325,    37,   -54,  -144,    20,   287,  -144,   301,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,  -144,    90,  -144,   261,  -144,    61,  -144,
    -144,   352,   287,    63,    63,    63,    63,    63,    63,    11,
      11,  -144,  -144,  -144,    90,   275,  -144,    54,  -144,   325,
      64,    70,  -144,  -144,  -144,    90,  -144,   137,    70,    90,
      90,   -54,  -144,  -144,    62,    68,  -144,    69,  -144,  -144,
      32,  -144,   339,     8,  -144,   225,   225,  -144,  -144,  -144,
     -54,    90,    90,  -144,    96,  -144,  -144,    71,    67,   198,
    -144,    74,   325,   325,  -144,  -144,  -144,  -144,    72,    90,
      73,    80,    90,  -144,   325,    59,    59,   325,    44,    82,
    -144,    90,    59,  -144,   325,  -144,    85,    59,  -144
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    98,     0,     0,     1,    97,     0,     2,     7,     0,
       0,    99,     0,     0,     0,     6,     5,    96,    30,    31,
       3,     0,    39,    39,    95,    29,     8,     0,    32,     0,
      34,    98,    27,    24,    28,    26,    25,    38,     0,    38,
      41,    13,     0,     0,     0,    35,     0,    15,     0,     0,
       0,     0,    80,    79,    83,    84,    75,    74,    33,    87,
      63,     0,    40,    39,     0,    12,     0,    76,    69,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    88,     0,    85,     0,     9,    15,    16,
      86,    77,    78,    70,    71,    81,    72,    73,    82,    64,
      65,    66,    67,    68,    91,     0,    37,     0,    14,    94,
       0,    93,    62,    19,    89,     0,    90,     0,    93,     0,
       0,     0,    98,    10,     0,     0,    59,     0,    17,    18,
      96,    56,    55,    63,    92,    96,    96,    57,    23,    99,
       0,     0,     0,    42,    85,    51,    52,    63,     0,     0,
      11,     0,    44,    46,    60,    58,    99,    21,    22,     0,
       0,     0,     0,    43,    48,     0,     0,    61,     0,    54,
      47,     0,     0,    45,    49,    53,     0,     0,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
      29,    75,  -144,  -144,  -144,   -11,  -116,  -144,  -144,  -144,
    -144,  -144,  -144,   -10,  -144,  -143,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -130,   -30,  -144,  -144,  -144,
       9,    13,  -100,    -3,   -29,  -124
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     9,    10,    15,    31,   107,   139,    46,
      65,    47,   117,   148,   149,    37,    16,    17,    18,    38,
      19,    40,    43,    28,    45,   129,   160,   161,   168,   176,
     173,   130,   147,   131,   162,    85,   132,    59,   104,   110,
     116,   111,    25,    60,     3,    20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       6,   128,    41,   144,     1,     4,   158,    12,     5,    21,
      22,    23,    58,    30,    62,   150,     7,   155,    39,    67,
      68,    69,   169,   170,    13,    14,    80,    81,    82,   175,
     143,    86,   163,   157,   178,   145,   146,    83,    48,    84,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    87,   105,    89,    32,    11,    33,    -4,
      24,    48,    26,    27,    29,    49,   -36,    34,    42,    44,
      35,    61,    63,    50,   109,    36,    78,    79,    80,    81,
      82,   119,   120,   121,    66,   109,    64,   113,    51,   135,
     136,   140,   122,   138,   114,   115,    49,   141,   142,   154,
     171,   156,    84,   165,    50,    52,   -20,   124,   125,   159,
     166,   152,   153,   126,   133,   177,    53,   108,   137,    51,
     127,     5,    54,    55,    56,    57,   172,   134,   118,   164,
       0,     0,   167,     0,     0,     0,    52,   151,     0,    88,
       0,   174,     0,    49,     0,     0,   133,    53,     0,     0,
       0,    50,     5,    54,    55,    56,    57,     0,     0,   119,
     120,   121,   133,   133,     0,     0,    51,     0,     0,   133,
     122,   123,     0,     0,   133,     0,     0,     0,     0,     0,
       0,     0,     0,    52,     0,   124,   125,     0,     0,     0,
       0,   126,     0,     0,    53,     0,    13,    14,   127,     5,
      54,    55,    56,    57,    49,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
     119,   120,   121,     0,     0,     0,     0,    51,     0,    70,
      71,   122,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,     0,    52,     0,   124,   125,     0,     0,
       0,     0,   126,    24,     0,    53,     0,    13,    14,   127,
       5,    54,    55,    56,    57,    70,    71,     0,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    70,
      71,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,   106,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    70,    71,   112,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    70,
      71,    90,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    70,    71,     0,    72,    73,    74,    75,
      76,    77,    78,     0,    80,    81,    82,    71,     0,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
       3,   117,    31,   133,    52,     0,   149,    42,    62,    12,
      13,    14,    42,    23,    44,   139,    33,   147,    29,    49,
      50,    51,   165,   166,    59,    60,    15,    16,    17,   172,
     130,    61,   156,   149,   177,   135,   136,    29,    41,    31,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    63,    84,    66,    36,    34,    38,    34,
      28,    64,    29,    26,    26,     6,    31,    47,     3,     3,
      50,    31,    30,    14,   104,    55,    13,    14,    15,    16,
      17,    22,    23,    24,    26,   115,    25,    33,    29,   119,
     120,    29,    33,   122,    30,    25,     6,    29,    29,     3,
      56,    34,    31,    30,    14,    46,    34,    48,    49,    35,
      30,   141,   142,    54,   117,    30,    57,    88,   121,    29,
      61,    62,    63,    64,    65,    66,    44,   118,   115,   159,
      -1,    -1,   162,    -1,    -1,    -1,    46,   140,    -1,    64,
      -1,   171,    -1,     6,    -1,    -1,   149,    57,    -1,    -1,
      -1,    14,    62,    63,    64,    65,    66,    -1,    -1,    22,
      23,    24,   165,   166,    -1,    -1,    29,    -1,    -1,   172,
      33,    34,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    48,    49,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    57,    -1,    59,    60,    61,    62,
      63,    64,    65,    66,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      22,    23,    24,    -1,    -1,    -1,    -1,    29,    -1,     4,
       5,    33,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    -1,    46,    -1,    48,    49,    -1,    -1,
      -1,    -1,    54,    28,    -1,    57,    -1,    59,    60,    61,
      62,    63,    64,    65,    66,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    32,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     4,     5,    32,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,    30,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    -1,    15,    16,    17,     5,    -1,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    52,    68,   111,     0,    62,   110,    33,    69,    70,
      71,    34,    42,    59,    60,    72,    83,    84,    85,    87,
     112,   110,   110,   110,    28,   109,    29,    26,    90,    26,
      90,    73,    36,    38,    47,    50,    55,    82,    86,    82,
      88,   111,     3,    89,     3,    91,    76,    78,   110,     6,
      14,    29,    46,    57,    63,    64,    65,    66,   103,   104,
     110,    31,   103,    30,    25,    77,    26,   103,   103,   103,
       4,     5,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    29,    31,   102,   103,    90,    78,    82,
      30,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   105,   103,    32,    74,    77,   103,
     106,   108,    32,    33,    30,    25,   107,    79,   108,    22,
      23,    24,    33,    34,    48,    49,    54,    61,    83,    92,
      98,   100,   103,   110,   107,   103,   103,   110,   111,    75,
      29,    29,    29,   109,   102,   109,   109,    99,    80,    81,
     112,   110,   103,   103,     3,   102,    34,    83,    92,    35,
      93,    94,   101,   112,   103,    30,    30,   103,    95,    92,
      92,    56,    44,    97,   103,    92,    96,    30,    92
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    69,    68,    70,    71,    71,    71,    73,    74,
      75,    72,    76,    76,    77,    77,    78,    79,    79,    79,
      80,    81,    81,    81,    82,    82,    82,    82,    82,    83,
      84,    84,    86,    85,    88,    87,    89,    87,    90,    90,
      91,    91,    92,    92,    93,    92,    94,    92,    95,    96,
      92,    92,    92,    97,    97,    98,    98,    99,    98,    98,
     101,   100,   102,   102,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   105,   104,
     106,   106,   107,   107,   108,   109,   109,   110,   111,   112
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     8,     2,     2,     2,     0,     0,     0,
       0,    14,     2,     0,     3,     0,     3,     2,     2,     0,
       2,     2,     2,     0,     1,     1,     1,     1,     1,     2,
       1,     1,     0,     6,     0,     5,     0,     8,     2,     0,
       2,     0,     2,     5,     0,     7,     0,     6,     0,     0,
      11,     3,     3,     2,     0,     1,     1,     0,     4,     1,
       0,     5,     3,     0,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     3,     1,     1,     2,     3,     3,     1,
       1,     3,     3,     1,     1,     2,     3,     1,     0,     5,
       2,     0,     3,     0,     1,     1,     0,     1,     0,     0
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
#line 127 "xxx.y" /* yacc.c:1646  */
    { insertIntoHashTable(ident, _object, _none); }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 144 "xxx.y" /* yacc.c:1646  */
    {
		// insert the method symbol into the currently-scoped hash-table
		insertIntoHashTable(ident, _method, _none);
		// temporally save the method-item
		methItem = lookupInHashTable(ident);
	}
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 149 "xxx.y" /* yacc.c:1646  */
    {
		// set the return type to the currently-defining method
		setReturnType(&(methItem->methDef), (yyvsp[0].dataType));
	}
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 152 "xxx.y" /* yacc.c:1646  */
    {
		// check the return type if hasn't do the checking yet
		checkReturnType();
		// nullify the pointer to the already-defined method
		methItem = NULL;
	}
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 174 "xxx.y" /* yacc.c:1646  */
    {
		// add a new formal argument into the currently-defining method
		if (methItem != NULL)
			addFormalArgu(&(methItem->methDef), ident, (yyvsp[0].dataType));
		// also insert it into the currently-scoped hash-table
		insertIntoHashTable(ident, _variable, (yyvsp[0].dataType));
	}
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 204 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _char; }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 205 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _string; }
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 206 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _int; }
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 207 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _boolean; }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 208 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _float; }
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 224 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); }
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 224 "xxx.y" /* yacc.c:1646  */
    {
		Enode* e = pop_e();
		initNewId(assignee, _constant, (yyvsp[-3].dataType), (e == NULL) ? _none : e->_type);
		free_e(e);
	}
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 233 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); }
#line 1684 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 233 "xxx.y" /* yacc.c:1646  */
    {
		Enode* e = pop_e();
		initNewId(assignee, _variable, (yyvsp[-2].dataType), (e == NULL) ? _none : e->_type);
		free_e(e);
	}
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 238 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); }
#line 1700 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 238 "xxx.y" /* yacc.c:1646  */
    {
		Enode* e = pop_e();
		initNewId(assignee, _array, (yyvsp[-4].dataType), (e == NULL) ? _none : e->_type);
		free_e(e);
	}
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 247 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = (yyvsp[0].dataType); }
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 248 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _none; }
#line 1722 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 253 "xxx.y" /* yacc.c:1646  */
    { /* pop'd */ }
#line 1728 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 266 "xxx.y" /* yacc.c:1646  */
    { checkBooleanExpr("IF"); }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 267 "xxx.y" /* yacc.c:1646  */
    { checkBooleanExpr("WHILE"); }
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 268 "xxx.y" /* yacc.c:1646  */
    { checkNumExpr(); }
#line 1746 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 268 "xxx.y" /* yacc.c:1646  */
    { checkNumExpr(); }
#line 1752 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 269 "xxx.y" /* yacc.c:1646  */
    { printFlag = 1; returnFlag = 0; }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 270 "xxx.y" /* yacc.c:1646  */
    { printFlag = 2; returnFlag = 0; }
#line 1764 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 281 "xxx.y" /* yacc.c:1646  */
    { checkReturnType(); }
#line 1770 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 283 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); }
#line 1776 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 283 "xxx.y" /* yacc.c:1646  */
    { checkUsageOfValVarArr(assignee, 1); }
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 284 "xxx.y" /* yacc.c:1646  */
    { returnFlag = 1; printFlag = 0; }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 289 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); checkUsageOfValVarArr(assignee, 1); }
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 289 "xxx.y" /* yacc.c:1646  */
    {
		Enode* e = pop_e();
		if (e == NULL)
			warn("No assigned value found in an assignment.");
		else {
			Item* item = lookupInHashTable(assignee);
			if (item) {
				if (item->dataType == _none)
					item->dataType = e->_type;
				else if (item->dataType != e->_type)
					fwarn("The types are NOT the same between LHS (%s) and RHS (%s) in an assignment.", toS(item->dataType), toS(e->_type), NULL, NULL, NULL);
			}
		}
		free_e(e);
	}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 308 "xxx.y" /* yacc.c:1646  */
    { squaredFlag = 1; }
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 309 "xxx.y" /* yacc.c:1646  */
    { squaredFlag = 0; }
#line 1826 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 316 "xxx.y" /* yacc.c:1646  */
    { doOp("+", 1, warn); }
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 317 "xxx.y" /* yacc.c:1646  */
    { doOp("-", 1, warn); }
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 318 "xxx.y" /* yacc.c:1646  */
    { doOp("*", 1, warn); }
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 319 "xxx.y" /* yacc.c:1646  */
    { doOp("/", 1, warn); }
#line 1850 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 320 "xxx.y" /* yacc.c:1646  */
    { doOp("%", 1, warn); }
#line 1856 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 321 "xxx.y" /* yacc.c:1646  */
    { doOp("UMINUS", 0, warn); }
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 322 "xxx.y" /* yacc.c:1646  */
    { doOp("<", 1, warn); }
#line 1868 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 323 "xxx.y" /* yacc.c:1646  */
    { doOp("<=", 1, warn); }
#line 1874 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 324 "xxx.y" /* yacc.c:1646  */
    { doOp(">=", 1, warn); }
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 325 "xxx.y" /* yacc.c:1646  */
    { doOp(">", 1, warn); }
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 326 "xxx.y" /* yacc.c:1646  */
    { push_e(_float, &((yyvsp[0].f))); }
#line 1892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 327 "xxx.y" /* yacc.c:1646  */
    { push_e(_int, &((yyvsp[0].i))); }
#line 1898 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 329 "xxx.y" /* yacc.c:1646  */
    { doOp("!", 0, warn); }
#line 1904 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 330 "xxx.y" /* yacc.c:1646  */
    { doOp("||", 1, warn); }
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 331 "xxx.y" /* yacc.c:1646  */
    { doOp("&&", 1, warn); }
#line 1916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 332 "xxx.y" /* yacc.c:1646  */
    { int t = 1; push_e(_boolean, &t); }
#line 1922 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 333 "xxx.y" /* yacc.c:1646  */
    { int f = 0; push_e(_boolean, &f); }
#line 1928 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 335 "xxx.y" /* yacc.c:1646  */
    { doOp("==", 1, warn); }
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 336 "xxx.y" /* yacc.c:1646  */
    { doOp("!=", 1, warn); }
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 338 "xxx.y" /* yacc.c:1646  */
    { push_e(_char, &((yyvsp[0].c))); }
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 340 "xxx.y" /* yacc.c:1646  */
    { char* s = (char*)malloc(sizeof(char) * (strlen((yyvsp[0].s)) + 1)); strcpy(s, (yyvsp[0].s)); push_e(_string, &s); free(s); }
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 342 "xxx.y" /* yacc.c:1646  */
    {
		// get the identifier stored in the currently-scoped hash-table
		Item* item = lookupInHashTable(ident);
		// check if the identifier is used correctly or not
		checkUsageOfValVarArr(ident, 0);
		// push the data-type back into the expr-stack
		push_e((item == NULL) ? _none : item->dataType, NULL);
	}
#line 1965 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 353 "xxx.y" /* yacc.c:1646  */
    {
		// push an Enode according to the return type of this invocated function
		push_e((methItem == NULL || methItem->methDef == NULL) ? _none : methItem->methDef->_ret_type, NULL);
		// nullify the pointer to the method item
		methItem = NULL;
	}
#line 1976 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 363 "xxx.y" /* yacc.c:1646  */
    {
		// set the counter of actual arguments to zero
		actualArguCounter = 0;
		// get the name of the defined method in the hash-table
		methItem = lookupInHashTable(ident);
		// not found
		if (methItem == NULL)
			fwarn("The identifier \"%s\" does NOT exist.", ident, NULL, NULL, NULL, NULL);
		// found but the identifier is NOT a method
		else if (methItem->itemType != _method) {
			methItem = NULL;
			fwarn("The identifier \"%s\" is NOT a method.", ident, NULL, NULL, NULL, NULL);
		}
	}
#line 1995 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 376 "xxx.y" /* yacc.c:1646  */
    {
		// if the number of actual arguments are NOT enough according to the defined formal arguments
		if (actualArguCounter < methItem->methDef->argc)
			fwarn("The argument(s) are NOT enough when invocating the method \"%s\".", methItem->name, NULL, NULL, NULL, NULL);
		// reset the counter for actual arguments
		actualArguCounter = 0;
	}
#line 2007 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 399 "xxx.y" /* yacc.c:1646  */
    {
		Enode* nd = pop_e();
		// check this actual argument with the formal argument
		if (methItem != NULL) {
			int res = checkFormalArguType(methItem->methDef, (nd == NULL ? _none : nd->_type), actualArguCounter);
			if (res == -1)
				fwarn("Too much argument(s) when invocating the method \"%s\".", methItem->name, NULL, NULL, NULL, NULL);
			else if (res == 0)
				fwarn("Types are NOT matched when invocating the method \"%s\".", methItem->name, NULL, NULL, NULL, NULL);
		}
		free_e(nd);
		// count the number of actual arguments
		++actualArguCounter;
	}
#line 2026 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 417 "xxx.y" /* yacc.c:1646  */
    { checkReturnType(); }
#line 2032 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 423 "xxx.y" /* yacc.c:1646  */
    {
		// store it in a global variable 'ident'
		if (ident != NULL)
			free(ident);
		ident = (char*)malloc(sizeof(char) * (strlen((yyvsp[0].s)) + 1));
		ident[0] = 0;
		strcpy(ident, (yyvsp[0].s));
	}
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 435 "xxx.y" /* yacc.c:1646  */
    { appendHashTable(); }
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 439 "xxx.y" /* yacc.c:1646  */
    { removeHashTable(); }
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
#line 441 "xxx.y" /* yacc.c:1906  */


// warning happens -> just tell the user
int warn(const char* msg) {
	// get the line number
	extern int yylineno;
	// print the warning message out
	fprintf(stderr, "line %d: %s\n", yylineno, msg);
	return 0;
}

// construct the warning message and print it out to warn the user (f stands for formatted)
int fwarn(const char* msgBody, const char* p0, const char* p1, const char* p2, const char* p3, const char* p4) {
	// the buffer for storing the warning message
	char msg[20002];
	// build up the warning message
	sprintf(msg, msgBody, (p0 == NULL ? "" : p0), (p1 == NULL ? "" : p1), (p2 == NULL ? "" : p2), (p3 == NULL ? "" : p3), (p4 == NULL ? "" : p4));
	// call the 'warn' function to print it out
	return warn(msg);
}

// the main function
int main() {
	// start parsing
	yyparse();
	return 0;
}

// append a new hash-table when reaching a new scope
void appendHashTable() {
	// create a new hnode for storing the latest hash-table
	Hnode* newNode = (Hnode*)malloc(sizeof(Hnode));
	newNode->table = create();
	newNode->prev = NULL;

	// the first node
	if (hhead == NULL) {
		hhead = newNode;
		htail = hhead;
	}
	// general case
	else {
		newNode->prev = htail;
		htail = newNode;
	}
}

// remove a hash-table when leaving a scope
void removeHashTable() {
	// if there's no symbol-table, return directly
	if (htail == NULL)
		return;
	
	// delete the table at the tail
	delete_table(htail->table);
	
	// update the htail pointer
	Hnode* p = htail;
	htail = htail->prev;
	
	// free the Hnode pointer that just been removed
	free(p);
}

// insert an identifier into the hash-table for the current scope with optionally-passed item-type and data-type
int insertIntoHashTable(const char* name, ItemType itemType, DataType dataType) {
	// first, check if the htail (the latest hash-table) is NULL or not
	if (htail == NULL)
		warn("Syntax error. You cannot assign variables here.");
	
	// try to insert the symbol into the latest hash-table
	int insertionResult = insert(htail->table, name);
	
	// insertion failed: the identifier has already been declared in the current scope
	if (insertionResult == -1) {
		fwarn("The identifier \"%s\" has already been declared in the current scope.", name, NULL, NULL, NULL, NULL);
		return -1;
	}
	
	// get the just-inserted symbol
	Item* item = lookupInHashTable(name);
	if (item != NULL) {
		// set the item-type if needs
		item->itemType = itemType;
		
		// set the data-type if needs
		item->dataType = dataType;
	}
	
	//printf("ID:|%s|%d|%s|\n", item->name, item->itemType, toS(item->dataType));
	
	// return the result of insertion
	return insertionResult;
}

// search for a certain identifier in the latest hash-table
Item* lookupInHashTable(const char* name) {
	// iteratively search for the identifier from the latest symbol-table to the first one
	Hnode* p = htail;
	while (p) {
		Item* item = lookup(p->table, name);
		if (item != NULL)
			return item;
		p = p->prev;
	}
	
	// not found
	return NULL;
}




// initialize the new identifier and insert it into the currently-scoped hash-table
int initNewId(const char* name, ItemType itemType, DataType declaredDataType, DataType assignedDataType) {
	// if the passed item is a variable
	if (itemType == _variable) {
		// no declared & assigned data-types
		if (declaredDataType == _none && assignedDataType == _none)
			return insertIntoHashTable(name, _variable, _none);
		
		// there's only assigned data-type
		else if (declaredDataType == _none)
			return insertIntoHashTable(name, _variable, assignedDataType);
		
		// there's only declared data-type
		else if (assignedDataType == _none)
			return insertIntoHashTable(name, _variable, declaredDataType);
		
		// both declared & assigned data-types
		else {
			// if the explicitly-declared & assigned data-types are NOT matched -> warning
			if (declaredDataType != assignedDataType)
				fwarn("The declared type (%s) and the assigned type (%s) are NOT matched when declaring the variable \"%s\".", toS(declaredDataType), toS(assignedDataType), name, NULL, NULL);
			
			// the tie is broken in favor of the explicitly-declared data-type
			return insertIntoHashTable(name, _variable, declaredDataType);
		}
	}
	
	// if the passed item is a constant
	else if (itemType == _constant) {
		// no declared & assigned data-types
		if (declaredDataType == _none && assignedDataType == _none) {
			warn("No declared & assigned data-type of a constant. The default type is INT.");
			return insertIntoHashTable(name, _constant, _int);
		}
		
		// there's only assigned data-type
		else if (declaredDataType == _none)
			return insertIntoHashTable(name, _constant, assignedDataType);
		
		// there's only declared data-type
		else if (assignedDataType == _none) {
			warn("There\'s no initially-assigned value of a constant\'s declaration.");
			return insertIntoHashTable(name, _constant, declaredDataType);
		}
		
		// both declared & assigned data-types
		else {
			// if the explicitly-declared & assigned data-types are NOT matched -> warning
			if (declaredDataType != assignedDataType)
				fwarn("The declared type (%s) and the assigned type (%s) are NOT matched when declaring the constant \"%s\".", toS(declaredDataType), toS(assignedDataType), name, NULL, NULL);
			
			// the tie is broken in favor of the explicitly-declared data-type
			return insertIntoHashTable(name, _constant, declaredDataType);
		}
	}
	
	// if the passed item is an array
	else if (itemType == _array) {
		// no declared data-type
		if (declaredDataType == _none)
			warn("The declaration of the data-type for an array initialization is a must. The default type is INT.");
		
		// the given size of this array is NOT an INT type
		if (assignedDataType != _int)
			warn("The size of an array must be integer.");
		
		// insert into the currently-scoped hash-table
		return insertIntoHashTable(name, _array, (declaredDataType == _none) ? _int : declaredDataType);
	}
	
	// if the passed item is neither a variable/constant nor an array
	else
		return insertIntoHashTable(name, _none_item, _none);
}

// check if the usage of a/an variable/constant/array is correct or not
int checkUsageOfValVarArr(const char* symbol, int toBeAssignedFlag) {
	// get the item from the currently-scoped hash-table
	Item* item = lookupInHashTable(symbol);
	
	// get the expression as index if any
	Enode* nd = NULL;
	if (squaredFlag)
		nd = pop_e();
	
	if (item == NULL)
		fwarn("The identifier \"%s\" does NOT exist.", symbol, NULL, NULL, NULL, NULL);
	else {
		// there's a pair of squared-brackets
		if (squaredFlag) {
			if (item->itemType != _array)
				fwarn("The identifier \"%s\" is NOT an array but you use it as it is.", symbol, NULL, NULL, NULL, NULL);
			else {
				if (nd == NULL)
					fwarn("The identifier \"%s\" is an array but NO index found.", symbol, NULL, NULL, NULL, NULL);
				else if (nd->_type != _int)
					warn("The index of an array must be integer.");
			}
		}
		// no squared-brackets
		else {
			if (item->itemType == _constant) {
				if (toBeAssignedFlag)
					fwarn("The identifier \"%s\" is a constant which CANNOT be re-assigned after initialized.", symbol, NULL, NULL, NULL, NULL);
			}
			else if (item->itemType == _array)
				fwarn("The identifier \"%s\" is an array but NO index found.", symbol, NULL, NULL, NULL, NULL);
			else if (item->itemType != _variable)
				fwarn("The identifier \"%s\" is NOT a variable or a constant.", symbol, NULL, NULL, NULL, NULL);
		}
	}
	
	// free the pop'd Enode if needs
	free_e(nd);
}

// set the assignee, i.e., the identifier which is about to be assigned
void setAssignee() {
	// free the assignee if needs
	if (assignee != NULL)
		free(assignee);
	
	// nullify it
	assignee = NULL;
	
	// re-assign the value through the temporally-saved variable 'ident' if any
	if (ident) {
		assignee = (char*)malloc(sizeof(char) * (strlen(ident) + 1));
		assignee[0] = 0;
		strcpy(assignee, ident);
	}
}

// check the return type of a method when analyzing a RETURN statement
int checkReturnType() {
	// pop an Enode as the return value
	Enode* e = pop_e();
	
	// if the return-falg is ON
	if (returnFlag) {
		// outside the method -> error
		if (methItem == NULL || methItem->methDef == NULL)
			warn("No RETURN statement allowed outside the method.");
		
		// general case
		else {
			// the method prototype says that this method does NOT have any return type
			if (methItem->methDef->_ret_type == _none) {
				// but there's one -> warning
				if (e != NULL && e->_type != _none)
					fwarn("There\'s NO return type of the method \"%s\", but a type \'%s\' has been found inside this method.", methItem->name, toS(e->_type), NULL, NULL, NULL);
			}
			
			// this method has a return type but NOTHING found after a RETURN keyword
			else if (e == NULL)
				fwarn("The return type of the method \"%s\" is \'%s\', but there\'s a RETURN statement without any values.", methItem->name, toS(methItem->methDef->_ret_type), NULL, NULL, NULL);
			
			// types between method prototype and actual return-type are NOT the same
			else if (methItem->methDef->_ret_type != e->_type)
				fwarn("The return type of the method \"%s\" is \'%s\', but a type \'%s\' has been found inside this method.", methItem->name, toS(methItem->methDef->_ret_type), toS(e->_type), NULL, NULL);
			
		}
	}
	
	// reset the flags
	printFlag = 0;
	returnFlag = 0;
	
	// free the pop'd Enode
	free_e(e);
}
	
// check if the expression is a boolean expression or not (for IF & WHILE statements)
int checkBooleanExpr(const char* if_or_while) {
	// pop an Enode that is about to be checked
	Enode* e = pop_e();
	
	// if the expr-stack is empty -> expression-lacking error
	if (e == NULL) {
		if (strcmp(if_or_while, "IF") == 0)
			warn("No boolean expression of the conditional statement IF.");
		else if (strcmp(if_or_while, "WHILE") == 0)
			warn("No boolean expression of the loop statement WHILE.");
	}
	// the type of the pop'd expression must be a BOOLEAN type in either IF-clause or WHILE-clause
	else if (e->_type != _boolean) {
		if (strcmp(if_or_while, "IF") == 0)
			warn("The expression of the conditional statement IF must be a boolean expression.");
		else if (strcmp(if_or_while, "WHILE") == 0)
			warn("The expression of the loop statement WHILE must be a boolean expression.");
	}
	
	// free the pop'd Enode
	free_e(e);
}

// check if the expression is a numeric (int & float) expression or not
int checkNumExpr() {
	// pop an Enode that is about to be checked
	Enode* e = pop_e();
	
	// if the expr-stack is empty -> expression-lacking error
	if (e == NULL)
		warn("There shall be a numeric expression but no found.");
	// the type of the pop'd expression must be a numeric type, i.e., an INT or a FLOAT
	else if (e->_type != _int && e->_type != _float)
		fwarn("The expression here shall be numeric but the type of '%s' found.", toS(e->_type), NULL, NULL, NULL, NULL);
	
	// free the pop'd Enode
	free_e(e);
}
