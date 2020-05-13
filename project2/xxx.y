%{
	#include <stdio.h>
	#include "symbol_table.hpp"
	
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
	int yywarning(char*, char*);
	
	// append a new hash-table when reaching a new scope
	void appendHashTable();
	// insert an identifier into the hash-table for the current scope
	int insertIntoHashTable(const char*);
	// search for a certain identifier in the latest hash-table
	Item* lookupInHashTable(const char*);
	// set the value of a variable in the latest hash-table
	void setValueInHashTable(const char*, ItemType, void*);
	
	/* helper variables */
	
	// check if the current deriving numeric expression is an INT (or a FLOAT)
	int isIntFlag = 1;
	
	// temporally store the name of an identifier
	char* ident = NULL;
%}

/* the union of different types */
%union {
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
}

/* associativities & precedences */
%right '='
%left AND OR
%right NOT
%left LT LE EQ GE GT NE
%left '+' '-'
%left '*' '/' MOD
%nonassoc UMINUS

/* type definitions */
%type <sval> string_expr
%type <type_idx> opt_type_dclr
%type <type_idx> data_type
%type <bval> boolean_expr
%type <dval> numeric_expr
%type <dval> numeric_term

/* tokens */
%token COMMA COLON PERIOD SEMICOLON
%token OPEN_PAR CLOSE_PAR OPEN_SQB CLOSE_SQB OPEN_BRA CLOSE_BRA
%token BOOLEAN BREAK CHAR CASE CLASS CONTINUE DEF DO ELSE EXIT FALSE FLOAT FOR IF INT NULLS OBJECT PRINT PRINTLN READ REPEAT RETURN STRING TO TRUE TYPE VAL VAR WHILE
%token <sval> ID
%token <ival> LITERAL_INTEGER
%token <dval> LITERAL_FLOAT
%token <sval> LITERAL_STRING

%%

/* the start symbol */
program
	: OBJECT identifier OPEN_BRA object_body CLOSE_BRA {
		// insert object's name into hash-table
		insertIntoHashTable(ident);
		// set the value of object's name
		setValueInHashTable(ident, ItemType_OBJECT, NULL);
	}
	;

/* the body of an object */
object_body
	: object_body statement
	| object_body declaration
	| %empty
	;

/* the pre-defined types */
data_type
	: CHAR { $$ = 0; }
	| STRING { $$ = 1; }
	| INT { $$ = 2; }
	| BOOLEAN { $$ = 3; }
	| FLOAT { $$ = 4; }
	;

/* the declaration optionally followed by a semicolon */
declaration
	: dclr opt_semi
	;

/* the declaration of a variable or a constant */
dclr
	: val_dclr
	| var_dclr
	;

/* the declaration of a constant */
val_dclr
	: VAL identifier opt_type_dclr '=' string_expr {
		// first, insert this new constant into hash-table
		if (insertIntoHashTable(ident) == -1)
			yyerror("Symbol Error", "The constant in this scope has already been declared before.");
		
		/* explicitly-declared type checking (char: 0, string: 1, int: 2, boolean: 3, float: 4) */
		else {
			// type STRING declared or no type explicitly-declared
			if ($3 == 1 || $3 == -1)
				printf("[%s]\n", $5),
				setValueInHashTable(ident, ItemType_VAL_S, $5),
				printf("{%s}\n", $5);
			// CHAR, INT, BOOLEAN, or FLOAT declared -> type error
			else
				yyerror("Type Error", "A string value is assigned to a non-string type constant.");
			
			Item* item = lookupInHashTable(ident);
			if (item != NULL)
				printf("|%s|%d|%s|\n", item->name, item->itemType, item->value);
		}
	}
	| VAL identifier opt_type_dclr '=' numeric_expr {
		// first, insert this new constant into hash-table
		if (insertIntoHashTable(ident) == -1)
			yyerror("Symbol Error", "The constant in this scope has already been declared before.");
		
		/* explicitly-declared type checking (char: 0, string: 1, int: 2, boolean: 3, float: 4) */
		else {
			int integerized = (int) $5;
			double floatized = (double) ($5 + 0.0);
		
			// type INT declared
			if ($3 == 2) {
				// the declared type and the assigned value are both INTs
				if (isIntFlag)
					setValueInHashTable(ident, ItemType_VAL_I, &integerized);
				// the declared type is INT, but the assigned value is FLOAT
				else {
					yywarning("Type warning", "A FLOAT value is assigned to an INT type constant. The value loss is highly possible.");
					setValueInHashTable(ident, ItemType_VAL_I, &integerized);
				}
			}
			// type FLOAT declared
			else if ($3 == 4) {
				// the declared type is FLOAT, but the assigned value is INT
				if (isIntFlag) {
					yywarning("Type warning", "An INT value is assigned to a FLOAT type constant.");
					setValueInHashTable(ident, ItemType_VAL_F, &floatized);
				}
				// the declared type and the assigned value are both FLOATs
				else
					setValueInHashTable(ident, ItemType_VAL_F, &floatized);
			}
			// no type explicitly-declared
			else if ($3 == -1) {
				if (isIntFlag)
					setValueInHashTable(ident, ItemType_VAL_I, &integerized);
				else
					setValueInHashTable(ident, ItemType_VAL_F, &floatized);
			}
			// CHAR, STRING, or BOOLEAN declared -> type error
			else
				yyerror("Type Error", "A numeric value is assigned to a non-numeric type constant.");
		}
		
		// reset the is-int-flag
		isIntFlag = 1;
	}
	| VAL identifier opt_type_dclr '=' boolean_expr {
		// first, insert this new constant into hash-table
		if (insertIntoHashTable(ident) == -1)
			yyerror("Symbol Error", "The constant in this scope has already been declared before.");
		
		/* explicitly-declared type checking (char: 0, string: 1, int: 2, boolean: 3, float: 4) */
		else {
			// type BOOLEAN declared or no type explicitly-declared
			if ($3 == 3 || $3 == -1)
				setValueInHashTable(ident, ItemType_VAL_B, &($5));
			// CHAR, STRING, INT, or FLOAT declared -> type error
			else
				yyerror("Type Error", "A boolean value is assigned to a non-boolean type constant.");
		}
	}
	;

/* the declaration of a variable */
var_dclr
	: VAR identifier opt_type_dclr opt_init
	| VAR identifier COLON data_type OPEN_SQB numeric_expr CLOSE_SQB
	;

/* the optional type declaration when declaring a variable/constant */
opt_type_dclr
	: COLON data_type { $$ = $2; }
	| %empty { $$ = -1; }
	;

/* the optional initialization of a variable declaration */
opt_init
	: '=' string_expr
	| '=' numeric_expr
	| '=' boolean_expr
	| %empty
	;

/* the statement optionally followed by a semicolon */
statement
	: stmt opt_semi
	;

/* a single statement */
stmt
	: assignment
	| string_expr
	| numeric_expr
	| boolean_expr
	| func_invoc
	;

/* the assignment */
assignment
	: identifier '=' string_expr { /* TODO */ }
	| identifier '=' numeric_expr { /* TODO */ }
	| identifier '=' boolean_expr { /* TODO */ }
	;

/* the string expression */
string_expr
	: LITERAL_STRING { strcpy($$, $1); }
	;

/* the numeric expression (int or float) */
numeric_expr
	: numeric_term
	;
numeric_term
	: numeric_term '+' numeric_term { $$ = $1 + $3; }
	| numeric_term '-' numeric_term { $$ = $1 - $3; }
	| numeric_term '*' numeric_term { $$ = $1 * $3; }
	| numeric_term '/' numeric_term { $$ = $1 / $3; }
	| numeric_term MOD numeric_term {
		if (isIntFlag == 0) {
			yywarning("Type Warning", "Float values in MOD operation: possible lossy conversion from FLOAT to INT.");
			$$ = (double) ((int) $1 % (int) $3);
		}
		else
			$$ = (int) $1 % (int) $3;
	}
	| '-' numeric_term %prec UMINUS { $$ = (-$2); }
	| OPEN_PAR numeric_term CLOSE_PAR { $$ = $2; }
	| identifier { printf("|%s|\n", ident);  }
	| LITERAL_FLOAT { $$ = $1; isIntFlag = 0; }
	| LITERAL_INTEGER { $$ = $1; }
	;

/* the boolean expression */
boolean_expr
	: numeric_expr LT numeric_expr { $$ = ($1 < $3); }
	| numeric_expr LE numeric_expr { $$ = ($1 <= $3); }
	| numeric_expr EQ numeric_expr { $$ = ($1 == $3); }
	| numeric_expr GE numeric_expr { $$ = ($1 >= $3); }
	| numeric_expr GT numeric_expr { $$ = ($1 > $3); }
	| numeric_expr NE numeric_expr { $$ = ($1 != $3); }
	| OPEN_PAR boolean_expr CLOSE_PAR { $$ = ($2); }
	| NOT boolean_expr { $$ = (!($2)); }
	| OPEN_PAR identifier CLOSE_PAR
	| boolean_expr OR boolean_expr { $$ = ($1 || $3); }
	| boolean_expr AND boolean_expr { $$ = ($1 && $3); }
	| TRUE { $$ = 1; }
	| FALSE { $$ = 0; }
	;

/* the function invocation */
func_invoc
	: identifier OPEN_PAR actual_argus CLOSE_PAR
	| identifier OPEN_PAR CLOSE_PAR
	;

/* the actual arguments in a function invocation */
actual_argus
	: actual_argus COMMA string_expr
	| actual_argus COMMA numeric_expr
	| actual_argus COMMA boolean_expr
	| string_expr
	| numeric_expr
	| boolean_expr
	;

/* the optimal semicolon */
opt_semi
	: SEMICOLON
	| %empty
	;

/* the identifier (for temporally storing it) */
identifier
	: ID {
		if (ident != NULL)
			free(ident);
		ident = (char*)malloc(sizeof(char) * (strlen($1) + 1));
		ident[0] = 0;
		strcpy(ident, $1);
	}
	;

%%

// error happens -> tell the user and exit
int yyerror(char* errType, char* msg) {
	fprintf(stderr, " >>> |%s|\n     %s\n", errType, msg);
	return 0;
}

// warning happens -> just tell the user
int yywarning(char* warningType, char* msg) {
	fprintf(stderr, " >>> |%s|\n     %s\n", warningType, msg);
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
		yyerror("Syntax error", "You cannot assign variables here.");
	
	// insert into the latest hash-table
	return insert(htail->table, name);
}

// search for a certain identifier in the latest hash-table
Item* lookupInHashTable(const char* name) {
	return lookup(htail->table, name);
}

// set the value of an identifier in the latest hash-table
void setValueInHashTable(const char* name, ItemType itemType, void* value) {
	// first, check if the htail (the latest hash-table) is NULL or not
	if (htail == NULL)
		yyerror("Syntax error", "You cannot try to get identifiers here.");
	
	// search for the identifier in the latest hash-table
	Item* item = lookup(htail->table, name);
	
	// no such identifier
	if (item == NULL)
		yyerror("Symbol Error", "No such identifier.");
	
	// identifier found, set its item-type and value
	else {
		// set the item-type
		item->itemType = itemType;
		
		// the item-type is STRING
		if (value != NULL || itemType == ItemType_VAL_S || itemType == ItemType_VAR_S) {
			char* s = (char*)value;
			item->value = (char*)malloc(sizeof(char) * (strlen(s) + 1));
			strcpy(item->value, s);
		}
		// the rest cases
		else
			item->value = value;
	}
}