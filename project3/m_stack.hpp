#include <string.h>
#include <stdlib.h>

/* ============================================================ */

// a node of a invocated method (m stands for method)
typedef struct m_node {
	int argCounter;
	char* name;
	struct m_node* prev;
}Mnode;

// the top of the method-stack
Mnode* top_m = NULL;

/* ============================================================ */

// push a method into the method-stack
void push_m(const char* name) {
	// create a new Vnode
	Mnode* nd = (Mnode*)malloc(sizeof(Mnode));
	nd->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	nd->name[0] = 0;
	nd->argCounter = 0;
	strcpy(nd->name, name);
	nd->prev = NULL;
	
	// push the built Mnode into the method-stack
	if (top_m == NULL)
		top_m = nd;
	else {
		nd->prev = top_m;
		top_m = nd;
	}
}

// pop a method from the method-stack
Mnode* pop_m() {
	if (top_m == NULL)
		return NULL;
	
	Mnode* top = top_m;
	top_m = top_m->prev;
	return top;
}

// peek a method (no popping)
Mnode* peek_m() {
	return top_m;
}

// free a Mnode
void free_m(Mnode* nd) {
	if (nd != NULL) {
		if (nd->name != NULL)
			free(nd->name);
		free(nd);
	}
}

// clear the method-stack
void clear_m() {
	Mnode* p = top_m;
	while(p) {
		top_m = p->prev;
		free_m(p);
		p = top_m;
	}
}