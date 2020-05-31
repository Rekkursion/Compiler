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
    COMMA = 271,
    COLON = 272,
    PERIOD = 273,
    SEMICOLON = 274,
    OPEN_PAR = 275,
    CLOSE_PAR = 276,
    OPEN_SQB = 277,
    CLOSE_SQB = 278,
    OPEN_BRA = 279,
    CLOSE_BRA = 280,
    ARROW_IN_FOR = 281,
    BOOLEAN = 282,
    BREAK = 283,
    CHAR = 284,
    CASE = 285,
    CLASS = 286,
    CONTINUE = 287,
    DEF = 288,
    DO = 289,
    ELSE = 290,
    EXIT = 291,
    FALSE = 292,
    FLOAT = 293,
    FOR = 294,
    IF = 295,
    INT = 296,
    NULLS = 297,
    OBJECT = 298,
    PRINT = 299,
    PRINTLN = 300,
    READ = 301,
    REPEAT = 302,
    RETURN = 303,
    STRING = 304,
    TO = 305,
    TRUE = 306,
    TYPE = 307,
    VAL = 308,
    VAR = 309,
    WHILE = 310,
    ID = 311,
    LITERAL_CHAR = 312,
    LITERAL_STRING = 313,
    LITERAL_INTEGER = 314,
    LITERAL_FLOAT = 315
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
#define COMMA 271
#define COLON 272
#define PERIOD 273
#define SEMICOLON 274
#define OPEN_PAR 275
#define CLOSE_PAR 276
#define OPEN_SQB 277
#define CLOSE_SQB 278
#define OPEN_BRA 279
#define CLOSE_BRA 280
#define ARROW_IN_FOR 281
#define BOOLEAN 282
#define BREAK 283
#define CHAR 284
#define CASE 285
#define CLASS 286
#define CONTINUE 287
#define DEF 288
#define DO 289
#define ELSE 290
#define EXIT 291
#define FALSE 292
#define FLOAT 293
#define FOR 294
#define IF 295
#define INT 296
#define NULLS 297
#define OBJECT 298
#define PRINT 299
#define PRINTLN 300
#define READ 301
#define REPEAT 302
#define RETURN 303
#define STRING 304
#define TO 305
#define TRUE 306
#define TYPE 307
#define VAL 308
#define VAR 309
#define WHILE 310
#define ID 311
#define LITERAL_CHAR 312
#define LITERAL_STRING 313
#define LITERAL_INTEGER 314
#define LITERAL_FLOAT 315

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 82 "xxx.y" /* yacc.c:1909  */

	char c;
	char s[2002];
	int i;
	int b;
	double f;
	DataType dataType;

#line 183 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
