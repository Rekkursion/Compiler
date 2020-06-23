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
	#include "e_stack.hpp" // the stack for expressions
	#include "v_stack.hpp" // the stack for variables/constands/arrays
	#include "m_stack.hpp" // the stack for methods (invocations)
	#include "l_stack.hpp" // the stack for generating labels in java byte code
	
	// for the symbol table
	#ifndef _SYMBOL_TABLE
	#include "symbol_table.hpp"
	#define _SYMBOL_TABLE
	#endif
	
	// the file pointer for outputting the java assembly code
	FILE* fout = NULL;
	
	// a node of a single hash-table
	typedef struct hnode {
		// the flag for identifying if this symbol-table is global or not
		int inGlobalFlag;
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
	
	// get the number of a local variable stored in the currently-scoped hash-table
	int getLocalVarNoInHashTable(const char*);
	
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
	
	// generate the java assembly code w/ a plain string
	void genJavaa(const char*);
	
	// generate the java assembly code w/ a formatted string ('f' stands for 'formatted')
	void fgenJavaa(const char*, const char*, const char*, const char*, const char*, const char*);
	
	// generate the java assembly code w/ an integer value ('i' stands for 'integer')
	void igenJavaa(const char*, const int, const char*);
	
	// generate the java assembly code for a relational operation ('r' stands for 'relational')
	void rgenJavaa(const char*);
	
	// generate the java assembly code for a read-clause ('u' stands for 'user' input)
	void ugenJavaa(const char*);
	
	// buffer the java assembly code w/ a plain string
	void bufJavaa(const char*);
	
	// buffer the java assembly code w/ a formatted string ('f' stands for 'formatted')
	void fbufJavaa(const char*, const char*, const char*, const char*, const char*, const char*);
	
	// buffer the java assembly code w/ an integer value ('i' stands for 'integer')
	void ibufJavaa(const char*, const int, const char*);
	
	// flush the buffered java assembly code
	void flushJavaa();
	
	
	
	/* helper variables */
	
	// the object name
	char* objName = NULL;
	
	// the temporally-saved identifier
	char* ident = NULL;
	
	// the temporally-saved assignee, i.e., the identifier which is about to be assigned
	char* assignee = NULL;
	
	// the buffer of java assembly code
	char* jBuf = NULL;
	
	// the temporally-saved method when defining one
	Item* methItem = NULL;
	
	// the flag to check if there's a pair of squared-brackets after an identifier or not
	int squaredFlag = 0;
	
	// the flag to check if the expression is the return value of a method or not
	int returnFlag = 0;
	
	// the flag to check if the expression is inside a PRINT or a PRINTLN command
	/* 0 = NOT inside, 1 = in PRINT, 2 = in PRINTLN */
	int printFlag = 0;
	
	// the flag to check if there's a method named "main" or not
	int hasMainFlag = 0;
	
	// the counter for localizing the local variables to jvm
	int localCounter = 0;
	
	// in global or local currently
	int inGlobal = 1;
	
	// in a global's variable declaration or not
	int inGlobalVarDclr = 0;
	
	// the counter of labels
	int labelCounter = 0;
	
	// the counter of the label for loop statements
	int loopLabelCounter = 0;
	
	// the counter for for-loops
	int forLoopCounter = 0;
	
	// the counter of labels for the read-clause
	int readLabelCounter = 0;

#line 219 "y.tab.c" /* yacc.c:339  */

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
    RETURN = 275,
    RETURN_W_EXPR = 276,
    COMMA = 277,
    COLON = 278,
    PERIOD = 279,
    SEMICOLON = 280,
    OPEN_PAR = 281,
    CLOSE_PAR = 282,
    OPEN_SQB = 283,
    CLOSE_SQB = 284,
    OPEN_BRA = 285,
    CLOSE_BRA = 286,
    ARROW_IN_FOR = 287,
    BOOLEAN = 288,
    BREAK = 289,
    CHAR = 290,
    CASE = 291,
    CLASS = 292,
    CONTINUE = 293,
    DEF = 294,
    DO = 295,
    ELSE = 296,
    EXIT = 297,
    FALSE = 298,
    FLOAT = 299,
    FOR = 300,
    IF = 301,
    INT = 302,
    LENGTH = 303,
    NULLS = 304,
    OBJECT = 305,
    REPEAT = 306,
    STRING = 307,
    TO = 308,
    TRUE = 309,
    TYPE = 310,
    VAL = 311,
    VAR = 312,
    WHILE = 313,
    ID = 314,
    LITERAL_CHAR = 315,
    LITERAL_STRING = 316,
    LITERAL_INTEGER = 317,
    LITERAL_FLOAT = 318
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
#define RETURN 275
#define RETURN_W_EXPR 276
#define COMMA 277
#define COLON 278
#define PERIOD 279
#define SEMICOLON 280
#define OPEN_PAR 281
#define CLOSE_PAR 282
#define OPEN_SQB 283
#define CLOSE_SQB 284
#define OPEN_BRA 285
#define CLOSE_BRA 286
#define ARROW_IN_FOR 287
#define BOOLEAN 288
#define BREAK 289
#define CHAR 290
#define CASE 291
#define CLASS 292
#define CONTINUE 293
#define DEF 294
#define DO 295
#define ELSE 296
#define EXIT 297
#define FALSE 298
#define FLOAT 299
#define FOR 300
#define IF 301
#define INT 302
#define LENGTH 303
#define NULLS 304
#define OBJECT 305
#define REPEAT 306
#define STRING 307
#define TO 308
#define TRUE 309
#define TYPE 310
#define VAL 311
#define VAR 312
#define WHILE 313
#define ID 314
#define LITERAL_CHAR 315
#define LITERAL_STRING 316
#define LITERAL_INTEGER 317
#define LITERAL_FLOAT 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 155 "xxx.y" /* yacc.c:355  */

	char c;
	char s[2002];
	int i;
	int b;
	double f;
	DataType dataType;

#line 394 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 411 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  188

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

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
      60,    61,    62,    63,    64,    65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   198,   198,   198,   213,   218,   219,   220,   225,   233,
     257,   225,   275,   276,   281,   282,   287,   298,   299,   300,
     305,   306,   307,   312,   313,   314,   315,   316,   321,   326,
     327,   332,   332,   351,   351,   382,   382,   400,   401,   406,
     407,   417,   418,   419,   425,   419,   438,   442,   438,   453,
     456,   490,   453,   531,   532,   537,   538,   539,   539,   540,
     544,   548,   548,   565,   565,   586,   586,   611,   611,   623,
     624,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   636,   637,   638,   639,   640,   642,   643,   645,   647,
     655,   679,   679,   686,   688,   698,   709,   709,   744,   745,
     750,   751,   756,   778,   779,   784,   796,   800
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "OR", "AND", "NOT", "LT", "LE",
  "EQ", "GE", "GT", "NE", "'+'", "'-'", "'*'", "'/'", "MOD", "UMINUS",
  "ASSIGNMENT", "EXPR", "STMT", "PRINT", "PRINTLN", "READ", "RETURN",
  "RETURN_W_EXPR", "COMMA", "COLON", "PERIOD", "SEMICOLON", "OPEN_PAR",
  "CLOSE_PAR", "OPEN_SQB", "CLOSE_SQB", "OPEN_BRA", "CLOSE_BRA",
  "ARROW_IN_FOR", "BOOLEAN", "BREAK", "CHAR", "CASE", "CLASS", "CONTINUE",
  "DEF", "DO", "ELSE", "EXIT", "FALSE", "FLOAT", "FOR", "IF", "INT",
  "LENGTH", "NULLS", "OBJECT", "REPEAT", "STRING", "TO", "TRUE", "TYPE",
  "VAL", "VAR", "WHILE", "ID", "LITERAL_CHAR", "LITERAL_STRING",
  "LITERAL_INTEGER", "LITERAL_FLOAT", "$accept", "program", "$@1",
  "object_body", "object_body_first_part", "method_def", "$@2", "$@3",
  "$@4", "opt_formal_argus", "more_formal_argus", "one_formal_argu",
  "def_body", "block_body", "data_type", "declaration", "dclr", "val_dclr",
  "$@5", "var_dclr", "$@6", "$@7", "opt_type_dclr", "opt_init",
  "statement", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "opt_else", "stmt", "$@15", "$@16", "$@17", "assignment", "$@18", "$@19",
  "expr", "$@20", "func_invoc", "$@21", "opt_actual_argus",
  "more_actual_argu", "one_actual_argu", "opt_semi", "identifier",
  "new_symtab", "rem_symtab", YY_NULLPTR
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
     310,   311,   312,   313,   314,   315,   316,   317,   318
};
# endif

#define YYPACT_NINF -152

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-152)))

#define YYTABLE_NINF -36

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -51,  -152,     5,   -56,  -152,  -152,   -22,  -152,  -152,   -19,
     -37,  -152,   -56,   -56,   -56,    20,  -152,    27,  -152,  -152,
    -152,    29,    34,    35,  -152,  -152,  -152,    26,  -152,    26,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,    64,    36,
      65,   -56,    23,    39,    23,  -152,    41,    47,    52,    23,
      23,    23,  -152,  -152,  -152,  -152,  -152,  -152,   267,  -152,
      48,    23,   267,    34,   -56,  -152,    26,   195,  -152,   253,
      23,    23,    23,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    31,  -152,  -152,   211,  -152,    47,  -152,
    -152,   281,   195,    84,    84,    84,    84,    84,    84,    11,
      11,  -152,  -152,  -152,  -152,    23,    23,  -152,    50,  -152,
     267,    54,    66,   225,  -152,  -152,    23,  -152,  -152,    96,
      66,  -152,  -152,  -152,    23,  -152,  -152,    61,    71,    72,
    -152,  -152,    27,  -152,  -152,     1,  -152,    23,    23,   -56,
     267,  -152,  -152,   -56,    23,  -152,  -152,  -152,    92,   267,
     267,  -152,   129,  -152,  -152,   267,    23,    23,    23,  -152,
    -152,  -152,    67,    73,   267,   239,   267,  -152,    23,   150,
      74,   106,   267,  -152,   150,    23,    53,    69,  -152,   267,
      23,   150,  -152,   267,  -152,    78,   150,  -152
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   106,     0,     0,     1,   105,     0,     2,     7,     0,
       0,   107,     0,     0,     0,     6,     5,   104,    29,    30,
       3,     0,    38,    38,   103,    28,     8,     0,    31,     0,
      33,   106,    26,    23,    27,    25,    24,    37,     0,    37,
      40,    13,     0,     0,     0,    34,     0,    15,     0,     0,
       0,     0,    85,    84,    88,    89,    80,    79,    32,    94,
      90,     0,    39,    38,     0,    12,     0,    81,    74,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    96,    91,     0,     9,    15,    16,
      93,    82,    83,    75,    76,    86,    77,    78,    87,    69,
      70,    71,    72,    73,    95,    99,     0,    36,     0,    14,
     102,     0,   101,     0,    19,    97,     0,    98,    92,     0,
     101,    61,    63,    57,    60,   106,    10,     0,     0,     0,
      17,    18,   104,    55,    56,    65,   100,     0,     0,     0,
      59,    22,   107,     0,     0,    46,    41,    67,     0,    62,
      64,    58,     0,    11,    49,    43,     0,     0,     0,   107,
      20,    21,     0,     0,    47,     0,    66,    42,     0,     0,
       0,     0,    50,    44,     0,     0,     0,    54,    48,    68,
       0,     0,    45,    51,    53,     0,     0,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
      24,    49,  -152,  -152,    -7,  -113,  -152,  -152,  -152,  -152,
    -152,  -152,    -8,  -152,  -151,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
     -30,  -152,  -116,  -152,  -152,     2,     7,   -15,    -3,   -29,
    -126
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     8,     9,    10,    15,    31,   108,   142,    46,
      65,    47,   119,   152,    37,    16,    17,    18,    38,    19,
      40,    43,    28,    45,   131,   163,   177,   156,   170,   162,
     176,   185,   182,   132,   139,   137,   138,   133,   148,   157,
     110,   106,    59,   105,   111,   117,   112,    25,    60,     3,
      20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       6,   161,    41,   134,     1,     4,   130,    12,     5,    21,
      22,    23,    58,     7,    62,    30,   153,    11,   173,    67,
      68,    69,    39,   178,    13,    14,    80,    81,    82,    49,
     184,    86,    84,   167,   147,   187,   134,    50,    48,   160,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   134,    51,    87,    -4,    24,   134,    89,
      26,    48,    27,    29,    32,   134,    33,    42,    44,   -35,
     134,    52,    61,    63,    64,    34,   113,    83,    35,    84,
      66,    85,    53,    36,   104,   114,   115,     5,    54,    55,
      56,    57,   143,   116,   140,   158,   141,    78,    79,    80,
      81,    82,   144,   145,   168,   169,   174,   149,   150,   175,
     186,   180,   109,    88,   155,   181,   135,   146,   121,   122,
     123,   124,   136,   120,     0,     0,   164,   165,   166,     0,
       0,   125,   126,     0,     0,     0,   151,     0,   172,     0,
     154,     0,     0,     0,     0,   179,   127,   128,     0,   135,
     183,   121,   122,   123,   124,     0,     0,    13,    14,   129,
       5,     0,     0,     0,   125,   159,   135,     0,     0,     0,
       0,   135,   121,   122,   123,   124,     0,     0,   135,   127,
     128,     0,     0,   135,     0,   125,     0,     0,     0,     0,
      13,    14,   129,     5,     0,     0,     0,     0,     0,     0,
     127,   128,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,   129,     5,    70,    71,     0,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    70,
      71,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    70,    71,   107,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    70,    71,   118,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    70,    71,   171,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    90,    71,     0,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
       3,   152,    31,   119,    55,     0,   119,    44,    64,    12,
      13,    14,    42,    35,    44,    23,   142,    36,   169,    49,
      50,    51,    29,   174,    61,    62,    15,    16,    17,     6,
     181,    61,    31,   159,    33,   186,   152,    14,    41,   152,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,   169,    31,    63,    36,    30,   174,    66,
      31,    64,    28,    28,    38,   181,    40,     3,     3,    33,
     186,    48,    33,    32,    27,    49,   106,    29,    52,    31,
      28,    33,    59,    57,    53,    35,    32,    64,    65,    66,
      67,    68,    31,    27,   124,     3,   125,    13,    14,    15,
      16,    17,    31,    31,    37,    32,    32,   137,   138,     3,
      32,    58,    88,    64,   144,    46,   119,   132,    22,    23,
      24,    25,   120,   116,    -1,    -1,   156,   157,   158,    -1,
      -1,    35,    36,    -1,    -1,    -1,   139,    -1,   168,    -1,
     143,    -1,    -1,    -1,    -1,   175,    50,    51,    -1,   152,
     180,    22,    23,    24,    25,    -1,    -1,    61,    62,    63,
      64,    -1,    -1,    -1,    35,    36,   169,    -1,    -1,    -1,
      -1,   174,    22,    23,    24,    25,    -1,    -1,   181,    50,
      51,    -1,    -1,   186,    -1,    35,    -1,    -1,    -1,    -1,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    63,    64,     4,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     4,
       5,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     4,     5,    34,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     4,     5,    34,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,     4,     5,    34,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    32,     5,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    55,    70,   118,     0,    64,   117,    35,    71,    72,
      73,    36,    44,    61,    62,    74,    84,    85,    86,    88,
     119,   117,   117,   117,    30,   116,    31,    28,    91,    28,
      91,    75,    38,    40,    49,    52,    57,    83,    87,    83,
      89,   118,     3,    90,     3,    92,    78,    80,   117,     6,
      14,    31,    48,    59,    65,    66,    67,    68,   109,   111,
     117,    33,   109,    32,    27,    79,    28,   109,   109,   109,
       4,     5,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    29,    31,    33,   109,    91,    80,    83,
      32,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,    53,   112,   110,    34,    76,    79,
     109,   113,   115,   109,    35,    32,    27,   114,    34,    81,
     115,    22,    23,    24,    25,    35,    36,    50,    51,    63,
      84,    93,   102,   106,   111,   117,   114,   104,   105,   103,
     109,   118,    77,    31,    31,    31,   116,    33,   107,   109,
     109,   117,    82,   119,   117,   109,    96,   108,     3,    36,
      84,    93,    98,    94,   109,   109,   109,   119,    37,    32,
      97,    34,   109,    93,    32,     3,    99,    95,    93,   109,
      58,    46,   101,   109,    93,   100,    32,    93
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    69,    71,    70,    72,    73,    73,    73,    75,    76,
      77,    74,    78,    78,    79,    79,    80,    81,    81,    81,
      82,    82,    82,    83,    83,    83,    83,    83,    84,    85,
      85,    87,    86,    89,    88,    90,    88,    91,    91,    92,
      92,    93,    93,    94,    95,    93,    96,    97,    93,    98,
      99,   100,    93,   101,   101,   102,   102,   103,   102,   102,
     102,   104,   102,   105,   102,   107,   106,   108,   106,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   110,   109,   109,   109,   109,   112,   111,   113,   113,
     114,   114,   115,   116,   116,   117,   118,   119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     8,     2,     2,     2,     0,     0,     0,
       0,    14,     2,     0,     3,     0,     3,     2,     2,     0,
       2,     2,     0,     1,     1,     1,     1,     1,     2,     1,
       1,     0,     6,     0,     5,     0,     8,     2,     0,     2,
       0,     2,     5,     0,     0,     8,     0,     0,     7,     0,
       0,     0,    12,     2,     0,     1,     1,     0,     3,     2,
       1,     0,     3,     0,     3,     0,     4,     0,     7,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     1,
       1,     2,     3,     3,     1,     1,     3,     3,     1,     1,
       1,     0,     5,     3,     1,     3,     0,     5,     2,     0,
       3,     0,     1,     1,     0,     1,     0,     0
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
#line 198 "xxx.y" /* yacc.c:1646  */
    {
		objName = (char*)malloc(sizeof(char) * (strlen(ident) + 1));
		objName[0] = 0;
		strcpy(objName, ident);
		
		fgenJavaa("class %s {\n", ident, NULL, NULL, NULL, NULL);
		
		insertIntoHashTable(ident, _object, _none);
	}
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 206 "xxx.y" /* yacc.c:1646  */
    {
		genJavaa("}");
	}
#line 1673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 225 "xxx.y" /* yacc.c:1646  */
    {
		// insert the method symbol into the currently-scoped hash-table
		insertIntoHashTable(ident, _method, _none);
		// temporally save the method-item
		methItem = lookupInHashTable(ident);
		// check if this method is named "main" or not and set the flag of has-main
		if (strcmp(ident, "main") == 0)
			hasMainFlag = 1;
	}
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 233 "xxx.y" /* yacc.c:1646  */
    {
		inGlobal = 0;
	
		// set the return type to the currently-defining method
		setReturnType(&(methItem->methDef), (yyvsp[0].dataType));
		
		// generate the java assembly code of a method
		genJavaa("method public static ");
		if (strcmp(methItem->name, "main") == 0) {
			genJavaa("void main(java.lang.String[]");
		}
		else {
			fgenJavaa("%s %s(", toS((yyvsp[0].dataType)), methItem->name, NULL, NULL, NULL);
			int k;
			for (k = 0; k < methItem->methDef->argc; ++k) {
				if (k > 0)
					genJavaa(", ");
				genJavaa(toS(methItem->methDef->argTypeArr[k]));
			}
		}
		genJavaa(")\nmax_stack 15\nmax_locals 15\n{\n");
		
		if (strcmp(methItem->name, "main") == 0)
			flushJavaa();
	}
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 257 "xxx.y" /* yacc.c:1646  */
    {
		if (methItem->methDef->_ret_type == _none)
			genJavaa("return\n");
		else
			genJavaa("ireturn\n");
		genJavaa("}\n");
		
		// check the return type if hasn't do the checking yet
		checkReturnType();
		// nullify the pointer to the already-defined method
		methItem = NULL;
		
		inGlobal = 1;
	}
#line 1736 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 287 "xxx.y" /* yacc.c:1646  */
    {
		// add a new formal argument into the currently-defining method
		if (methItem != NULL)
			addFormalArgu(&(methItem->methDef), ident, (yyvsp[0].dataType));
		// also insert it into the currently-scoped hash-table
		insertIntoHashTable(ident, _variable, (yyvsp[0].dataType));
	}
#line 1748 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 312 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _char; }
#line 1754 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 313 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _string; }
#line 1760 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 314 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _int; }
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 315 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _boolean; }
#line 1772 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 316 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _float; }
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 332 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); }
#line 1784 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 332 "xxx.y" /* yacc.c:1646  */
    {
		Enode* e = pop_e();
		initNewId(assignee, _constant, (yyvsp[-3].dataType), (e == NULL) ? _none : e->_type);
		
		// store the constant value in the symbol-table
		if (e != NULL) {
			Item* item = lookupInHashTable(assignee);
			if (item != NULL)
				item->constantVal = e->_i;
			if (!inGlobal)
				genJavaa("pop\n");
		}
		
		free_e(e);
	}
#line 1804 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 351 "xxx.y" /* yacc.c:1646  */
    {
		setAssignee();
		if (inGlobal)
			inGlobalVarDclr = 1;
	}
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 355 "xxx.y" /* yacc.c:1646  */
    {
		Enode* e = pop_e();
		initNewId(assignee, _variable, _int, (e == NULL) ? _none : e->_type);
		
		// the global variable
		if (inGlobal) {
			fgenJavaa("field static %s %s\n", toS(_int), assignee, NULL, NULL, NULL);
			if (e != NULL) {
				if (inGlobal) {
					bufJavaa("putstatic "); bufJavaa(toS(_int)); bufJavaa(" "); bufJavaa(objName); bufJavaa("."); bufJavaa(assignee); bufJavaa("\n");
				}
				else
					fgenJavaa("putstatic %s %s.%s\n", toS(_int), objName, assignee, NULL, NULL);
			}
		}
		// the local variable
		else {
			if (e != NULL) {
				Item* item = lookupInHashTable(assignee);
				if (item != NULL)
					igenJavaa("istore ", item->localNum, "\n");
			}
		}
		
		free_e(e);
		inGlobalVarDclr = 0;
	}
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 382 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); }
#line 1852 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 382 "xxx.y" /* yacc.c:1646  */
    {
		// e.g. var arr: int[5]
		Enode* e = pop_e();
		initNewId(assignee, _array, (yyvsp[-4].dataType), (e == NULL) ? _int : e->_type);
		
		if (e != NULL) {
			Item* item = lookupInHashTable(assignee);
			fgenJavaa("newarray %s\n", toS(item->dataType), NULL, NULL, NULL, NULL);
			igenJavaa("astore ", item->localNum, "\n");
		}
		
		free_e(e);
		inGlobalVarDclr = 0;
	}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 400 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = (yyvsp[0].dataType); }
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 401 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _none; }
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 406 "xxx.y" /* yacc.c:1646  */
    { /* pop'd */ }
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 417 "xxx.y" /* yacc.c:1646  */
    { clear_e(); }
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 419 "xxx.y" /* yacc.c:1646  */
    {
		checkBooleanExpr("IF");
		
		push_b(loopLabelCounter);
		igenJavaa("ifeq Lfalse_", loopLabelCounter, "\n");
		++loopLabelCounter;
	}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 425 "xxx.y" /* yacc.c:1646  */
    {
		Bnode* bnd = peek_b();
		igenJavaa("goto Lendif_", bnd->lblNum, "\n");
		igenJavaa("Lfalse_", bnd->lblNum, ":\n");
	}
#line 1917 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 429 "xxx.y" /* yacc.c:1646  */
    {
		Bnode* bnd = pop_b();
		
		// this redundant goto-clause is generated for solving the "empty-else" error
		igenJavaa("goto Lendif_", bnd->lblNum, "\n");
		
		igenJavaa("Lendif_", bnd->lblNum, ":\n");
		free_b(bnd);
	}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 438 "xxx.y" /* yacc.c:1646  */
    {
		push_b(loopLabelCounter);
		igenJavaa("Lbegin_", loopLabelCounter, ":\n");
		++loopLabelCounter;
	}
#line 1941 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 442 "xxx.y" /* yacc.c:1646  */
    {
		checkBooleanExpr("WHILE");
		
		Bnode* bnd = peek_b();
		igenJavaa("ifeq Lexit_", bnd->lblNum, "\n");
	}
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 447 "xxx.y" /* yacc.c:1646  */
    {
		Bnode* bnd = pop_b();
		igenJavaa("goto Lbegin_", bnd->lblNum, "\n");
		igenJavaa("Lexit_", bnd->lblNum, ":\n");
		free_b(bnd);
	}
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 453 "xxx.y" /* yacc.c:1646  */
    {
		// push an iterator (of a for-loop) into the it-stack
		push_it(ident);
	}
#line 1972 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 456 "xxx.y" /* yacc.c:1646  */
    {
		Enode* e = pop_e();
		if (e == NULL)
			warn("No assigned value found in an assignment.");
		else {
			ItNode* itnd = peek_it();
			Item* item = lookupInHashTable(itnd->iterator);
			if (item) {
				if (item->dataType == _none)
					item->dataType = e->_type;
				else if (item->dataType != e->_type)
					fwarn("The types are NOT the same between LHS (%s) and RHS (%s) in an assignment.", toS(item->dataType), toS(e->_type), NULL, NULL, NULL);
				
				// if it is a variable (not a constant)
				if (item->itemType == _variable) {
					// a global variable
					if (item->isGlobalFlag == 1) {
						fgenJavaa("putstatic %s %s.%s\n", toS(item->dataType), objName, item->name, NULL, NULL);
						igenJavaa("Lbegin_", loopLabelCounter, ":\n");
						fgenJavaa("getstatic %s %s.%s\n", toS(item->dataType), objName, item->name, NULL, NULL);
					}
					// otherwise, a local variable
					else {
						igenJavaa("istore ", item->localNum, "\n");
						igenJavaa("Lbegin_", loopLabelCounter, ":\n");
						igenJavaa("iload ", item->localNum, "\n");
					}
				}
			}
		}
		free_e(e);
		
		push_b(loopLabelCounter);
		++loopLabelCounter;
	}
#line 2012 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 490 "xxx.y" /* yacc.c:1646  */
    {
		Enode* e = pop_e();
		rgenJavaa("ifle");
		free_e(e);
		
		Bnode* bnd = peek_b();
		igenJavaa("ifeq Lexit_", bnd->lblNum, "\n");
	}
#line 2025 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 497 "xxx.y" /* yacc.c:1646  */
    {
		ItNode* itnd = pop_it();
		Bnode* bnd = pop_b();
		
		// the implicit add-one operation applied on the iterator
		Item* item = lookupInHashTable(itnd->iterator);
		if (item) {
			// a global variable
			if (item->isGlobalFlag == 1)
				fgenJavaa("getstatic %s %s.%s\n", toS(item->dataType), objName, item->name, NULL, NULL);
			// otherwise, a local variable
			else
				igenJavaa("iload ", item->localNum, "\n");
		}
		genJavaa("ldc 1\niadd\n");
		if (item) {
			// a global variable
			if (item->isGlobalFlag == 1)
				fgenJavaa("putstatic %s %s.%s\n", toS(item->dataType), objName, item->name, NULL, NULL);
			// otherwise, a local variable
			else
				igenJavaa("istore ", item->localNum, "\n");
		}
		
		igenJavaa("goto Lbegin_", bnd->lblNum, "\n");
		igenJavaa("Lexit_", bnd->lblNum, ":\n");
		
		free_b(bnd);
		free_it(itnd);
	}
#line 2060 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 539 "xxx.y" /* yacc.c:1646  */
    { clear_e(); }
#line 2066 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 539 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); ugenJavaa(ident); }
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 540 "xxx.y" /* yacc.c:1646  */
    {
		returnFlag = 1; printFlag = 0; checkReturnType();
		genJavaa("ireturn\n");
	}
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 544 "xxx.y" /* yacc.c:1646  */
    {
		clear_e(); returnFlag = 1; printFlag = 0; checkReturnType();
		genJavaa("return\n");
	}
#line 2090 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 548 "xxx.y" /* yacc.c:1646  */
    {
		genJavaa("getstatic java.io.PrintStream java.lang.System.out\n");
	}
#line 2098 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 550 "xxx.y" /* yacc.c:1646  */
    {
		printFlag = 1; returnFlag = 0;
		Enode* e = pop_e();
		if (e != NULL) {
			genJavaa("invokevirtual void java.io.PrintStream.print(");
			if (e->_type == _int)
				genJavaa("int");
			else if (e->_type == _boolean)
				genJavaa("boolean");
			else
				genJavaa("java.lang.String");
			genJavaa(")\n");
		}
		free_e(e);
	}
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 565 "xxx.y" /* yacc.c:1646  */
    {
		genJavaa("getstatic java.io.PrintStream java.lang.System.out\n");
	}
#line 2126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 567 "xxx.y" /* yacc.c:1646  */
    {
		printFlag = 2; returnFlag = 0;
		Enode* e = pop_e();
		if (e != NULL) {
			genJavaa("invokevirtual void java.io.PrintStream.println(");
			if (e->_type == _int)
				genJavaa("int");
			else if (e->_type == _boolean)
				genJavaa("boolean");
			else
				genJavaa("java.lang.String");
			genJavaa(")\n");
		}
		free_e(e);
	}
#line 2146 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 586 "xxx.y" /* yacc.c:1646  */
    { setAssignee(); }
#line 2152 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 586 "xxx.y" /* yacc.c:1646  */
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
				
				// if it is a variable (not a constant)
				if (item->itemType == _variable) {
					// a global variable
					if (item->isGlobalFlag == 1)
						fgenJavaa("putstatic %s %s.%s\n", toS(item->dataType), objName, item->name, NULL, NULL);
					// otherwise, a local variable
					else
						igenJavaa("istore ", item->localNum, "\n");
				}
			}
		}
		free_e(e);
	}
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 611 "xxx.y" /* yacc.c:1646  */
    {
		Item* aItem = lookupInHashTable(ident);
		igenJavaa("aload ", aItem->localNum, "\n");
	}
#line 2191 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 614 "xxx.y" /* yacc.c:1646  */
    {
		genJavaa("iastore\n");
	}
#line 2199 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 623 "xxx.y" /* yacc.c:1646  */
    { doOp("+", 1, warn); if (!inGlobal) { genJavaa("iadd\n"); } else if (inGlobalVarDclr) { bufJavaa("iadd\n"); } }
#line 2205 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 624 "xxx.y" /* yacc.c:1646  */
    { doOp("-", 1, warn); if (!inGlobal) { genJavaa("isub\n"); } }
#line 2211 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 625 "xxx.y" /* yacc.c:1646  */
    { doOp("*", 1, warn); if (!inGlobal) { genJavaa("imul\n"); } }
#line 2217 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 626 "xxx.y" /* yacc.c:1646  */
    { doOp("/", 1, warn); if (!inGlobal) { genJavaa("idiv\n"); } }
#line 2223 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 627 "xxx.y" /* yacc.c:1646  */
    { doOp("%", 1, warn); if (!inGlobal) { genJavaa("irem\n"); } }
#line 2229 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 628 "xxx.y" /* yacc.c:1646  */
    { doOp("UMINUS", 0, warn); if (!inGlobal) { genJavaa("ineg\n"); } }
#line 2235 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 629 "xxx.y" /* yacc.c:1646  */
    { doOp("<", 1, warn); if (!inGlobal) { rgenJavaa("iflt"); } }
#line 2241 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 630 "xxx.y" /* yacc.c:1646  */
    { doOp("<=", 1, warn); if (!inGlobal) { rgenJavaa("ifle"); } }
#line 2247 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 631 "xxx.y" /* yacc.c:1646  */
    { doOp(">=", 1, warn); if (!inGlobal) { rgenJavaa("ifge"); } }
#line 2253 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 632 "xxx.y" /* yacc.c:1646  */
    { doOp(">", 1, warn); if (!inGlobal) { rgenJavaa("ifgt"); } }
#line 2259 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 633 "xxx.y" /* yacc.c:1646  */
    { push_e(_float, &((yyvsp[0].f))); }
#line 2265 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 634 "xxx.y" /* yacc.c:1646  */
    { push_e(_int, &((yyvsp[0].i))); if (!inGlobal) { igenJavaa("ldc ", (yyvsp[0].i), "\n"); } else if (inGlobalVarDclr) { ibufJavaa("ldc ", (yyvsp[0].i), "\n"); } }
#line 2271 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 636 "xxx.y" /* yacc.c:1646  */
    { doOp("!", 0, warn); if (!inGlobal) { genJavaa("iconst_1\nixor\n"); } }
#line 2277 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 637 "xxx.y" /* yacc.c:1646  */
    { doOp("||", 1, warn); if (!inGlobal) { genJavaa("ior\n"); } }
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 638 "xxx.y" /* yacc.c:1646  */
    { doOp("&&", 1, warn); if (!inGlobal) { genJavaa("iand\n"); } }
#line 2289 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 639 "xxx.y" /* yacc.c:1646  */
    { int t = 1; push_e(_boolean, &t); if (!inGlobal) { genJavaa("iconst_1\n"); } }
#line 2295 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 640 "xxx.y" /* yacc.c:1646  */
    { int f = 0; push_e(_boolean, &f); if (!inGlobal) { genJavaa("iconst_0\n"); } }
#line 2301 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 642 "xxx.y" /* yacc.c:1646  */
    { doOp("==", 1, warn); if (!inGlobal) { rgenJavaa("ifeq"); } }
#line 2307 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 643 "xxx.y" /* yacc.c:1646  */
    { doOp("!=", 1, warn); if (!inGlobal) { rgenJavaa("ifne"); } }
#line 2313 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 645 "xxx.y" /* yacc.c:1646  */
    { push_e(_char, &((yyvsp[0].c))); if (!inGlobal) { igenJavaa("ldc ", (yyvsp[0].c), "\n"); } }
#line 2319 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 647 "xxx.y" /* yacc.c:1646  */
    {
		char* s = (char*)malloc(sizeof(char) * (strlen((yyvsp[0].s)) + 1)); s[0] = 0;
		strcpy(s, (yyvsp[0].s));
		push_e(_string, &s);
		if (!inGlobal) { fgenJavaa("ldc \"%s\"\n", s, NULL, NULL, NULL, NULL); }
		free(s);
	}
#line 2331 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 655 "xxx.y" /* yacc.c:1646  */
    {
		// get the identifier stored in the currently-scoped hash-table
		Item* item = lookupInHashTable(ident);
		
		// push the data-type back into the expr-stack
		push_e((item == NULL) ? _none : item->dataType, NULL);
		
		// variable (or constant)
		if (item != NULL && !inGlobal) {
			// if this identifier is a constant, no need to check whether it is global or not, get the value from the symbol-table directly
			if (item->itemType == _constant)
				igenJavaa("ldc ", item->constantVal, "\n");
			
			// if this identifier is a variable
			else if (item->itemType == _variable) {
				// this identifier is a global variable
				if (item->isGlobalFlag == 1)
					fgenJavaa("getstatic %s %s.%s\n", toS(item->dataType), objName, item->name, NULL, NULL);
				// otherwise, a local variable
				else
					igenJavaa("iload ", item->localNum, "\n");
			}
		}
	}
#line 2360 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 679 "xxx.y" /* yacc.c:1646  */
    {
		Item* aItem = lookupInHashTable(ident);
		igenJavaa("aload ", aItem->localNum, "\n");
	}
#line 2369 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 682 "xxx.y" /* yacc.c:1646  */
    {
		genJavaa("iaload\n");
	}
#line 2377 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 688 "xxx.y" /* yacc.c:1646  */
    {
		Mnode* m_nd = pop_m();
		Item* mItem = NULL;
		if (m_nd != NULL && m_nd->name != NULL)
			mItem = lookupInHashTable(m_nd->name);
		// push an Enode according to the return type of this invocated function
		push_e((mItem == NULL || mItem->methDef == NULL) ? _none : mItem->methDef->_ret_type, NULL);
		free_m(m_nd);
	}
#line 2391 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 698 "xxx.y" /* yacc.c:1646  */
    {
		Item* aItem = lookupInHashTable(ident);
		if (aItem != NULL) {
			igenJavaa("aload ", aItem->localNum, "\n");
			genJavaa("arraylength\n");
		}
	}
#line 2403 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 709 "xxx.y" /* yacc.c:1646  */
    {
		Item* mItem = lookupInHashTable(ident);
		push_m(ident);
		// not found
		if (mItem == NULL)
			fwarn("The identifier \"%s\" does NOT exist.", ident, NULL, NULL, NULL, NULL);
		// found but the identifier is NOT a method
		else if (mItem->itemType != _method) {
			mItem = NULL;
			fwarn("The identifier \"%s\" is NOT a method.", ident, NULL, NULL, NULL, NULL);
		}
	}
#line 2420 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 720 "xxx.y" /* yacc.c:1646  */
    {
		Mnode* meth_nd = peek_m();
		Item* mItem = NULL;
		if (meth_nd != NULL && meth_nd->name != NULL)
			mItem = lookupInHashTable(meth_nd->name);
		if (mItem != NULL && mItem->itemType == _method) {
			// if the number of actual arguments are NOT enough according to the defined formal arguments
			if (meth_nd->argCounter < mItem->methDef->argc)
				fwarn("The argument(s) are NOT enough when invocating the method \"%s\".", mItem->name, NULL, NULL, NULL, NULL);
			
			fgenJavaa("invokestatic %s %s.%s(", toS(mItem->methDef->_ret_type), objName, mItem->name, NULL, NULL);
			int k;
			for (k = 0; k < mItem->methDef->argc; ++k) {
				if (k > 0)
					genJavaa(", ");
				genJavaa(toS(mItem->methDef->argTypeArr[k]));
			}
			genJavaa(")\n");
		}
	}
#line 2445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 756 "xxx.y" /* yacc.c:1646  */
    {
		Enode* nd = pop_e();
		Mnode* m_nd = peek_m();
		Item* mItem = NULL;
		if (m_nd != NULL && m_nd->name != NULL)
			mItem = lookupInHashTable(m_nd->name);
		// check this actual argument with the formal argument
		if (mItem != NULL) {
			int res = checkFormalArguType(mItem->methDef, (nd == NULL ? _none : nd->_type), m_nd->argCounter);
			if (res == -1)
				fwarn("Too much argument(s) when invocating the method \"%s\".", mItem->name, NULL, NULL, NULL, NULL);
			else if (res == 0)
				fwarn("Types are NOT matched when invocating the method \"%s\".", mItem->name, NULL, NULL, NULL, NULL);
			// count the number of actual arguments
			++(m_nd->argCounter);
		}
		free_e(nd);
	}
#line 2468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 778 "xxx.y" /* yacc.c:1646  */
    { checkReturnType(); }
#line 2474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 784 "xxx.y" /* yacc.c:1646  */
    {
		// store it in a global variable 'ident'
		if (ident != NULL)
			free(ident);
		ident = (char*)malloc(sizeof(char) * (strlen((yyvsp[0].s)) + 1));
		ident[0] = 0;
		strcpy(ident, (yyvsp[0].s));
	}
#line 2487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 796 "xxx.y" /* yacc.c:1646  */
    { appendHashTable(); }
#line 2493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 800 "xxx.y" /* yacc.c:1646  */
    { removeHashTable(); }
#line 2499 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2503 "y.tab.c" /* yacc.c:1646  */
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
#line 802 "xxx.y" /* yacc.c:1906  */


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
	// open the file pointer for outputting the java assembly code
	fout = fopen("xxx.jasm", "w");
	
	// start parsing
	yyparse();
	
	// close the file pointer
	fclose(fout);
	
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
		newNode->inGlobalFlag = 1;
	}
	// general case
	else {
		newNode->prev = htail;
		htail = newNode;
		newNode->inGlobalFlag = 0;
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
	
	// zero-fy the local-counter if the symbol-table comes back to the scale of object
	if (htail != NULL && htail == hhead)
		localCounter = 0;
	
	// free the Hnode pointer that just been removed
	free(p);
}

// insert an identifier into the hash-table for the current scope with optionally-passed item-type and data-type
int insertIntoHashTable(const char* name, ItemType itemType, DataType dataType) {
	// first, check if the htail (the latest hash-table) is NULL or not
	if (htail == NULL)
		warn("Syntax error. You cannot assign variables here.");
	
	// try to insert the symbol into the latest hash-table
	int insertionResult = insert(htail->table, name, htail->inGlobalFlag, localCounter);
	if ((itemType == _variable || itemType == _array) && htail->inGlobalFlag == 0)
		++localCounter;
	
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

// get the number of a local variable stored in the currently-scoped hash-table
int getLocalVarNoInHashTable(const char* name) {
	Item* item = lookupInHashTable(name);
	if (item == NULL)
		return -1;
	return item->localNum;
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
			else if (e == NULL || e->_type == _none)
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

// generate the java assembly code w/ a plain string
void genJavaa(const char* str) {
	fprintf(fout, "%s", str);
}

// generate the java assembly code w/ a formatted string ('f' stands for 'formatted')
void fgenJavaa(const char* str, const char* p0, const char* p1, const char* p2, const char* p3, const char* p4) {
	fprintf(fout, str, (p0 == NULL ? "" : p0), (p1 == NULL ? "" : p1), (p2 == NULL ? "" : p2), (p3 == NULL ? "" : p3), (p4 == NULL ? "" : p4));
}

// generate the java assembly code w/ an integer value ('i' stands for 'integer')
void igenJavaa(const char* pre, const int value, const char* post) {
	fprintf(fout, "%s%d%s", (pre == NULL ? "" : pre), value, (post == NULL ? "" : post));
}

// generate the java assembly code for a relational operation ('r' stands for 'relational')
void rgenJavaa(const char* reOp) {
	fprintf(fout, "isub\n%s L%d\niconst_0\ngoto L%d\nL%d:\niconst_1\nL%d:\n", reOp, labelCounter, labelCounter + 1, labelCounter, labelCounter + 1);
	labelCounter += 2;
}

// generate the java assembly code for a read-clause ('u' stands for 'user' input)
void ugenJavaa(const char* idName) {
	// append a new symbol-table for avoiding the issue of identifier duplication
	appendHashTable();
	
	// initialize two temporal variables: 'tmp' & 'total'
	initNewId("tmp", _variable, _int, _int);
	initNewId("total", _variable, _int, _int);
	Item* tmp = lookupInHashTable("tmp");
	Item* ttl = lookupInHashTable("total");
	
	// get the item of the to-be-assigned variable
	Item* id = lookupInHashTable(idName);
	
	// initialize 'total' to zero
	genJavaa("ldc 0\n");
	igenJavaa("istore ", ttl->localNum, "\n");
	
	// the beginning label of this read operation
	igenJavaa("Lread_begin_", readLabelCounter, ":\n");
	
	// read a byte of input data and store it into 'tmp'
	genJavaa("getstatic java.io.InputStream java.lang.System.in\n");
	genJavaa("invokevirtual int java.io.InputStream.read()\n");
	igenJavaa("istore ", tmp->localNum, "\n");
	
	// check if the input data is redundant (10) or not
	igenJavaa("iload ", tmp->localNum, "\n");
	genJavaa("ldc 10\n");
	genJavaa("isub\n");
	igenJavaa("ifeq Lread_begin_", readLabelCounter, "\n");
	
	// check if the read operation shall finish or not
	igenJavaa("iload ", tmp->localNum, "\n");
	genJavaa("ldc 13\n");
	genJavaa("isub\n");
	igenJavaa("ifeq Lread_exit_", readLabelCounter, "\n");
	
	// subtract 'tmp' (the value that just be read-in) by 48
	igenJavaa("iload ", tmp->localNum, "\n");
	genJavaa("ldc 48\n");
	genJavaa("isub\n");
	
	// multiply 'total' by 10
	igenJavaa("iload ", ttl->localNum, "\n");
	genJavaa("ldc 10\n");
	genJavaa("imul\n");
	
	// add 'total' by the subtracted 'tmp'
	genJavaa("iadd\n");
	igenJavaa("istore ", ttl->localNum, "\n");
	
	// go back to the beginning of this read operation
	igenJavaa("goto Lread_begin_", readLabelCounter, "\n");
	
	// the exit of this read operation
	igenJavaa("Lread_exit_", readLabelCounter, ":\n");
	
	// store the calculated input value back to the to-be-assigned variable
	igenJavaa("iload ", ttl->localNum, "\n");
	if (id->isGlobalFlag)
		fgenJavaa("putstatic %s %s.%s\n", toS(id->dataType), objName, id->name, NULL, NULL);
	else
		igenJavaa("istore ", id->localNum, "\n");
	
	// add the read-label-counter by 1
	++readLabelCounter;
	
	// remove this temporal symbol-table
	removeHashTable();
}

// buffer the java assembly code w/ a plain string
void bufJavaa(const char* str) {
	if (str != NULL) {
		if (jBuf == NULL) {
			jBuf = (char*)malloc(sizeof(char) * (strlen(str) + 1));
			strcpy(jBuf, str);
		}
		else {
			char* tmp = (char*)malloc(sizeof(char) * (strlen(jBuf) + 1));
			strcpy(tmp, jBuf);
			free(jBuf);
			jBuf = (char*)malloc(sizeof(char) * (strlen(tmp) + strlen(str) + 1));
			strcpy(jBuf, tmp);
			strcat(jBuf, str);
			free(tmp);
		}
	}
	printf("|%s|\n", jBuf);
}

// buffer the java assembly code w/ a formatted string ('f' stands for 'formatted')
void fbufJavaa(const char* str, const char* p0, const char* p1, const char* p2, const char* p3, const char* p4) {
	char* formatted = (char*)malloc(sizeof(char) * (
		(p0 == NULL ? 0 : strlen(p0)) +
		(p1 == NULL ? 0 : strlen(p1)) +
		(p2 == NULL ? 0 : strlen(p2)) +
		(p3 == NULL ? 0 : strlen(p3)) +
		(p4 == NULL ? 0 : strlen(p4)) + 1
	));
	formatted[0] = 0;
	sprintf(formatted, str, (p0 == NULL ? "" : p0), (p1 == NULL ? "" : p1), (p2 == NULL ? "" : p2), (p3 == NULL ? NULL : p3), (p4 == NULL ? NULL : p4));
	bufJavaa(formatted);
	free(formatted);
}

// buffer the java assembly code w/ an integer value ('i' stands for 'integer')
void ibufJavaa(const char* pre, const int value, const char* post) {
	char* formatted = (char*)malloc(sizeof(char) * (strlen(pre) + strlen(post) + 22));
	formatted[0] = 0;
	sprintf(formatted, "%s%d%s", (pre == NULL ? "" : pre), value, (post == NULL ? "" : post));
	bufJavaa(formatted);
	free(formatted);
}

// flush the buffered java assembly code
void flushJavaa() {
	if (jBuf == NULL)
		return;
	genJavaa(jBuf);
	free(jBuf);
	jBuf = NULL;
}
