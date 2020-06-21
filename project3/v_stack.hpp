#include <string.h>
#include <stdlib.h>

/* ============================================================ */

// a node of a variable/constant/array (for simplification, we use a single character 'v' to represent 3 kinds of identifiers)
typedef struct v_node {
	char* name;
	struct v_node* prev;
}Vnode;

// the top of the v-stack
Vnode* top_v = NULL;

/* ============================================================ */

// push a/an var/val/arr into the v-stack
void push_v(const char* name) {
	// create a new Vnode
	Vnode* nd = (Vnode*)malloc(sizeof(Vnode));
	nd->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	nd->name[0] = 0;
	strcpy(nd->name, name);
	nd->prev = NULL;
	
	// push the built Vnode into the v-stack
	if (top_v == NULL)
		top_v = nd;
	else {
		nd->prev = top_v;
		top_v = nd;
	}
}

// pop a/an var/val/arr from the v-stack
Vnode* pop_v() {
	if (top_v == NULL)
		return NULL;
	
	Vnode* top = top_v;
	top_v = top_v->prev;
	return top;
}

// peek a/an var/val/arr (no popping)
Vnode* peek_v() {
	return top_v;
}

// free a Vnode
void free_v(Vnode* nd) {
	if (nd != NULL) {
		if (nd->name != NULL)
			free(nd->name);
		free(nd);
	}
}

// get the bottom Vnode of the v-stack
Vnode* bottom_v() {
	Vnode* p = top_v;
	while(p) {
		if (p->prev == NULL)
			return p;
		top_v = p->prev;
		free_v(p);
		p = top_v;
	}
	return NULL;
}

// clear the v-stack
void clear_v() {
	Vnode* p = top_v;
	while(p) {
		top_v = p->prev;
		free_v(p);
		p = top_v;
	}
}