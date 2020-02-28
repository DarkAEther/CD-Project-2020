%option yylineno
%{
#include <stdio.h>
#include "header.h"
#include "y.tab.h"
void comment();
void yyerror();
int comment_stack_count = 1;
int lit=0;
int scope=0;
int max_depth=0;

void dispLit();
void installLiteral(char *value,char *type);
void installID(char *name,int lno);
void dispST();

struct symtbl symbolTable;

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
KW_PRINTLN println!
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

ARITH_OPERATOR [+\-\/\*\%]
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
MAIN main
%%
{WHITE_SPACE} {printf(" ");}
\n {;}
{OPEN_BLOCK} {scope++;if(scope>max_depth){ max_depth=scope;};return OPEN_BLOCK;}
{CLOSE_BLOCK} {scope--;return CLOSE_BLOCK;}
{OPEN_PARANTHESIS} {return OPEN_PARANTHESIS;}
{CLOSE_PARANTHESIS} {return CLOSE_PARANTHESIS;}
{ASSIGN_OPS} {return ASSIGN_OPS;}
{ASSIGN} {return ASSIGN;}
{RELATIONAL} {return RELATIONAL;}
{ARITH_OPERATOR} {return ARITH;}
{BITWISE_OPERATOR} {return BITWISE;}
{KW_AS} {return KW_AS;}
{KW_BREAK} {return KW_BREAK;}
{KW_CONST} {return KW_CONST;}
{KW_CONTINUE} {return KW_CONTINUE;}
{KW_CRATE} {return KW_CRATE;}
{KW_ELSE} {return KW_ELSE;}

{KW_FN} {return KW_FN;}
{KW_FOR} {return KW_FOR;}
{KW_IF} {return KW_IF;}
{KW_IN} {return KW_IN;}
{KW_LET} {return KW_LET;}
{KW_LOOP} {return KW_LOOP;}
{KW_WHILE} {return KW_WHILE;}
{KW_PRINTLN} {return KW_PRINTLN;}
{MAIN} {return KW_MAIN;}
{DOC_COMMENT}|{INNER_LINE_DOC}|{INNER_BLOCK_DOC}|{SINGLE_LINE_COMMENT}|{EMPTY_MULTI} {;}
{MULTI_LINE_COMMENT} {comment();}
{CHARACTER} {installLiteral(yytext,"CHARACTER");return CHARACTER;}
{STRING} {installLiteral(yytext,"STRING");return STRING;}
{RAW_STRING} {return RAW_STRING;}
{BYTE} {printf("BYTE");installLiteral(yytext,"BYTE");;return BYTE;}
{BYTE_STRING} {printf("BYTE_STRING");return BYTE_STRING;}
{RAW_BYTE_STRING} {printf("RAW_BYTE_STRING");return RAW_BYTE_STRING;}
{IDENTIFIER_OR_KEYWORD} {installID(yytext,yylineno);return IDENTIFIER;}

{DECIMAL} {installLiteral(yytext,"DECIMAL");;return DECIMAL;}
".." {return RANGE;}
{HEX_INT} {printf("HEX_INT");return HEX_INT;}
{OCTAL_INT} {printf("OCTAL_INT");return OCTAL_INT;}
{BIN_INT} {printf("BIN_INT");return BIN_INT;}
{FLOAT} {installLiteral(yytext,"FLOAT");return FLOAT;}
{STMT_TERMINATOR} {return STMT_TERMINATOR;}
[0-9]+[a-zA-Z]+ {yyerror();return ERROR;}
{ARITH_OPERATOR}{2,} {yyerror();return ERROR;}
{COMMA} {return COMMA;}
#EOF {dispLit();dispST();return EOF;}
. {yyerror();}

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

void installLiteral(char *value, char *type) {
	strcpy(symbolTable.literalTable[lit].value, value);
	strcpy(symbolTable.literalTable[lit].type, type);
	lit++;
}
void dispLit(){
	int i;
	for (i = 0; i < lit; i++)
		printf("Literal: %s \t Type: %s \n", symbolTable.literalTable[i].value, symbolTable.literalTable[i].type);

}
void installID(char *name,int lno){
	int i;
	int present=1;
	for (i = 0; i < symbolTable.table[scope].count; i++){
		if(strcmp(symbolTable.table[scope].identifiers[i].name, name)==0){
			present=0;
			break;
		}
		
	}
	
	if(i==symbolTable.table[scope].count){
		int x=symbolTable.table[scope].count;
		strcpy(symbolTable.table[scope].identifiers[x].name, name);
		symbolTable.table[scope].identifiers[i].lineno=lno;
		symbolTable.table[scope].count++;

	}
	
}
void dispST(){
	int i=0;
	while(i<max_depth){
		int j=0;
		printf("Symbol Table at depth %d\n",i);
		while(j<symbolTable.table[i].count){
			printf("<Identifier,%s,value,datatype,%d> ",symbolTable.table[i].identifiers[j].name,symbolTable.table[i].identifiers[j].lineno);
			j++;
		}
		printf("\n");
		i++;

	}
}

void yyerror(char *s){
	printf("ERROR: \"%s\" on line: %d\n",s, yylineno);
}