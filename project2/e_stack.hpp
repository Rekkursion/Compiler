#include <string.h>
#include <stdlib.h>

#ifndef _DATA_TYPE
#include "data_type.h"
#define _DATA_TYPE
#endif

#define _DEFAULT_CHAR '_'
#define _DEFAULT_STRING ""
#define _DEFAULT_INT 1
#define _DEFAULT_BOOLEAN 1
#define _DEFAULT_FLOAT 1.0

/* ============================================================ */

const char* _literal_char = "char";
const char* _literal_string = "string";
const char* _literal_int = "int";
const char* _literal_boolean = "boolean";
const char* _literal_float = "float";
const char* _literal_none = "none";

// a node of an expression
typedef struct e_node {
	DataType _type;
	char _c;
	char* _s;
	int _i;
	int _b;
	double _f;
	
	struct e_node* prev;
}Enode;

// the top of the expr-stack
Enode* top_e = NULL;

/* ============================================================ */

// push an expression into the expr-stack
void push_e(DataType _type, void* value) {
	// create a new Enode
	Enode* nd = (Enode*)malloc(sizeof(Enode));
	nd->_type = _type;
	nd->_s = NULL;
	nd->prev = NULL;
	
	// assign its value according to the passed data-type
	switch (_type) {
		// CHAR
		case _char:
			if (value == NULL)
				nd->_c = _DEFAULT_CHAR;
			else
				nd->_c = *(char*)value;
			break;
		
		// STRING
		case _string:
			if (value == NULL) {
				nd->_s = (char*)malloc(sizeof(char) * (strlen(_DEFAULT_STRING) + 1));
				strcpy(nd->_s, _DEFAULT_STRING);
			}
			else {
				char* s = *(char**)value;
				nd->_s = (char*)malloc(sizeof(char) * (strlen(s) + 1));
				strcpy(nd->_s, s);
			}
			break;
		
		// INT
		case _int:
			if (value == NULL)
				nd->_i = _DEFAULT_INT;
			else
				nd->_i = *(int*)value;
			break;
		
		// BOOLEAN
		case _boolean:
			if (value == NULL)
				nd->_b = _DEFAULT_BOOLEAN;
			else
				nd->_b = *(int*)value;
			break;
		
		// FLOAT
		case _float:
			if (value == NULL)
				nd->_f = _DEFAULT_FLOAT;
			else
				nd->_f = *(double*)value;
			break;
	}
	
	// push the built Enode into the expr-stack
	if (top_e == NULL)
		top_e = nd;
	else {
		nd->prev = top_e;
		top_e = nd;
	}
}

// pop an expression from the expr-stack
Enode* pop_e() {
	if (top_e == NULL)
		return NULL;
	
	Enode* top = top_e;
	top_e = top_e->prev;
	return top;
}

// peek an expression (no popping)
Enode* peek_e() {
	return top_e;
}

// free an Enode
void free_e(Enode* nd) {
	if (nd != NULL) {
		if (nd->_s != NULL)
			free(nd->_s);
		free(nd);
	}
}

// clear the expr-stack
void clear_e() {
	Enode* p = top_e;
	while(p) {
		top_e = p->prev;
		free_e(p);
		p = top_e;
	}
}



// convert a DataType to the corresponding string
const char* toS(DataType _type) {
	switch (_type) {
		case _char: return _literal_char;
		case _string: return _literal_string;
		case _int: return _literal_int;
		case _boolean: return _literal_boolean;
		case _float: return _literal_float;
	}
	return _literal_none;
}

// check if an Enode is a numeric type (int or float) or not
int isNumericType(int _type) {
	return (_type == _int || _type == _float);
}

// construct the warning message and print it out to warn the user
int warnUser(int (*warn)(const char*), const char* msgBody, const char* p0, const char* p1, const char* p2, const char* p3, const char* p4) {
	char msg[20002];
	sprintf(msg, msgBody,
		(p0 == NULL ? "" : p0),
		(p1 == NULL ? "" : p1),
		(p2 == NULL ? "" : p2),
		(p3 == NULL ? "" : p3),
		(p4 == NULL ? "" : p4));
	return warn(msg);
}

// do an operation, return 0 if something wrong happens
int doOp(char* opName, int isBinOp, int (*warn)(const char*)) {
	// get the RHS operand
	Enode* rhs = pop_e();
	
	// if there's no operand for RHS
	if (rhs == NULL) {
		warnUser(warn, "There\'s no any operands in the operation \"%s\".", opName, NULL, NULL, NULL, NULL);
		return 0;
	}
	
	// get the LHS operand if it's a binary operation
	Enode* lhs = NULL;
	if (isBinOp) {
		lhs = pop_e();
		// if there's no operand for LHS
		if (lhs == NULL) {
			warnUser(warn, "The binary operation \"%s\" has only one operand.", opName, NULL, NULL, NULL, NULL);
			free_e(rhs);
			return 0;
		}
	}
	
	// get the types of both sides of operands
	int ltype = (lhs == NULL) ? _none : lhs->_type;
	int rtype = rhs->_type;
	
	/* do the operation */
	
	// binary numeric operations: +, -, *, /
	if (!strcmp(opName, "+") || !strcmp(opName, "-") || !strcmp(opName, "*") || !strcmp(opName, "/")) {
		// type incompatible with numeric operations
		if (isNumericType(ltype) == 0 || isNumericType(rtype) == 0) {
			push_e((ltype == _float || rtype == _float ? _float : _int), NULL);
			warnUser(warn, "The binary operation \"%s\" is a numeric operation, but the operands are \'%s\' and \'%s\'.", opName, toS(ltype), toS(rtype), NULL, NULL);
		}
		// no type errors (but a warning is still possible, e.g., INT + FLOAT)
		else {
			// the INT value as the calculation result
			int ir;
			// the FLOAT value as the calculation result
			double fr;
			
			// do this numeric operation
			switch (opName[0]) {
				// add
				case '+':
					if (ltype == _int && rtype == _int)
						ir = lhs->_i + rhs->_i;
					else
						fr = (ltype == _int ? lhs->_i : lhs->_f) + (rtype == _int ? rhs->_i : rhs->_f);
					break;
				
				// minus
				case '-':
					if (ltype == _int && rtype == _int)
						ir = lhs->_i - rhs->_i;
					else
						fr = (ltype == _int ? lhs->_i : lhs->_f) - (rtype == _int ? rhs->_i : rhs->_f);
					break;
				
				// multiply
				case '*':
					if (ltype == _int && rtype == _int)
						ir = lhs->_i * rhs->_i;
					else
						fr = (ltype == _int ? lhs->_i : lhs->_f) * (rtype == _int ? rhs->_i : rhs->_f);
					break;
				
				// divide
				case '/':
					if (ltype == _int && rtype == _int) {
						// divided by zero
						if (rhs->_i == 0) {
							warnUser(warn, "Divided by zero in a \"/\" operation.", NULL, NULL, NULL, NULL, NULL);
							ir = (int)(lhs->_i / (rhs->_i + 1E-10));
						}
						// general case
						else
							ir = lhs->_i / rhs->_i;
					}
					else {
						// if the RHS is an INT type
						if (rtype == _int) {
							// divided by zero
							if (rhs->_i == 0) {
								warnUser(warn, "Divided by zero in a \"/\" operation.", NULL, NULL, NULL, NULL, NULL);
								fr = lhs->_f / (rhs->_i + 1E-10);
							}
							// general case
							else
								fr = lhs->_f / rhs->_i;
						}
						// else if the RHS is a FLOAT type
						else {
							// divided by zero
							if (rhs->_f == 0) {
								warnUser(warn, "Divided by zero in a \"/\" operation.", NULL, NULL, NULL, NULL, NULL);
								fr = lhs->_f / (rhs->_f + 1E-10);
							}
							// general case
							else
								fr = lhs->_f / rhs->_f;
						}
					}
					break;
			}
			
			// if there's an INT and a FLOAT in both sides -> type warning
			if (ltype != rtype)
				warnUser(warn, "Type warning: The operands\' types of the numeric operation \"%s\" is NOT the same (\'%s\' and \'%s\'), that may loss some precision of the value.", opName, toS(ltype), toS(rtype), NULL, NULL);
			
			// push
			if (ltype == _int && rtype == _int)
				push_e(_int, &ir);
			else
				push_e(_float, &fr);
		}
	}
	
	// binary INT operation: %
	else if (!strcmp(opName, "%")) {
		// the INT value as the calculation result
		int ir;
		
		// get the INT operands for this MOD operation
		int lhsInt, rhsInt;
		if (ltype == _int && rtype == _int) {
			lhsInt = lhs->_i;
			rhsInt = rhs->_i;
		}
		else {
			lhsInt = (lhs->_type == _int ? lhs->_i : (int)(lhs->_f));
			rhsInt = (rhs->_type == _int ? rhs->_i : (int)(rhs->_f));
			warnUser(warn, "The binary operation \"%%\" is an INT operation, but operands are \'%s\' and \'%s\'.", toS(ltype), toS(rtype), NULL, NULL, NULL);
		}
		
		// divided by zero
		if (rhsInt == 0) {
			warnUser(warn, "Divided by zero in a \"%%\" operation.", NULL, NULL, NULL, NULL, NULL);
			ir = _DEFAULT_INT;
		}
		// general case
		else
			ir = lhsInt % rhsInt;
		
		// push
		push_e(_int, &ir);
	}
	
	// unary numeric operation: UMINUS
	else if (!strcmp(opName, "UMINUS")) {
		// type incompatible with numeric operations
		if (isNumericType(rtype) == 0) {
			push_e(_float, NULL);
			warnUser(warn, "The unary operation \"%s\" is a numeric operation, but the operand is \'%s\'.", opName, toS(rtype), NULL, NULL, NULL);
		}
		// no type errors and warnings
		else {
			// INT
			if (rtype == _int) {
				int res = (-(rhs->_i));
				push_e(_int, &res);
			}
			
			// FLOAT
			else {
				double res = (-(rhs->_f));
				push_e(_float, &res);
			}
		}
	}
	
	// binary numeric operations: <, <=, >=, >, which yields BOOLEAN type
	else if (!strcmp(opName, "<") || !strcmp(opName, "<=") || !strcmp(opName, ">=") || !strcmp(opName, ">")) {
		// type incompatible with numeric operations
		if (isNumericType(ltype) == 0 || isNumericType(rtype) == 0) {
			push_e(_boolean, NULL);
			warnUser(warn, "The operands of relational operation \"%s\" must be both numeric, but they are \'%s\' and \'%s\'.", opName, toS(ltype), toS(rtype), NULL, NULL);
		}
		// no type errors and warnings
		else {
			// the result of this relational operation
			int relRes = _DEFAULT_BOOLEAN;
			
			// get the length of the operation's name
			int opNameLen = strlen(opName);
			
			// do the operation
			switch (opName[0]) {
				// < or <=
				case '<':
					if (ltype == _int && rtype == _int)
						relRes = (opNameLen == 1 ? (lhs->_i < rhs->_i) : (lhs->_i <= rhs->_i));
					else if (ltype == _int && rtype == _float)
						relRes = (opNameLen == 1 ? (lhs->_i < rhs->_f) : (lhs->_i <= rhs->_f));
					else if (ltype == _float && rtype == _int)
						relRes = (opNameLen == 1 ? (lhs->_f < rhs->_i) : (lhs->_f <= rhs->_i));
					else
						relRes = (opNameLen == 1 ? (lhs->_f < rhs->_f) : (lhs->_f <= rhs->_f));
					break;
				
				// >= or >
				case '>':
					if (ltype == _int && rtype == _int)
						relRes = (opNameLen == 1 ? (lhs->_i > rhs->_i) : (lhs->_i >= rhs->_i));
					else if (ltype == _int && rtype == _float)
						relRes = (opNameLen == 1 ? (lhs->_i > rhs->_f) : (lhs->_i >= rhs->_f));
					else if (ltype == _float && rtype == _int)
						relRes = (opNameLen == 1 ? (lhs->_f > rhs->_i) : (lhs->_f >= rhs->_i));
					else
						relRes = (opNameLen == 1 ? (lhs->_f > rhs->_f) : (lhs->_f >= rhs->_f));
					break;
			}
			
			// push
			push_e(_boolean, &relRes);
		}
	}
	
	// unary BOOLEAN operation: !
	else if (!strcmp(opName, "!")) {
		// type incompatible with BOOLEAN operations
		if (rtype != _boolean) {
			push_e(_boolean, NULL);
			warnUser(warn, "The unary operation \"%s\" is a BOOLEAN operation, but the operand is \'%s\'.", opName, toS(rtype), NULL, NULL, NULL);
		}
		// no type errors and warnings
		else {
			int res = (!(rhs->_b));
			push_e(_boolean, &res);
		}
	}
	
	// binary BOOLEAN operation: ||, &&
	else if (!strcmp(opName, "||") || !strcmp(opName, "&&")) {
		// type incompatible with BOOLEAN operations
		if (ltype != _boolean || rtype != _boolean) {
			push_e(_boolean, NULL);
			warnUser(warn, "The binary operation \"%s\" is a BOOLEAN operation, but the operands are \'%s\' and \'%s\'.", opName, toS(ltype), toS(rtype), NULL, NULL);
		}
		// no type errors and warnings
		else {
			int res = (opName[0] == '|' ? (lhs->_b || rhs->_b) : (lhs->_b && rhs->_b));
			push_e(_boolean, &res);
		}
	}
	
	// binary BOOLEAN operation: ==, !=
	else if (!strcmp(opName, "==") || !strcmp(opName, "!=")) {
		// type incompatible with == or != operation
		if (ltype != rtype) {
			int b = (opName[0] == '!');
			push_e(_boolean, &b);
			if (opName[0] == '=')
				warnUser(warn, "This \"==\" operation always yields FALSE since the operands are different types (\'%s\' and \'%s\').", toS(ltype), toS(rtype), NULL, NULL, NULL);
			else
				warnUser(warn, "This \"!=\" operation always yields TRUE since the operands are different types (\'%s\' and \'%s\').", toS(ltype), toS(rtype), NULL, NULL, NULL);
		}
		// no type errors and warnings
		else {
			int res = _DEFAULT_BOOLEAN;
			switch (ltype) {
				case _char: res = (opName[0] == '=' ? (lhs->_c == rhs->_c) : (lhs->_c != rhs->_c)); break;
				case _string: res = (opName[0] == '=' ? (strcmp(lhs->_s, rhs->_s) == 0) : (strcmp(lhs->_s, rhs->_s) != 0)); break;
				case _int: res = (opName[0] == '=' ? (lhs->_i == rhs->_i) : (lhs->_i != rhs->_i)); break;
				case _boolean: res = (opName[0] == '=' ? (lhs->_b == rhs->_b) : (lhs->_b != rhs->_b)); break;
				case _float: res = (opName[0] == '=' ? (lhs->_f == rhs->_f) : (lhs->_f != rhs->_f)); break;
			}
			
			// push
			push_e(_boolean, &res);
		}
	}
	
	// free the pop'd values if needs
	free_e(rhs);
	free_e(lhs);
	
	// return as success
	return 1;
}




















