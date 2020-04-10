#ifndef HEADER
#include "../header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#endif

struct id* lookup_ST(struct symtbl* ST, char* target, int scope){
    //int found = 0;
    for (int k = scope; k >= 0; k--){ //check from current scope going upwards
        for (int j = 0; j < ST->table[k].count; j++){
            printf("%s %s #%s#\n",target,ST->table[k].identifiers[j].name,ST->table[k].identifiers[j].type);fflush(stdout);
            if (strcmp(target,ST->table[k].identifiers[j].name) == 0){
                //found
                //found = 1;
                return (ST->table[k].identifiers + j);
            }
        }
    }
    return NULL;
}

struct literal* lookup_LT(struct symtbl* ST, char* target){ //type is discriminator
    for (int k = 0; k < ST->literal_count;k++){
        if (ST->literalTable[k].discriminator == 0){
          if(ST->literalTable[k].value.integer == atoi(target)){
            return ST->literalTable +k;
            break;
          }
        }else{
          if (ST->literalTable[k].discriminator == 1){
            
            if(ST->literalTable[k].value.floating == atof(target)){
              return ST->literalTable+k;
              break;
            }
          }else{
            if (ST->literalTable[k].discriminator == 2){
              if(strcmp(ST->literalTable[k].value.character,target)==0){
                return ST->literalTable +k;
                break;
              }
            }else{
              if (ST->literalTable[k].discriminator == 3){
                if(strcmp(ST->literalTable[k].value.string, target)==0){
                  return ST->literalTable+k;
                  break;
                }
              }
            }
          }
        }
      
    }
    return NULL;
}