#ifndef HEADER
#include "../header.h"
#endif

extern struct literal* installLiteral(struct symtbl* symbolTable,char *value, char *type);
extern void dispLit(struct symtbl* symbolTable);
extern struct id* installID(struct symtbl* symbolTable,char *name,int scope,int lno);
extern void dispST(struct symtbl* symbolTable,int max_depth);