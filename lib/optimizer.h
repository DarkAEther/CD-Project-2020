#ifndef HEADER
#include "../header.h"
#include "quadruple.h"
#endif

extern void remove_temp_assigns(QUAD* quad_table);
extern void CSE(QUAD* quad_table);
extern int const_prop(QUAD* head);
extern int const_fold(QUAD* head, struct symtbl* ST);
extern void deadcode_removal(QUAD* head);
extern void remove_dead_variables(QUAD** head);