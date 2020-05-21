#ifndef HEADER
#include "../header.h"
#include "quadruple.h"
#include "symtab_util.h"
#include "lookup.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimizer.h"
#endif

void remove_dead_variables(QUAD** head){
    QUAD* temp = *head;
    QUAD* internal = NULL;
    QUAD* prev = NULL;
    while (temp->next != NULL){
        int delete = 1;
        if (temp->d_res == 0){
            //symbol table entry - uses a variable
           
            internal = temp->next;
            while (internal!=NULL){
                if (internal->d_arg1 == 0){
                    if (strcmp(internal->arg1.st_entry->name,temp->result.st_entry->name)==0){
                        //variable is being used here. Can't kill it.
                        delete = 0;
                        break;
                    }
                }
                if (internal->d_arg2 == 0){
                    if (strcmp(internal->arg2.st_entry->name,temp->result.st_entry->name)==0){
                        //variable is being used here. Can't kill it.
                        delete = 0;
                        break;
                    }
                }
                if (strcmp(internal->op,"goto") == 0 && (internal->next!=NULL && strcmp(internal->next->op,"Label")==0)){
                    if (strcmp(internal->result.l_val,internal->next->result.l_val) < 0){
                        //the goto is before the next label (this is a loop)
                        //start looking for the label from head
                        QUAD* tempsearch = *head;
                        //QUAD* tempsearch = NULL;
                        while (tempsearch->next!=NULL){
                            if (strcmp(tempsearch->op,"Label") == 0 && strcmp(tempsearch->result.l_val,internal->result.l_val)==0){
                                    tempsearch = tempsearch->next; //starting position
                                    if (tempsearch->d_arg1 == 0){
                                        if (strcmp(tempsearch->arg1.st_entry->name,temp->result.st_entry->name)==0){
                                            //variable is being used here. Can't kill it.
                                            delete = 0;
                                            break;
                                        }
                                    }
                                    if (tempsearch->d_arg2 == 0){
                                        if (strcmp(tempsearch->arg2.st_entry->name,temp->result.st_entry->name)==0){
                                            //variable is being used here. Can't kill it.
                                            delete = 0;
                                            break;
                                        }
                                    }
                            }
                            tempsearch = tempsearch->next;
                        }
                        if (delete ==0){
                            break;
                        }
                    }
                }
                internal = internal->next;
            }      
        }
         if (temp->d_res == 0 && delete == 1){
                //var was not detected elsewhere, remove the entry
                if (prev != NULL){
                    prev->next = temp->next;
                    free(temp);
                    temp = prev->next;
                }else{
                    QUAD* t = temp;
                    temp = temp->next;
                    free(t);
                    *head = temp;
                }
                
        }else{
                prev = temp;
                temp = temp->next;
        }
        
    }
}

void remove_temp_assigns(QUAD* quad_table){
    QUAD* temp = quad_table;
    QUAD* next = NULL;
    while (temp->next->next != NULL){
        if (strcmp(temp->op,"+")==0 || strcmp(temp->op,"-")==0 || strcmp(temp->op,"*")==0 || strcmp(temp->op,"/")==0){
            //an operation, potential assignment
            next = temp->next;
            if (strcmp("=",next->op) == 0 && next->d_arg2 == -1 ){
                temp->result.st_entry = next->result.st_entry;
                temp->next = next->next;
                free(next);
            }
        }
        temp = temp->next;
    }
}

void CSE(QUAD* quad_table){
    QUAD* temp = quad_table;
    QUAD* traverser = NULL;
    QUAD* latest_match = NULL; // used since we use singly linked list
    
    while (temp != NULL){
        //Traverse through the ICG to find operations to optimize
        if (strcmp(temp->op,"+")==0 || strcmp(temp->op,"-")==0 || strcmp(temp->op,"*")==0 || strcmp(temp->op,"/")==0 ){
            //arith ops
            traverser = quad_table;
            latest_match = NULL;
            while (traverser != temp){
                if (strcmp(traverser->op,temp->op) == 0){ //is the operation identical?
                    int a1_match = 0;
                    if (traverser->d_arg1 == 0 && temp->d_arg1 ==0){
                        if (strcmp(traverser->arg1.st_entry->name,temp->arg1.st_entry->name)==0){
                            //matched
                            a1_match = 1;
                        }
                    }else if (traverser->d_arg1 == 1 && temp->d_arg1 == 1)
                    {
                        if (traverser->arg1.lt_entry == temp->arg1.lt_entry){
                            a1_match = 1;
                        }
                    }
                    
                    int a2_match = 0;
                    if (traverser->d_arg2 == 0 && temp->d_arg2 ==0){
                        if (strcmp(traverser->arg2.st_entry->name,temp->arg2.st_entry->name)==0){
                            //matched
                            a2_match = 1;
                        }
                    }else if (traverser->d_arg2 == 1 && temp->d_arg2 == 1)
                    {
                        if (traverser->arg2.lt_entry == temp->arg2.lt_entry){
                            a2_match = 1;
                        }
                    }
                    if (a1_match == 1 && a2_match == 1){
                        //operation match_up, add to stack
                        latest_match = traverser;
                    }
                }
                traverser = traverser->next;
            }
            //check in between latest and current for any edits to the arguments
            if (latest_match != NULL){
                traverser = latest_match->next;
                int allow_optimization = 1;
                while (traverser!= temp){
                    int arg1_changed = 0;
                    if (traverser->d_res == 0 && temp->d_arg1 == 0 && (strcmp(traverser->result.st_entry->name,temp->arg1.st_entry->name)==0)){
                        arg1_changed = 1;
                    }
                    int arg2_changed = 0;
                    if (traverser->d_res == 0 && temp->d_arg2 == 0 && (strcmp(traverser->result.st_entry->name,temp->arg2.st_entry->name)==0)){
                        arg2_changed = 1;
                    }
                    if (arg2_changed == 1 || arg1_changed == 1){
                        allow_optimization = 0;
                        break;
                    }
                    traverser = traverser->next;
                }
                if (allow_optimization == 1){//no changes, proceed
                    strcpy(temp->op,"=");
                    temp->arg1.st_entry = latest_match->result.st_entry;
                    temp->d_arg2 = -1;
                    temp->arg2.st_entry = NULL; //SHORTCUT may be wrong
                }
            }
        }
        temp = temp->next;
    }
}   

int const_prop(QUAD* head){
    QUAD* temp = head;
    QUAD* traverser = NULL;
    QUAD* prev = NULL;
    int changed = 0;
    int label_state = 0;
    while (temp->next->next!= NULL){
        if (strcmp(temp->op,"=")==0 && temp->d_arg2 == -1){ //check for value assignments
            prev = traverser;
            traverser = temp->next;
            label_state = 0;
            while (traverser != NULL){
                if (strcmp(traverser->op,"ifFalse")==0){
                    //printf("LABEL SET 1\n");
                    label_state = 1;
                }else
                if (strcmp(traverser->op,"goto")==0 || strcmp(traverser->op,"Label")==0){
                    label_state = 0;
                    //printf("LABEL SET 0\n");
                }
                if (label_state == 0 && (prev!=NULL && strcmp(prev->op,"Label")!= 0) && (traverser->next!=NULL && strcmp(traverser->next->op,"ifFalse")!=0)){
                    if (traverser->d_arg1 == 0 && strcmp(traverser->arg1.st_entry->name,temp->result.st_entry->name)==0){
                        //argument one is the same variable
                        traverser->d_arg1 = 1;
                        traverser->arg1.lt_entry = temp->arg1.lt_entry;
                        changed = 1;
                    }
                    if (traverser->d_arg2 == 0 && strcmp(traverser->arg2.st_entry->name,temp->result.st_entry->name)==0){
                        //argument two is the same variable
                        traverser->d_arg2 = 1;
                        traverser->arg2.lt_entry = temp->arg1.lt_entry;
                        changed = 1;
                    }
                    
                }
                if (traverser->d_res == 0 && strcmp(traverser->result.st_entry->name,temp->result.st_entry->name)==0){
                        break; // the value may have been updated..stop propagating
                }
                prev = traverser;
                traverser = traverser->next;
            }
        }
        temp = temp->next;
    }
    return changed;
}

int const_fold(QUAD* head, struct symtbl* ST){
    QUAD* temp = head;
    QUAD* traverser = NULL;
    int changed = 0;
    while (temp->next!= NULL){
        if (strcmp(temp->op,"+")==0 || strcmp(temp->op,"-")==0 || strcmp(temp->op,"*")==0 || strcmp(temp->op,"/")==0 ){
            //folding for arithmetic operations
            if (temp->d_arg1 == 1 && temp->d_arg2 == 1){
                //both the arguments are literals.. we can fold
                if (strcmp(temp->op,"+")==0){
                    if (temp->arg1.lt_entry->discriminator==0 && temp->arg2.lt_entry->discriminator==0){
                        //both are decimals
                        int t = temp->arg1.lt_entry->value.integer + temp->arg2.lt_entry->value.integer;
                        char buff[100];
                        snprintf(buff,99,"%d",t);
                        struct literal* new_literal = installLiteral(ST,buff,"DECIMAL");
                        strcpy(temp->op,"=");
                        temp->d_arg1 = 1;
                        temp->arg1.lt_entry = new_literal;
                        temp->d_arg2 = -1;
                        temp->arg2.lt_entry = NULL;
                        changed = 1;
                    }
                    if (temp->arg1.lt_entry->discriminator==1 && temp->arg2.lt_entry->discriminator==1){
                        //both are floats
                        float t = temp->arg1.lt_entry->value.floating + temp->arg2.lt_entry->value.floating;
                        char buff[100];
                        snprintf(buff,99,"%f",t);
                        struct literal* new_literal = installLiteral(ST,buff,"FLOAT");
                        strcpy(temp->op,"=");
                        temp->d_arg1 = 1;
                        temp->arg1.lt_entry = new_literal;
                        temp->d_arg2 = -1;
                        temp->arg2.lt_entry = NULL;
                         changed = 1;
                    }
                }
                if (strcmp(temp->op,"-")==0){
                    if (temp->arg1.lt_entry->discriminator==0 && temp->arg2.lt_entry->discriminator==0){
                        //both are decimals
                        int t = temp->arg1.lt_entry->value.integer - temp->arg2.lt_entry->value.integer;
                        char buff[100];
                        snprintf(buff,99,"%d",t);
                        struct literal* new_literal = installLiteral(ST,buff,"DECIMAL");
                        strcpy(temp->op,"=");
                        temp->d_arg1 = 1;
                        temp->arg1.lt_entry = new_literal;
                        temp->d_arg2 = -1;
                        temp->arg2.lt_entry = NULL;
                         changed = 1;
                    }
                    if (temp->arg1.lt_entry->discriminator==1 && temp->arg2.lt_entry->discriminator==1){
                        //both are floats
                        float t = temp->arg1.lt_entry->value.floating - temp->arg2.lt_entry->value.floating;
                        char buff[100];
                        snprintf(buff,99,"%f",t);
                        struct literal* new_literal = installLiteral(ST,buff,"FLOAT");
                        strcpy(temp->op,"=");
                        temp->d_arg1 = 1;
                        temp->arg1.lt_entry = new_literal;
                        temp->d_arg2 = -1;
                        temp->arg2.lt_entry = NULL;
                         changed = 1;
                    }
                }
                 if (strcmp(temp->op,"*")==0){
                    if (temp->arg1.lt_entry->discriminator==0 && temp->arg2.lt_entry->discriminator==0){
                        //both are decimals
                        int t = temp->arg1.lt_entry->value.integer * temp->arg2.lt_entry->value.integer;
                        char buff[100];
                        snprintf(buff,99,"%d",t);
                        struct literal* new_literal = installLiteral(ST,buff,"DECIMAL");
                        strcpy(temp->op,"=");
                        temp->d_arg1 = 1;
                        temp->arg1.lt_entry = new_literal;
                        temp->d_arg2 = -1;
                        temp->arg2.lt_entry = NULL;
                         changed = 1;
                    }
                    if (temp->arg1.lt_entry->discriminator==1 && temp->arg2.lt_entry->discriminator==1){
                        //both are floats
                        float t = temp->arg1.lt_entry->value.floating * temp->arg2.lt_entry->value.floating;
                        char buff[100];
                        snprintf(buff,99,"%f",t);
                        struct literal* new_literal = installLiteral(ST,buff,"FLOAT");
                        strcpy(temp->op,"=");
                        temp->d_arg1 = 1;
                        temp->arg1.lt_entry = new_literal;
                        temp->d_arg2 = -1;
                        temp->arg2.lt_entry = NULL;
                         changed = 1;
                    }
                }
                if (strcmp(temp->op,"/")==0){
                    if (temp->arg1.lt_entry->discriminator==0 && temp->arg2.lt_entry->discriminator==0){
                        //both are decimals
                        int t = temp->arg1.lt_entry->value.integer / temp->arg2.lt_entry->value.integer;
                        char buff[100];
                        snprintf(buff,99,"%d",t);
                        struct literal* new_literal = installLiteral(ST,buff,"DECIMAL");
                        strcpy(temp->op,"=");
                        temp->d_arg1 = 1;
                        temp->arg1.lt_entry = new_literal;
                        temp->d_arg2 = -1;
                        temp->arg2.lt_entry = NULL;
                         changed = 1;
                    }
                    if (temp->arg1.lt_entry->discriminator==1 && temp->arg2.lt_entry->discriminator==1){
                        //both are floats
                        float t = temp->arg1.lt_entry->value.floating / temp->arg2.lt_entry->value.floating;
                        char buff[100];
                        snprintf(buff,99,"%f",t);
                        struct literal* new_literal = installLiteral(ST,buff,"FLOAT");
                        strcpy(temp->op,"=");
                        temp->d_arg1 = 1;
                        temp->arg1.lt_entry = new_literal;
                        temp->d_arg2 = -1;
                        temp->arg2.lt_entry = NULL;
                         changed = 1;
                    }
                }
            }
        }
        temp = temp->next;
    }
    return changed;
}

void deadcode_removal(QUAD* head){
    //this will take care of if statements with unreachable code
    QUAD* preprev = NULL;
    QUAD* prev = NULL;
    QUAD* temp = head;
    int changed = 0;
    while (temp->next!=NULL){
        //find ifFalses
        changed = 0;
        if (strcmp(temp->op, "ifFalse") == 0){
            if (prev != NULL){
                //look at the prev to check the condition
                if (prev->d_arg1 == 1 && prev->d_arg2 == 1){
                    //both literals.. can compute
                    if (strcmp(prev->op,"<")==0){
                        if (prev->arg1.lt_entry->discriminator == 0 && prev->arg2.lt_entry->discriminator == 0){
                            //both integers
                            if (prev->arg1.lt_entry->value.integer < prev->arg2.lt_entry->value.integer){
                                //evaluates to true always, not a problem
                            }else{
                                //evaluates to false.. everything inside if block is dead code
                                while (strcmp(temp->op,"Label") != 0){
                                    prev = temp;
                                    temp = temp->next;
                                }
                                preprev->next = temp;
                                changed = 1;
                            }
                        }else
                        if (prev->arg1.lt_entry->discriminator == 1 && prev->arg2.lt_entry->discriminator == 1){
                            //both integers
                            if (prev->arg1.lt_entry->value.floating < prev->arg2.lt_entry->value.floating){
                                //evaluates to true always, not a problem
                            }else{
                                //evaluates to false.. everything inside if block is dead code
                                while (strcmp(temp->op,"Label") != 0){
                                    prev = temp;
                                    temp = temp->next;
                                }
                                preprev->next = temp;
                                changed = 1;
                            }
                        }
                    }
                    if (strcmp(prev->op,">")==0){
                        if (prev->arg1.lt_entry->discriminator == 0 && prev->arg2.lt_entry->discriminator == 0){
                            //both integers
                            if (prev->arg1.lt_entry->value.integer > prev->arg2.lt_entry->value.integer){
                                //evaluates to true always, not a problem
                            }else{
                                //evaluates to false.. everything inside if block is dead code
                                while (strcmp(temp->op,"Label") != 0){
                                    prev = temp;
                                    temp = temp->next;
                                }
                                preprev->next = temp;
                                changed = 1;

                            }
                        }else
                        if (prev->arg1.lt_entry->discriminator == 1 && prev->arg2.lt_entry->discriminator == 1){
                            //both integers
                            if (prev->arg1.lt_entry->value.floating > prev->arg2.lt_entry->value.floating){
                                //evaluates to true always, not a problem
                            }else{
                                //evaluates to false.. everything inside if block is dead code
                                while (strcmp(temp->op,"Label") != 0){
                                    prev = temp;
                                    temp = temp->next;
                                }
                                preprev->next = temp;
                                changed = 1;
                            }
                        }
                    }
                    if (strcmp(prev->op,"==")==0){
                        if (prev->arg1.lt_entry->discriminator == 0 && prev->arg2.lt_entry->discriminator == 0){
                            //both integers
                            if (prev->arg1.lt_entry->value.integer == prev->arg2.lt_entry->value.integer){
                                //evaluates to true always, not a problem
                            }else{
                                //evaluates to false.. everything inside if block is dead code
                                while (strcmp(temp->op,"Label") != 0){
                                    prev = temp;
                                    temp = temp->next;
                                }
                                preprev->next = temp;
                                changed = 1;
                            }
                        }else
                        if (prev->arg1.lt_entry->discriminator == 1 && prev->arg2.lt_entry->discriminator == 1){
                            //both integers
                            if (prev->arg1.lt_entry->value.floating == prev->arg2.lt_entry->value.floating){
                                //evaluates to true always, not a problem
                            }else{
                                //evaluates to false.. everything inside if block is dead code
                                while (strcmp(temp->op,"Label") != 0){
                                    prev = temp;
                                    temp = temp->next;
                                }
                                preprev->next = temp;
                                changed = 1;
                            }
                        }
                    }
                }
            }
        }
        if (changed == 0){
            preprev = prev;
            prev = temp;
            temp = temp->next;
        }
    }
}