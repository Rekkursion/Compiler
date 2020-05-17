#include <string.h>
#include <stdlib.h>

#ifndef _TNODE
#include "tnode.h"
#define _TNODE
#endif

char* _literal_char = "char";
char* _literal_string = "string";
char* _literal_int = "int";
char* _literal_boolean = "boolean";
char* _literal_float = "float";
char* _literal_numeric = "numeric";
char* _literal_none = "unknown_type";

// get the literal string of a certain data type, e.g., type _int returns "int", type _char returns "char"
char* getLiteralDataTypeName(DataType _type) {
	switch (_type) {
		// CHAR
		case _char: return _literal_char;
		
		// STRING
		case _string: return _literal_string;
		
		// INT
		case _int: return _literal_int;
		
		// BOOLEAN
		case _boolean: return _literal_boolean;
		
		// FLOAT
		case _float: return _literal_float;
		
		// numeric (INT or FLOAT)
		case _numeric: return _literal_numeric;
	}
	
	// the unknown type
	return _literal_none;
}

// a node of a stack for Tnode's
typedef struct stk_node {
	Tnode* nd;
	struct stk_node* prev;
}Snode;

// the top of the stack
Snode* top = NULL;

/* function prototypes that are related to the stack operations */
void push_stk(Tnode*);
Tnode* pop_stk();
Tnode* peek_stk();
void clear_stk(int);
void free_snode(Snode*);
Tnode* copyTnode(Tnode*);

// push a Tnode into the stack
void push_stk(Tnode* nd) {
	if (nd == NULL)
		return;
	
	Tnode* newNd = copyTnode(nd);
	
	Snode* newSNd = (Snode*)malloc(sizeof(Snode));
	newSNd->nd = newNd;
	newSNd->prev = NULL;
	
	if (top == NULL)
		top = newSNd;
	else {
		newSNd->prev = top;
		top = newSNd;
	}
}

// pop a Tnode from the stack
Tnode* pop_stk() {
	if (top == NULL)
		return NULL;
	Tnode* ret = copyTnode(top->nd);
	Snode* p = top;
	top = top->prev;
	free_snode(p);
	return ret;
}

// peek a Tnode (no popping)
Tnode* peek_stk() {
	if (top == NULL)
		return NULL;
	return top->nd;
}

// clear the stack
void clear_stk(int shouldDump) {
	Snode* p = top;
	while(p) {
		if (shouldDump) {
			switch (p->nd->_type) {
				case _char: printf("|c|%c|\n", p->nd->_c); break;
				case _string: printf("|s|%s|\n", p->nd->_s); break;
				case _int: printf("|i|%d|\n", p->nd->_i); break;
				case _boolean: printf("|b|%d|\n", p->nd->_b); break;
				case _float: printf("|f|%lf|\n", p->nd->_f); break;
			}
		}
		p = p->prev;
		free_snode(top);
		top = p;
	}
}

// free a single Snode
void free_snode(Snode* snode) {
	if (snode == NULL)
		return;
	if (snode->nd != NULL) {
		if (snode->nd->_s != NULL)
			free(snode->nd->_s);
		free(snode->nd);
	}
	free(snode);
}

// copy a Tnode
Tnode* copyTnode(Tnode* nd) {
	Tnode* newNd = (Tnode*)malloc(sizeof(Tnode));
	newNd->_type = nd->_type;
	newNd->_s = NULL;
	switch (nd->_type) {
		case _char: newNd->_c = nd->_c; break;
		case _string:
			newNd->_s = (char*)malloc(sizeof(char) * (strlen(nd->_s) + 1));
			strcpy(newNd->_s, nd->_s);
			break;
		case _int: newNd->_i = nd->_i; break;
		case _boolean: newNd->_b = nd->_b; break;
		case _float: newNd->_f = nd->_f; break;
	}
	return newNd;
}