#include <stdio.h>
#include "read_ppm.h"
#include <string.h>
#include <stdlib.h>

int main() {
  int h,w;
  struct ppm_pixel *pixels = read_ppm("feep-raw.ppm",&w,&h);
  printf("Testing file feep-raw.ppm: %i x %i\n", w, h);// todo: call read_ppm
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%hhu, %hhu, %hhu)\t", pixels[i*w+j].red,pixels[i*w + j].green,pixels[i*w + j].blue);
    }
    printf("\n");
  }
  free(pixels);
  pixels = NULL;
  return 0;
}

