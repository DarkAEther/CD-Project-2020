#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char la[20];
    char s1[20];
    int lnum = 2;
    sprintf(s1, "%d", lnum);
    strcpy(la, "L");
    strcat(la, s1);
    printf("%s\n", la);
}
