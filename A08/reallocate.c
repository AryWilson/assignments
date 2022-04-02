#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {
  void *init = sbrk(0);
  void* current;
  void* end; 
  for (int i = 1; i <= 10; i++){
    int *memory = malloc(100);
    if(memory == NULL){
      printf("malloc failed\n");
      exit(1);
    }
    
  current = sbrk(0);
  int allocated = (int) (( current - init)); // /1.024
  printf("Round: %d \nCurrent top of heap = %p\nIncrease: %d Bytes\n",i,current,allocated);
  *memory = 123;
  free(memory);  
  memory = NULL;
  end = sbrk(0); 
  } 

  printf("After all frees: %p\n",end);
  return 0 ;
}
