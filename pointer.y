%{
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "./lib/queue.h"
#include "./lib/lookup.h"
#include "./lib/quadruple.h"
#include "./lib/symtab_util.h"
#include "./lib/optimizer.h"
#include <string.h>
#include <assert.h>
void yyerror();
int line_num=1;  
int error_count = 0;  
extern int scope;
extern int max_depth;
NODE* st[100];
QUEUE queue;
int top;
int temp_count;
int label_count;
QUAD* head_quad;

char * temp_value;
char* CUSTYPES[] ={"ID\0","STRING\0","DECIMAL\0","FLOAT\0","CHARACTER\0","BOOLEAN\0","OP\0","KW\0"};

NODE* get_new_node(char* token,int child_nodes,NODE** children,enum TYPE type){
  NODE* newnode = (NODE*)malloc(sizeof(NODE));
  newnode->value.value.string = (char*)(malloc(sizeof(char)*strlen(token)+1));
  strcpy(newnode->value.value.string,token);
  newnode->child_count = child_nodes;
  newnode->children = children;
  newnode->type = type;
  return newnode;
}

NODE* mod_node(NODE* original,int child_nodes,NODE** children){
  original->child_count = child_nodes;
  original->children = children;
  return original;
}

void display_AST_BFS(NODE* root){
  if (error_count > 0){
    printf("Semantic Errors, Cannot build parse tree\n");
    return;
  }
  enqueue(&queue,root);
  NODE* current;int currlvl = 0;
  while (queue.queue_front!= -1){
    current = dequeue(&queue);
    assert (current !=NULL);
    if (currlvl != current->level){
      printf("\n");
      currlvl = current->level;
    }
    printf(" %s ",current->value.value.string);fflush(stdout);
    for (int i = 0;i < current->child_count;i++){
      current->children[i]->level = currlvl+1;
      enqueue(&queue,current->children[i]);
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

%type <node> Main Blk Code Eval Exp id Val op Var_dec equals
%type <node> Out Body If Else For While
%%
start: Main EOFI {printf("\n-------------DONE----------------\n"); }
  | Blk
  | EOFI
  | error ';'
  | error '\n'
  ;
Main: KW_FN KW_MAIN OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_BLOCK Blk CLOSE_BLOCK {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*7);
  kids[0]= get_new_node("FN",0,NULL,KW); kids[1] = get_new_node("MAIN",0,NULL,KW); kids[2]=get_new_node("(",0,NULL,KW); kids[3] = get_new_node(")",0,NULL,KW); kids[5] = $6;kids[4] = get_new_node("{",0,NULL,KW); kids[6] = get_new_node("}",0,NULL,KW);
  $$ = get_new_node("MAIN",7,kids,KW);
  //display_AST_BFS($$);
}
  ;
Blk: Code Blk {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= $1; kids[1] = $2; 
  $$ = get_new_node("BLK",2,kids,KW);
}
  | If Blk {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= $1; kids[1] = $2; 
  $$ = get_new_node("BLK",2,kids,KW);
}
  | While Blk { NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= $1; kids[1] = $2; 
  $$ = get_new_node("BLK",2,kids,KW);}
  | For Blk {NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0]= $1; kids[1] = $2; 
  $$ = get_new_node("BLK",2,kids,KW);}
  | {$$ = get_new_node("LAMBDA",0,NULL,KW);}
  ;
Code: Eval {$$ = $1;}
  | Out {$$ = $1;}
  | Exp {$$ = $1;}
  | Var_dec {$$ = $1;}
  ;
Eval: Val equals Exp STMT_TERMINATOR{
  if ($1->type != ID){
    printf("ERROR - LHS must be an identifier. Given %s Line no. %d\n",CUSTYPES[$1->type],yylineno);
    error_count++;
    $$ = get_new_node("ERROR",0,NULL,KW);
  }else{
    NODE ** kids = (NODE**)malloc(sizeof(NODE*)*2);
    NODE** assign_kids = (NODE**)malloc(sizeof(NODE*)*2);
    assign_kids[0] = $1; assign_kids[1] = $3;
    kids[0] = get_new_node("ASSIGN",2,assign_kids,KW); kids[1] = get_new_node(";",0,NULL,KW);
    $$ = get_new_node("ASSIGNMENT",2,kids,KW);
    //Write changes to ST
    struct id* record = lookup_ST_declared(&symbolTable,$1->value.value.string,scope);
    if (record != NULL){
        //printf("ASSIGN TYPE %s #%s#\n",record->name,record->type);
        if (strcmp(record->type,"") != 0){
                //variable is declared
                //strcpy(record->type,CUSTYPES[$3->type]);
                if ($3->type == DEC){
                  $1->type = DEC;
                  record->value.discriminator = 0;
                  strcpy(record->type,"DECIMAL");
                }
                if ($3->type == FLT){
                  $1->type = FLT;
                  record->value.discriminator = 1;
                  strcpy(record->type,"FLOAT");
                }
                if ($3->type == CHAR){
                  $1->type = CHAR;
                  record->value.discriminator = 2;
                  strcpy(record->type,"CHARACTER");
                }
                if ($3->type == STR){
                  $1->type = STR;
                  record->value.discriminator = 3;
                  strcpy(record->type,"STRING");
                }
                $1->PTR.st_ptr = record;
          }
          
    }else{
      printf("ERROR - Variable use before declaration %s on line %d\n",$1->value.value.string,yylineno);
      error_count++;
    } 
  }
  if ($3->core_type == VAL){
    struct literal* assigned = lookup_LT(&symbolTable,$3->value.value.string);
    if (assigned != NULL){
      $3->PTR.lt_ptr = assigned;
    }
  }
  if ($3->core_type == ID){
    struct id* record = lookup_ST_declared(&symbolTable,$3->value.value.string,scope);
    if (record != NULL){
      $3->PTR.st_ptr = record;
    }
  }
  codegen_assign(scope,st,&top,&head_quad);
}
  ;
Exp: Val op Exp {
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0] = $1; kids[1] = $3; 
  $$ = mod_node($2,2,kids);
  if ($2->type == REL){
      $$->type = BOOL;
  }
  if ($1->type == ID){
    struct id* record = lookup_ST_declared(&symbolTable,$1->value.value.string,scope);
    if (record != NULL){
      if (strcmp(record->type,"") != 0){
            //declared var
            if (record->value.discriminator == 0){
              $1->type = DEC;
            }
            if (record->value.discriminator == 1){
              $1->type = FLT;
            }
            if (record->value.discriminator == 2){
              $1->type = CHAR;
            }
            if (record->value.discriminator == 3){
              $1->type = STR;
            }
      }
       $1->PTR.st_ptr = record;
    }
  }else{
    //literal
    struct literal * lit = lookup_LT(&symbolTable,$1->value.value.string);
    if (lit!=NULL){
      //literal found
      //printf("LITERAL 1 FOUND %d\n",lit->value.integer);
      $1->PTR.lt_ptr = lit;
      //printf("DISCRIMINATOR 1 %d\n",lit->discriminator);
      if (lit->discriminator == 0){
        $1->type = DEC;
      }
      if (lit->discriminator == 1){
        $1->type = FLT;
      }
      if (lit->discriminator == 2){
        $1->type = CHAR;
      }
      if (lit->discriminator == 3){
        $1->type = STR;
      }
    }
  }
  if ($3->type == ID){
    struct id* record = lookup_ST_declared(&symbolTable,$3->value.value.string,scope);
    if (record != NULL){
        // The variable has been 
        //printf("TYPE 3 #%s#\n",record->type);
        if (strcmp(record->type,"") != 0){
            //declared var
            if (record->value.discriminator == 0){
              $3->type = DEC;
            }
            if (record->value.discriminator == 1){
              $3->type = FLT;
            }
            if (record->value.discriminator == 2){
              $3->type = CHAR;
            }
            if (record->value.discriminator == 3){
              $3->type = STR;
            }
        }
        $3->PTR.st_ptr = record;
      }
  }else{
    struct literal * lit = lookup_LT(&symbolTable,$3->value.value.string);
    if (lit!=NULL){
      //literal found
      //printf("LITERAL 3 FOUND %d\n",lit->value.integer);
      $3->PTR.lt_ptr = lit;
      //printf("DISCRIMINATOR 3 %d\n",lit->discriminator);
      if (lit->discriminator == 0){
        $3->type = DEC;
      }
      if (lit->discriminator  == 1){
        $3->type = FLT;
      }
      if (lit->discriminator  == 2){
        $3->type = CHAR;
      }
      if (lit->discriminator  == 3){
        $3->type = STR;
      }
    }
  }
  if ($2->type == NUM){
    int set = 0;
    if ($1->type == ID){
        printf("ERROR - Variable use before declaration - %s Line No - %d\n",$1->value.value.string,yylineno);
        error_count++;
    }
    if ($3->type == ID){
        printf("ERROR - Variable use before declaration - %s Line No - %d\n",$3->value.value.string,yylineno);
        error_count++;
    }
    if ($1->type == DEC && $3->type == FLT){
        $$->type = FLT;set = 1;
    }
    if ($1->type == FLT && $3->type == DEC){
        $$->type = FLT;set = 1;
    }
    if ($1->type == DEC && $3->type == DEC){
      $$->type = DEC;set=1;
    }
    if ($1->type == FLT && $3->type == FLT){
      $$->type = FLT;set=1;
    }
    if (set!= 1){
      error_count++;
      printf("ERROR-  CANNOT PERFORM %s operation on %s and %s Line No- %d\n",$2->value.value.string, CUSTYPES[$1->type], CUSTYPES[$3->type], yylineno);
    }
  }
  codegen(st,&top,&temp_count,yylineno,&head_quad,scope,&symbolTable);
}
  | OPEN_PARANTHESIS Exp CLOSE_PARANTHESIS {$$ = $2;}
  | Val { $$ = $1;}
  ;
id: IDENTIFIER {$$= get_new_node(yylval.str,0,NULL,ID);$$->core_type = ID;push_value($$);$$->PTR.st_ptr = lookup_ST(&symbolTable,yylval.str,scope);}
  ;
Val: IDENTIFIER {$$ = get_new_node(yylval.str,0, NULL,ID);$$->core_type = ID;push_value($$);$$->PTR.st_ptr = lookup_ST(&symbolTable,yylval.str,scope);}
  | STRING {$$ =get_new_node(yylval.str,0,NULL,STR);$$->core_type = VAL;push_value($$);$$->PTR.lt_ptr = lookup_LT(&symbolTable,yylval.str);}
  | DECIMAL {$$ = get_new_node(yylval.str,0,NULL,DEC);$$->core_type = VAL;push_value($$);$$->PTR.lt_ptr = lookup_LT(&symbolTable,yylval.str);}
  | FLOAT {$$ = get_new_node(yylval.str,0,NULL,FLT);$$->core_type = VAL;push_value($$);$$->PTR.lt_ptr = lookup_LT(&symbolTable,yylval.str);}
  | CHARACTER {$$ = get_new_node(yylval.str,0,NULL,CHAR);$$->core_type = VAL;push_value($$);$$->PTR.lt_ptr = lookup_LT(&symbolTable,yylval.str);}
  ;
op: ARITH {$$ = get_new_node(yylval.str,0, NULL,NUM);$$->core_type = OP;push_value($$);}
  | BITWISE {$$ = get_new_node(yylval.str,0, NULL, NUM);$$->core_type = OP;push_value($$);}
  | RELATIONAL {$$ = get_new_node(yylval.str,0, NULL,REL);$$->core_type = OP;push_value($$);}
  ;
equals: ASSIGN {$$ = get_new_node(yylval.str,0, NULL,NUM);$$->core_type = OP;push_value($$);}
  ;
Var_dec: KW_LET id equals Exp STMT_TERMINATOR {
  
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*3);
  NODE** assign_kids = (NODE**)malloc(sizeof(NODE*)*2);
  assign_kids[0] = $2; assign_kids[1] = $4;
  kids[0]= get_new_node("LET",0,NULL,KW); kids[1]=get_new_node("=",2,assign_kids,KW); kids[2] = get_new_node(";",0,NULL,KW);
  $$ = get_new_node("VARDEC",3,kids,KW);
  
  if ($4->core_type == ID){
        $2->type = $4->type;
        //write changes to ST
        struct id * record = lookup_ST(&symbolTable,$2->value.value.string,scope);
        if (record != NULL){
               if ($2->type == DEC){
                    strcpy(record->type, "DECIMAL");
                    record->value.discriminator = 0;
                }
                if ($2->type == FLT){
                    strcpy(record->type, "FLOAT");
                    record-> value.discriminator = 1;
                }
                if ($2->type == CHAR){
                  strcpy(record->type, "CHARACTER");
                  record->value.discriminator = 2;
                }
                if ($2->type == STR){
                  strcpy(record->type, "STRING");
                  record->value.discriminator = 3;
                }
               $2->PTR.st_ptr = record;
        }
  }else{
    
  int literal_assign = 0;
  struct literal * assigned = NULL;
  struct id* record = lookup_ST(&symbolTable,$2->value.value.string,scope);
  $2->PTR.st_ptr = record;
  if (record != NULL){
    //printf("Record found\n");fflush(stdout);
      for (int k = 0; k < symbolTable.literal_count;k++){
        if (symbolTable.literalTable[k].discriminator == 0){
          if(symbolTable.literalTable[k].value.integer == atoi($4->value.value.string)){
            record->value.discriminator = 0;
            literal_assign = 1;
            assigned = symbolTable.literalTable +k;
            $2->type = DEC;
            strcpy(record->type, symbolTable.literalTable[k].type);
            record->value.value.integer= atoi($4->value.value.string);
            break;
          }
        }else{
          if (symbolTable.literalTable[k].discriminator == 1){
            
            if(symbolTable.literalTable[k].value.floating == atof($4->value.value.string)){
              record->value.discriminator = 1;
              literal_assign = 1;
              assigned = symbolTable.literalTable+k;
              $2->type = FLT;
              strcpy(record->type, symbolTable.literalTable[k].type);
              record->value.value.floating= atof($4->value.value.string);
              break;
            }
          }else{
            if (symbolTable.literalTable[k].discriminator == 2){
              if(strcmp(symbolTable.literalTable[k].value.character,$4->value.value.string)==0){
                record->value.discriminator = 2;
                literal_assign= 1;
                assigned = symbolTable.literalTable +k;
                $2->type = CHAR;
                strcpy(record->type, symbolTable.literalTable[k].type);
                strcpy(record->value.value.character,$4->value.value.string);
                break;
              }
            }else{
              if (symbolTable.literalTable[k].discriminator == 3){
                if(strcmp(symbolTable.literalTable[k].value.string, $4->value.value.string)==0){
                  record->value.discriminator = 3;
                  literal_assign = 1;
                  assigned = symbolTable.literalTable+k;
                  $2->type = STR;
                  strcpy(record->type, symbolTable.literalTable[k].type);
                  record->value.value.string = (char*)malloc(sizeof(char)*strlen($4->value.value.string));
                  strcpy(record->value.value.string,$4->value.value.string);
                  break;
                }
              }
            }
          }
        }
      
    }
    if (literal_assign ==1){
        //printf("Literal assigned with value\n");fflush(stdout);
        $4->PTR.lt_ptr = assigned;
      }
  }else{
    printf("RET NULL\n"); fflush(stdout);
  }
  }
  codegen_assign(scope,st,&top,&head_quad);
}
  ;
Out: KW_PRINTLN OPEN_PARANTHESIS Body CLOSE_PARANTHESIS STMT_TERMINATOR
  ;
Body: STRING
  | STRING COMMA Val
  ;
If: KW_IF Exp {lab1(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);} OPEN_BLOCK Blk CLOSE_BLOCK Else {
    NODE** kids = (NODE**)malloc(sizeof(NODE*)*5);
    kids[0]= $2; kids[1]=get_new_node("{",0,NULL,KW);kids[2] = $5; kids[3]=get_new_node("}",0,NULL,KW);kids[4] = $7;
    $$ = get_new_node("IF",5,kids,KW);
    if ($2->type != BOOL){
        error_count ++;
        printf("ERROR - Incorrect IF - CONDITION does not evaluate to Boolean Line no: %d\n",yylineno);
    }
}
  ;
Else: KW_ELSE {lab2_else(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);} OPEN_BLOCK Blk CLOSE_BLOCK {
    lab3(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);
    NODE** kids = (NODE**)malloc(sizeof(NODE*)*3);
    kids[0]= get_new_node("{",0,NULL,KW); kids[1]=$4; kids[2] =get_new_node("}",0,NULL,KW);
    $$ = get_new_node("ELSE",3,kids,KW);
}
  | {lab2_noelse(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);$$ = get_new_node("LAMBDA",0,NULL,KW);}
  ;
While: KW_WHILE {while_lab1(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);} Exp {while_lab2(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);} OPEN_BLOCK Blk CLOSE_BLOCK {
   while_lab3(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);
   NODE** kids = (NODE**)malloc(sizeof(NODE*)*4);
    kids[0]= $3; kids[1]=get_new_node("{",0,NULL,KW);kids[2] = $6; kids[3]=get_new_node("}",0,NULL,KW);//kids[4] = $5;
    $$ = get_new_node("WHILE",4,kids,KW);
    if ($3->type != BOOL){
        error_count ++;
        printf("ERROR - Incorrect WHILE - CONDITION does not evaluate to Boolean Line no: %d\n",yylineno);
    }
}
  ;
For: KW_FOR id KW_IN Val {for_lab1(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);} RANGE Val {for_lab2(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);} OPEN_BLOCK Blk CLOSE_BLOCK {
   for_lab3(&symbolTable,st,&top,&temp_count,&label_count,scope,yylineno,&head_quad);
   NODE** kids = (NODE**)malloc(sizeof(NODE*)*6);
   NODE** range_kids = (NODE**)malloc(sizeof(NODE*)*2);
    range_kids[0] = $4; range_kids[1] = $7;
    kids[0]= $2; kids[1]=get_new_node("IN",0,NULL,KW);kids[2] = get_new_node("RANGE",2,range_kids,KW); 
    kids[3]=get_new_node("{",0,NULL,KW);kids[4] = $10;kids[5] = get_new_node("}",0,NULL,KW);
    $$ = get_new_node("FOR",6,kids,KW);
    //write changes to ST
    $2->type = DEC;
    
    if ($4->type !=DEC || $7->type!=DEC){
      printf("ERROR - Loop range must have DECIMALS given types %s and %s\n",CUSTYPES[$4->type],CUSTYPES[$7->type]);
      error_count++;
    }
    struct id* record = lookup_ST(&symbolTable,$2->value.value.string,scope);
    if (record != NULL){
              strcpy(record->type,"DECIMAL");
              record->value.discriminator = 0;
    }
}
  ;
%%

int main(){
        head_quad = NULL;
        top = 0;
        temp_count = 0;
        label_count = 0;
        queue.queue = NULL;
        queue.queue_front = -1;
        queue.queue_rear = -1;
        symbolTable.literal_count = 0;
        symbolTable.literalTable = (struct literal*)malloc(sizeof(struct literal)*100);
        installLiteral(&symbolTable,"1","DECIMAL");
        yyparse();
        if (error_count > 0){
          printf("Compilation Errors - Will not generate ICG\n");
        }else{
          //display_quad(head_quad);
          //printf("After Removal of temp assigns\n\n");
          remove_temp_assigns(head_quad);
          //display_quad(head_quad);
          CSE(head_quad);
          //printf("\n After CSE\n\n");
          //display_quad(head_quad);
          int prop = 1;
          int fold = 1;
          while (prop == 1 && fold == 1){
            prop = const_prop(head_quad);
            fold = const_fold(head_quad,&symbolTable);
          }
          //printf("\nAfter Propagating and Folding\n");
          //display_quad(head_quad);
          deadcode_removal(head_quad);
          //printf("\nAfter dead code removal\n");
          //display_quad(head_quad);
          remove_dead_variables(&head_quad);
          //printf("After Removal dead variables\n\n");
          //printf("@\n");
          display_quad(head_quad);
          //dispLit(&symbolTable);
          //dispST(&symbolTable,max_depth);
         }
        return 0;
}

void yyerror(char *s){
	printf("ERROR: \"%s\" on line: %d\n",s, yylineno);
  yyparse();
}

char* get_new_temp(int count){
  char* new_temp;
  char buff[3];
  if (count < 9){
    new_temp = (char*)malloc(sizeof(char)*2);
  }else{
    new_temp = (char*)malloc(sizeof(char)*3);
  }
  snprintf(buff,3,"%d",count);
  strcpy(new_temp,"t");
  strcat(new_temp, buff);
  return new_temp;
}

char* get_new_label(int count){
  char* new_label;
  char buff[3];
  if (count < 9){
    new_label = (char*)malloc(sizeof(char)*2);
  }else{
    new_label = (char*)malloc(sizeof(char)*3);
  }
  snprintf(buff,3,"%d",count);
  strcpy(new_label,"L");
  strcat(new_label, buff);
  return new_label;
}

void push_value(NODE* value) {
  st[++top] = value;
}




