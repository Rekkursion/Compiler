#ifndef _TNODE
#include "tnode.h"
#define _TNODE
#endif

// a node of an array
typedef struct _anode {
	/* all of the field names start with an 'a', which stands for "array" */
	
	// the data type of this Anode (array)
	DataType _atype;
	
	// the size of this Anode (array)
	int asize;
	
	// for determining if the position of this Anode (array) has been assigned any value or not
	int* hasAssigned;
	
	// the array data according to _atype
	char* _ac;
	char** _as;
	int* _ai;
	int* _ab;
	double* _af;
}Anode;