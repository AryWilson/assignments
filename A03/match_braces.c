//---------------------------------------------------------------------
// match_braces.c 
// CS223 - Spring 2022
// Identify matched braces from a given file
// Name: Ary Wilson
//
#include <stdio.h>
#include <stdlib.h>

struct node {
  char sym;
  int linenum;
  int colnum;
  struct node* next;
};

// Push a new node to a stack (implemented as a linked list). 
// The new node should store the given symbol, line number, and column number
// Param sym: a character symbol, '{' for this program
// Param line: the line number of the symbol
// Param line: the column number of the symbol
// Param top: the top node of the stack (NULL if empty)
// Returns the new top of the stack
struct node* push(char sym, int line, int col, struct node* top) {
  struct node* n = malloc(sizeof(struct node));
  if (n == NULL) {
    printf("ERROR: Out of space!\n");
    exit(1);
  }
  n->sym = sym;
  n->linenum = line;
  n->colnum = col;
  if(top==NULL){
    n->next = NULL;
    return n;
  }else {
    n->next = top;
    return n;
  }
  return n;
}

// Pop the top node from a stack (implemented as a linked list) and frees it
// Param top: the top node of the current stack (NULL if empty)
// Returns the new top of the stack
struct node* pop(struct node* top) {
  if(top==NULL){
    return NULL;  
  }
  struct node* ntop = top->next;
  free(top);
  top=NULL;
  return ntop;
}

// Delete (e.g. free) all nodes in the given stack
// Param top: the top node of the stack (NULL if empty)
void clear(struct node* top) {
  if(top == NULL){
    return;
  }
  clear(pop(top));
  return;
}

// Print all nodes in the given stack (from top to bottom)
// Param top: the top node of the stack (NULL if empty)
void print(struct node* top) {
  if(top == NULL){ return;}
  struct node* temp = top;
  while(temp->next != NULL){
    printf("(%d %d ), %c\n",temp->linenum,temp->colnum,temp->sym);
    temp = temp->next;
  }

}

int main(int argc, char* argv[]) {
  if(argc != 2){
    printf("Program expects 2 command line arguments. Exiting... \n");
    exit(1);
  }
  FILE *infile;
  infile = fopen(argv[1],"r"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", argv[1]);
    exit(1);
  }
  
  struct node* head = NULL;
  int acol = 0;
  int arow = 1;
  char ch=' ';
  
  while(ch != EOF){
    ch = fgetc(infile);
    acol++;
    if(ch == '\n'){
      acol=0;
      arow++;
    } else if(ch == '{'){
      //printf("ch = %c,arow = %d,acol = %d\n",ch,arow,acol);
      head = push(ch,arow,acol,head);
      //print(head);
    } else if (ch == '}'){
      //print(head);
      if(head==NULL){ 
        printf("Unmatched brace on Line %d and Column %d\n",arow,acol);
      } else if(head->sym == '{'){
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n",
                head->linenum,head->colnum,arow,acol);
      } else {
        printf("Unmatched brace on Line %d and Column %d\n",arow,acol);
      }
      head = pop(head);
    }
  }

  while(head != NULL){
    printf("Unmatched brace on Line %d and Column %d\n",
            head->linenum,head->colnum);
    head = pop(head);
  }  

  clear(head); 
  fclose(infile);
  return 0;
}
