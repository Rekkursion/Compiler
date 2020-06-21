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