#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  float cost;
  int quantity;
};

void addNew(struct snack *iSnack){
  char name[32];
  float cost;
  int quantity;  
  printf("enter a name: ");
  scanf("%s",name);
  printf("\n");
  
  printf("enter a cost: ");
  scanf("%f",&cost);
  printf("\n");
  
  printf("enter a quantity: ");
  scanf("%i",&quantity);
  printf("\n");
  
  strcpy(iSnack->name,name);
  iSnack->cost = cost;
  iSnack->quantity = quantity;

}


int main() {
  int snackCount; 
  printf("enter a number of snacks: ");
  scanf("%i",&snackCount);
  printf("\n");
  
  struct snack *theSnacks;
  theSnacks = malloc(sizeof(struct snack)*snackCount);
  if(theSnacks==NULL){
    printf("Malloc error. Exiting...\n");
    exit(1);
  }
  for(int i =0;i<snackCount;i++){
    addNew(&(theSnacks[i]));
  }
  
	for(int i=0;i<snackCount;i++){
    printf("%i)\t",i);
		printf("%s \t",theSnacks[i].name);
		printf("cost: %f \t",theSnacks[i].cost);
		printf("quantity: %i \n",theSnacks[i].quantity);
	}	
  free(theSnacks);
  theSnacks = NULL;
  return 0;
}
