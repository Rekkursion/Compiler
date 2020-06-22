#include <string.h>
#include <stdlib.h>

/* ============================================================ */

// a node of a label for generating the java byte code of a loop
// since l_node/Lnode has already been used, we use 'b' instead ('b' stands for 'laBel')
typedef struct b_node {
	int lblNum;
	struct b_node* prev;
}Bnode;

// the top of the label-stack
Bnode* top_b = NULL;

/* ============================================================ */

// push a label into the label-stack
void push_b(int labelNum) {
	// create a new Vnode
	Bnode* nd = (Bnode*)malloc(sizeof(Bnode));
	nd->lblNum = labelNum;
	
	// push the built Bnode into the label-stack
	if (top_b == NULL)
		top_b = nd;
	else {
		nd->prev = top_b;
		top_b = nd;
	}
}

// pop a label from the label-stack
Bnode* pop_b() {
	if (top_b == NULL)
		return NULL;
	
	Bnode* top = top_b;
	top_b = top_b->prev;
	return top;
}

// peek a label (no popping)
Bnode* peek_b() {
	return top_b;
}

// free a Bnode
void free_b(Bnode* nd) {
	if (nd != NULL)
		free(nd);
}

// clear the label-stack
void clear_b() {
	Bnode* p = top_b;
	while(p) {
		top_b = p->prev;
		free_b(p);
		p = top_b;
	}
}

/* ============================================================================================================== */
/* ============================================================================================================== */
/* ============================================================================================================== */
/* ============================================================================================================== */
/* ============================================================================================================== */
/* ============================================================================================================== */

// a node of an iterator of a for-loop
typedef struct it_node {
	char* iterator;
	struct it_node* prev;
}ItNode;

// the top of the it-stack
ItNode* top_it = NULL;

/* ============================================================ */

// push an iterator into the it-stack
void push_it(char* it) {
	// create a new ItNode
	ItNode* nd = (ItNode*)malloc(sizeof(ItNode));
	nd->iterator = (char*)malloc(sizeof(char) * (strlen(it) + 1));
	nd->iterator[0] = 0;
	strcpy(nd->iterator, it);
	
	// push the built ItNode into the it-stack
	if (top_it == NULL)
		top_it = nd;
	else {
		nd->prev = top_it;
		top_it = nd;
	}
}

// pop an iterator from the it-stack
ItNode* pop_it() {
	if (top_it == NULL)
		return NULL;
	
	ItNode* top = top_it;
	top_it = top_it->prev;
	return top;
}

// peek an iterator (no popping)
ItNode* peek_it() {
	return top_it;
}

// free an ItNode
void free_it(ItNode* nd) {
	if (nd != NULL) {
		if (nd->iterator != NULL)
			free(nd->iterator);
		free(nd);
	}
}

// clear the it-stack
void clear_it() {
	ItNode* p = top_it;
	while(p) {
		top_it = p->prev;
		free_it(p);
		p = top_it;
	}
}
