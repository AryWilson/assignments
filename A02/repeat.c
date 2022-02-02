#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
        char word[32];
        int count;
        printf("enter a word: ");
        scanf("%s",word);
        printf("\n"); 
        printf("enter a count: ");
        scanf("%i",&count);
        printf("\n");
        char *toPrint;
        toPrint = malloc(sizeof(int)*32*count+1);
        if(toPrint ==NULL){
                printf("Cannot allocate new string. Exiting...\n");
                exit(1);
        }
        for(int i =0;i<count;i++){
                strcat(toPrint,word);
        } 
        printf("your word is: %s\n",toPrint);
        free(toPrint);
        toPrint = NULL;
        return 0;
}
