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
#line 155 "xxx.y" /* yacc.c:1909  */

	char c;
	char s[2002];
	int i;
	int b;
	double f;
	DataType dataType;

#line 189 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
