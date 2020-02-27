%{
	#ifndef YYSTYPE
   #define YYTYPE char*
   #endif

   int yylex();
   int yyerror();
   
   #include<stdio.h>
   #include<string.h>
   #include<stdlib.h>
   #include"2.h"
   #define MAX 100

   int valid=1;

   struct ident symbol_table[MAX];
   int i_symtab;
   int scope;

   int add_value(char* lexeme,char* val)
   {
      for(int i=0;i<i_symtab;i++)
      {
         if(strcmp(symbol_table[i].lexeme,lexeme)==0)
         {
            if(symbol_table[i].scope == scope)
            {
               strcpy(symbol_table[i].val,val);
               return 1;
            }
         }
      }
      return 0;
   }

%}

%token T_op T_ident T_symbol T_char T_const SEMICOLON LET COMMA COLON DATATYPE IN FOR DOT EQ FN MAIN PAR_OP PAR_CL CUR_OP CUR_CL PRINTLN IF ELSE WHILE

%%
Main : FN MAIN PAR_OP PAR_CL CUR_OP Blk CUR_CL;
Blk  : Code Blk|If Blk|While Blk|For Blk| ;
Code : Eval|Out|Exp|Var_dec;
Eval : T_ident EQ Exp SEMICOLON;

Exp : Val T_op Exp| PAR_OP Exp PAR_CL|Val;
Val : T_ident| T_const;

Out : PRINTLN PAR_OP Body PAR_CL SEMICOLON;
Body : T_char| T_char COMMA Val|;

Var_dec : LET T_ident COLON DATATYPE EQ Val SEMICOLON {printf("trying to add\n");add_value($2,$6);printf("added\n");}
        ;

If      : IF Exp CUR_OP Blk CUR_CL Else ; 
Else    : ELSE CUR_OP Blk CUR_CL | ;

While   : WHILE Exp CUR_OP Blk CUR_CL;

For : FOR T_ident IN T_const DOT DOT T_const CUR_OP Blk CUR_CL;
%%

yyparse();

int yyerror(char* s) 
 { 
    valid=0;
    printf("\nSyntax Error\n"); 
    return 1;
 } 