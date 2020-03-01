%{
#include <stdio.h>
#include <stdlib.h>
#include "header.h" 
#include <string.h>
void yyerror();
int line_num=1;    
extern int scope;
%}
%token KW_AS
%token KW_BREAK
%token KW_CONST
%token KW_CONTINUE
%token KW_CRATE
%token KW_ELSE
%token KW_ENUM
%token KW_EXTERN
%token KW_FALSE
%token KW_FN
%token KW_FOR
%token KW_IF
%token KW_IMPL
%token KW_IN
%token KW_LET
%token KW_MATCH
%token KW_MOD
%token KW_MOVE
%token KW_MUT
%token KW_PUB
%token KW_REF
%token KW_RETURN
%token KW_SELFVALUE
%token KW_SELFTYPE
%token KW_STATIC
%token KW_STRUCT
%token KW_SUPER
%token KW_TRAIT
%token KW_TRUE
%token KW_TYPE
%token KW_UNSAFE
%token KW_USE
%token KW_WHERE
%token KW_WHILE
%token KW_LOOP
%token CHARACTER
%token STRING
%token RAW_STRING
%token BYTE
%token BYTE_STRING
%token RAW_BYTE_STRING
%token DECIMAL
%token HEX_INT
%token OCTAL_INT
%token BIN_INT
%token FLOAT
%token ARITH
%token BITWISE
%token ASSIGN_OPS
%token ASSIGN
%token RELATIONAL
%token IDENTIFIER
%token STMT_TERMINATOR
%token RANGE
%token ERROR
%token OPEN_BLOCK
%token CLOSE_BLOCK
%token OPEN_PARANTHESIS
%token CLOSE_PARANTHESIS
%token COMMA
%token KW_MAIN
%token KW_PRINTLN
%token EOFI
%%
start: Main EOFI {printf("\n-------------ACCEPTED----------------\n");}
  | Blk
  | EOFI
  | error ';'
  | error '\n'
  ;
Main: KW_FN KW_MAIN OPEN_PARANTHESIS CLOSE_PARANTHESIS OPEN_BLOCK Blk CLOSE_BLOCK
  ;
Blk: Code Blk
  | If Blk
  | While Blk
  | For Blk
  | 
  ;
Code: Eval
  | Out
  | Var_dec {$$ = 1;}
  ;
Eval: IDENTIFIER ASSIGN DECIMALEXP STMT_TERMINATOR
  | IDENTIFIER ASSIGN FLOATEXP STMT_TERMINATOR
  ;
DECIMALEXP: DECIMAL op DECIMALEXP {
  switch ($2){
    case '+':{
      $$ = $1 + $3;break;
    }
    case '-':{
      $$ = $1 - $3;break;
    }
    case '*':{
      $$ = $1 * $3;break;
    }
    case '/':{
      if ($3 == 0){
        printf("ERROR: ZERO DIVISION\n"); $$=1;
      }else{
        $$ = $1 / $3;
      }
      break;
    }
  }
}
  | OPEN_PARANTHESIS DECIMALEXP CLOSE_PARANTHESIS
  | DECIMAL {$$ = $1;}
  ;
FLOATEXP: FLOAT op FLOATEXP {
  switch ($2){
    case '+':{
      $$ = $1 + $3;break;
    }
    case '-':{
      $$ = $1 - $3;break;
    }
    case '*':{
      $$ = $1 * $3;break;
    }
    case '/':{
      if ($3 == 0){
        printf("ERROR: ZERO DIVISION\n"); $$=1;
      }else{
        $$ = $1 / $3;
      }
      break;
    }
  }
  }
  | OPEN_PARANTHESIS FLOATEXP CLOSE_PARANTHESIS
  | FLOAT {$$ = $1;}
  ;
RELATIONALEXP: Val RELATIONAL Val;
id: IDENTIFIER {$$= yylval;}
  ;
Val: IDENTIFIER {$$ = yylval;}
  | STRING {$$ = yylval;}
  | DECIMAL {$$ = yylval;}
  | FLOAT {$$ = yylval;}
  | CHARACTER {$$ = yylval;}
  ;
op: ARITH {$$ = $1;}
  | BITWISE {$$ = $1;}
  | RELATIONAL {$$ = $1;}
  ;
Var_dec: KW_LET id ASSIGN Val STMT_TERMINATOR {
  for (int j = 0; j < symbolTable.table[scope].count; j++){
    if (strcmp($2,symbolTable.table[scope].identifiers[j].name) == 0){
      for (int k = 0; k < symbolTable.literal_count;k++){
        if (symbolTable.literalTable[k].discriminator == 0){
          if(symbolTable.literalTable[k].value.integer == atoi($4)){
            symbolTable.table[scope].identifiers[j].value.discriminator = 0;
            strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
            symbolTable.table[scope].identifiers[j].value.value.integer= atoi($4);
          }
        }else{
          if (symbolTable.literalTable[k].discriminator == 1){
            
            if(symbolTable.literalTable[k].value.floating == atof($4)){
              symbolTable.table[scope].identifiers[j].value.discriminator = 1;
              strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
              symbolTable.table[scope].identifiers[j].value.value.floating= atof($4);
            }
          }else{
            if (symbolTable.literalTable[k].discriminator == 2){
              if(strcmp(symbolTable.literalTable[k].value.character,$4)==0){
                symbolTable.table[scope].identifiers[j].value.discriminator = 2;
                strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
                strcpy(symbolTable.table[scope].identifiers[j].value.value.character,$4);
                
              }
            }else{
              if (symbolTable.literalTable[k].discriminator == 3){
                if(strcmp(symbolTable.literalTable[k].value.string, $4)==0){
                  symbolTable.table[scope].identifiers[j].value.discriminator = 3;
                  strcpy(symbolTable.table[scope].identifiers[j].type, symbolTable.literalTable[k].type);
                  symbolTable.table[scope].identifiers[j].value.value.string = (char*)malloc(sizeof(char)*strlen($4));
                  strcpy(symbolTable.table[scope].identifiers[j].value.value.string,$4);
                }
              }
            }
          }
        }
      }
    }
  }
}
  | KW_LET id ASSIGN DECIMALEXP STMT_TERMINATOR {
      for (int j = 0; j < symbolTable.table[scope].count; j++){
        if (strcmp($2,symbolTable.table[scope].identifiers[j].name) == 0){
            symbolTable.table[scope].identifiers[j].value.discriminator = 0;
            strcpy(symbolTable.table[scope].identifiers[j].type, "DECIMAL");
            symbolTable.table[scope].identifiers[j].value.value.integer= $4;
        }
      }
  }
  | KW_LET id ASSIGN FLOATEXP STMT_TERMINATOR {
      for (int j = 0; j < symbolTable.table[scope].count; j++){
        if (strcmp($2,symbolTable.table[scope].identifiers[j].name) == 0){
            symbolTable.table[scope].identifiers[j].value.discriminator = 0;
            strcpy(symbolTable.table[scope].identifiers[j].type, "FLOAT");
            symbolTable.table[scope].identifiers[j].value.value.floating= $4;
        }
      }
  }
  ;
Out: KW_PRINTLN OPEN_PARANTHESIS Body CLOSE_PARANTHESIS STMT_TERMINATOR
  ;
Body: STRING
  | STRING COMMA Val
  ;
If: KW_IF RELATIONALEXP OPEN_BLOCK Blk CLOSE_BLOCK Else
  ; 
Else: KW_ELSE OPEN_BLOCK Blk CLOSE_BLOCK
  ;
While: KW_WHILE RELATIONALEXP OPEN_BLOCK Blk CLOSE_BLOCK 
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
