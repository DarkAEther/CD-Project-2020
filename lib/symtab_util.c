#ifndef HEADER
#include "../header.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#endif

struct literal* installLiteral(struct symtbl* symbolTable,char *value, char *type) {
	//symbolTable->literalTable = (struct literal*)realloc(symbolTable->literalTable,sizeof(struct literal)*(symbolTable->literal_count+1));
	// if (symbolTable->literalTable == NULL){
    //     symbolTable->literalTable = (struct literal*)malloc(sizeof(struct literal)*100);
    // }
    if (strcmp(type,"DECIMAL") == 0){
		symbolTable->literalTable[symbolTable->literal_count].discriminator = 0;
		symbolTable->literalTable[symbolTable->literal_count].value.integer = atoi(value);
	}else{
		if (strcmp(type,"FLOAT") == 0){
			symbolTable->literalTable[symbolTable->literal_count].discriminator = 1;
			symbolTable->literalTable[symbolTable->literal_count].value.floating = atof(value);
		}else{
			if (strcmp(type,"CHARACTER")==0){
				symbolTable->literalTable[symbolTable->literal_count].discriminator = 2;
				strcpy(symbolTable->literalTable[symbolTable->literal_count].value.character,value);
			}else{
				if (strcmp(type,"STRING")==0){
					symbolTable->literalTable[symbolTable->literal_count].discriminator = 3;
					symbolTable->literalTable[symbolTable->literal_count].value.string = (char*)malloc(sizeof(char)*strlen(value));
					strcpy(symbolTable->literalTable[symbolTable->literal_count].value.string,value);
				}
			}
		}
	}
    
	strcpy(symbolTable->literalTable[symbolTable->literal_count].type, type);
	symbolTable->literal_count++;
	return (symbolTable->literalTable+symbolTable->literal_count-1);
}
void dispLit(struct symtbl* symbolTable){
	int i;
	for (i = 0; i < symbolTable->literal_count; i++){
		if (symbolTable->literalTable[i].discriminator == 0){
			printf("Literal: %-10d \t Type: %-10s Discrim: %-10d\n", symbolTable->literalTable[i].value.integer, symbolTable->literalTable[i].type,symbolTable->literalTable[i].discriminator);fflush(stdout);
		}else{
			if (symbolTable->literalTable[i].discriminator == 1){
				printf("Literal: %-10f \t Type: %-10s Discrim: %-10d\n", symbolTable->literalTable[i].value.floating, symbolTable->literalTable[i].type,symbolTable->literalTable[i].discriminator);fflush(stdout);
			}else{
				if (symbolTable->literalTable[i].discriminator == 2){
					printf("Literal: %-10s \t Type: %-10s Discrim: %-10d\n", symbolTable->literalTable[i].value.character, symbolTable->literalTable[i].type,symbolTable->literalTable[i].discriminator);fflush(stdout);
				}else{
					if (symbolTable->literalTable[i].discriminator == 3){
						printf("Literal: %-10s \t Type: %-10s Discrim: %-10d\n", symbolTable->literalTable[i].value.string, symbolTable->literalTable[i].type,symbolTable->literalTable[i].discriminator);fflush(stdout);
					}
				}
			}
		}
	}
}

struct id* installID(struct symtbl* symbolTable,char *name,int scope,int lno){
	int i;
	int present=1;
	for (i = 0; i < symbolTable->table[scope].count; i++){
		if(strcmp(symbolTable->table[scope].identifiers[i].name, name)==0){
			present=0;
			return symbolTable->table[scope].identifiers + i;
			break;
		}	
	}
	if(i==symbolTable->table[scope].count){
		int x=symbolTable->table[scope].count;
		strcpy(symbolTable->table[scope].identifiers[x].name, name);
		symbolTable->table[scope].identifiers[i].lineno=lno;
		symbolTable->table[scope].count++;
        return symbolTable->table[scope].identifiers + i;
	}
}

void dispST(struct symtbl* symbolTable,int max_depth){
	int i=0;
	FILE* fp = fopen("symbol_table.txt", "w");
	while(i<=max_depth){
		int j=0;
		char* name = "Name";
		char* value = "Value";
		char* dtype = "DataType";
		char* lineno = "LineNo.";
		fprintf(fp, "Symbol Table at depth %d\n",i);
		fprintf(fp, "%-20s\t%-20s\t%-30s\t%-20s\t%-20s\t\n", "Type of Symbol" ,name, value, dtype, lineno);
		while(j<symbolTable->table[i].count){
			if (symbolTable->table[i].identifiers[j].value.discriminator == 0){
				fprintf(fp, "%-20s\t%-20s\t%-30d\t%-20s\t%-20d\t\n","Identifier",symbolTable->table[i].identifiers[j].name,symbolTable->table[i].identifiers[j].value.value.integer,symbolTable->table[i].identifiers[j].type,symbolTable->table[i].identifiers[j].lineno);
				
			}else{
				if (symbolTable->table[i].identifiers[j].value.discriminator == 1){
					fprintf(fp, "%-20s\t%-20s\t%-30f\t%-20s\t%-20d\t\n","Identifier",symbolTable->table[i].identifiers[j].name,symbolTable->table[i].identifiers[j].value.value.floating,symbolTable->table[i].identifiers[j].type,symbolTable->table[i].identifiers[j].lineno);
			
				}else{
					if (symbolTable->table[i].identifiers[j].value.discriminator == 2){
						fprintf(fp, "%-20s\t%-20s\t%-30s\t%-20s\t%-20d\t\n","Identifier",symbolTable->table[i].identifiers[j].name,symbolTable->table[i].identifiers[j].value.value.character,symbolTable->table[i].identifiers[j].type,symbolTable->table[i].identifiers[j].lineno);

					}else{
						if (symbolTable->table[i].identifiers[j].value.discriminator == 3){
							fprintf(fp, "%-20s\t%-20s\t%-30s\t%-20s\t%-20d\t\n","Identifier",symbolTable->table[i].identifiers[j].name,symbolTable->table[i].identifiers[j].value.value.string,symbolTable->table[i].identifiers[j].type,symbolTable->table[i].identifiers[j].lineno);
							
						}
					}
				}
			}
			j++;
		}
		printf("\n");
		i++;
	}
	fclose(fp);
}