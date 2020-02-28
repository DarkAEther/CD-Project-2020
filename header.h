struct literal {
	char value[20];
	char type[10];
};
struct id {
	char name[32];
	int lineno;
	char value[20];
	char dtype[10];
}; // Identifier token format 
struct scopes{
	struct id identifiers[100];
	int count;
}; // Scope-specific symbol table
struct symtbl{
	struct scopes table[5];
	struct literal literalTable[500];
};

extern struct symtbl symbolTable;
extern int yylineno;
void yyerror(char *s){
	printf("ERROR: \"%s\" on line: %d\n",s, yylineno);
	yyparse();
}
