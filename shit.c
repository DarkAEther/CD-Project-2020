for (int j = 0; j < symbolTable.table[scope].count; j++){
        if (strcmp($2,symbolTable.table[scope].identifiers[j].name) == 0){
                       strcpy(symbolTable.table[scope].identifiers[j].value, $4);
                       for (int k = 0; k < 500;k++){
                                if(strcmp(symbolTable.literalTable[k].value,$4)==0){
                                        strcpy(symbolTable.table[scope].identifiers[j].dtype, symbolTable.literalTable[k].type);
                                 }
                       }
          }
}
