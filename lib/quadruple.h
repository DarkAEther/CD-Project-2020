#ifndef HEADER
#include "../header.h"
#endif

union entry {
  struct id* st_entry;
  struct literal* lt_entry;
  char l_val[30];
};

typedef struct quad {
  int d_arg1;
  int d_arg2;
  int d_res;
  /*
  0 : ST
  1 : LT
  */
  char op[10];
  union entry arg1;
  union entry arg2;
  union entry result;
  struct quad* next;
} QUAD;

extern void display_quad(QUAD*);
extern void insert_quad(QUAD**, QUAD*);
extern void codegen(NODE** STACK, int* top, int* temp_count, int lineno, QUAD** head_quad,int scope,struct symtbl* ST);
extern void codegen_assign(int scope, NODE** STACK, int* top, QUAD** head_quad);
extern void lab1(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void lab3(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void lab2_else(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void lab2_noelse(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void while_lab1(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void while_lab2(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void while_lab3(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void for_lab1(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void for_lab2(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
extern void for_lab3(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad);
 