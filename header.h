struct value{
	int discriminator;
	/*
		0 - DECIMAL
		1 - FLOAT
		2 - CHAR
		3 - STRING
	*/
	union value{
		int integer;
		float floating;
		char character;
		char* string;
	};
};
struct literal{
	int discriminator;
	/*
		0 - DECIMAL
		1 - FLOAT
		2 - CHAR
		3 - STRING
	*/
	union value{
		int integer;
		float floating;
		char character;
		char* string;
	};
	char type[10];
};
struct id {
	char name[32];
	int lineno;
	struct value;
	char dtype[10];
}; // Identifier token format
struct scope_vars{
	struct id identifiers[100];
	int count;
}; // Scope-specific symbol table
struct symtbl{
	struct scope_vars table[5];
	struct literal* literalTable;
	int literal_count;
};

extern struct symtbl symbolTable;
extern int yylineno;

