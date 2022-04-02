#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

struct chunk {
  int size;
  int in_use;
  struct chunk *next;
};
struct chunk *flist = NULL;

void *malloc (size_t size) {
  if (size == 0){
    return NULL;
  }
  struct chunk *next = flist;
  struct chunk *prev = NULL;
  
  while(next!=NULL){
    if(next->size >= size){
      if(prev != NULL){
        prev->next = next->next;  
      }else {flist = next->next;}
      next->in_use = size;
      return (void*)(next+1);
    }else {
      prev = next;
      next = next->next;
    }
  }
  
  void *memory = sbrk(size + sizeof(struct chunk));
  if (memory == (void *) -1) {
    return NULL;
  } else {
    struct chunk* new = (struct chunk*) memory;
    new->size = size;
    new->in_use = size;
    return (void*) (new + 1);
  }
}

void free(void *memory) {
  if (memory !=NULL){
    struct chunk *new = (struct chunk*)((struct chunk*)memory-1);
    new->next = flist;
    flist = new; 
  }
  return;
}

void fragstats(void* buffers[], int len) {

  int tInUnu = 0;
  int tExUnu = 0;
  int uCount = 0;
  int fCount = 0;
  int inS=0;
  int inL=0;
  int exS=0;
  int exL=0;
  
  for(int i = 0;i<len;i++){
    if(buffers[i]!=NULL){ 
      
      struct chunk *buf = (struct chunk*)((struct chunk*) buffers[i]-1);
      uCount+=1;
      int s = buf->size;
      int inu = buf->in_use;
      int unu = s-inu;
      tInUnu += unu;
      if(inS==0){inS=unu;}
      if(unu>inL){
        inL = unu;
      }else if (unu<inS){
        inS = unu;
      }
    }
  }
  struct chunk *cnk = flist;
  while(cnk->next!=NULL){
    int s = cnk->size;
    int inu = cnk->in_use;
    int unu = s-inu;
    fCount+=1;
    tExUnu+=s;
    if(exS==0){exS=unu;}
    
    if(unu>exL){
      exL = unu;
    }else if ((unu<exS)&&(unu>0)){
      exS = unu;
    }
    cnk=cnk->next;
  }
  

  printf("Total blocks: %d Free: %d Used: %d\n",uCount+fCount,fCount,uCount);
  printf("(Internal unused) total: %d average: %.1f smallest: %d largest: %d\n",
                                   tInUnu,(float)tInUnu/uCount,inS,        inL);
  printf("(External unused) total: %d average: %.1f smallest: %d largest: %d\n",  
                                   tExUnu,(float)tExUnu/fCount,exS,        exL);
  


}

