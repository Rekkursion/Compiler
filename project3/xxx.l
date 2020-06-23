%{
	/**
	 * project 1 - lexical analyzer by lex
	 * by B10615031
	 */
	
	/* file inclusions */
	
	#include <stdio.h>
	#include <string.h>
	#include "data_type.h"
	#include "y.tab.h"
	
	// buffer the attained text of the input content
	#define bufText(t) { \
		strcat(sgLnBuf, t); \
		if (t[strlen(t) - 1] == '\n') { \
			printf("%d: %s", numOfLines, sgLnBuf); \
			sgLnBuf[0] = 0; \
		} \
	}
	
	// get a literal character token
	#define tokenChar(ch) { \
		yylval.c = ch; \
		return LITERAL_CHAR; \
	}
	
	// get a literal string token
	#define tokenString(str) { \
		strcpy(yylval.s, str); \
		yylval.s[strlen(str)] = 0; \
		return LITERAL_STRING; \
	}
	
	// get an integer token
	#define tokenInteger(str_i) { \
		sscanf(yytext, "%d", &(yylval.i)); \
		return LITERAL_INTEGER; \
	}
	
	// get a real number token
	#define tokenReal(str_r) { \
		sscanf(yytext, "%lf", &(yylval.f)); \
		return LITERAL_FLOAT; \
	}
	
	// get an identifier token
	#define tokenId(id) { \
		strcpy(yylval.s, yytext); \
		yylval.s[strlen(yytext)] = 0; \
		return ID; \
	}
	
	// get a token of rest cases
	#define token(t) return t
	
	/* helping variable declarations */
	
	// the buffer for building the string token
	char* strBuf;
	
	// the flag to check if it's a new literal string
	int newLiteralStringFlag = 1;

	// the counter of lines
	int numOfLines = 1;
	
	// the single-line buffer for storing the input content
	char sgLnBuf[200002] = {0};
%}

%option yylineno

	/* state declaration: the comment state */
%x COMMENT

	/* regular definition: one or more digits */
dgts [0-9]+

%%
	/* ============================================================ */
	/* tokens of delimiters */
	
	/* TOKEN: commas */
"," { bufText(","); token(COMMA); }
	
	/* TOKEN: colons */
":" { bufText(":"); token(COLON); }
	
	/* TOKEN: periods */
"." { bufText("."); token(PERIOD); }
	
	/* TOKEN: semicolons */
";" { bufText(";"); token(SEMICOLON); }
	
	/* TOKEN: open parentheses */
"(" { bufText("("); token(OPEN_PAR); }
	
	/* TOKEN: close parentheses */
")" { bufText(")"); token(CLOSE_PAR); }
	
	/* TOKEN: open square brackets */
"[" { bufText("["); token(OPEN_SQB); }
	
	/* TOKEN: close square brackets */
"]" { bufText("]"); token(CLOSE_SQB); }
	
	/* TOKEN: open brackets */
"{" { bufText("{"); token(OPEN_BRA); }
	
	/* TOKEN: close brackets */
"}" { bufText("}"); token(CLOSE_BRA); }

	/* ============================================================ */
	/* tokens of operators */

	/* TOKEN: "+" (add) -> arithmetic operators */
"+" { bufText("+"); token('+'); }

	/* TOKEN: "-" (minus) -> arithmetic operators */
"-" { bufText("-"); token('-'); }

	/* TOKEN: "*" (multiply) -> arithmetic operators */
"*" { bufText("*"); token('*'); }

	/* TOKEN: "/" (divide) -> arithmetic operators */
"/" { bufText("/"); token('/'); }

	/* TOKEN: "%" (mod) -> arithmetic operators */
"%" { bufText("%"); token(MOD); }

	/* ======= */

	/* TOKEN: "<" (less-than) -> relational operators */
"<" { bufText("<"); token(LT); }

	/* TOKEN: "<=" (less-equal) -> relational operators */
"<=" { bufText("<="); token(LE); }

	/* TOKEN: ">=" (greater-equal) -> relational operators */
">=" { bufText(">="); token(GE); }

	/* TOKEN: ">" (greater-than) -> relational operators */
">" { bufText(">"); token(GT); }

	/* TOKEN: "==" (equal-to) -> relational operators */
"==" { bufText("=="); token(EQ); }

	/* TOKEN: "!=" (not-equal-to) -> relational operators */
"!=" { bufText("!="); token(NE); }

	/* ======= */

	/* TOKEN: "&&" (logical AND) -> logical operators */
"&&" { bufText("&&"); token(AND); }

	/* TOKEN: "||" (logical OR) -> logical operators */
"||" { bufText("||"); token(OR); }

	/* TOKEN: "!" (logical NOT) -> logical operators */
"!" { bufText("!"); token(NOT); }

	/* ======= */

	/* TOKEN: "=" (assignment) -> assignment operators */
"=" { bufText("="); token('='); }

	/* TOKEN: "<-" (identifier assignment in a FOR loop) -> assignment operators */
"<-" { bufText("<-"); token(ARROW_IN_FOR); }

	/* ============================================================ */
	/* tokens of keywords */

	/* TOKEN: "boolean" -> keywords */
boolean { bufText(yytext); token(BOOLEAN); }

	/* TOKEN: "break" -> keywords */
break { bufText(yytext); token(BREAK); }

	/* TOKEN: "char" -> keywords */
char { bufText(yytext); token(CHAR); }

	/* TOKEN: "case" -> keywords */
case { bufText(yytext); token(CASE); }

	/* TOKEN: "class" -> keywords */
class { bufText(yytext); token(CLASS); }

	/* TOKEN: "continue" -> keywords */
continue { bufText(yytext); token(CONTINUE); }

	/* TOKEN: "def" -> keywords */
def { bufText(yytext); token(DEF); }

	/* TOKEN: "do" -> keywords */
do { bufText(yytext); token(DO); }

	/* TOKEN: "else" -> keywords */
else { bufText(yytext); token(ELSE); }

	/* TOKEN: "exit" -> keywords */
exit { bufText(yytext); token(EXIT); }

	/* TOKEN: "false" -> keywords */
false { bufText(yytext); token(FALSE); }

	/* TOKEN: "float" -> keywords */
float { bufText(yytext); token(FLOAT); }

	/* TOKEN: "for" -> keywords */
for { bufText(yytext); token(FOR); }

	/* TOKEN: "if" -> keywords */
if { bufText(yytext); token(IF); }

	/* TOKEN: "int" -> keywords */
int { bufText(yytext); token(INT); }

	/* TOKEN: "length" -> keywords */
length { bufText(yytext); token(LENGTH); }

	/* TOKEN: "null" -> keywords */
null { bufText(yytext); token(NULLS); }

	/* TOKEN: "object" -> keywords */
object { bufText(yytext); token(OBJECT); }

	/* TOKEN: "print" -> keywords */
print { bufText(yytext); token(PRINT); }

	/* TOKEN: "println" -> keywords */
println { bufText(yytext); token(PRINTLN); }

	/* TOKEN: "read" -> read */
read { bufText(yytext); token(READ); }

	/* TOKEN: "repeat" -> keywords */
repeat { bufText(yytext); token(REPEAT); }

	/* TOKEN: "return" -> keywords */
return { bufText(yytext); token(RETURN); }

	/* TOKEN: "string" -> keywords */
string { bufText(yytext); token(STRING); }

	/* TOKEN: "to" -> keywords */
to { bufText(yytext); token(TO); }

	/* TOKEN: "true" -> keywords */
true { bufText(yytext); token(TRUE); }

	/* TOKEN: "type" -> keywords */
type { bufText(yytext); token(TYPE); }

	/* TOKEN: "val" -> keywords */
val { bufText(yytext); token(VAL); }

	/* TOKEN: "var" -> keywords */
var { bufText(yytext); token(VAR); }

	/* TOKEN: "while" -> keywords */
while { bufText(yytext); token(WHILE); }

	/* ============================================================ */
	/* other kinds of tokens which should be passed to the parser */

	/* TOKEN: identifiers */
[a-zA-Z][0-9a-zA-Z]* {
	// buffer the text
	bufText(yytext);
	
	// get a new identifier token
	tokenId(yytext);
}

	/* TOKEN: integers */
{dgts} { bufText(yytext); tokenInteger(yytext); }

	/* TOKEN: real numbers */
([0-9]*\.{dgts}([Ee][\+\-]?{dgts})?)|({dgts}[Ee][\+\-]?{dgts}) {
	bufText(yytext);
	tokenReal(yytext);
}

	/* TOKEN: characters */
(\'[^\n\t]\')|(\'\'\'\')|(\'\"\"\') {
	// buffer the text
	bufText(yytext);
	
	// special case 1: '''', which means a single-quote sign '
	if (!strcmp("\'\'\'\'", yytext)) {
		tokenChar('\'');
	}
	// special case 2: '""', which means a double-quote sign "
	else if (!strcmp("\'\"\"\'", yytext)) {
		tokenChar('\"');
	}
	// general case, e.g., 'e', '4', '+', ...
	else {
		char ch = yytext[1];
		tokenChar(ch);
	}
}

	/* TOKEN: strings */
\"[^\"\n]*\" {
	// buffer the attained text
	bufText(yytext);
	
	// concatenate the input to the string token buffer without the open & closing '\"'
	if (newLiteralStringFlag) {
		if (strBuf != NULL)
			free(strBuf);
		strBuf = (char*)malloc(sizeof(char) * 200002);
		strBuf[0] = 0;
		if (yyleng > 2) {
			strncpy(strBuf, yytext + 1, yyleng - 2);
			strBuf[yyleng - 2] = 0;
		}
	}
	else {
		int tLen = strlen(strBuf);
		strncat(strBuf, yytext + 1, yyleng - 2);
		strBuf[tLen + yyleng - 2] = 0;
	}

	// read the next character to check if the string ends or not
	char nextChar = input();
	
	// the string token continues
	if (nextChar == '\"') {
		strcat(strBuf, "\"");
		// give back the character just read
		unput(nextChar);
		newLiteralStringFlag = 0;
	}
	
	// the string token ends -> get a new token
	else {
		newLiteralStringFlag = 1;
		// give back the character just read
		unput(nextChar);
		tokenString(strBuf);
	}
}

	/* ============================================================ */
	/* tokens that shoud be discarded */
	
	/* newlines */
\n {
	bufText(yytext);
	++numOfLines;
}

	/* single-line comments */
\/\/.*\n {
	bufText(yytext);
	++numOfLines;
}

	/* begin the COMMENT state when "/*" has been found */
\/\* {
	bufText(yytext);
	BEGIN COMMENT;
}

	/* in COMMENT state: any character excepts for '\n' and '*' ends with a '\n' */
	/* -> count for lines */
<COMMENT>[^\n\*]*\n {
	bufText(yytext);
	++numOfLines;
}

	/* in COMMENT state: the end of this multi-line comment */
	/* -> end the COMMENT state and go back to the INITIAL state */
<COMMENT>\*\/ {
	bufText(yytext);
	BEGIN 0;
}

	/* in COMMENT state: just a single '*' */
	/* -> skip it */
<COMMENT>\* { bufText(yytext); }

	/* in COMMENT state: any character excepts for '\n' and '*' */
	/* -> skip it */
<COMMENT>[^\n\*]+ { bufText(yytext); }

	/* tabs & spaces */
[ \t]* { bufText(yytext); }

%%