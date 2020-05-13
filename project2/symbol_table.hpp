#include <string.h>
#include <stdlib.h>

// the size of the hash-table
#define HT_SIZE 1024

/* ============================================================ */

// the item-types
typedef enum item_type {
	// an object
	ItemType_OBJECT = 0,
	
	// a function definition
	ItemType_DEF = 1,
	
	// a constant of a character
	ItemType_VAL_C = 2,
	// a variable of a character
	ItemType_VAR_C = 3,
	
	// a constant of a string
	ItemType_VAL_S = 4,
	// a variable of a string
	ItemType_VAR_S = 5,
	
	// a constant of an integer
	ItemType_VAL_I = 6,
	// a variable of an integer
	ItemType_VAR_I = 7,
	
	// a constant of a boolean
	ItemType_VAL_B = 8,
	// a variable of a boolean
	ItemType_VAR_B = 9,
	
	// a constant of a float
	ItemType_VAL_F = 10,
	// a variable of a float
	ItemType_VAR_F = 11
}ItemType;

// an item (data) of a node
typedef struct item {
	char* name;
	ItemType itemType;
	void* value;
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

// check if an identifier is a constant or not
int isConstant(Item* item) {
	if (item == NULL)
		return 0;
	return item->itemType == 2 ||
		item->itemType == 4 ||
		item->itemType == 6 ||
		item->itemType == 8 ||
		item->itemType == 10;
}

// check if an identifier is a variable or not
int isVariable(Item* item) {
	if (item == NULL)
		return 0;
	return item->itemType == 3 ||
		item->itemType == 5 ||
		item->itemType == 7 ||
		item->itemType == 9 ||
		item->itemType == 11;
}

// check if an identifier is an integer constant/variable or not
int isInteger(Item* item) {
	if (item == NULL)
		return 0;
	return item->itemType == 6 || item->itemType == 7;
}

// check if an identifier is a float constant/variable or not
int isFloat(Item* item) {
	if (item == NULL)
		return 0;
	return item->itemType == 10 || item->itemType == 11;
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
	data->value = NULL;
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
			// print the identifier out
			printf("%s\n", ptr->data->name);
			
			// count the number of identifiers
			++counter;
			// go to the next node
			ptr = ptr->next;
		}
	}
	
	// return the number of identifiers
	return counter;
}