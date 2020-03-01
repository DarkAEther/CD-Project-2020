
union value{
		int integer;
		double floating;
		char character[3];
		char* string;
};
struct value_wrap{
	int discriminator;
	/*
		0 - DECIMAL
		1 - FLOAT
		2 - CHAR
		3 - STRING
	*/
	union value value;
};
struct literal{
	int discriminator;
	/*
		0 - DECIMAL
		1 - FLOAT
		2 - CHAR
		3 - STRING
	*/
	union value value;
	char type[10];
};
struct id {
	char name[32];
	int lineno;
	struct value_wrap value;
	char type[10];
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

