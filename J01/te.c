#include <stdio.h>
#include <stdlib.h>
struct abs{
  char c;
  float q[4];
};

int main(){
  char q = ' ';
  struct abs aaa[3];
  float *m = malloc(sizeof(float)*10);  
  char a[10] = "ciao";
  printf("%lu %lu %lu %lu \n",sizeof(float), sizeof(struct abs), sizeof(aaa), sizeof(m));
  free(m);
  return 0;
}
