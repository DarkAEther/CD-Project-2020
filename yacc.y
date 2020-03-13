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
NODE* mod_node(NODE* original,int child_nodes,NODE** children){
  original->child_count = child_nodes;
  original->children = children;
  return original;
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
  //printf("QUEUE REAR %d\n",queue_rear);
  queue[queue_rear] = item;
  //printf("%s\n",queue[queue_rear]->value.value.string);fflush(stdout);
}
NODE* dequeue(){
  if (queue_front != -1 && queue_front <= queue_rear){
    //not empty
    //printf("%d\n",queue_rear);
    NODE* temp = queue[queue_front];
    queue_front++;
    //printf("DQ 1\n");fflush(stdout);
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
  //printf("CAME HERE\n");fflush(stdout);
  NODE* current;int currlvl = 0;
  while (queue_front!= -1){
    current = dequeue();
    assert (current !=NULL);
    if (currlvl != current->level){
      printf("\n");
      currlvl = current->level;
    }
    //printf("CAME HERE TWO\n");fflush(stdout);
   
    printf(" %s ",current->value.value.string);fflush(stdout);
    //printf("Child count %d\n",current->child_count);fflush(stdout);
    for (int i = 0;i < current->child_count;i++){
      //printf("I->%d\n",i);fflush(stdout);
      current->children[i]->level = currlvl+1;
      enqueue(current->children[i]);
    }
  }
  printf("\n");
}

%}
%union {
  char *str;
  struct node* node;
}

%token <node> KW_AS
%token <node> KW_BREAK
%token <node> KW_CONST
%token <node> KW_CONTINUE
%token <node> KW_CRATE
%token <node> KW_ELSE
%token <node> KW_ENUM
%token <node> KW_EXTERN
%token <node> KW_FALSE
%token <node> KW_FN
%token <node> KW_FOR
%token <node> KW_IF
%token <node> KW_IMPL
%token <node> KW_IN
%token <node> KW_LET
%token <node> KW_MATCH
%token <node> KW_MOD
%token <node> KW_MOVE
%token <node> KW_MUT
%token <node> KW_PUB
%token <node> KW_REF
%token <node> KW_RETURN
%token <node> KW_SELFVALUE
%token <node> KW_SELFTYPE
%token <node> KW_STATIC
%token <node> KW_STRUCT
%token <node> KW_SUPER
%token <node> KW_TRAIT
%token <node> KW_TRUE
%token <node> KW_TYPE
%token <node> KW_UNSAFE
%token <node> KW_USE
%token <node> KW_WHERE
%token <node> KW_WHILE
%token <node> KW_LOOP
%token <node> CHARACTER
%token <node> STRING
%token <node> RAW_STRING
%token <node> BYTE
%token <node> BYTE_STRING
%token <node> RAW_BYTE_STRING
%token <node> DECIMAL
%token <node> HEX_INT
%token <node> OCTAL_INT
%token <node> BIN_INT
%token <node> FLOAT
%token <node> ARITH
%token <node> BITWISE
%token <node> ASSIGN_OPS
%token <node> ASSIGN
%token <node> RELATIONAL
%token <node> IDENTIFIER
%token <node> STMT_TERMINATOR
%token <node> RANGE
%token <node> ERROR
%token <node> OPEN_BLOCK
%token <node> CLOSE_BLOCK
%token <node> OPEN_PARANTHESIS
%token <node> CLOSE_PARANTHESIS
%token <node> COMMA
%token <node> KW_MAIN
%token <node> KW_PRINTLN
%token <node> EOFI

%type <node> Main Blk Code Eval Exp id Val op Var_dec
%type <node> Out Body If Else For While
%%
start: Main EOFI {printf("\n-------------ACCEPTED----------------\n"); }
  | Blk
  | EOFI
  | error ';'
  | error '\n'
  ;
Main: KW_FN KW_MAIN OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_BLOCK Blk CLOSE_BLOCK {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*7);
  kids[0]= get_new_node("FN",0,NULL); kids[1] = get_new_node("MAIN",0,NULL); kids[2]=get_new_node("(",0,NULL); kids[3] = get_new_node(")",0,NULL); kids[5] = $6;kids[4] = get_new_node("{",0,NULL); kids[6] = get_new_node("}",0,NULL);
  $$ = get_new_node("MAIN",7,kids);
  display_AST_BFS($$);
}
  ;
Blk: Code Blk {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= $1; kids[1] = $2; 
  $$ = get_new_node("BLK",2,kids);
}
  | If Blk {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= $1; kids[1] = $2; 
  $$ = get_new_node("BLK",2,kids);
}
  | While Blk {$$ = get_new_node("LAMBDA",0,NULL);}
  | For Blk {$$ = get_new_node("LAMBDA",0,NULL);}
  | {$$ = get_new_node("LAMBDA",0,NULL);}
  ;
Code: Eval {$$ = $1;}
  | Out {$$ = $1;}
  | Exp {$$ = $1;}
  | Var_dec {$$ = $1;}
  ;
Eval: IDENTIFIER ASSIGN Exp STMT_TERMINATOR
  ;
Exp: Val op Exp {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0] = $1; kids[1] = $3; 
  $$ = mod_node($2,2,kids);
}
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
op: ARITH {$$ = get_new_node(yylval.str,0, NULL);}
  | BITWISE {$$ = get_new_node(yylval.str,0, NULL);}
  | RELATIONAL {$$ = get_new_node(yylval.str,0, NULL);}
  ;
Var_dec: KW_LET id ASSIGN Exp STMT_TERMINATOR {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*3);
  NODE** assign_kids = (NODE**)malloc(sizeof(NODE*)*2);
  assign_kids[0] = $2; assign_kids[1] = $4;
  kids[0]= get_new_node("LET",0,NULL); kids[1]=get_new_node("=",2,assign_kids); kids[2] = get_new_node(";",0,NULL);
  $$ = get_new_node("VARDEC",3,kids);
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
If: KW_IF Exp OPEN_BLOCK Blk CLOSE_BLOCK Else {
    NODE** kids = (NODE**)malloc(sizeof(NODE*)*5);
    kids[0]= $2; kids[1]=get_new_node("{",0,NULL);kids[2] = $4; kids[3]=get_new_node("}",0,NULL);kids[4] = $5;
    $$ = get_new_node("IF",5,kids);
}
  ; 
Else: KW_ELSE OPEN_BLOCK Blk CLOSE_BLOCK {
    NODE** kids = (NODE**)malloc(sizeof(NODE*)*3);
    kids[0]= get_new_node("{",0,NULL); kids[1]=$3; kids[2] =get_new_node("}",0,NULL);
    $$ = get_new_node("ELSE",3,kids);
}
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
