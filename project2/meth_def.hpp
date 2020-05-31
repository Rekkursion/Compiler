#include <string.h>
#include <stdlib.h>

#ifndef _ITEM_TYPE
#include "item_type.h"
#define _ITEM_TYPE
#endif

#ifndef _DATA_TYPE
#include "data_type.h"
#define _DATA_TYPE
#endif

/* ============================================================ */

// the formal argument of a method definition
typedef struct formal_argu_lnode {
	// the symbol of this formal argument
	char* symbol;
	
	// the data-type of this formal argument
	DataType _type;
	
	// the pointer to the next node
	struct formal_argu_lnode* next;
}FArguLnode;

// the prototype of a method definition
typedef struct method_definition {
	// the return-data-type, _none if there's no return value of this method
	DataType _ret_type;
	
	// the number of arguments
	int argc;
	
	// the head and the tail of the linked-list of formal arguments ("fa" stands for formal argument)
	FArguLnode* fahead;
	FArguLnode* fatail;
	
	// the static array for storing types of formal arguments
	DataType* argTypeArr;
}MethDef;

/* ============================================================ */

// add a new formal argument to the passed method definition
void addFormalArgu(MethDef** meth, const char* symbol, DataType _type) {
	// if the passed method definition is NULL
	if (*meth == NULL) {
		*meth = (MethDef*)malloc(sizeof(MethDef));
		(*meth)->_ret_type = _none;
		(*meth)->argc = 0;
		(*meth)->fahead = NULL;
		(*meth)->fatail = NULL;
	}
	
	// build a new node for the formal argument
	FArguLnode* newNd = (FArguLnode*)malloc(sizeof(FArguLnode));
	newNd->symbol = (char*)malloc(sizeof(char) * (strlen(symbol) + 1));
	newNd->symbol[0] = 0;
	strcpy(newNd->symbol, symbol);
	newNd->_type = _type;
	newNd->next = NULL;
	
	// the first formal argument
	if ((*meth)->fatail == NULL) {
		(*meth)->fahead = newNd;
		(*meth)->fatail = newNd;
	}
	// general case
	else {
		(*meth)->fatail->next = newNd;
		(*meth)->fatail = (*meth)->fatail->next;
	}
	
	// add the argc by 1
	++((*meth)->argc);
}

// set the return type of the passed method definition
void setReturnType(MethDef** meth, DataType _ret_type) {
	// if the passed method definition is NULL
	if (*meth == NULL) {
		*meth = (MethDef*)malloc(sizeof(MethDef));
		(*meth)->_ret_type = _none;
		(*meth)->argc = 0;
		(*meth)->fahead = NULL;
		(*meth)->fatail = NULL;
	}
	
	// set the return type
	(*meth)->_ret_type = _ret_type;
	
	// build a static array for storing all types of formal arguments
	(*meth)->argTypeArr = (DataType*)malloc(sizeof(DataType) * (*meth)->argc);
	FArguLnode* p = (*meth)->fahead;
	int k = 0;
	while(p) {
		(*meth)->argTypeArr[k] = p->_type;
		++k;
		p = p->next;
	}
}

// check the type of a single formal argument
int checkFormalArguType(MethDef* meth, DataType _type, int idx) {
	// index out of range
	if (idx >= meth->argc)
		return -1;
	// compare with the types at a certain index
	return (meth->argTypeArr[idx] == _type) ? 1 : 0;
}

// print the method definition out (for debugging)
void printMeth(MethDef* meth) {
	if (meth == NULL)
		return;
	
	// print the argc out
	printf("|%d|", meth->argc);
	
	// print all of the formal arguments out
	FArguLnode* p = meth->fahead;
	while(p) {
		printf("%s:%d, ", p->symbol, p->_type);
		p = p->next;
	}
	
	// print the return type out
	printf("|%d|\n", meth->_ret_type);
}