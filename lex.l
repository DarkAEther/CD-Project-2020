%option yylineno
%{
#include <stdio.h>
#include "yacc.tab.h"
void comment();
void yyerror();
int comment_stack_count = 1;
int lit=0;
struct literal {
	char value[20];
	char type[10];
};
struct var {
	char name[32];
	char lineNums[100];
	char value[20];
	char dtype[10];
};
struct literal literalTable[250];
void dispLit();
void installLiteral(char *value,char *type);
%}
KW_AS as
KW_BREAK break
KW_CONST const
KW_CONTINUE continue
KW_CRATE crate
KW_ELSE else
KW_ENUM enum
KW_EXTERN extern
KW_FALSE false
KW_FN fn
KW_FOR for
KW_IF if
KW_IMPL impl
KW_IN in
KW_LET let
KW_LOOP loop
KW_MATCH match
KW_MOD mod
KW_MOVE move
KW_MUT mut
KW_PUB pub
KW_REF ref
KW_RETURN return
KW_SELFVALUE self
KW_SELFTYPE Self
KW_STATIC static
KW_STRUCT struct
KW_SUPER super
KW_TRAIT trait
KW_TRUE true
KW_TYPE type
KW_UNSAFE unsafe
KW_USE use
KW_WHERE where
KW_WHILE while
KW_ASYNC async
KW_AWAIT await
KW_DYN dyn
KW_ABSTRACT abstract
KW_BECOME become
KW_BOX box
KW_DO do
KW_FINAL final
KW_MACRO macro
KW_OVERRIDE override
KW_PRIV priv
KW_TYPEOF typeof
KW_UNSIZED unsized
KW_VIRTUAL virtual
KW_YIELD yield
KW_TRY try

IDENTIFIER_OR_KEYWORD [a-zA-Z][a-zA-Z0-9_]*|_[a-zA-Z0-9_]+

DOC_COMMENT \/\/\!.*\n
INNER_LINE_DOC \/\/!{1,2}
INNER_BLOCK_DOC \/\*\!!{0,1}.*\*\/
SINGLE_LINE_COMMENT \/{2,4}.*\n
EMPTY_MULTI \/\*{1,3}\/
MULTI_LINE_COMMENT \/\*{1,3}
WHITE_SPACE [ \t]

CHARACTER \'.\'
STRING \".*\"
RAW_STRING_LITERAL r\".*\"
RAW_STRING r#\".*\"#
BYTE b\'.*\'
BYTE_STRING b\".*\"
RAW_BYTE_STRING br#\".*\"#

DECIMAL [1-9]((_[0-9]{1,3})*|[0-9]*)*
HEX_INT 0x[0-9a-fA-F]*
OCTAL_INT 0o[0-7]*
BIN_INT 0b1*0*
FLOAT [1-9][0-9]*\.[0-9]+

ARITH_OPERATOR [+\-\/\*]
BITWISE_OPERATOR ([\^\!]|&&|\|\||<<|>>)
ASSIGN_OPS (\+\=|\-\=|\*\=|\/\=|%\=|\^\=|&\=|\|\=|<<\=|>>\=)
ASSIGN \=
RELATIONAL (\=\=|\!\=|>|<|>\=|<\=)
STMT_TERMINATOR ;
OPEN_BLOCK \{
CLOSE_BLOCK \}
OPEN_PARANTHESIS \(
CLOSE_PARANTHESIS \)
COMMA ,
%%
{WHITE_SPACE} {printf(" ");}
\n {printf("\n");}
{OPEN_BLOCK} {printf("OPEN_BLOCK");return OPEN_BLOCK;}
{CLOSE_BLOCK} {printf("CLOSE_BLOCK");return CLOSE_BLOCK;}
{OPEN_PARANTHESIS} {printf("OPEN_PARANTHESIS");return OPEN_PARANTHESIS;}
{CLOSE_PARANTHESIS} {printf("CLOSE_PARANTHESIS");return CLOSE_PARANTHESIS;}
{ASSIGN_OPS} {printf("ASSIGN_OPS");return ASSIGN_OPS;}
{ASSIGN} {printf("ASSIGN");return ASSIGN;}
{RELATIONAL} {printf("RELATIONAL");return RELATIONAL;}
{ARITH_OPERATOR} {printf("ARITH");return ARITH;}
{BITWISE_OPERATOR} {printf("BITWISE_OPERATOR");return BITWISE;}
{KW_AS} {printf("KW_AS");return KW_AS;}
{KW_BREAK} {printf("KW_BREAK");return KW_BREAK;}
{KW_CONST} {printf("KW_CONST");return KW_CONST;}
{KW_CONTINUE} {printf("KW_CONTINUE");return KW_CONTINUE;}
{KW_CRATE} {printf("KW_CRATE");return KW_CRATE;}
{KW_ELSE} {printf("KW_ELSE");return KW_ELSE;}
{KW_ENUM} {printf("KW_ENUM");return KW_ENUM;}
{KW_EXTERN} {printf("KW_EXTERN");return KW_EXTERN;}
{KW_FALSE} {printf("KW_FALSE");return KW_FALSE;}
{KW_FN} {printf("KW_FN");return KW_FN;}
{KW_FOR} {printf("KW_FOR");return KW_FOR;}
{KW_IF} {printf("KW_IF");return KW_IF;}
{KW_IMPL} {printf("KW_IMPL");return KW_IMPL;}
{KW_IN} {printf("KW_IN");return KW_IN;}
{KW_LET} {printf("KW_LET");return KW_LET;}
{KW_LOOP} {printf("KW_LOOP");return KW_LOOP;}
{KW_MATCH} {printf("KW_MATCH");return KW_MATCH;}
{KW_MOD} {printf("KW_MOD");return KW_MOD;}
{KW_MOVE} {printf("KW_MOVE");return KW_MOVE;}
{KW_MUT} {printf("KW_MUT");return KW_MUT;}
{KW_PUB} {printf("KW_PUB");return KW_PUB;}
{KW_REF} {printf("KW_REF");return KW_REF;}
{KW_RETURN} {printf("KW_RETURN");return KW_RETURN;}
{KW_SELFVALUE} {printf("KW_SELFVALUE");return KW_SELFVALUE;}
{KW_SELFTYPE} {printf("KW_SELFTYPE");return KW_SELFTYPE;}
{KW_STATIC} {printf("KW_STATIC");return KW_STATIC;}
{KW_STRUCT} {printf("KW_STRUCT");return KW_STRUCT;}
{KW_SUPER} {printf("KW_SUPER");return KW_SUPER;}
{KW_TRAIT} {printf("KW_TRAIT");return KW_TRAIT;}
{KW_TRUE} {printf("KW_TRUE");return KW_TRUE;}
{KW_TYPE} {printf("KW_TYPE");return KW_TYPE;}
{KW_UNSAFE} {printf("KW_UNSAFE");return KW_UNSAFE;}
{KW_USE} {printf("KW_USE");return KW_USE;}
{KW_WHERE} {printf("KW_WHERE");return KW_WHERE;}
{KW_WHILE} {printf("KW_WHILE");return KW_WHILE;}

{DOC_COMMENT}|{INNER_LINE_DOC}|{INNER_BLOCK_DOC}|{SINGLE_LINE_COMMENT}|{EMPTY_MULTI} {;}
{MULTI_LINE_COMMENT} {comment();}
{CHARACTER} {printf("CHARACTER");installLiteral(yytext,"CHARACTER");return CHARACTER;}
{STRING} {printf("STRING");installLiteral(yytext,"STRING");return STRING;}
{RAW_STRING} {printf("RAW_STRING");return RAW_STRING;}
{BYTE} {printf("BYTE");installLiteral(yytext,"BYTE");;return BYTE;}
{BYTE_STRING} {printf("BYTE_STRING");return BYTE_STRING;}
{RAW_BYTE_STRING} {printf("RAW_BYTE_STRING");return RAW_BYTE_STRING;}
{IDENTIFIER_OR_KEYWORD} {printf("IDENTIFIER");return IDENTIFIER;}

{DECIMAL} {printf("DECIMAL");installLiteral(yytext,"DECIMAL");;return DECIMAL;}
".." {printf("RANGE");return RANGE;}
{HEX_INT} {printf("HEX_INT");return HEX_INT;}
{OCTAL_INT} {printf("OCTAL_INT");return OCTAL_INT;}
{BIN_INT} {printf("BIN_INT");return BIN_INT;}
{FLOAT} {printf("FLOAT");installLiteral(yytext,"FLOAT");return FLOAT;}
{STMT_TERMINATOR} {printf("STMT_TERMINATOR");return STMT_TERMINATOR;}
[0-9]+[a-zA-Z]+ {yyerror();return ERROR;}
{ARITH_OPERATOR}{2,} {yyerror();return ERROR;}
{COMMA} {printf("COMMA");return COMMA;}
. {yyerror();}
#EOF {dispLit();}
%%
void comment()
{
	char c, c1;
loop:
	while ((c = input()) != '*' && c != 0){
		
		if (c == '/'){
			if ((c1 = input()) == '*'){
				
				comment_stack_count++;
			}else{
				
				if (c1 == 0){
					break;	
				}
			}
		}
	}
	if ((c1 = input()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}
	
	comment_stack_count--;
	
	if (comment_stack_count > 0){
		goto loop;
	}else{
		comment_stack_count = 1;
	}
}
void yyerror(){
	printf("ERROR: \"%s\" on line: %d\n",yytext,yylineno);
}
void installLiteral(char *value, char *type) {
	strcpy(literalTable[lit].value, value);
	strcpy(literalTable[lit].type, type);
	lit++;
}
void dispLit(){
	int i;
	for (i = 0; i < lit; i++)
		printf("Literal: %s \t Type: %s \n", literalTable[i].value, literalTable[i].type);

}