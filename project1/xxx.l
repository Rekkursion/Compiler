%{
	/**
	 * project 1 - lexical analyzer by lex
	 * by B10615031
	 */
	
	/* file inclusions */
	
	#include <stdio.h>
	#include <string.h>
	#include "symbol_table.hpp"
	#include "util.hpp"
	
	/* macro definitions */
	
	// buffer the attained text of the input content
	#define bufText(t) { \
		strcat(sgLnBuf, t); \
		if (t[strlen(t) - 1] == '\n') { \
			printf("%d: %s", numOfLines, sgLnBuf); \
			sgLnBuf[0] = 0; \
		} \
	}
	
	// get a string token, including identifiers, strings, & real-numbers
	#define tokenString(t, s) printf("<%s:%s>\n", #t, s)
	
	// get an integer token
	#define tokenInteger(t, i) printf("<%s:%d>\n", #t, i)
	
	// get a token of rest cases
	#define token(t) printf("<%s>\n", #t)
	
	/* helping variable declarations */
	
	// the buffer for building the string token
	char strBuf[200002] = {0};

	// the counter of lines
	int numOfLines = 1;
	
	// the single-line buffer for storing the input content
	char sgLnBuf[200002] = {0};
	
	// the symbol table
	HashTable table;
%}

	/* state declaration: the comment state */
%x COMMENT

	/* regular definition: one or more digits */
dgts [0-9]+

%%
	/* ============================================================ */
	/* tokens of delimiters */
	
	/* TOKEN: commas */
"," { bufText(","); token(','); }
	
	/* TOKEN: colons */
":" { bufText(":"); token(':'); }
	
	/* TOKEN: periods */
"." { bufText("."); token('.'); }
	
	/* TOKEN: semicolons */
";" { bufText(";"); token(';'); }
	
	/* TOKEN: open parentheses */
"(" { bufText("("); token('('); }
	
	/* TOKEN: close parentheses */
")" { bufText(")"); token(')'); }
	
	/* TOKEN: open square brackets */
"[" { bufText("["); token('['); }
	
	/* TOKEN: close square brackets */
"]" { bufText("]"); token(']'); }
	
	/* TOKEN: open brackets */
"{" { bufText("{"); token('{'); }
	
	/* TOKEN: close brackets */
"}" { bufText("}"); token('}'); }

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
"%" { bufText("%"); token('%'); }

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

	/* TOKEN: "null" -> keywords */
null { bufText(yytext); token(NULL); }

	/* TOKEN: "object" -> keywords */
object { bufText(yytext); token(OBJECT); }

	/* TOKEN: "print" -> keywords */
print { bufText(yytext); token(PRINT); }

	/* TOKEN: "println" -> keywords */
println { bufText(yytext); token(PRINTLN); }

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
	
	// get a new token, which is an identifier
	tokenString(id, yytext);
	
	// insert this identifier into the symbol table
	insert(table, yytext);
}

	/* TOKEN: integers */
{dgts} { bufText(yytext); tokenInteger(integer, toInt(yytext)); }

	/* TOKEN: real numbers */
([0-9]*\.{dgts}([Ee][\+\-]?{dgts})?)|({dgts}[Ee][\+\-]?{dgts}) {
	bufText(yytext);
	tokenString(real, yytext);
}

	/* TOKEN: strings */
\"[^\"\n]*\" {
	// buffer the attained text
	bufText(yytext);
	
	// concatenate the input to the string token buffer without the open & closing '\"'
	strncat(strBuf, yytext + 1, yyleng - 2);

	// read the next character to check if the string ends or not
	char nextChar = input();
	
	// the string token continues
	if (nextChar == '\"')
		strcat(strBuf, "\"");
		
	// the string token ends -> get a new token
	else {
		tokenString(string, strBuf);
		strBuf[0] = 0;
	}
	
	// give back the character just read
	unput(nextChar);
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

// the main function
int main() {
	// create a new symbol table
	table = create();

	// do lexical analysis
	yylex();
	
	// print out the last line
	bufText("\n");
	
	// print out the number of lines
	printf("\nNumber of lines = %d\n\n", numOfLines);
	
	// dump all identifiers of the symbol table
	dump(table);
	
	// return
    return 0;
}

int yywrap() {
	return 1;
}