%option yylineno

%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int scopeDepth[30];
int depth = 0;
int currScope = 0;

struct var {
	char vName[32];
	char lineNums[100];
	char value[20];
	char dtype[10];
};

struct scope {
	struct var variables[50];
	int activeVars;
};

struct literal {
	char value[20];
	char type[10];
};

struct symbolTable {
	struct scope identifierTable[50];
	struct literal literalTable[150];
	int activeLits;
};

struct symbolTable symTable;

void InstallID(char *name, int lineNo, int scope);
void InstallLit(char *value, char *type);
void DisplaySymTable();

%}

letter [a-zA-Z]
digit [0-9]
ws  [ \t\r\f\v]+
identifier (_|{letter})({letter}|{digit}|_){0,31}

%%

{ws} 																										;
"//"(.*)[\n]? 																					;
"/*"([^*]|(\*+[^*/]))*"*/"[\n]? 												;
fn 																											printf("fn\n");
main 																										printf("main\n");
let 																										printf("let\n");
in 																											printf("in\n");
mut 																										printf("mut\n");
for 																										printf("for\n");
if 																											printf("if\n");
else 																										printf("else\n");
while 																									printf("while\n");
\"[^"]*\" 																							{ InstallLit(yytext, "string"); printf("strlit\n"); }
\'[^']\' 																								{ InstallLit(yytext, "char"); printf("charlit\n"); }
({digit})+ 																							{ InstallLit(yytext, "int"); printf("intlit\n"); }
0(x|o|b)({digit})+ 																			{ InstallLit(yytext, "machineint"); printf("machintlit\n"); }
({digit})+"."({digit})+ 																{ InstallLit(yytext, "float"); printf("floatlit\n"); }
true|false 																							{ InstallLit(yytext, "bool"); printf("boollit\n"); }
({digit})+".."({digit})+ 																{ InstallLit(yytext, "range"); printf("rangelit\n"); }
i8|i16|i32|i64|i128 																		printf("inttype\n");
u8|u16|u32|u64|u128 																		printf("uinttype\n");
f32|f64 																								printf("floattype\n");
char 																										printf("chartype\n");
bool 																										printf("booltype\n");
{identifier} 																						{ InstallID(yytext, yylineno, scopeDepth[depth]); printf("id\n"); }
":" 																										printf("colon\n");
";"																											printf("semicolon\n");
"," 																										printf("comma\n");
"(" 																										printf("oparan\n");
")" 																										printf("cparan\n");
"{" 																										{ currScope++; depth++; scopeDepth[depth]=currScope; printf("ocurly\n"); }
"}" 																										{ depth--; printf("ccurly\n"); }
"="|"+="|"-="|"*="|"/="|"%="|"&="|"|="|"^="|"<<="|">>=" printf("opl1\n");
"&&"|"||" 																							printf("opl2\n");
"=="|"!="|"<"|">"|"<="|">=" 														printf("opl3\n");
"|"|"^"|"&" 																						printf("opl4\n");
"+"|"-"|"<<"|">>" 																			printf("opl5\n");
"*"|"/"|"%" 																						printf("opl6\n");
"!"|"~"|"-"|"+"|"*"|"&"|"++"|"--" 											printf("unop\n");

. 																											printf("Invalid token at %d\n",yylineno);

%%

void InstallID(char *name, int lineNo, int scope) {
	int i;
	for (i = 0; i < symTable.identifierTable[scope].activeVars && strcmp(symTable.identifierTable[scope].variables[i].vName, name); i++);

	char strLineNo[10];
	sprintf(strLineNo, "%d", lineNo);

	if (i == symTable.identifierTable[scope].activeVars) {
		int varNo=symTable.identifierTable[scope].activeVars;
		strcpy(symTable.identifierTable[scope].variables[varNo].vName, name);
		strcpy(symTable.identifierTable[scope].variables[varNo].lineNums, strLineNo);
		symTable.identifierTable[scope].activeVars++;
	} else {
		strcat(symTable.identifierTable[scope].variables[i].lineNums, ", ");
		strcat(symTable.identifierTable[scope].variables[i].lineNums, strLineNo);
	}
}

void InstallLit(char *value, char *type) {
	strcpy(symTable.literalTable[symTable.activeLits].value, value);
	strcpy(symTable.literalTable[symTable.activeLits].type, type);
	symTable.activeLits++;
}

void DisplaySymTable() {
	int i, j;
	for (i = 0; i <= currScope; i++)
		for (j = 0; j < symTable.identifierTable[i].activeVars; j++)
			printf("Identifier: %s \t Scope: %d \t Line number(s): %s \n", symTable.identifierTable[i].variables[j].vName, i, symTable.identifierTable[i].variables[j].lineNums);
	for (i = 0; i < symTable.activeLits; i++)
		printf("Literal: %s \t Type: %s \n", symTable.literalTable[i].value, symTable.literalTable[i].type);
}

int yywrap() {
}

int main(int argc, char** argv) {
	extern FILE* yyin, * yyout;
	yyin = fopen(argv[1], "r");
	yyout = fopen("Output.txt", "w");

	yylex();
	DisplaySymTable();

	return 0;
}