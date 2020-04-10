
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
	struct id identifiers[200];
	int count;
}; // Scope-specific symbol table
struct symtbl{
	struct scope_vars table[5];
	struct literal* literalTable;
	int literal_count;
};

extern struct symtbl symbolTable;
extern int yylineno;

enum TYPE {ID, STR, DEC, FLT, CHAR, BOOL, OP,KW,REL,NUM,VAL};

union PTR
  {
	  struct id* st_ptr;
	  struct literal* lt_ptr;
  };

typedef struct node{
  struct node** children;
  int child_count;
  struct value_wrap value;
  int level;
  enum TYPE type;
  enum TYPE core_type;
  union PTR PTR;
  struct node* result;
} NODE;

NODE* get_new_node(char* token,int child_nodes,NODE** children,enum TYPE type);
char* get_new_temp(int count);
char* get_new_label(int count);
void push_value(NODE* value);

#define HEADER 1