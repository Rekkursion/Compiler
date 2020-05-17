// enumerate of the data types (char: 0, string: 1, int: 2, boolean: 3, float: 4)
typedef enum data_type {
	_char = 0,
	_string = 1,
	_int = 2,
	_boolean = 3,
	_float = 4,
	_id = 5,
	_numeric = 6,
	_none = 2147483647
}DataType;

// a node of a single data, i.e., NOT an array
typedef struct _tnode {
	DataType _type;
	char _c;
	char* _s;
	int _i;
	int _b;
	double _f;
}Tnode;