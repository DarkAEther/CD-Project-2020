%{
#include <stdio.h>
#include <stdlib.h>
#include "header.h" 
#include <string.h>
#include <assert.h>
void yyerror();
int line_num=1;    
extern int scope;

typedef struct node{
  struct node** children;
  int child_count;
  struct value_wrap value;
  int level;
} NODE;


NODE* get_new_node(char* token,int child_nodes,NODE** children){
  NODE* newnode = (NODE*)malloc(sizeof(NODE));
  newnode->value.value.string = (char*)(malloc(sizeof(char)*strlen(token)));
  strcpy(newnode->value.value.string,token);
  newnode->child_count = child_nodes;
  newnode->children = children;
  return newnode;
}
NODE** queue = NULL;
int queue_front = -1;
int queue_rear = -1;
void enqueue(NODE* item){
  if (queue == NULL){
    queue = (NODE**)malloc(100*sizeof(NODE*));
    queue_front = 0;
  }
  queue_rear++;
  printf("QUEUE REAR %d\n",queue_rear);
  queue[queue_rear] = item;
  printf("%s\n",queue[queue_rear]->value.value.string);fflush(stdout);
}
NODE* dequeue(){
  if (queue_front != -1 && queue_front <= queue_rear){
    //not empty
    printf("%d\n",queue_rear);
    NODE* temp = queue[queue_front];
    queue_front++;
    printf("DQ 1\n");fflush(stdout);
    if (queue_front > queue_rear){
      //empty
      free(queue);
      queue = NULL;
      queue_front = -1;
      queue_rear = -1;
    }
    return temp;
  }else{
    return NULL;
  }
}
void display_AST_BFS(NODE* root){
  enqueue(root);
  printf("CAME HERE\n");fflush(stdout);
  NODE* current;int currlvl = 0;
  while (queue_front!= -1){
    current = dequeue();
    assert (current !=NULL);
    printf("ASSERTION VALID\n"); fflush(stdout);
    if (currlvl != current->level){
      printf("LEVEL change to %d\n",current->level);currlvl = current->level;
    }
    printf("CAME HERE TWO\n");fflush(stdout);
   
    printf(" %s ",current->value.value.string);fflush(stdout);
    printf("CAME HERE THREE\n");fflush(stdout);
    for (int i = 0;i < current->child_count;i++){
      current->children[i]->level = currlvl+1;
      if (current->children != NULL){
        enqueue(current->children[i]);
      }
    }
  }
}

%}
%union {
  char *str;
  struct node* node;
}

%token <str> KW_AS
%token <str> KW_BREAK
%token <str> KW_CONST
%token <str> KW_CONTINUE
%token <str> KW_CRATE
%token <str> KW_ELSE
%token <str> KW_ENUM
%token <str> KW_EXTERN
%token <str> KW_FALSE
%token <str> KW_FN
%token <str> KW_FOR
%token <str> KW_IF
%token <str> KW_IMPL
%token <str> KW_IN
%token <str> KW_LET
%token <str> KW_MATCH
%token <str> KW_MOD
%token <str> KW_MOVE
%token <str> KW_MUT
%token <str> KW_PUB
%token <str> KW_REF
%token <str> KW_RETURN
%token <str> KW_SELFVALUE
%token <str> KW_SELFTYPE
%token <str> KW_STATIC
%token <str> KW_STRUCT
%token <str> KW_SUPER
%token <str> KW_TRAIT
%token <str> KW_TRUE
%token <str> KW_TYPE
%token <str> KW_UNSAFE
%token <str> KW_USE
%token <str> KW_WHERE
%token <str> KW_WHILE
%token <str> KW_LOOP
%token <str> CHARACTER
%token <str> STRING
%token <str> RAW_STRING
%token <str> BYTE
%token <str> BYTE_STRING
%token <str> RAW_BYTE_STRING
%token <str> DECIMAL
%token <str> HEX_INT
%token <str> OCTAL_INT
%token <str> BIN_INT
%token <str> FLOAT
%token <str> ARITH
%token <str> BITWISE
%token <str> ASSIGN_OPS
%token <str> ASSIGN
%token <str> RELATIONAL
%token <str> IDENTIFIER
%token <str> STMT_TERMINATOR
%token <str> RANGE
%token <str> ERROR
%token <str> OPEN_BLOCK
%token <str> CLOSE_BLOCK
%token <str> OPEN_PARANTHESIS
%token <str> CLOSE_PARANTHESIS
%token <str> COMMA
%token <str> KW_MAIN
%token <str> KW_PRINTLN
%token <str> EOFI

%type <node> Main Blk Code Eval Exp id Val op Var_dec
%type <node> Out Body If Else For While
%%
start: Main EOFI {printf("\n-------------ACCEPTED----------------\n");}
  | Blk
  | EOFI
  | error ';'
  | error '\n'
  ;
Main: KW_FN KW_MAIN OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_BLOCK Blk CLOSE_BLOCK {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*7);
  kids[0]= $1; kids[1] = $2; kids[2]=$3; kids[3] = $4; kids[4] = $5;kids[5] = $6; kids[6] = $7;
  $$ = get_new_node("MAIN",7,kids);
}
  ;
Blk: Code Blk {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= $1; kids[1] = $2; 
  $$ = get_new_node("BLK",2,kids);
}
  | If Blk
  | While Blk
  | For Blk
  | {$$ = get_new_node("LAMBDA",0,NULL);}
  ;
Code: Eval {$$ = $1;}
  | Out {$$ = $1;}
  | Exp {$$ = $1;}
  | Var_dec {$$ = $1;}
  ;
Eval: IDENTIFIER ASSIGN Exp STMT_TERMINATOR
  ;
Exp: Val op Exp
  | OPEN_PARANTHESIS Exp CLOSE_PARANTHESIS {$$ = $2;}
  | Val {$$ = $1;}
  ;
id: IDENTIFIER {$$= get_new_node(yylval.str,0,NULL);}
  ;
Val: IDENTIFIER {$$ = get_new_node(yylval.str,0, NULL);}
  | STRING {$$ =get_new_node(yylval.str,0,NULL);}
  | DECIMAL {$$ = get_new_node(yylval.str,0,NULL);}
  | FLOAT {$$ = get_new_node(yylval.str,0,NULL);}
  | CHARACTER {$$ = get_new_node(yylval.str,0,NULL);}
  ;
op: ARITH
  | BITWISE
  | RELATIONAL
  ;
Var_dec: KW_LET id ASSIGN Exp STMT_TERMINATOR {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*5);
  kids[0]= $1; kids[1] = $2; kids[2]=$3; kids[3] = $4; kids[4] = $5;
  $$ = get_new_node("VARDEC",5,kids);
  display_AST_BFS($$);
  for (int j = 0; j < symbolTable.table[scope].count; j++){
    if (strcmp($2->value.value.string,symbolTable.table[scope].identifiers[j].name) == 0){
      for (int k = 0; k < symbolTable.literal_count;k++){
        if (symbolTable.literalTable[k].discriminator == 0){
          if(symbolTable.literalTable[k].value.integer == atoi($4->value.value.string)){
            symbolTable.table[scope].identifiers[j].value.discriminator = 0;
            strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
            symbolTable.table[scope].identifiers[j].value.value.integer= atoi($4->value.value.string);
          }
        }else{
          if (symbolTable.literalTable[k].discriminator == 1){
            
            if(symbolTable.literalTable[k].value.floating == atof($4->value.value.string)){
              symbolTable.table[scope].identifiers[j].value.discriminator = 1;
              strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
              symbolTable.table[scope].identifiers[j].value.value.floating= atof($4->value.value.string);
            }
          }else{
            if (symbolTable.literalTable[k].discriminator == 2){
              if(strcmp(symbolTable.literalTable[k].value.character,$4->value.value.string)==0){
                symbolTable.table[scope].identifiers[j].value.discriminator = 2;
                strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
                strcpy(symbolTable.table[scope].identifiers[j].value.value.character,$4->value.value.string);
                
              }
            }else{
              if (symbolTable.literalTable[k].discriminator == 3){
                if(strcmp(symbolTable.literalTable[k].value.string, $4->value.value.string)==0){
                  symbolTable.table[scope].identifiers[j].value.discriminator = 3;
                  strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
                  symbolTable.table[scope].identifiers[j].value.value.string = (char*)malloc(sizeof(char)*strlen($4->value.value.string));
                  strcpy(symbolTable.table[scope].identifiers[j].value.value.string,$4->value.value.string);
                }
              }
            }
          }
        }
      }
    }
  }
}
  ;
Out: KW_PRINTLN OPEN_PARANTHESIS Body CLOSE_PARANTHESIS STMT_TERMINATOR
  ;
Body: STRING
  | STRING COMMA Val
  ;
If: KW_IF Exp OPEN_BLOCK Blk CLOSE_BLOCK Else
  ; 
Else: KW_ELSE OPEN_BLOCK Blk CLOSE_BLOCK
  ;
While: KW_WHILE Exp OPEN_BLOCK Blk CLOSE_BLOCK 
  ;
For: KW_FOR IDENTIFIER KW_IN DECIMAL RANGE DECIMAL OPEN_BLOCK Blk CLOSE_BLOCK 
  ;
%%

int main(){
        symbolTable.literal_count = 0;
        symbolTable.literalTable = (struct literal*)malloc(sizeof(struct literal));
        yyparse();
        return 0;
}
void yyerror(char *s){
	printf("ERROR: \"%s\" on line: %d\n",s, yylineno);
  yyparse();
}
