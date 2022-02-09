//---------------------------------------------------------------------
// sorted_snackbar.c 
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name:
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  int quantity;
  float cost;
  struct snack* next;
};

// Insert a new node to a list (implemented as a linked list). 
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks, 
  const char* name, int quantity, float cost) {
//construct n
  struct snack* n = malloc(sizeof(struct snack));//error
  if (n == NULL) {
    printf("ERROR: Out of space!\n");
    exit(1);
  }
  strcpy(n->name,name);
  n->cost = cost;
  n->quantity = quantity;

//if list is empty
  if(snacks==NULL){
    n->next = NULL;
    return n;
  }

//if n is firt in the list
  if(strcmp(n->name,snacks->name)<=0){
    n->next = snacks;
    return n;
  }
  
//if n is in the middle of the list
  struct snack* temp=snacks;
  while(temp->next != NULL){
    struct snack* tempNext = temp->next;
    if(strcmp((n->name),(tempNext->name))<=0){
      temp->next = n;
      n->next = tempNext;
      return snacks;
    } 
    temp = temp->next;
  }
  temp->next = n;
  return snacks;
}

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
  struct snack* tempHead = snacks;
  while(snacks->next != NULL){
    tempHead = snacks->next;
    free(snacks);
    snacks = NULL;
    snacks = tempHead; 
  }
  free(tempHead);
  tempHead = NULL;

}

int main() { 
  int snackCount; 
  printf("enter a number of snacks: ");
  scanf("%i",&snackCount);
  printf("\n");
 
  struct snack* head = NULL;
  for (int i = 0;i<snackCount;i++){
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
  
    head = insert_sorted(head,name,quantity,cost);//error
  } 

  printf("Welcome to the Sorted Snackbar!\n");
  struct snack* toPrint = head;
  for(int i =0;i<snackCount;i++){
    printf("%d) %s \t cost: $%.2f \t quantity: %d\n",i,toPrint->name,toPrint->cost,toPrint->quantity); 
    toPrint = toPrint->next; 
  }
  clear(head);
  head = NULL;
  return 0;
}

