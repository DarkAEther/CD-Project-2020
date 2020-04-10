a.out: y.tab.c lex.yy.c header.h library
	gcc -g lex.yy.c y.tab.c header.h ./lib/lookup.c ./lib/lookup.h ./lib/quadruple.c ./lib/quadruple.h ./lib/queue.c ./lib/queue.h ./lib/symtab_util.c ./lib/symtab_util.h ./lib/optimizer.h ./lib/optimizer.c -lfl -ll -Wall -Wextra -Wconversion -pedantic -std=gnu11 -w
generate: lex.yy.c y.tab.c library
lex.yy.c: lex.l y.tab.c ./lib/symtab_util.c ./lib/symtab_util.h
	flex lex.l
y.tab.c: pointer.y
	yacc -d pointer.y
library: ./lib/* header.h