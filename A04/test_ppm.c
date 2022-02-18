#include <stdio.h>
#include "read_ppm.c"

int main() {
  int *h;
  h = malloc(sizeof(int));
  *h = 4;
  printf("Testing file feep-ascii.ppm:");// todo: call read_ppm
  read_ppm("feep-ascii.ppm",h,h);
  free(h);
  h = NULL;
  return 0;
}

