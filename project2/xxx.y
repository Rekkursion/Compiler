%{
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
%}

/* the union of different types */
%union {
	Tnode* tnode;
	DataType dataType;
}

/* associativities & precedences */
%right '='
%left OR
%left AND
%right NOT
%left LT LE EQ GE GT NE
%left '+' '-'
%left '*' '/' MOD
%nonassoc UMINUS

/* type definitions */
%type <dataType> data_type
%type <dataType> opt_type_dclr
%type <tnode> expr

/* tokens */
%token COMMA COLON PERIOD SEMICOLON
%token OPEN_PAR CLOSE_PAR OPEN_SQB CLOSE_SQB OPEN_BRA CLOSE_BRA
%token BOOLEAN BREAK CHAR CASE CLASS CONTINUE DEF DO ELSE EXIT FALSE FLOAT FOR IF INT NULLS OBJECT PRINT PRINTLN READ REPEAT RETURN STRING TO TRUE TYPE VAL VAR WHILE
%token <tnode> ID
%token <tnode> LITERAL_INTEGER
%token <tnode> LITERAL_FLOAT
%token <tnode> LITERAL_CHAR
%token <tnode> LITERAL_STRING

%%

/* the start symbol */
program
	: OBJECT identifier OPEN_BRA object_body CLOSE_BRA {
		// insert object's name into hash-table
		insertIntoHashTable(ident);
		clear_stk(1);
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
	: CHAR { $$ = _char; }
	| STRING { $$ = _string; }
	| INT { $$ = _int; }
	| BOOLEAN { $$ = _boolean; }
	| FLOAT { $$ = _float; }
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
	: VAL identifier { storeAssigneeFromIdent(); } opt_type_dclr '=' expr { insertAndInitId(1, $4); }
	;

/* the declaration of a variable */
var_dclr
	: VAR identifier { storeAssigneeFromIdent(); } var_dclr_postfix
	;

/* the postfix portion of a declaration of a variable */
var_dclr_postfix
	: opt_type_dclr opt_init { insertAndInitId(0, $1); }
	| COLON data_type OPEN_SQB expr CLOSE_SQB { insertArrayId($2); }
	;

/* the optional type declaration when declaring a variable/constant */
opt_type_dclr
	: COLON data_type { $$ = $2; }
	| %empty { $$ = _none; }
	;

/* the optional initialization of a variable declaration */
opt_init
	: '=' expr
	| %empty
	;

/* the statement optionally followed by a semicolon */
statement
	: stmt opt_semi
	;

/* a single statement */
stmt
	: assignment
	| expr
	| func_invoc
	;

/* the assignment */
assignment
	: identifier { storeAssigneeFromIdent(); } assignment_postfix
	;

/* the postfix portion of an assignment */
assignment_postfix
	: '=' expr { /* TODO */ }
	| OPEN_SQB expr CLOSE_SQB '=' expr { /* TODO */ }
	;

expr
/* numeric expression */
	: expr '+' expr { doOperation($$, "+", 1, 1); }
	| expr '-' expr { doOperation($$, "-", 1, 1); }
	| expr '*' expr { doOperation($$, "*", 1, 1); }
	| expr '/' expr { doOperation($$, "/", 1, 1); }
	| expr MOD expr { doOperation($$, "%", 1, 0); }
	| '-' expr %prec UMINUS { doOperation($$, "UMINUS", 0, 1); }
	| expr LT expr { doOperation($$, "<", 1, 1); }
	| expr LE expr { doOperation($$, "<=", 1, 1); }
	| expr GE expr { doOperation($$, ">=", 1, 1); }
	| expr GT expr { doOperation($$, ">", 1, 1); }
	| LITERAL_FLOAT { push_stk($1); }
	| LITERAL_INTEGER { push_stk($1); }
/* boolean expression */
	| NOT expr { doOperation($$, "!", 0, 0); }
	| expr OR expr { doOperation($$, "||", 1, 0); }
	| expr AND expr { doOperation($$, "&&", 1, 0); }
	| TRUE { $$->_type = _boolean; $$->_b = 1; push_stk($$); }
	| FALSE { $$->_type = _boolean; $$->_b = 0; push_stk($$); }
/* general expression, i.e., equal-to & not-equal-to */
	| expr EQ expr { doOperation($$, "==", 1, 0); }
	| expr NE expr { doOperation($$, "!=", 1, 0); }
/* character expression */
	| LITERAL_CHAR { push_stk($1); }
/* string expression */
	| LITERAL_STRING { push_stk($1); }
/* identifier, including variable, constant, & array */
	| identifier OPEN_SQB expr CLOSE_SQB {
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
	| identifier {
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
/* an expression which is wrapped by a pair of parentheses */
	| OPEN_PAR expr CLOSE_PAR

/* the function invocation */
func_invoc
	: identifier OPEN_PAR actual_argus CLOSE_PAR
	| identifier OPEN_PAR CLOSE_PAR
	;

/* the actual arguments in a function invocation */
actual_argus
	: actual_argus COMMA expr
	| expr
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
		ident = (char*)malloc(sizeof(char) * (strlen($1->_s) + 1));
		ident[0] = 0;
		strcpy(ident, $1->_s);
	}
	;

%%

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