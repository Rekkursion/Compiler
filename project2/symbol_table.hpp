#include <string.h>
#include <stdlib.h>

#ifndef _TNODE
#include "tnode.h"
#define _TNODE
#endif

#ifndef _ANODE
#include "anode.h"
#define _ANODE
#endif

// the size of the hash-table
#define HT_SIZE 1024

/* ============================================================ */

typedef enum item_type {
	_variable = 0,
	_constant = 1,
	_array = 2,
	_none_item = 65536
}ItemType;

// an item (data) of a hash-table node
typedef struct item {
	ItemType itemType;
	char* name;
	Tnode* value;
	
	// 'a' in the field name stands for "array"
	Anode* a_value;
}Item;

// an lnode is a node of a list
typedef struct lnode {
	Item* data;
	struct lnode* next;
}Lnode;

// a slot of a hash-table
typedef struct slot {
	Lnode* lhead;
	Lnode* ltail;
}Slot;

// define the table
typedef Slot* HashTable;

/* ============================================================ */

// do hashing with a string
int hash(const char* str) {
	// the returning value
	int ret = 0;
	
	// scan the string and sum up all ascii values which is mod'd by the table size
	int k;
	for(k = 0; str[k]; ++k) {
		ret += str[k];
		ret %= HT_SIZE;
	}
	
	// return the summed up value
	return ret;
}

/* ============================================================ */

// create a new hash-table
Slot* create() {
	// declare a new hash-table
	Slot* ret = (Slot*)malloc(sizeof(Slot) * HT_SIZE);
	
	// nullify all slots of the hash-table
	int k;
	for (k = 0; k < HT_SIZE; ++k)
		ret[k].lhead = ret[k].ltail = NULL;
	
	// return it
	return ret;
}

// return a certain identifier's item, or null if the identifier is not found
Item* lookup(Slot* table, const char* name) {
	// get the index of the hash-table by doing hashing
	int idx = hash(name);
	
	// linearly search the whole list to find the identifier
	Lnode* ptr = table[idx].lhead;
	while (ptr) {
		// found
		if (!strcmp(ptr->data->name, name))
			return ptr->data;
		// go to the next node
		ptr = ptr->next;
	}
	
	// not found, return null
	return NULL;
}

// insert a new identifier
int insert(Slot* table, const char* name) {
	// get the index of the hash-table by doing hashing
	int idx = hash(name);
	
	// check if the passed identifier is already in the table
	if (lookup(table, name))
		return -1;
	
	// build a to-be-inserted item
	int nameLen = strlen(name);
	Item* data = (Item*)malloc(sizeof(Item));
	data->name = (char*)malloc(sizeof(char) * (nameLen + 1));
	data->itemType = _none_item;
	data->value = NULL;
	data->a_value = NULL;
	strcpy(data->name, name);
	
	// build a list node
	Lnode* lnode = (Lnode*)malloc(sizeof(Lnode));
	lnode->data = data;
	lnode->next = NULL;
	
	// append the node into the corresponding list
	Slot* slot = &(table[idx]);
	// the corresponding list already has values
	if (slot->ltail) {
		slot->ltail->next = lnode;
		slot->ltail = slot->ltail->next;
	}
	// the corresponding list is still empty
	else {
		slot->lhead = lnode;
		slot->ltail = lnode;
	}
	
	// return the index of this identifier of the hash-table
	return idx;
}

// dump all identifiers of a hash-table and return the number of identifiers
int dump(Slot* table) {
	// for counting the number of identifiers
	int counter = 0;
	
	// print the title of the symbol table
	puts("Symbol Table:");
	
	// visit all entries
	int k;
	for(k = 0; k < HT_SIZE; ++k) {
		// visit all nodes of each entry
		Lnode* ptr = table[k].lhead;
		while (ptr) {
			/* print the identifier out */
			printf("|%d|%s|", ptr->data->itemType, ptr->data->name);
			if (ptr->data->value)
				printf("dtype:%d|\n", ptr->data->value->_type);
			else {
				if (ptr->data->a_value)
					printf("size_of_arr:%d|\n", ptr->data->a_value->asize);
				else
					printf("no assigned value|\n");
			}
			
			// count the number of identifiers
			++counter;
			// go to the next node
			ptr = ptr->next;
		}
	}
	
	// return the number of identifiers
	return counter;
}