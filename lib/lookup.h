#ifndef HEADER
#include "../header.h"
#endif
extern struct id* lookup_ST(struct symtbl* , char*, int );
extern struct literal* lookup_LT(struct symtbl* , char* );
extern struct id* lookup_ST_declared(struct symtbl* ST, char* target, int scope);
