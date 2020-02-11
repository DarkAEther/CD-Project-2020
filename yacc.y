%{
#include <stdio.h>
#include <stdlib.h>        
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
%%
stmt:
    ;
%%

void yyerror(char* text){
        printf("Error: %s\n",text);
}
void main(){
        yyparse();
}