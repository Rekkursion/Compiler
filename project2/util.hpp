/**
 * some utility functions
 * by B10615031
 */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// convert a string into an integer
int toInt(char* str) {
	int ret = 0;
	sscanf(str, "%d", &ret);
	return ret;
}

// convert a string into a real number
double toReal(char* str) {
	double ret = 0.0L;
	sscanf(str, "%lf", &ret);
	return ret;
}

// return a string that is the passed string but all lowercases are converted into uppercases
char* toUpper(char* str) {
	char* ret;
	ret = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	
	int k;
	for(k = 0; str[k]; ++k)
		ret[k] = toupper(str[k]);
	ret[k] = 0;
	
	return ret;
}

// return a string that is the passed string but all uppercases are converted into lowercases
char* toLower(char* str) {
	char* ret;
	ret = (char*)malloc(sizeof(char) * (strlen(str) + 1));
	
	int k;
	for(k = 0; str[k]; ++k)
		ret[k] = tolower(str[k]);
	ret[k] = 0;
	
	return ret;
}