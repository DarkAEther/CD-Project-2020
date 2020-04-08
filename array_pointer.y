%{
#include <stdio.h>
#include <stdlib.h>
#include "header.h" 
#include <string.h>
#include <assert.h>
void yyerror();
int line_num=1;  
int error_count = 0;  
extern int scope;
int quad_num = 0;

char* CUSTYPES[] ={"ID\0","STRING\0","DECIMAL\0","FLOAT\0","CHARACTER\0","BOOLEAN\0","OP\0","KW\0"};
typedef struct node{
  struct node** children;
  int child_count;
  struct value_wrap value;
  int level;
  enum TYPE type;
  enum TYPE core_type;
} NODE;


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
  if (error_count > 0){
    printf("Semantic Errors, Cannot build parse tree\n");
    return;
  }
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
  | While Blk { $$ = $1;}
  | For Blk {$$ = $1;}
  | {$$ = get_new_node("LAMBDA",0,NULL,KW);}
  ;
Code: Eval {$$ = $1;}
  | Out {$$ = $1;}
  | Exp {$$ = $1;}
  | Var_dec {$$ = $1;}
  ;
Eval: Val ASSIGN Exp STMT_TERMINATOR{ push_value($2); codegen_assign();
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
    int found = 0;
    for (int k = scope; k >= 0; k--){
        for(int i = 0; i < symbolTable.table[k].count;i++){
          if (strcmp(symbolTable.table[k].identifiers[i].name,$1->value.value.string)==0){
            if (strcmp(symbolTable.table[k].identifiers[i].type,"") != 0){
                //variable is declared
                strcpy(symbolTable.table[k].identifiers[i].type,CUSTYPES[$3->type]);
                found = 1;
                if ($3->type == DEC){
                  $1->type = DEC;
                  symbolTable.table[k].identifiers[i].value.discriminator = 0;
                }
                if ($3->type == FLT){
                  $1->type = FLT;
                  symbolTable.table[k].identifiers[i].value.discriminator = 1;
                }
                if ($3->type == CHAR){
                  $1->type = CHAR;
                  symbolTable.table[k].identifiers[i].value.discriminator = 3;
                }
                if ($3->type == STR){
                  $1->type = STR;
                  symbolTable.table[k].identifiers[i].value.discriminator = 4;
                }
                break;
            }
          }
       }
       if (found == 1){
         break;
       }
    }
    if (found == 0){
      printf("ERROR - Variable use before declaration %s on line %d\n",$1->value.value.string,yylineno);
      error_count++;
    }
  }
}
  ;
Exp: Val op Exp {
  codegen();
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*2);
  kids[0] = $1; kids[1] = $3; 
  $$ = mod_node($2,2,kids);
  if ($2->type == REL){
      $$->type = BOOL;
  }
  if ($1->type == ID){
      int found = 0;
      
    for (int k = scope; k >=0 && found == 0; k--){
    for(int i = 0; i < symbolTable.table[k].count;i++){
      //printf("TEST %s %s %d\n",symbolTable.table[k].identifiers[i].name,$1->value.value.string,strcmp(symbolTable.table[k].identifiers[i].name,($1)->value.value.string));
      if (strcmp(symbolTable.table[k].identifiers[i].name,$1->value.value.string)==0){
        // The variable has been found
        //printf("D1#%s# #%s# %d\n",symbolTable.table[k].identifiers[i].type,"",strcmp(symbolTable.table[k].identifiers[i].type,""));
        if (strcmp(symbolTable.table[k].identifiers[i].type,"") != 0){
            //declared var
            //printf("I am here\n");
            found = 1;
            if (symbolTable.table[k].identifiers[i].value.discriminator == 0){
              $1->type = DEC;
            }
            if (symbolTable.table[k].identifiers[i].value.discriminator == 1){
              $1->type = FLT;
            }
            if (symbolTable.table[k].identifiers[i].value.discriminator == 2){
              $1->type = CHAR;
            }
            if (symbolTable.table[k].identifiers[i].value.discriminator == 3){
              $1->type = STR;
            }
            
        }else{
          //printf("variable %s is undeclared\n",$1->value.value.string);
        }
       break; 
      }
    }
    }
  }
  if ($3->type == ID){
      int found = 0;
    for (int k = scope; k >=0 && found == 0; k--){
    for(int i = 0; i < symbolTable.table[k].count;i++){
      //printf("TEST %s %s %d\n",symbolTable.table[k].identifiers[i].name,$1->value.value.string,strcmp(symbolTable.table[k].identifiers[i].name,($1)->value.value.string));
      if (strcmp(symbolTable.table[k].identifiers[i].name,($3)->value.value.string)==0){
        // The variable has been found
        if (strcmp(symbolTable.table[k].identifiers[i].type,"") != 0){
            //declared var
            //printf("I am here\n");
            found = 1;
            //printf("###%s %s %d\n",symbolTable.table[k].identifiers[i].name,symbolTable.table[k].identifiers[i].type,symbolTable.table[k].identifiers[i].value.discriminator);
            if (symbolTable.table[k].identifiers[i].value.discriminator == 0){
              $3->type = DEC;
            }
            if (symbolTable.table[k].identifiers[i].value.discriminator == 1){
              $3->type = FLT;
            }
            if (symbolTable.table[k].identifiers[i].value.discriminator == 2){
              $3->type = CHAR;
            }
            if (symbolTable.table[k].identifiers[i].value.discriminator == 3){
              $3->type = STR;
            }
        }else{
          //printf("variable %s is undeclared\n",$1->value.value.string);
        }
        break;
      }
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
  
}
  | OPEN_PARANTHESIS Exp CLOSE_PARANTHESIS {$$ = $2;}
  | Val { $$ = $1;}
  ;
id: IDENTIFIER {push_value($1); $$= get_new_node(yylval.str,0,NULL,ID);$$->core_type = ID;}
  ;
Val: IDENTIFIER {push_value($1); $$ = get_new_node(yylval.str,0, NULL,ID);$$->core_type = ID;}
  | STRING {push_value($1); $$ =get_new_node(yylval.str,0,NULL,STR);$$->core_type = VAL;}
  | DECIMAL {push_value($1); $$ = get_new_node(yylval.str,0,NULL,DEC);$$->core_type = VAL;}
  | FLOAT {push_value($1); $$ = get_new_node(yylval.str,0,NULL,FLT);$$->core_type = VAL;}
  | CHARACTER {push_value($1); $$ = get_new_node(yylval.str,0,NULL,CHAR);$$->core_type = VAL;}
  ;
op: ARITH {push_value($1); $$ = get_new_node(yylval.str,0, NULL,NUM);$$->core_type = OP;}
  | BITWISE {push_value($1); $$ = get_new_node(yylval.str,0, NULL, NUM);$$->core_type = OP;}
  | RELATIONAL {push_value($1); $$ = get_new_node(yylval.str,0, NULL,REL);$$->core_type = OP;}
  ;
Var_dec: KW_LET id ASSIGN Exp STMT_TERMINATOR { push_value($3); codegen_assign();
  NODE** kids = (NODE**)malloc(sizeof(NODE*)*3);
  NODE** assign_kids = (NODE**)malloc(sizeof(NODE*)*2);
  assign_kids[0] = $2; assign_kids[1] = $4;
  kids[0]= get_new_node("LET",0,NULL,KW); kids[1]=get_new_node("=",2,assign_kids,KW); kids[2] = get_new_node(";",0,NULL,KW);
  $$ = get_new_node("VARDEC",3,kids,KW);
  if ($4->core_type != VAL){
        //printf("%s %s\n",CUSTYPES[$2->type],CUSTYPES[$4->type]);
        $2->type = $4->type;
        
        //write changes to ST
        for (int p = 0; p < symbolTable.table[scope].count;p++){
          //printf("TEST %s %s %d\n",$2->value.value.string,symbolTable.table[scope].identifiers[p].name,strcmp($2->value.value.string,symbolTable.table[scope].identifiers[p].name));
          if (strcmp($2->value.value.string,symbolTable.table[scope].identifiers[p].name) == 0){
               if ($2->type == DEC){
                    strcpy(symbolTable.table[scope].identifiers[p].type, "DECIMAL");
                    symbolTable.table[scope].identifiers[p].value.discriminator = 0;
                }
                if ($2->type == FLT){
                    strcpy(symbolTable.table[scope].identifiers[p].type, "FLOAT");
                    symbolTable.table[scope].identifiers[p].value.discriminator = 1;
                }
                if ($2->type == CHAR){
                  strcpy(symbolTable.table[scope].identifiers[p].type, "CHARACTER");
                  symbolTable.table[scope].identifiers[p].value.discriminator = 2;
                }
                if ($2->type == STR){
                  strcpy(symbolTable.table[scope].identifiers[p].type, "STRING");
                  symbolTable.table[scope].identifiers[p].value.discriminator = 3;
                }
          }
        }
  }else{
  int literal_assign = 0;
  
  for (int j = 0; j < symbolTable.table[scope].count; j++){
    if (strcmp($2->value.value.string,symbolTable.table[scope].identifiers[j].name) == 0){
      for (int k = 0; k < symbolTable.literal_count;k++){
        if (symbolTable.literalTable[k].discriminator == 0){
          if(symbolTable.literalTable[k].value.integer == atoi($4->value.value.string)){
            
            symbolTable.table[scope].identifiers[j].value.discriminator = 0;
            literal_assign = 1;
            $2->type = DEC;
            strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
            symbolTable.table[scope].identifiers[j].value.value.integer= atoi($4->value.value.string);
            break;
          }
        }else{
          if (symbolTable.literalTable[k].discriminator == 1){
            
            if(symbolTable.literalTable[k].value.floating == atof($4->value.value.string)){
              symbolTable.table[scope].identifiers[j].value.discriminator = 1;
              literal_assign = 1;
              $2->type = FLT;
              strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
              symbolTable.table[scope].identifiers[j].value.value.floating= atof($4->value.value.string);
              break;
            }
          }else{
            if (symbolTable.literalTable[k].discriminator == 2){
              if(strcmp(symbolTable.literalTable[k].value.character,$4->value.value.string)==0){
                symbolTable.table[scope].identifiers[j].value.discriminator = 2;
                literal_assign= 1;
                $2->type = CHAR;
                strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
                strcpy(symbolTable.table[scope].identifiers[j].value.value.character,$4->value.value.string);
                break;
              }
            }else{
              if (symbolTable.literalTable[k].discriminator == 3){
                if(strcmp(symbolTable.literalTable[k].value.string, $4->value.value.string)==0){
                  symbolTable.table[scope].identifiers[j].value.discriminator = 3;
                  literal_assign = 1;
                  $2->type = STR;
                  strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
                  symbolTable.table[scope].identifiers[j].value.value.string = (char*)malloc(sizeof(char)*strlen($4->value.value.string));
                  strcpy(symbolTable.table[scope].identifiers[j].value.value.string,$4->value.value.string);
                  break;
                }
              }
            }
          }
        }
      }
      if (literal_assign ==1){
        break;
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
If: KW_IF Exp {lab1();} OPEN_BLOCK Blk CLOSE_BLOCK {lab2();} Else {
    printf("Scope for IF %d\n", scope);
    printf("Count %d\n", symbolTable.table[scope].count);
}
  ;
Else: KW_ELSE OPEN_BLOCK Blk CLOSE_BLOCK {
    lab3();
    printf("Scope for Else %d\n", scope);
    printf("Count %d\n", symbolTable.table[scope].count);
}
  | {$$ = get_new_node("LAMBDA",0,NULL,KW);}
  ;
While: KW_WHILE {while_lab1();} Exp {whilelab2();} OPEN_BLOCK Blk CLOSE_BLOCK {
    whilelab3();
    printf("Scope for While %d\n", scope);
    printf("Count %d\n", symbolTable.table[scope].count);
}
  ;
For: KW_FOR id KW_IN Val {push_value($3); codegen_assign(); for_lab1();} RANGE Val {for_lab2();} OPEN_BLOCK Blk CLOSE_BLOCK {
    for_lab3();
    printf("Scope for FOR %d\n", scope);
    printf("Count %d\n", symbolTable.table[scope].count);
}
  ;
%%

union entry {
  struct id* st_entry;
  struct literal* lt_entry;
};

struct quad {
  int discriminator1;
  int discriminator2;
  /*
  0 : ST
  1 : LT
  */
  char* op;
  union entry arg1;
  union entry arg2;
  union entry result;
};
struct quad q[100];

int main(){
        symbolTable.literal_count = 0;
        symbolTable.literalTable = (struct literal*)malloc(sizeof(struct literal));
        yyparse();
        //display_quad(head_quad);
        return 0;
}
void yyerror(char *s){
	printf("ERROR: \"%s\" on line: %d\n",s, yylineno);
  yyparse();
}

char st[100][20];
int top = 0;
char i_value[2] = "0";
char temp_value[2] = "t";
int label[20];
int lnum = 0;
int ltop = 0;
int start = 0;
int for_start = 0;

void push_value(char* value) {
  strcpy(st[++top], value);
}

void codegen() {
  //printf("Generate Code\n");
  strcpy(temp_value, "t");
  strcat(temp_value, i_value);
  int x=symbolTable.table[scope].count;
    strcpy(symbolTable.table[scope].identifiers[x].name, temp_value);
    symbolTable.table[scope].identifiers[x].lineno=0;
    symbolTable.table[scope].count++;

  struct quad* node = malloc(sizeof(struct quad));

  int j = 0;
  while (j < symbolTable.table[scope].count) {
    printf("Values : %s\n", symbolTable.table[scope].identifiers[j].name);
    j++;
  }
  int i = 0;
  strcpy(q[quad_num].op, "!");
  q[quad_num].result.st_entry = &symbolTable.table[scope].identifiers[x];
  
  while(i < symbolTable.literal_count) {
    if (symbolTable.literalTable[i].discriminator == 0) {
      printf("Int %d\n", atoi(st[top-2]));
      if(symbolTable.literalTable[i].value.integer == atoi(st[top-2])) {
        q[quad_num].discriminator1 = 1;
        q[quad_num].arg1.lt_entry = &symbolTable.literalTable[i];
        printf("Lit Check Value %d\n", symbolTable.literalTable[i].value.integer);
      }
        else if(symbolTable.literalTable[i].value.integer == atoi(st[top])) {
            q[quad_num].discriminator2 = 1;
            q[quad_num].arg2.lt_entry = &symbolTable.literalTable[i];
            printf("Lit Check Value %d\n", symbolTable.literalTable[i].value.integer);
        }
    }
    // else if (symbolTable.literalTable[i].discriminator == 1) {
    //   printf("Lit Check Value %f\n", symbolTable.literalTable[i].value.floating);
    //   if(symbolTable.literalTable[i].value.floating == (double)st[top-2]) {
    //     node->discriminator1 = 1;
    //     node->arg1.lt_entry = &symbolTable.literalTable[i];
    //   }
    // }
//     else if (symbolTable.literalTable[i].discriminator == 2) {
//         printf(" Char %c\n", st[top-2]);
//       if(strcmp(symbolTable.literalTable[i].value.character, st[top-2])==0) {
//         node->discriminator1 = 1;
//         node->arg1.lt_entry = &symbolTable.literalTable[i];
//         printf("Lit Check Value %c\n", symbolTable.literalTable[i].value.character);
//       }
//     }
//     else if (symbolTable.literalTable[i].discriminator == 3) {
//       printf("Str %s\n", st[top-2]);
//       if(strcmp(symbolTable.literalTable[i].value.string, st[top-2])==0) {
//         node->discriminator1 = 1;
//         node->arg1.lt_entry = &symbolTable.literalTable[i];
//         printf("Lit Check Value %s\n", symbolTable.literalTable[i].value.string);
//       }
//     }
    printf("Lit Values : %s %d\n", symbolTable.literalTable[i].type,symbolTable.literalTable[i].discriminator);
    i++;
  }
  quad_num++;
  printf("%s = %s %s %s \n", temp_value, st[top-2], st[top-1], st[top]);

  top -= 3;
  push_value(temp_value);
  i_value[0]++;
}

void codegen_assign() {
  printf("%s = %s\n", st[top-2], st[top-1]);
  top -= 2;
}

void lab1() {
  lnum++;
  strcpy(temp_value, "t");
  strcat(temp_value, i_value);
  int x=symbolTable.table[scope].count;
    strcpy(symbolTable.table[scope].identifiers[x].name, temp_value);
    symbolTable.table[scope].identifiers[x].lineno=0;
    symbolTable.table[scope].count++;

    int j = 0;
  while (j < symbolTable.table[scope].count) {
    printf("Values : %s\n", symbolTable.table[scope].identifiers[j].name);
    j++;
  }

  strcpy(q[quad_num].op, "!");
  q[quad_num].result.st_entry = &symbolTable.table[scope].identifiers[x];
  int i = 0;
  while(i < symbolTable.literal_count) {
    if (symbolTable.literalTable[i].discriminator == 0) {
    printf("Int %d\n", atoi(st[top-2]));
      if(symbolTable.literalTable[i].value.integer == atoi(st[top])) {
        q[quad_num].discriminator1 = 1;
        q[quad_num].arg1.lt_entry = &symbolTable.literalTable[i];
        printf("Lit Check Value %d\n", symbolTable.literalTable[i].value.integer);
      }
      q[quad_num].discriminator2 = 0;
      q[quad_num].arg2.st_entry = NULL;
    }
    // else if (symbolTable.literalTable[i].discriminator == 1) {
    //   printf("Lit Check Value %f\n", symbolTable.literalTable[i].value.floating);
    //   if(symbolTable.literalTable[i].value.floating == (double)st[top-2]) {
    //     node->discriminator1 = 1;
    //     node->arg1.lt_entry = &symbolTable.literalTable[i];
    //   }
    // }
//     else if (symbolTable.literalTable[i].discriminator == 2) {
//         printf("Char %c\n", st[top-2]);
//       if(strcmp(symbolTable.literalTable[i].value.character, st[top])==0) {
//         node->discriminator1 = 1;
//         node->arg1.lt_entry = &symbolTable.literalTable[i];
//         printf("Lit Check Value %c\n", symbolTable.literalTable[i].value.character);
//       }
//     }
//     else if (symbolTable.literalTable[i].discriminator == 3) {
//         printf("Str %s\n", st[top-2]);
//       if(strcmp(symbolTable.literalTable[i].value.string, st[top])==0) {
//         node->discriminator1 = 1;
//         node->arg1.lt_entry = &symbolTable.literalTable[i];
//         printf("Lit Check Value %s\n", symbolTable.literalTable[i].value.string);
//       }
//     }
    printf("Lit Values : %s %d\n", symbolTable.literalTable[i].type,symbolTable.literalTable[i].discriminator);
    i++;
  }
  quad_num++;
  //insert_quad(head_quad, &node);
  printf("%s = not %s\n", temp_value, st[top]);
  printf("if %s goto L%d\n", temp_value, lnum);
  i_value[0]++;
  label[++ltop] = lnum;
}

void lab2() {
  int x;
  lnum++;
  x = label[ltop--];
  printf("goto L%d\n", lnum);
  printf("L%d: \n", x);
  label[++ltop] = lnum;
}

void lab3() {
  int y;
  y = label[ltop--];
  printf("L%d: \n", y);
}


void while_lab1() {
  printf("L%d: \n", lnum++);
  start += lnum-1;
}

void whilelab2() {
  strcpy(temp_value, "t");
  strcat(temp_value, i_value);
  int x=symbolTable.table[scope].count;
    strcpy(symbolTable.table[scope].identifiers[x].name, temp_value);
    symbolTable.table[scope].identifiers[x].lineno=0;
    symbolTable.table[scope].count++;

    int j = 0;
  while (j < symbolTable.table[scope].count) {
    printf("Values : %s\n", symbolTable.table[scope].identifiers[j].name);
    j++;
  }

  int i = 0;
  strcpy(q[quad_num].op, "!");
  q[quad_num].result.st_entry = &symbolTable.table[scope].identifiers[x];
  while(i < symbolTable.literal_count) {
    if (symbolTable.literalTable[i].discriminator == 0) {
      if(symbolTable.literalTable[i].value.integer == atoi(st[top])) {
        printf("Int %d\n", atoi(st[top-2]));
        q[quad_num].discriminator1 = 1;
        q[quad_num].arg1.lt_entry = &symbolTable.literalTable[i];
        printf("Lit Check Value %d\n", symbolTable.literalTable[i].value.integer);
      }
      q[quad_num].discriminator2 = 0;
      q[quad_num].arg2.st_entry = NULL;
    }
    // else if (symbolTable.literalTable[i].discriminator == 1) {
    //   printf("Lit Check Value %f\n", symbolTable.literalTable[i].value.floating);
    //   if(symbolTable.literalTable[i].value.floating == (double)st[top-2]) {
    //     node->discriminator1 = 1;
    //     node->arg1.lt_entry = &symbolTable.literalTable[i];
    //   }
    // }
//     else if (symbolTable.literalTable[i].discriminator == 2) {
//         printf("Char %c\n", st[top-2]);
//       if(strcmp(symbolTable.literalTable[i].value.character, st[top])==0) {
//         node->discriminator1 = 1;
//         node->arg1.lt_entry = &symbolTable.literalTable[i];
//         printf("Lit Check Value %c\n", symbolTable.literalTable[i].value.character);
//       }
//     }
//     else if (symbolTable.literalTable[i].discriminator == 3) {
//         printf("Str %s\n", st[top-2]);
//       if(strcmp(symbolTable.literalTable[i].value.string, st[top])==0) {
//         node->discriminator1 = 1;
//         node->arg1.lt_entry = &symbolTable.literalTable[i];
//         printf("Lit Check Value %s\n", symbolTable.literalTable[i].value.string);
//       }
//     }
    printf("Lit Values : %s %d\n", symbolTable.literalTable[i].type,symbolTable.literalTable[i].discriminator);
    i++;
  }
  quad_num++;
  //insert_quad(head_quad, node);
  printf("%s = not %s\n", temp_value, st[top]);
  printf("if %s goto L%d\n", temp_value, lnum);
  i_value[0]++;
}

void whilelab3() {
  printf("goto L%d \n", start);
  printf("L%d: \n", start+1);
}

char value[20];
void for_lab1() {
  printf("L%d: \n", lnum++);
  strcpy(value, st[top]);
  for_start += lnum-1;
}

void for_lab2() {
  strcpy(temp_value, "t");
  strcat(temp_value, i_value);
  int x=symbolTable.table[scope].count;
    strcpy(symbolTable.table[scope].identifiers[x].name, temp_value);
    symbolTable.table[scope].identifiers[x].lineno=0;
    symbolTable.table[scope].count++;

    int j = 0;
  while (j < symbolTable.table[scope].count) {
    printf("Values : %s\n", symbolTable.table[scope].identifiers[j].name);
    j++;
  }

  strcpy(q[quad_num].op, "!");
  q[quad_num].result.st_entry = &symbolTable.table[scope].identifiers[x];
  int i = 0;
  while(i < symbolTable.literal_count) {
    
    if (symbolTable.literalTable[i].discriminator == 0) {
        printf("Int %d\n", atoi(st[top-2]));
      if(symbolTable.literalTable[i].value.integer == atoi(st[top])) {
        q[quad_num].discriminator1 = 1;
        q[quad_num].arg1.lt_entry = &symbolTable.literalTable[i];
        printf("Lit Check Value %d\n", symbolTable.literalTable[i].value.integer);
      }
    }
    // else if (symbolTable.literalTable[i].discriminator == 1) {
    //   printf("Lit Check Value %f\n", symbolTable.literalTable[i].value.floating);
    //   if(symbolTable.literalTable[i].value.floating == (double)st[top-2]) {
    //     node->discriminator1 = 1;
    //     node->arg1.lt_entry = &symbolTable.literalTable[i];
    //   }
    // }
    else if (symbolTable.literalTable[i].discriminator == 2) {
        printf("Char %c\n", st[top-2]);
      if(strcmp(symbolTable.literalTable[i].value.character, st[top])==0) {
        q[quad_num].discriminator1 = 1;
        q[quad_num].arg1.lt_entry = &symbolTable.literalTable[i];
      printf("Lit Check Value %c\n", symbolTable.literalTable[i].value.character);
      }
    }
    else if (symbolTable.literalTable[i].discriminator == 3) {
        printf("Str %s\n", st[top-2]);
      if(strcmp(symbolTable.literalTable[i].value.string, st[top])==0) {
        q[quad_num].discriminator1 = 1;
        q[quad_num].arg1.lt_entry = &symbolTable.literalTable[i];
        printf("Lit Check Value %s\n", symbolTable.literalTable[i].value.string);
      }
    }
    printf("Lit Values : %s %d\n", symbolTable.literalTable[i].type, symbolTable.literalTable[i].discriminator);
    i++;
  }
  quad_num++;
  //insert_quad(head_quad, node);
  printf("%s = %s not < %s\n", temp_value, value, st[top]);
  printf("if %s goto L%d\n", temp_value, lnum);
  i_value[0]++;
}

void for_lab3() {
  push_value(value);
  push_value("+");
  push_value("1");
  codegen();
  char res[20];
  strcpy(res, st[top]);
  push_value(value);
  push_value(res);
  push_value("=");
  codegen_assign();
  printf("goto L%d\n", for_start);
  printf("L%d: \n", for_start + 1);
}
