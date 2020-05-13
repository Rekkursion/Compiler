/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
    AND = 258,
    OR = 259,
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
    LITERAL_STRING = 311
  };
#endif
/* Tokens.  */
#define AND 258
#define OR 259
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
#define LITERAL_STRING 311

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 40 "xxx.y" /* yacc.c:1909  */

	// the string value
	char* sval;

	// the index of data type
	int type_idx;
	
	// the integer value
	int ival;
	
	// the boolean value
	int bval;
	
	// the double value
	double dval;

#line 183 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
