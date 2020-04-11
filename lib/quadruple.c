#ifndef HEADER
#include "../header.h"
#include "quadruple.h"
#include "symtab_util.h"
#include "lookup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

void display_quad(QUAD* head_quad) {
    printf("Quadruple Format ICG\n");
    QUAD* temp = head_quad;
    printf("Op\tArg1\tArg2\tResult\n");
    int disc = -1;
    while(temp != NULL) {
        disc = -1;
        printf("%s\t", temp->op);fflush(stdout);
        if (temp->d_arg1 == 0) {
            //identifier
            printf("%s\t",temp->arg1.st_entry->name);
        }else if (temp->d_arg1 == 1){
            disc = temp->arg1.lt_entry->discriminator;
            switch (disc)
            {
            case 0:
                printf("%d\t", temp->arg1.lt_entry->value.integer);fflush(stdout);
                break;
            case 1:
                printf("%f\t", temp->arg1.lt_entry->value.floating);fflush(stdout);
                break;
            case 2:
                printf("%s\t", temp->arg1.lt_entry->value.character);fflush(stdout);
                break;
            case 3:
                printf("%s\t", temp->arg1.lt_entry->value.string);fflush(stdout);
                break;
            default:
                break;
            }
        }else{
            printf("NULL\t");
        }
        if (temp->d_arg2 == 0) {
            printf("%s\t", temp->arg2.st_entry->name);fflush(stdout);
        }else if (temp->d_arg2 == 1) {
            disc = temp->arg2.lt_entry->discriminator;
            switch (disc)
            {
            case 0:
                printf("%d\t", temp->arg2.lt_entry->value.integer);fflush(stdout);
                break;
            case 1:
                printf("%f\t", temp->arg2.lt_entry->value.floating);fflush(stdout);
                break;
            case 2:
                printf("%s\t", temp->arg2.lt_entry->value.character);fflush(stdout);
                break;
            case 3:
                printf("%s\t", temp->arg2.lt_entry->value.string);fflush(stdout);
                break;
            default:
                break;
            }
        }else{
            printf("NULL\t");
        }
        if (temp->d_res == 0) {
            printf("%s\n", temp->result.st_entry->name);fflush(stdout);
        }else {
            printf("%s\n", temp->result.l_val);fflush(stdout);
        }
        temp = temp->next;
    }
}

void insert_quad(QUAD** head_quad, QUAD* node) {
    struct quad* temp = *head_quad;
    node->next = NULL;
    if (*head_quad == NULL) {
        *head_quad =node;
    }else {
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void codegen_assign(int scope, NODE** STACK, int* top, QUAD** head_quad) {
    //printf("GENERATE CODE ASSIGN\n");
    QUAD* node = (QUAD*)malloc(sizeof(QUAD));
    strcpy(node->op, "=");
    //printf("top -2 NAME %s VALUE %d\n",STACK[*top-2]->value.value.string,STACK[*top-2]->PTR.st_ptr->value);fflush(stdout);
    //printf("top NAME %s VALUE %d\n",STACK[*top]->value.value.string,STACK[*top]->PTR.lt_ptr->value.integer);fflush(stdout);
    if (STACK[*top-2]->core_type == ID){
        //identifier - add symtab pointer
        node->d_res = 0;
        node->result.st_entry = STACK[*top-2]->PTR.st_ptr;
    }
    if (STACK[*top]->core_type == ID){
        //identifier - add symtab pointer
        node->d_arg1 = 0;
        node->arg1.st_entry = STACK[*top]->PTR.st_ptr;
    }else{
        //literal
        node->d_arg1 = 1;
        node->arg1.lt_entry = STACK[*top]->PTR.lt_ptr;
    }
    node->arg2.st_entry = NULL;
    node->d_arg2 = -1;
    node->next = NULL;
    insert_quad(head_quad, node);
    //printf("%s = %d\n",STACK[*top-2]->value.value.string, node->arg1.lt_entry->value.integer);
    *top = *top - 3;
}

void codegen(NODE** STACK, int* top, int* temp_count, int lineno, QUAD** head_quad,int scope,struct symtbl* ST) {
  //printf("Generate Code\n");
  char* tempvar = get_new_temp(*temp_count);
  *temp_count += 1;
  struct id* record = installID(ST,tempvar,scope,lineno);
  QUAD* qnode = (QUAD*)malloc(sizeof(QUAD));
  strcpy(qnode->op, STACK[*top-1]->value.value.string);
  qnode->result.st_entry = record;
  qnode->d_res = 0;
  qnode->next = NULL;
  if (STACK[*top-2]->core_type == ID){
      //Identifier
      qnode->arg1.st_entry = STACK[*top-2]->PTR.st_ptr;
      qnode->d_arg1 = 0;
  }else{
      //Literal
      qnode->arg1.lt_entry = STACK[*top-2]->PTR.lt_ptr;
      qnode->d_arg1 = 1;
  }
  if (STACK[*top]->core_type == ID){
      //Identifier
      qnode->arg2.st_entry = STACK[*top]->PTR.st_ptr;
      qnode->d_arg2 = 0;
  }else{
      //Literal
      qnode->arg2.lt_entry = STACK[*top]->PTR.lt_ptr;
      qnode->d_arg2 = 1;
  }
  insert_quad(head_quad, qnode);
 // printf("%s = %s %s %s\n",tempvar, STACK[*top-2]->value.value.string, qnode->op ,STACK[*top]->value.value.string);
  *top -= 3;
  NODE* new_node = get_new_node(tempvar,0,NULL,ID);
  new_node->PTR.st_ptr = record;
  push_value(new_node);
}

void lab1(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  struct quad* node1 = malloc(sizeof(struct quad));
  strcpy(node1->op, "ifFalse");
  char * labvar = get_new_label((*label_value)++);
  strcpy(node1->result.l_val, labvar);
  node1->d_res = 1;
  node1->next = NULL;
  node1->d_arg1 = 0;
  node1->arg1.st_entry = STACK[*top]->PTR.st_ptr;
  node1->d_arg2 = -1;
  node1->arg2.st_entry = NULL;
  insert_quad(head_quad, node1);
  *top--;
}

void lab2_noelse(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  char * labvar = get_new_label(*label_value-1);
  struct quad* node1 = malloc(sizeof(struct quad));
  strcpy(node1->op, "Label");
  strcpy(node1->result.l_val, labvar);
  node1->d_res = 1;
  node1->d_arg1 = -1;
  node1->d_arg2 = -1;
  node1->next = NULL;
  node1->arg1.st_entry = NULL;
  node1->arg2.st_entry = NULL;
  insert_quad(head_quad, node1);
}

void lab2_else(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  //codegen(STACK,top,temp_value,lineno,head_quad,scope,ST);
  char * labvar = get_new_label((*label_value)++);
  struct quad* node1 = malloc(sizeof(struct quad));
  strcpy(node1->op, "goto");
  strcpy(node1->result.l_val, labvar);
  node1->d_res = 1;
  node1->next = NULL;
  node1->d_arg1 = -1;
  node1->d_arg2 = -1;
  node1->arg1.st_entry = NULL;
  node1->arg2.st_entry = NULL;
  insert_quad(head_quad, node1);
  
  char * oldlabel = get_new_label(*label_value-2);
  QUAD* node2 = (QUAD*)malloc(sizeof(QUAD));
  strcpy(node2->op, "Label");
  strcpy(node2->result.l_val, oldlabel);
  node2->d_res = 1;
  node2->next = NULL;
  node2->d_arg1 = -1;
  node2->d_arg2 = -1;
  node2->arg1.st_entry = NULL;
  node2->arg2.st_entry = NULL;
  insert_quad(head_quad, node2);

}

void lab3(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  //codegen(STACK,top,temp_value,lineno,head_quad,scope,ST);
  char * labvar = get_new_label(*label_value-1);
  struct quad* node1 = malloc(sizeof(struct quad));
  strcpy(node1->op, "Label");
  strcpy(node1->result.l_val, labvar);
  node1->d_res = 1;
  node1->next = NULL;
  node1->d_arg1 = -1;
  node1->d_arg2 = -1;
  node1->arg1.st_entry = NULL;
  node1->arg2.st_entry = NULL;
  insert_quad(head_quad, node1);
}

void while_lab1(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  char * labvar = get_new_label((*label_value)++);
  struct quad* node1 = malloc(sizeof(struct quad));
  strcpy(node1->op, "Label");
  strcpy(node1->result.l_val, labvar);
  node1->d_res = 1;
  node1->next = NULL;
  node1->d_arg1 = -1;
  node1->d_arg2 = -1;
  node1->arg1.st_entry = NULL;
  node1->arg2.st_entry = NULL;
  insert_quad(head_quad, node1);
}

void while_lab2(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  struct quad* node1 = malloc(sizeof(struct quad));
  strcpy(node1->op, "ifFalse");
  char * labvar = get_new_label((*label_value)++);
  strcpy(node1->result.l_val, labvar);
  node1->d_res = 1;
  node1->next = NULL;
  node1->d_arg1 = 0;
  node1->arg1.st_entry = STACK[*top]->PTR.st_ptr;
  node1->d_arg2 = -1;
  node1->arg2.st_entry = NULL;
  insert_quad(head_quad, node1);
  *top--;
}

void while_lab3(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  struct quad* node1 = malloc(sizeof(struct quad));
  strcpy(node1->op, "goto");
  char * labvar = get_new_label(*label_value-2);
  strcpy(node1->result.l_val, labvar);
  node1->d_res = 1;
  node1->next = NULL;
  node1->d_arg1 = -1;
  node1->arg1.st_entry = NULL;
  node1->d_arg2 = -1;
  node1->arg2.st_entry = NULL;
  insert_quad(head_quad, node1);

  char * labvar1 = get_new_label(*label_value-1);
  struct quad* node2 = malloc(sizeof(struct quad));
  strcpy(node2->op, "Label");
  strcpy(node2->result.l_val, labvar1);
  node2->d_res = 1;
  node2->next = NULL;
  node2->d_arg1 = -1;
  node2->d_arg2 = -1;
  node2->arg1.st_entry = NULL;
  node2->arg2.st_entry = NULL;
  insert_quad(head_quad, node2);
}

void for_lab1(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  struct quad* node1 = malloc(sizeof(struct quad));
  //assigns initial value to loop iterator top - 1
  strcpy(node1->op, "=");
  node1->result.st_entry = STACK[*top-1]->PTR.st_ptr;
  node1->d_res = 0;
  node1->next = NULL;
  node1->d_arg1 = 1;
  node1->d_arg2 = -1;
  node1->arg1.lt_entry = STACK[*top]->PTR.lt_ptr;
  node1->arg2.st_entry = NULL;
  insert_quad(head_quad, node1);
  *top--;
}

void for_lab2(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  
  //create new relop and label
  //label
  char * labvar1 = get_new_label(*label_value);
  *label_value = *label_value + 1;
  struct quad* node3 = malloc(sizeof(struct quad));
  strcpy(node3->op, "Label");
  strcpy(node3->result.l_val, labvar1);
  node3->d_res = 1;
  node3->next = NULL;
  node3->d_arg1 = -1;
  node3->d_arg2 = -1;
  node3->arg1.st_entry = NULL;
  node3->arg2.st_entry = NULL;
  insert_quad(head_quad, node3);

  char* tempvar = get_new_temp(*temp_value);
  *temp_value += 1;
  struct id* record = installID(ST,tempvar,scope,lineno);
  QUAD* node1 = (QUAD*)malloc(sizeof(QUAD));
  strcpy(node1->op, "<");
  node1->d_res = 0;
  node1->result.st_entry = record;
  if (STACK[*top-2]->core_type == ID){
      //Identifier
      node1->arg1.st_entry = STACK[*top-2]->PTR.st_ptr;
      node1->d_arg1 = 0;
  }else{
      //Literal
      node1->arg1.lt_entry = STACK[*top-2]->PTR.lt_ptr;
      node1->d_arg1 = 1;
  }
  if (STACK[*top]->core_type == ID){
      //Identifier
      node1->arg2.st_entry = STACK[*top]->PTR.st_ptr;
      node1->d_arg2 = 0;
  }else{
      //Literal
      node1->arg2.lt_entry = STACK[*top]->PTR.lt_ptr;
      node1->d_arg2 = 1;
  }
  insert_quad(head_quad, node1);

  //create ifFalse
  struct quad* node2 = malloc(sizeof(struct quad));
  strcpy(node2->op, "ifFalse");
  char * labvar = get_new_label(*label_value);
  *label_value = *label_value+1;
  strcpy(node2->result.l_val, labvar);
  node2->d_res = 1;
  node2->next = NULL;
  node2->d_arg1 = 0;
  node2->arg1.st_entry = record;
  node2->d_arg2 = -1;
  node2->arg2.st_entry = NULL;
  insert_quad(head_quad, node2);
}

void for_lab3(struct symtbl * ST,NODE** STACK,int* top, int* temp_value, int* label_value, int scope, int lineno,QUAD** head_quad) {
  //generate increment
  char* tempvar = get_new_temp(*temp_value-2);
  struct id* record = installID(ST,tempvar,scope,lineno);
  struct literal* increment = lookup_LT(ST,"1");
  QUAD* node1 = (QUAD*)malloc(sizeof(QUAD));
  strcpy(node1->op, "+");
  node1->result.st_entry = record;
  node1->d_res = 0;
  node1->next = NULL;
  node1->d_arg1 = 1;
  node1->d_arg2 = 0;
  node1->arg1.lt_entry = increment;
  node1->arg2.st_entry = STACK[*top-2]->PTR.st_ptr; // loop control
  insert_quad(head_quad, node1);
  
  //assign to loop control
  QUAD* node3 = (QUAD*)malloc(sizeof(QUAD));
  strcpy(node3->op, "=");
  node3->result.st_entry = STACK[*top-2]->PTR.st_ptr;
  node3->d_res = 0;
  node3->next = NULL;
  node3->d_arg1 = 0;
  node3->d_arg2 = -1;
  node3->arg1.st_entry = record;
  node3->arg2.st_entry = NULL; // loop control
  insert_quad(head_quad, node3);
  
  struct quad* node4 = malloc(sizeof(struct quad));
  strcpy(node4->op, "goto");
  char * labvar = get_new_label(*label_value-2);
  strcpy(node4->result.l_val, labvar);
  node4->d_res = 1;
  node4->next = NULL;
  node4->d_arg1 = -1;
  node4->arg1.st_entry = NULL;
  node4->d_arg2 = -1;
  node4->arg2.st_entry = NULL;
  insert_quad(head_quad, node4);

  char * labvar1 = get_new_label(*label_value-1);
  struct quad* node2 = malloc(sizeof(struct quad));
  strcpy(node2->op, "Label");
  strcpy(node2->result.l_val, labvar1);
  node2->d_res = 1;
  node2->next = NULL;
  node2->d_arg1 = -1;
  node2->d_arg2 = -1;
  node2->arg1.st_entry = NULL;
  node2->arg2.st_entry = NULL;
  insert_quad(head_quad, node2);
}
