%{
	#include <stdio.h>
	#include "e_stack.hpp" // the stack for expressions
	#include "v_stack.hpp" // the stack for variables/constands/arrays
	#include "m_stack.hpp" // the stack for methods (invocations)
	
	// for the symbol table
	#ifndef _SYMBOL_TABLE
	#include "symbol_table.hpp"
	#define _SYMBOL_TABLE
	#endif
	
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
	
	
	/* helper variables */
	
	// the temporally-saved identifier
	char* ident = NULL;
	
	// the temporally-saved assignee, i.e., the identifier which is about to be assigned
	char* assignee = NULL;
	
	// the temporally-saved the method when defining one
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
%}

/* the union of different types */
%union {
	char c;
	char s[2002];
	int i;
	int b;
	double f;
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
%nonassoc ASSIGNMENT
%nonassoc EXPR
%nonassoc STMT
%nonassoc PRINT PRINTLN READ
%nonassoc RETURN
%nonassoc RETURN_W_EXPR

/* type definitions for non-terminals */
%type <dataType> data_type
%type <dataType> opt_type_dclr

/* tokens */
%token COMMA COLON PERIOD SEMICOLON
%token OPEN_PAR CLOSE_PAR OPEN_SQB CLOSE_SQB OPEN_BRA CLOSE_BRA
%token ARROW_IN_FOR BOOLEAN BREAK CHAR CASE CLASS CONTINUE DEF DO ELSE EXIT FALSE FLOAT FOR IF INT NULLS OBJECT REPEAT STRING TO TRUE TYPE VAL VAR WHILE
%token <s> ID
%token <c> LITERAL_CHAR
%token <s> LITERAL_STRING
%token <i> LITERAL_INTEGER
%token <f> LITERAL_FLOAT

%%

/* the start symbol */
program
	: OBJECT new_symtab identifier OPEN_BRA { insertIntoHashTable(ident, _object, _none); } object_body CLOSE_BRA rem_symtab {
		// check if there's a method named "main" or not, if there's NO -> semantics error
		if (hasMainFlag == 0)
			warn("No \"main\" method found, but there must be one.");
	}
	;

/* the body of an object (an optional part + a method definition) */
object_body
	: object_body_first_part method_def
	;

/* the first part of the object body (var/val declarations & method definitions) */
object_body_first_part
	: object_body_first_part declaration
	| object_body_first_part method_def
	| %empty
	;

/* the method definition */
method_def
	: DEF identifier OPEN_PAR {
		// insert the method symbol into the currently-scoped hash-table
		insertIntoHashTable(ident, _method, _none);
		// temporally save the method-item
		methItem = lookupInHashTable(ident);
		// check if this method is named "main" or not and set the flag of has-main
		if (strcmp(ident, "main") == 0)
			hasMainFlag = 1;
	} new_symtab opt_formal_argus CLOSE_PAR opt_type_dclr {
		// set the return type to the currently-defining method
		setReturnType(&(methItem->methDef), $8);
	} OPEN_BRA def_body CLOSE_BRA {
		// check the return type if hasn't do the checking yet
		checkReturnType();
		// nullify the pointer to the already-defined method
		methItem = NULL;
	} rem_symtab
	;

/* the optional formal arguments for a method definition */
opt_formal_argus
	: one_formal_argu more_formal_argus
	| %empty
	;

/* more formal arguments for a method definition */
more_formal_argus
	: COMMA one_formal_argu more_formal_argus
	| %empty
	;

/* a single formal argument for a memory definition */
one_formal_argu
	: identifier COLON data_type {
		// add a new formal argument into the currently-defining method
		if (methItem != NULL)
			addFormalArgu(&(methItem->methDef), ident, $3);
		// also insert it into the currently-scoped hash-table
		insertIntoHashTable(ident, _variable, $3);
	}
	;

/* the body of a method definition */
def_body
	: def_body declaration
	| def_body statement
	| %empty
	;

/* the body of a block (could be empty) */
block_body
	: block_body declaration
	| block_body statement
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
	: VAL identifier opt_type_dclr { setAssignee(); } '=' expr {
		Enode* e = pop_e();
		initNewId(assignee, _constant, $3, (e == NULL) ? _none : e->_type);
		free_e(e);
	}
	;

/* the declaration of a variable */
var_dclr
	: VAR identifier opt_type_dclr { setAssignee(); } opt_init {
		Enode* e = pop_e();
		initNewId(assignee, _variable, $3, (e == NULL) ? _none : e->_type);
		free_e(e);
	}
	| VAR identifier COLON data_type { setAssignee(); } OPEN_SQB expr CLOSE_SQB {
		Enode* e = pop_e();
		initNewId(assignee, _array, $4, (e == NULL) ? _none : e->_type);
		free_e(e);
	}
	;

/* the optional type declaration when declaring a variable/constant */
opt_type_dclr
	: COLON data_type { $$ = $2; }
	| %empty { $$ = _none; }
	;

/* the optional initialization of a variable declaration */
opt_init
	: '=' expr { /* pop'd */ }
	| %empty
	;

/* the statement:
	1. a simple statement optionally followed by a semicolon
	2. a block
	3. IF
	4. WHILE
	5. FOR */
statement
	: stmt opt_semi %prec STMT { clear_e(); }
	| OPEN_BRA new_symtab block_body CLOSE_BRA rem_symtab
	| IF OPEN_PAR expr { checkBooleanExpr("IF"); } CLOSE_PAR statement opt_else
	| WHILE OPEN_PAR expr { checkBooleanExpr("WHILE"); } CLOSE_PAR statement
	| FOR OPEN_PAR identifier ARROW_IN_FOR expr { checkNumExpr(); } TO expr { checkNumExpr(); } CLOSE_PAR statement
	| PRINT expr opt_semi { printFlag = 1; returnFlag = 0; }
	| PRINTLN expr opt_semi { printFlag = 2; returnFlag = 0; }
	;

/* the optional ELSE-clause which is preceded by an IF-clause */
opt_else
	: ELSE statement
	| %empty
	;

/* a single simple statement */
stmt
	: assignment %prec ASSIGNMENT
	| func_invoc
	| READ { clear_e(); } identifier { setAssignee(); } opt_squared_brackets { checkUsageOfValVarArr(assignee, 1); }
	| RETURN expr %prec RETURN_W_EXPR { returnFlag = 1; printFlag = 0; checkReturnType(); }
	| RETURN { clear_e(); returnFlag = 1; printFlag = 0; checkReturnType(); }
	;

/* the assignment of a/an val/var/arr */
assignment
	: identifier opt_squared_brackets '=' { setAssignee(); checkUsageOfValVarArr(assignee, 1); } expr {
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
			}
		}
		free_e(e);
	}
	;

/* optional squared brackets for an identifier */
opt_squared_brackets
	: OPEN_SQB expr CLOSE_SQB { squaredFlag = 1; }
	| %empty { squaredFlag = 0; }
	;

/* the expression among literal values & identifiers (var/val/arr)
   'doOP' means 'do the operation' */
expr
/* numeric expression */
	: expr '+' expr { doOp("+", 1, warn); }
	| expr '-' expr { doOp("-", 1, warn); }
	| expr '*' expr { doOp("*", 1, warn); }
	| expr '/' expr { doOp("/", 1, warn); }
	| expr MOD expr { doOp("%", 1, warn); }
	| '-' expr %prec UMINUS { doOp("UMINUS", 0, warn); }
	| expr LT expr { doOp("<", 1, warn); }
	| expr LE expr { doOp("<=", 1, warn); }
	| expr GE expr { doOp(">=", 1, warn); }
	| expr GT expr { doOp(">", 1, warn); }
	| LITERAL_FLOAT { push_e(_float, &($1)); }
	| LITERAL_INTEGER { push_e(_int, &($1)); }
/* boolean expression */
	| NOT expr { doOp("!", 0, warn); }
	| expr OR expr { doOp("||", 1, warn); }
	| expr AND expr { doOp("&&", 1, warn); }
	| TRUE { int t = 1; push_e(_boolean, &t); }
	| FALSE { int f = 0; push_e(_boolean, &f); }
/* general expression, i.e., equal-to & not-equal-to */
	| expr EQ expr { doOp("==", 1, warn); }
	| expr NE expr { doOp("!=", 1, warn); }
/* character expression */
	| LITERAL_CHAR { push_e(_char, &($1)); }
/* string expression */
	| LITERAL_STRING { char* s = (char*)malloc(sizeof(char) * (strlen($1) + 1)); strcpy(s, $1); push_e(_string, &s); free(s); }
/* identifier, including variable/constant and array */
	| identifier opt_squared_brackets {
		// get the identifier stored in the currently-scoped hash-table
		Item* item = lookupInHashTable(ident);
		// check if the identifier is used correctly or not
		checkUsageOfValVarArr(ident, 0);
		// push the data-type back into the expr-stack
		push_e((item == NULL) ? _none : item->dataType, NULL);
	}
/* an expression which is wrapped by a pair of parentheses -> do nothing */
	| OPEN_PAR expr CLOSE_PAR
/* the function invocation */
	| func_invoc {
		Mnode* m_nd = pop_m();
		Item* mItem = NULL;
		if (m_nd != NULL && m_nd->name != NULL)
			mItem = lookupInHashTable(m_nd->name);
		// push an Enode according to the return type of this invocated function
		push_e((mItem == NULL || mItem->methDef == NULL) ? _none : mItem->methDef->_ret_type, NULL);
		free_m(m_nd);
	}
	;

/* the function invocation */
func_invoc
	: identifier OPEN_PAR {
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
	} opt_actual_argus CLOSE_PAR {
		Mnode* meth_nd = peek_m();
		Item* mItem = NULL;
		if (meth_nd != NULL && meth_nd->name != NULL)
			mItem = lookupInHashTable(meth_nd->name);
		if (mItem != NULL && mItem->itemType == _method) {
			// if the number of actual arguments are NOT enough according to the defined formal arguments
			if (meth_nd->argCounter < mItem->methDef->argc)
				fwarn("The argument(s) are NOT enough when invocating the method \"%s\".", mItem->name, NULL, NULL, NULL, NULL);
		}
	}
	;

/* the optional actual arguments in a function invocation */
opt_actual_argus
	: one_actual_argu more_actual_argu
	| %empty
	;

/* more actual arguments in a function invocation */
more_actual_argu
	: COMMA one_actual_argu more_actual_argu
	| %empty
	;

/* a single actual argument in a function invocation */
one_actual_argu
	: expr {
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
	;

/* the optional semicolon */
opt_semi
	: SEMICOLON { checkReturnType(); }
	| %empty
	;

/* the identifier (for temorally storing it) */
identifier
	: ID {
		// store it in a global variable 'ident'
		if (ident != NULL)
			free(ident);
		ident = (char*)malloc(sizeof(char) * (strlen($1) + 1));
		ident[0] = 0;
		strcpy(ident, $1);
	}
	;

/* the marker for creating a new symbol-table for scoping */
new_symtab
	: %empty { appendHashTable(); }

/* the marker for removing a symbol-table for scoping */
rem_symtab
	: %empty { removeHashTable(); }

%%

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
	// start parsing
	yyparse();
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
	
	// free the Hnode pointer that just been removed
	free(p);
}

// insert an identifier into the hash-table for the current scope with optionally-passed item-type and data-type
int insertIntoHashTable(const char* name, ItemType itemType, DataType dataType) {
	// first, check if the htail (the latest hash-table) is NULL or not
	if (htail == NULL)
		warn("Syntax error. You cannot assign variables here.");
	
	// try to insert the symbol into the latest hash-table
	int insertionResult = insert(htail->table, name);
	
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