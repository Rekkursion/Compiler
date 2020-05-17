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
	#include "tnode_stack.hpp"
	
	// a node of a hash-table
	typedef struct hnode {
		HashTable table;
		struct hnode* prev;
		struct hnode* next;
	}Hnode;
	
	// the linked-list of hash-tables for scoping
	Hnode* hhead = NULL;
	Hnode* htail = NULL;
	
	/* function definitions */
	
	// handle warnings
	int yywarning(const char*);
	
	// append a new hash-table when reaching a new scope
	void appendHashTable();
	// insert an identifier into the hash-table for the current scope
	int insertIntoHashTable(const char*);
	// search for a certain identifier in the latest hash-table
	Item* lookupInHashTable(const char*);
	
	// store the assignee (the identifier which is about to be assigned)
	void storeAssigneeFromIdent();
	
	// in a certain operation (UNARY or BINARY), check if type(s) of operand(s) are compatible with the operation or not
	int doOperation(Tnode*, char*, int, int);
	// insert a new variable/constant and do the initialization with the type checking
	int insertAndInitId(int, DataType);
	// insert a new array of some data type
	int insertArrayId(DataType);
	
	/* helper variables */
	
	// check if the current deriving numeric expression is an INT (or a FLOAT)
	int isIntFlag = 1;
	
	// temporally store the name of an identifier
	char* ident = NULL;
	
	// temporally store the name of a variable/constant that is about to be assigned
	char* assignee = NULL;

#line 116 "y.tab.c" /* yacc.c:339  */

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
    COMMA = 269,
    COLON = 270,
    PERIOD = 271,
    SEMICOLON = 272,
    OPEN_PAR = 273,
    CLOSE_PAR = 274,
    OPEN_SQB = 275,
    CLOSE_SQB = 276,
    OPEN_BRA = 277,
    CLOSE_BRA = 278,
    BOOLEAN = 279,
    BREAK = 280,
    CHAR = 281,
    CASE = 282,
    CLASS = 283,
    CONTINUE = 284,
    DEF = 285,
    DO = 286,
    ELSE = 287,
    EXIT = 288,
    FALSE = 289,
    FLOAT = 290,
    FOR = 291,
    IF = 292,
    INT = 293,
    NULLS = 294,
    OBJECT = 295,
    PRINT = 296,
    PRINTLN = 297,
    READ = 298,
    REPEAT = 299,
    RETURN = 300,
    STRING = 301,
    TO = 302,
    TRUE = 303,
    TYPE = 304,
    VAL = 305,
    VAR = 306,
    WHILE = 307,
    ID = 308,
    LITERAL_INTEGER = 309,
    LITERAL_FLOAT = 310,
    LITERAL_CHAR = 311,
    LITERAL_STRING = 312
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
#define COMMA 269
#define COLON 270
#define PERIOD 271
#define SEMICOLON 272
#define OPEN_PAR 273
#define CLOSE_PAR 274
#define OPEN_SQB 275
#define CLOSE_SQB 276
#define OPEN_BRA 277
#define CLOSE_BRA 278
#define BOOLEAN 279
#define BREAK 280
#define CHAR 281
#define CASE 282
#define CLASS 283
#define CONTINUE 284
#define DEF 285
#define DO 286
#define ELSE 287
#define EXIT 288
#define FALSE 289
#define FLOAT 290
#define FOR 291
#define IF 292
#define INT 293
#define NULLS 294
#define OBJECT 295
#define PRINT 296
#define PRINTLN 297
#define READ 298
#define REPEAT 299
#define RETURN 300
#define STRING 301
#define TO 302
#define TRUE 303
#define TYPE 304
#define VAL 305
#define VAR 306
#define WHILE 307
#define ID 308
#define LITERAL_INTEGER 309
#define LITERAL_FLOAT 310
#define LITERAL_CHAR 311
#define LITERAL_STRING 312

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 52 "xxx.y" /* yacc.c:355  */

	Tnode* tnode;
	DataType dataType;

#line 275 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 292 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   237

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  107

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   312

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
      60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    86,    86,    95,    96,    97,   102,   103,   104,   105,
     106,   111,   116,   117,   122,   122,   127,   127,   132,   133,
     138,   139,   144,   145,   150,   155,   156,   157,   162,   162,
     167,   168,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   186,   187,   188,   189,   190,   192,
     193,   195,   197,   199,   270,   300,   304,   305,   310,   311,
     316,   317,   322
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'='", "OR", "AND", "NOT", "LT", "LE",
  "EQ", "GE", "GT", "NE", "'+'", "'-'", "'*'", "'/'", "MOD", "UMINUS",
  "COMMA", "COLON", "PERIOD", "SEMICOLON", "OPEN_PAR", "CLOSE_PAR",
  "OPEN_SQB", "CLOSE_SQB", "OPEN_BRA", "CLOSE_BRA", "BOOLEAN", "BREAK",
  "CHAR", "CASE", "CLASS", "CONTINUE", "DEF", "DO", "ELSE", "EXIT",
  "FALSE", "FLOAT", "FOR", "IF", "INT", "NULLS", "OBJECT", "PRINT",
  "PRINTLN", "READ", "REPEAT", "RETURN", "STRING", "TO", "TRUE", "TYPE",
  "VAL", "VAR", "WHILE", "ID", "LITERAL_INTEGER", "LITERAL_FLOAT",
  "LITERAL_CHAR", "LITERAL_STRING", "$accept", "program", "object_body",
  "data_type", "declaration", "dclr", "val_dclr", "$@1", "var_dclr", "$@2",
  "var_dclr_postfix", "opt_type_dclr", "opt_init", "statement", "stmt",
  "assignment", "$@3", "assignment_postfix", "expr", "func_invoc",
  "actual_argus", "opt_semi", "identifier", YY_NULLPTR
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
     310,   311,   312
};
# endif

#define YYPACT_NINF -36

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-36)))

#define YYTABLE_NINF -29

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -24,   -35,    24,   -36,     1,   -36,   -36,    41,    99,    99,
      99,   -36,   -36,   -36,   -35,   -35,   -36,   -36,   -36,   -36,
     -36,     4,   -36,   -36,   -36,     4,   -36,   196,   -36,    26,
     220,     5,   -36,   178,   -36,   -36,   -36,   -36,   -36,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    59,    99,     2,   -36,    32,    33,   209,   220,
      93,    93,    93,    93,    93,    93,     3,     3,   -36,   -36,
     -36,   -36,   196,    -2,    -1,    99,    99,   -36,    19,    43,
      19,   -36,    51,    99,   -36,   -36,   196,   119,   -36,   -36,
     -36,   -36,   -36,   -36,    99,    31,    99,   -36,   196,    54,
     196,    99,   196,    99,   158,   196,   -36
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    62,     0,     1,     5,     0,     0,     0,
       0,     2,    48,    47,     0,     0,    43,    42,    51,    52,
       4,    61,    12,    13,     3,    61,    25,    26,    27,    54,
      44,    54,    37,     0,    14,    16,    60,    11,    24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    55,    21,    21,    45,    46,
      38,    39,    49,    40,    41,    50,    32,    33,    34,    35,
      36,    57,    59,     0,     0,     0,     0,    29,     0,     0,
       0,    17,    23,     0,    56,    53,    30,     0,     9,     6,
      10,     8,     7,    20,     0,    20,     0,    18,    58,     0,
      15,     0,    22,     0,     0,    31,    19
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -36,   -36,   -36,   -22,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,     6,   -36,   -36,   -36,   -36,   -36,   -36,    -8,   -36,
     -36,    35,    70
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,    93,    20,    21,    22,    56,    23,    57,
      81,    79,    97,    24,    25,    26,    54,    77,    27,    28,
      73,    37,    31
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      30,    32,    33,    39,    40,    75,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    83,    49,    50,
      51,     1,    84,     3,     5,    85,    36,    76,     6,   -28,
      53,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    72,    74,    94,     8,    88,    52,
      89,    53,    78,    80,    96,     9,   101,   103,    95,    90,
      38,     0,    91,    82,    10,     8,     0,    86,    87,    11,
      92,     4,     0,     9,     0,    98,     0,    29,     0,     0,
      12,     0,    10,    71,    34,    35,   100,     0,   102,     0,
       0,     0,     0,   104,    13,   105,    14,    15,    12,     3,
      16,    17,    18,    19,     0,     8,    47,    48,    49,    50,
      51,     0,    13,     9,     0,     0,     0,     3,    16,    17,
      18,    19,    10,    39,    40,     0,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,     0,    12,     0,
       0,     0,     0,     0,     0,    99,     0,     0,     0,     0,
       0,     0,    13,     0,     0,     0,     0,     3,    16,    17,
      18,    19,    39,    40,     0,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,     0,     0,     0,     0,
       0,     0,    39,    40,   106,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,     0,     0,     0,     0,
      39,    40,    55,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    40,     0,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51
};

static const yytype_int8 yycheck[] =
{
       8,     9,    10,     4,     5,     3,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    19,    15,    16,
      17,    45,    24,    58,     0,    26,    22,    25,    27,     3,
      25,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,     3,     6,    29,    23,
      31,    25,    20,    20,     3,    14,    25,     3,    80,    40,
      25,    -1,    43,    57,    23,     6,    -1,    75,    76,    28,
      51,     1,    -1,    14,    -1,    83,    -1,     7,    -1,    -1,
      39,    -1,    23,    24,    14,    15,    94,    -1,    96,    -1,
      -1,    -1,    -1,   101,    53,   103,    55,    56,    39,    58,
      59,    60,    61,    62,    -1,     6,    13,    14,    15,    16,
      17,    -1,    53,    14,    -1,    -1,    -1,    58,    59,    60,
      61,    62,    23,     4,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    58,    59,    60,
      61,    62,     4,     5,    -1,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,    26,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    -1,    -1,    -1,    -1,
       4,     5,    24,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     5,    -1,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,    64,    58,    85,     0,    27,    65,     6,    14,
      23,    28,    39,    53,    55,    56,    59,    60,    61,    62,
      67,    68,    69,    71,    76,    77,    78,    81,    82,    85,
      81,    85,    81,    81,    85,    85,    22,    84,    84,     4,
       5,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    23,    25,    79,    24,    70,    72,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    24,    81,    83,    81,     3,    25,    80,    20,    74,
      20,    73,    74,    19,    24,    26,    81,    81,    29,    31,
      40,    43,    51,    66,     3,    66,     3,    75,    81,    26,
      81,    25,    81,     3,    81,    81,    26
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    63,    64,    65,    65,    65,    66,    66,    66,    66,
      66,    67,    68,    68,    70,    69,    72,    71,    73,    73,
      74,    74,    75,    75,    76,    77,    77,    77,    79,    78,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    81,    81,    81,    81,
      81,    81,    81,    81,    81,    81,    82,    82,    83,    83,
      84,    84,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     2,     2,     0,     1,     1,     1,     1,
       1,     2,     1,     1,     0,     6,     0,     4,     2,     5,
       2,     0,     2,     0,     2,     1,     1,     1,     0,     3,
       2,     5,     3,     3,     3,     3,     3,     2,     3,     3,
       3,     3,     1,     1,     2,     3,     3,     1,     1,     3,
       3,     1,     1,     4,     1,     3,     4,     3,     3,     1,
       1,     0,     1
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
#line 86 "xxx.y" /* yacc.c:1646  */
    {
		// insert object's name into hash-table
		insertIntoHashTable(ident);
		clear_stk(1);
	}
#line 1482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 102 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _char; }
#line 1488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 103 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _string; }
#line 1494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 104 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _int; }
#line 1500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 105 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _boolean; }
#line 1506 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 106 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _float; }
#line 1512 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 122 "xxx.y" /* yacc.c:1646  */
    { storeAssigneeFromIdent(); }
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 122 "xxx.y" /* yacc.c:1646  */
    { insertAndInitId(1, (yyvsp[-2].dataType)); }
#line 1524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 127 "xxx.y" /* yacc.c:1646  */
    { storeAssigneeFromIdent(); }
#line 1530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 132 "xxx.y" /* yacc.c:1646  */
    { insertAndInitId(0, (yyvsp[-1].dataType)); }
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 133 "xxx.y" /* yacc.c:1646  */
    { insertArrayId((yyvsp[-3].dataType)); }
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 138 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = (yyvsp[0].dataType); }
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 139 "xxx.y" /* yacc.c:1646  */
    { (yyval.dataType) = _none; }
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 162 "xxx.y" /* yacc.c:1646  */
    { storeAssigneeFromIdent(); }
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 167 "xxx.y" /* yacc.c:1646  */
    { /* TODO */ }
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 168 "xxx.y" /* yacc.c:1646  */
    { /* TODO */ }
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 173 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "+", 1, 1); }
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 174 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "-", 1, 1); }
#line 1584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 175 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "*", 1, 1); }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 176 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "/", 1, 1); }
#line 1596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 177 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "%", 1, 0); }
#line 1602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 178 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "UMINUS", 0, 1); }
#line 1608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 179 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "<", 1, 1); }
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 180 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "<=", 1, 1); }
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 181 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), ">=", 1, 1); }
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 182 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), ">", 1, 1); }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 183 "xxx.y" /* yacc.c:1646  */
    { push_stk((yyvsp[0].tnode)); }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 184 "xxx.y" /* yacc.c:1646  */
    { push_stk((yyvsp[0].tnode)); }
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 186 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "!", 0, 0); }
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 187 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "||", 1, 0); }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 188 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "&&", 1, 0); }
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 189 "xxx.y" /* yacc.c:1646  */
    { (yyval.tnode)->_type = _boolean; (yyval.tnode)->_b = 1; push_stk((yyval.tnode)); }
#line 1668 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 190 "xxx.y" /* yacc.c:1646  */
    { (yyval.tnode)->_type = _boolean; (yyval.tnode)->_b = 0; push_stk((yyval.tnode)); }
#line 1674 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 192 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "==", 1, 0); }
#line 1680 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 193 "xxx.y" /* yacc.c:1646  */
    { doOperation((yyval.tnode), "!=", 1, 0); }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 195 "xxx.y" /* yacc.c:1646  */
    { push_stk((yyvsp[0].tnode)); }
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 197 "xxx.y" /* yacc.c:1646  */
    { push_stk((yyvsp[0].tnode)); }
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 199 "xxx.y" /* yacc.c:1646  */
    {
		// search for the identifier
		Item* item = lookupInHashTable(ident);
		
		// no identifier found -> symbol error
		if (item == NULL)
			yywarning("Symbol Error. No such array identifier found.");
		
		// normal case
		else {
			// this item is a single value, i.e., a variable or a constant -> symbol error
			if (item->itemType == _variable || item->itemType == _constant)
				yywarning("This identifier is NOT an array.");
			
			// is an array
			else if (item->itemType == _array) {
				// no value assigned -> symbol error
				if (item->a_value == NULL)
					yywarning("Symbol Error. The array has NOT been initialized.");
				// has value assigned -> create a new Tnode for the indexed data and push it into the stack
				else {
					// pop a Tnode for attaining the index of the array
					Tnode* ndForIdx = pop_stk();
					int idx = 0;
					
					// the index expression yields NON-integer value -> type error
					if (ndForIdx->_type != _int)
						yywarning("Type Error. The index of an array must be an INTEGER.");
					
					// the index expression is exactly an integer value
					else {
						// get the index
						idx = ndForIdx->_i;
						
						// if the index is out of range -> index error
						if (idx < 0 || idx >= item->a_value->asize)
							yywarning("Index Error. The index of the array is out of range.");
						
						// the index is NOT out of range
						else {
							// if the position of this array has NOT been assigned by any value -> value error
							if (item->a_value->hasAssigned[idx] == 0)
								yywarning("Value Error. The position of the array has NOT been assigned by any value.");
							
							// create a new Tnode for attaining the indexed data
							else {
								Tnode* newNd = (Tnode*)malloc(sizeof(Tnode));
								newNd->_s = NULL;
								newNd->_type = item->a_value->_atype;
								switch (newNd->_type) {
									case _char: newNd->_c = item->a_value->_ac[idx]; break;
									case _string:
										newNd->_s = (char*)malloc(sizeof(char*) * (strlen(item->a_value->_as[idx]) + 1));
										strcpy(newNd->_s, item->a_value->_as[idx]);
										break;
									case _int: newNd->_i = item->a_value->_ai[idx]; break;
									case _boolean: newNd->_b = item->a_value->_ab[idx]; break;
									case _float: newNd->_f = item->a_value->_af[idx]; break;
								}
								push_stk(newNd);
							}
						}
					}
				}
			}
			
			// not variable/constant nor array -> symbol error
			else
				yywarning("This identifier is NOT a variable/constant nor an array.");
		}
	}
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 270 "xxx.y" /* yacc.c:1646  */
    {
		// search for the identifier
		Item* item = lookupInHashTable(ident);
		
		// no identifier found -> symbol error
		if (item == NULL)
			yywarning("Symbol Error. No such variable/constant found.");
		
		// normal case
		else {
			// this item is a single value, i.e., a variable or a constant
			if (item->itemType == _variable || item->itemType == _constant) {
				// no value assigned -> symbol error
				if (item->value == NULL)
					yywarning("Symbol Error. The variable/constant has NOT been initialized.");
				// has value assigned -> push the Tnode into the stack
				else
					push_stk(item->value);
			}
			
			// is an array -> symbol error
			else if (item->itemType == _array)
				yywarning("Symbol Error. You cannot use array without explicitly telling the index.");
			
			// not variable/constant nor array -> symbol error
			else
				yywarning("This identifier is NOT a variable/constant nor an array.");
		}
	}
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 322 "xxx.y" /* yacc.c:1646  */
    {
		if (ident != NULL)
			free(ident);
		ident = (char*)malloc(sizeof(char) * (strlen((yyvsp[0].tnode)->_s) + 1));
		ident[0] = 0;
		strcpy(ident, (yyvsp[0].tnode)->_s);
	}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1824 "y.tab.c" /* yacc.c:1646  */
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
#line 331 "xxx.y" /* yacc.c:1906  */


// error happens -> tell the user and exit
/*void yyerror(const char* msg) {
	extern int yylineno;
	fprintf(stderr, "line %d: %s\n", yylineno, msg);
}*/

// warning happens -> just tell the user
int yywarning(const char* msg) {
	extern int yylineno;
	fprintf(stderr, "line %d: %s\n", yylineno, msg);
	return 0;
}

// the main function
int main() {
	// initialize the first-scoped hash-table
	appendHashTable();
	
	yyparse();
	return 0;
}

// append a new hash-table when reaching a new scope
void appendHashTable() {
	// create a new hnode for storing the latest hash-table
	Hnode* newNode = (Hnode*)malloc(sizeof(Hnode));
	newNode->table = create();
	newNode->next = NULL;
	newNode->prev = NULL;

	// the first node
	if (hhead == NULL) {
		hhead = newNode;
		htail  = hhead;
	}
	// general case
	else {
		htail->next = newNode;
		newNode->prev = htail;
		htail = htail->next;
	}
}

// insert an identifier into the hash-table for the current scope
int insertIntoHashTable(const char* name) {
	// first, check if the htail (the latest hash-table) is NULL or not
	if (htail == NULL)
		yywarning("Syntax error. You cannot assign variables here.");
	
	// insert into the latest hash-table
	return insert(htail->table, name);
}

// search for a certain identifier in the latest hash-table
Item* lookupInHashTable(const char* name) {
	return lookup(htail->table, name);
}

// in a certain unary operation, check if the type of the operand are compatible with this operation or not
int doOperation(Tnode* res, char* operationName, int isBinaryOperation, int isNumericOperation) {
	// first of all, nullify the string field of the result Tnode
	res->_s = NULL;
	
	// get an operand from the stack
	Tnode* rhs = pop_stk();
	Tnode* lhs = NULL;
	
	// if it's a binary operation, get another operand from the stack
	if (isBinaryOperation)
		lhs = pop_stk();
	
	// if the operand is NOT enough in the stack
	if (rhs == NULL || (isBinaryOperation && lhs == NULL)) {
		char msg[20002];
		sprintf(msg, "Operation error. The number of operand(s) in the operation \"%s\" is NOT enough.", operationName);
		yywarning(msg);
		return 0;
	}
	
	// the flag to check if the rhs is compatible or not
	int compatible = 0;
	
	// the true data type
	DataType trueDataType = _int;
	DataType resDataType = _int;
	
	// for BINARY numeric operations, check the loosen compatibility, i.e., ok for an INT and a FLOAT but a warning still is a must
	if (isBinaryOperation && isNumericOperation &&
		(lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float) &&
		lhs->_type != rhs->_type) {
		char msg[20002];
		sprintf(msg, "Type warning. The operands of the numeric operation \"%s\" is NOT the same type.", operationName);
		yywarning(msg);
	}
	
	// BINARY numeric: ADD
	if (!strcmp(operationName, "+")) {
		compatible = ((lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float));
		trueDataType = ((lhs->_type == _int && rhs->_type == _int) ? _int : _float);
		if (trueDataType == _int)
			res->_i = lhs->_i + rhs->_i;
		else
			res->_f = (lhs->_type == _int ? ((double) lhs->_i) : lhs->_f) + (rhs->_type == _int ? ((double) rhs->_i) : rhs->_f);
		res->_type = trueDataType;
	}
	// BINARY numeric: MINUS
	else if (!strcmp(operationName, "-")) {
		compatible = ((lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float));
		trueDataType = ((lhs->_type == _int && rhs->_type == _int) ? _int : _float);
		if (trueDataType == _int)
			res->_i = lhs->_i - rhs->_i;
		else
			res->_f = (lhs->_type == _int ? ((double) lhs->_i) : lhs->_f) - (rhs->_type == _int ? ((double) rhs->_i) : rhs->_f);
		res->_type = trueDataType;
	}
	// BINARY numeric: MULTIPLY
	else if (!strcmp(operationName, "*")) {
		compatible = ((lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float));
		trueDataType = ((lhs->_type == _int && rhs->_type == _int) ? _int : _float);
		if (trueDataType == _int)
			res->_i = lhs->_i * rhs->_i;
		else
			res->_f = (lhs->_type == _int ? ((double) lhs->_i) : lhs->_f) * (rhs->_type == _int ? ((double) rhs->_i) : rhs->_f);
		res->_type = trueDataType;
	}
	// BINARY numeric: DIVIDE
	else if (!strcmp(operationName, "/")) {
		compatible = ((lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float));
		double rhsValue = (rhs->_type == _int ? ((double) rhs->_i) : rhs->_f);
		if (rhsValue == 0) {
			if (compatible)
				yywarning("Divide by zero in a DIVISION operation.");
			rhsValue += 1E-10;
		}
		if (lhs->_type == _int && rhs->_type == _int) {
			trueDataType = _int;
			res->_i = (int) (lhs->_i / rhsValue);
			res->_type = _int;
		}
		else {
			trueDataType = _float;
			res->_f = (lhs->_type == _int ? ((double) lhs->_i) : lhs->_f) / rhsValue;
			res->_type = _float;
		}
	}
	// BINARY int: MOD
	else if (!strcmp(operationName, "%")) {
		compatible = (lhs->_type == _int && rhs->_type == _int);
		trueDataType = _int;
		int lhsValue = (lhs->_type == _int ? lhs->_i : ((int) lhs->_f));
		int rhsValue = (rhs->_type == _int ? rhs->_i : ((int) rhs->_f));
		if (compatible && rhsValue == 0)
			yywarning("Divide by zero in a MOD operation.");
		if (rhsValue)
			res->_i = lhsValue % rhsValue;
		res->_type = _int;
	}
	// BINARY numeric: LT
	else if (!strcmp(operationName, "<")) {
		compatible = ((lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float));
		trueDataType = _numeric;
		res->_b = ((lhs->_type == _int ? lhs->_i : lhs->_f) < (rhs->_type == _int ? rhs->_i : rhs->_f));
		res->_type = _boolean;
	}
	// BINARY numeric: LE
	else if (!strcmp(operationName, "<=")) {
		compatible = ((lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float));
		trueDataType = _numeric;
		res->_b = ((lhs->_type == _int ? lhs->_i : lhs->_f) <= (rhs->_type == _int ? rhs->_i : rhs->_f));
		res->_type = _boolean;
	}
	// BINARY numeric: GE
	else if (!strcmp(operationName, ">=")) {
		compatible = ((lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float));
		trueDataType = _numeric;
		res->_b = ((lhs->_type == _int ? lhs->_i : lhs->_f) >= (rhs->_type == _int ? rhs->_i : rhs->_f));
		res->_type = _boolean;
	}
	// BINARY numeric: GT
	else if (!strcmp(operationName, ">")) {
		compatible = ((lhs->_type == _int || lhs->_type == _float) && (rhs->_type == _int || rhs->_type == _float));
		trueDataType = _numeric;
		res->_b = ((lhs->_type == _int ? lhs->_i : lhs->_f) > (rhs->_type == _int ? rhs->_i : rhs->_f));
		res->_type = _boolean;
	}
	// BINARY general: EQ or NE ("==" or "!=")
	else if (!strcmp(operationName, "==") || !strcmp(operationName, "!=")) {
		compatible = (lhs->_type == rhs->_type);
		switch (lhs->_type) {
			// BOOLEAN
			case _boolean:
				if (compatible == 0)
					res->_b = 0;
				else
					res->_b = (operationName[0] == '=' ? (lhs->_b == rhs->_b) : (lhs->_b != rhs->_b));
				break;
			
			// CHAR
			case _char:
				if (compatible == 0)
					res->_b = 0;
				else
					res->_b = (operationName[0] == '=' ? (lhs->_c == rhs->_c) : (lhs->_c != rhs->_c));
				break;
			
			// STRING
			case _string:
				if (compatible == 0 || lhs->_s == NULL || rhs->_s == NULL)
					res->_b = 0;
				else
					res->_b = (operationName[0] == '=' ? (!strcmp(lhs->_s, rhs->_s)) : (strcmp(lhs->_s, rhs->_s) != 0));
				break;
			
			// numeric, i.e., INT or FLOAT
			default:
				if (lhs->_type == _int) {
					// INT and INT
					if (rhs->_type == _int)
						res->_b = (operationName[0] == '=' ? (lhs->_i == rhs->_i) : (lhs->_i != rhs->_i));
					// INT and FLOAT
					else if (rhs->_type == _float)
						res->_b = (operationName[0] == '=' ? (lhs->_i == rhs->_f) : (lhs->_i != rhs->_f));
					// INT and non-numeric
					else
						res->_b = 0;
				}
				else {
					// FLOAT and INT
					if (rhs->_type == _int)
						res->_b = (operationName[0] == '=' ? (lhs->_f == rhs->_i) : (lhs->_f != rhs->_i));
					// FLOAT and FLOAT
					else if (rhs->_type == _float)
						res->_b = (operationName[0] == '=' ? (lhs->_f == rhs->_f) : (lhs->_f != rhs->_f));
					// FLOAT and non-numeric
					else
						res->_b = 0;
				}
		}
		res->_type = _boolean;
	}
	// UNARY numeric: UMINUS
	else if (!strcmp(operationName, "UMINUS")) {
		compatible = (rhs->_type == _int || rhs->_type == _float);
		trueDataType = (rhs->_type == _int ? _int : _float);
		if (rhs->_type == _int)
			res->_i = (-(rhs->_i));
		else
			res->_f = (-(rhs->_f));
		res->_type = trueDataType;
	}
	// UNARY boolean: NOT
	else if (!strcmp(operationName, "!")) {
		compatible = (rhs->_type == _boolean);
		trueDataType = _boolean;
		res->_b = (!(rhs->_b));
		res->_type = _boolean;
	}
	// BINARY boolean: AND
	else if (!strcmp(operationName, "&&")) {
		compatible = (lhs->_type == _boolean && rhs->_type == _boolean);
		trueDataType = _boolean;
		res->_b = (lhs->_b && rhs->_b);
		res->_type = _boolean;
	}
	// BINARY boolean: OR
	else if (!strcmp(operationName, "||")) {
		compatible = (lhs->_type == _boolean && rhs->_type == _boolean);
		trueDataType = _boolean;
		res->_b = (lhs->_b || rhs->_b);
		res->_type = _boolean;
	}
	
	// push the result back to the stack
	push_stk(res);
	
	// loose the compatibility if it's a numeric operation and its result is a numeric value as well
	if (isNumericOperation && (trueDataType == _int || trueDataType == _float))
		trueDataType = _numeric;
	
	// if it's NOT compatible, build the error message and print it out
	if (compatible == 0) {
		char msg[20002];
		// the operation is EQ or NE
		if (!strcmp(operationName, "==") || !strcmp(operationName, "!="))
			sprintf(msg, "Type warning. The both sides of \"%s\" operation should be the SAME type or the result could be unexpected.",
				operationName);
		// not EQ nor NE
		else {
			// build the error message for this BINARY operation
			if (isBinaryOperation)
				sprintf(msg, "Type error. The BINARY operation \"%s\" is %s \'%s\' operation, but the operands are \'%s\' and \'%s\'.",
					operationName,
					(getLiteralDataTypeName(trueDataType)[0] == 'i' ? "an" : "a"),
					getLiteralDataTypeName(trueDataType),
					getLiteralDataTypeName(lhs->_type),
					getLiteralDataTypeName(rhs->_type));
			// the case of a UNARY operation
			else
				sprintf(msg, "Type error. The UNARY operation \"%s\" is %s \'%s\' operation, but the operand is \'%s\'.",
					operationName,
					(getLiteralDataTypeName(trueDataType)[0] == 'i' ? "an" : "a"),
					getLiteralDataTypeName(trueDataType),
					getLiteralDataTypeName(rhs->_type));
		}
		// print out the warning
		yywarning(msg);
	}
	
	// return that if the rhs is compatible or not
	return compatible;
}

// store the assignee (the identifier which is about to be assigned)
void storeAssigneeFromIdent() {
	// release the memory allocated before
	if (assignee != NULL)
		free(assignee);
	
	// nullify the assignee
	assignee = NULL;
	
	// re-assign the assignee from the temporally stored ident
	if (ident != NULL) {
		assignee = (char*)malloc(sizeof(char) * (strlen(ident) + 1));
		strcpy(assignee, ident);
	}
}

// insert a new variable/constant and do the initialization with the type checking
int insertAndInitId(int isConstant, DataType declaredType) {
	// get the assigned value (an expression) if any
	Tnode* rhs = pop_stk();

	// search for the identifier by the temporally stored assignee
	int insertionRes = insertIntoHashTable(assignee);
	
	// if this assignee has already been declared in the same (current) scope
	if (insertionRes == -1) {
		char msg[2002];
		sprintf(msg, "Symbol Error. The %s \'%s\' has already been declared in the same scope.",
			(isConstant ? "constant" : "variable"), assignee);
		yywarning(msg);
		return 0;
	}
	
	// get the item just inserted
	Item* item = lookupInHashTable(assignee);
	
	// set the boolean flag that shows this assignee is a constant or a variable
	if (isConstant)
		item->itemType = _constant;
	else
		item->itemType = _variable;
	
	// allocate a new memory space of a Tnode
	item->value = (Tnode*)malloc(sizeof(Tnode));
	item->value->_s = NULL;
	
	// set the type of this item
	item->value->_type = (declaredType == _none ? (rhs != NULL ? rhs->_type : _none) : declaredType);
	
	// if there's no assigned value, return directly
	if (rhs == NULL)
		return 1;
	
	// if the declared data type is NOT matched with the one of the assigned value -> type error
	if (declaredType != _none && declaredType != rhs->_type) {
		char msg[2002];
		sprintf(msg, "Type Error. The %s \'%s\' is declared as the type of \'%s\', but the assigned value is the type of \'%s\'.",
			(isConstant ? "constant" : "variable"),
			assignee,
			getLiteralDataTypeName(declaredType),
			getLiteralDataTypeName(rhs->_type));
		yywarning(msg);
		return 0;
	}
	
	// set its value according to the data type
	switch(item->value->_type) {
		case _char: item->value->_c = rhs->_c; break;
		case _string:
			item->value->_s = (char*)malloc(sizeof(char) * (strlen(rhs->_s) + 1));
			strcpy(item->value->_s, rhs->_s);
			break;
		case _int: item->value->_i = rhs->_i; break;
		case _boolean: item->value->_b = rhs->_b; break;
		case _float: item->value->_f = rhs->_f; break;
	}
	
	// return with the flag of success
	return 1;
}

// insert a new array of some data type
int insertArrayId(DataType declaredType) {
	// search for the identifier by the temporally stored assignee
	int insertionRes = insertIntoHashTable(assignee);
	
	// if this assignee has already been declared in the same (current) scope
	if (insertionRes == -1) {
		char msg[2002];
		sprintf(msg, "Symbol Error. The identifier \'%s\' has already been declared in the same scope.", assignee);
		yywarning(msg);
		return 0;
	}
	
	// get the item just inserted
	Item* item = lookupInHashTable(assignee);
	
	// set the item-type
	item->itemType = _array;
	
	// get the Tnode for determining the size of this array
	Tnode* ndForSize = pop_stk();
	
	// if there's no declared size -> syntax error
	if (ndForSize == NULL) {
		yywarning("Syntax Error. The size of an array must be explicitly declared.");
		return 0;
	}
	
	// the size of this array
	int size = 1;
	
	// if the type of the Tnode-for-size is NOT an INT -> type error
	if (ndForSize->_type != _int) {
		yywarning("Type Error. The size of an array must be an INTEGER.");
		return 0;
	}
	
	// determine the size of this array
	else
		size = ndForSize->_i;
	
	// build a new Anode
	Anode* anode = (Anode*)malloc(sizeof(Anode));
	anode->_ac = NULL;
	anode->_as = NULL;
	anode->_ai = NULL;
	anode->_ab = NULL;
	anode->_af = NULL;
	
	// set the size into the new Anode
	anode->asize = size;
	
	// set the type of the new Anode
	anode->_atype = declaredType;
	
	// allocate the memory for the array according to the declared type
	switch (declaredType) {
		case _char: anode->_ac = (char*)malloc(sizeof(char) * size); break;
		case _string: anode->_as = (char**)malloc(sizeof(char*) * size); break;
		case _int: anode->_ai = (int*)malloc(sizeof(int) * size); break;
		case _boolean: anode->_ab = (int*)malloc(sizeof(int) * size); break;
		case _float: anode->_af = (double*)malloc(sizeof(double) * size); break;
	}
	
	// set the has-assigned values to all false's
	anode->hasAssigned = (int*)malloc(sizeof(int) * size);
	int k;
	for (k = 0; k < size; ++k)
		anode->hasAssigned[k] = 0;
	
	// set the Anode as the a_value of the item
	item->a_value = anode;
	
	// return successfully
	return 1;
}
