
%{
#include <stdio.h>
#include <stdlib.h>
#include "header.h" 
#include <string.h>
#include "y.tab.h"
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
  | Exp {$$ = $1;}
  | Var_dec
  ;
Eval: IDENTIFIER ASSIGN Exp STMT_TERMINATOR
  ;
Exp: Val op Exp
  | OPEN_PARANTHESIS Exp CLOSE_PARANTHESIS
  | Val {$$ = $1;}
  ;
id: IDENTIFIER {$$= yylval;}
  ;
Val: IDENTIFIER {$$ = yylval;}
  | STRING {$$ = yylval;}
  | DECIMAL {$$ = yylval;}
  | FLOAT {$$ = yylval;}
  ;
op: ARITH
  | BITWISE
  | RELATIONAL
  ;
Var_dec: KW_LET id ASSIGN Exp STMT_TERMINATOR {for (int j = 0; j < symbolTable.table[scope].count; j++){if (strcmp($2,symbolTable.table[scope].identifiers[j].name) == 0){strcpy(symbolTable.table[scope].identifiers[j].value, $4);for (int k = 0; k < 500;k++){if(strcmp(symbolTable.literalTable[k].value,$4)==0){strcpy(symbolTable.table[scope].identifiers[j].dtype, symbolTable.literalTable[k].type);}}}}}
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
        yyparse();
        return 0;
}
void yyerror(char *s){
	printf("ERROR: \"%s\" on line: %d\n",s, yylineno);
	yyparse();
}
