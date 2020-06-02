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
#line 86 "xxx.y" /* yacc.c:1909  */

	char c;
	char s[2002];
	int i;
	int b;
	double f;
	DataType dataType;

#line 185 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
