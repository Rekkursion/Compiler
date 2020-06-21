#include <string.h>
#include <stdlib.h>

#ifndef _DATA_TYPE
#include "data_type.h"
#define _DATA_TYPE
#endif

#ifndef _ITEM_TYPE
#include "item_type.h"
#define _ITEM_TYPE
#endif

#ifndef _METH_DEF
#include "meth_def.hpp"
#define _METH_DEF
#endif

// the size of the hash-table
#define HT_SIZE 1024

/* ============================================================ */

// an item (data) of a hash-table node
typedef struct item {
	// for checking if this item is a global item or not
	int isGlobalFlag;
	
	// the number for being stored in local variables in jvm
	int localNum;
	
	// the value for a constant item
	int constantVal;
	
	// the type of this item: variable, constant, array, or method
	ItemType itemType;
	
	// the data type of this item if this item is a variable/constant or an array
	DataType dataType;
	
	// the method definition, used only when the item-type is _method
	MethDef* methDef;
	
	// the symbol of this item
	char* name;
}Item;

// an Lnode is a node of a list
typedef struct lnode {
	Item* data;
	struct lnode* next;
}Lnode;

// a slot of a hash-table
typedef struct slot {
	Lnode* lhead;
	Lnode* ltail;
}Slot;

// type-define the table
typedef Slot* HashTable;

/* ============================================================ */

// do hashing with a string:
// sum up ascii-values of all characters of a string, then mod'd it by a fixed number, i.e, the size of a hash-table
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
int insert(Slot* table, const char* name, int isGlobal, int localNum) {
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
	data->methDef = NULL;
	data->isGlobalFlag = isGlobal;
	data->localNum = localNum;
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

// free an item
void free_item(Item* item) {
	// free the name of this item
	if (item->name != NULL)
		free(item->name);
	
	// free itself
	free(item);
}

// delete a whole hash-table
void delete_table(Slot* table) {
	// delete every slot of the hash-table
	int k;
	for(k = 0; k < HT_SIZE; ++k) {
		// delete every node of the linked-list of this slot
		Lnode* lp = table[k].lhead;
		while (lp) {
			// free the item of this node
			free_item(lp->data);
			lp = lp->next;
		}
	}
	
	// free the table
	free(table);
	table = NULL;
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
			// print the identifier out
			if (ptr->data->itemType == _variable)
				printf("|%d|%s|%d|\n", ptr->data->itemType, ptr->data->name, ptr->data->localNum);
			
			// count the number of identifiers
			++counter;
			
			// go to the next node
			ptr = ptr->next;
		}
	}
	
	// return the number of identifiers
	return counter;
}