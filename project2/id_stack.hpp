#include <string.h>
#include <stdlib.h>

// a node of the id-stack for identifiers
typedef struct id_stk_node {
	char* id;
	struct id_stk_node* prev;
}Inode;

// the id_top of the id-stack
Inode* id_top = NULL;

/* function prototypes that are related to the id-stack operations */
void push_id(char*);
char* pop_id();
char* peek_id();
void clear_id_stk(int);
void free_inode(Inode*);

// push an identifier into the id-stack
void push_id(char* id) {
	if (id == NULL)
		return;
	
	Inode* newNd = (Inode*)malloc(sizeof(Inode));
	newNd->id = (char*)malloc(sizeof(char) * (strlen(id) + 1));
	newNd->prev = NULL;
	strcpy(newNd->id, id);
	
	if (id_top == NULL)
		id_top = newNd;
	else {
		newNd->prev = id_top;
		id_top = newNd;
	}
}

// pop an Inode from the id-stack and get the identifier
char* pop_id() {
	if (id_top == NULL)
		return NULL;
	
	char* ret = (char*)malloc(sizeof(strlen(id_top->id) + 1));
	strcpy(ret, id_top->id);
	
	Inode* tmp_inode = id_top;
	id_top = id_top->prev;
	free_inode(tmp_inode);
	
	return ret;
}

// peek an Inode (no popping)
char* peek_id() {
	if (id_top == NULL)
		return NULL;
	return id_top->id;
}

// clear the id-stack
void clear_id_stk(int shouldDump) {
	Inode* p = id_top;
	while(p) {
		if (shouldDump)
			printf("id=|%s|\n", p->id);
		p = p->prev;
		free_inode(id_top);
		id_top = p;
	}
}

// free a single Inode
void free_inode(Inode* inode) {
	if (inode == NULL)
		return;
	if (inode->id != NULL)
		free(inode->id);
	free(inode);
}