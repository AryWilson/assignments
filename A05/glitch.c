#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include <time.h>

int main(int argc, char** argv) {
  srand(time(0));
  if(argc != 2){
    printf("Program expects 2 command line arguments. Exiting... \n");
    exit(1);
  }
   
  int h,w;
  struct ppm_pixel *arr = NULL;
  arr = read_ppm(argv[1],&w,&h); 
  
  
  
  /*for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%i %i %i)",arr[i*w+j].red, arr[i*w+j].green, arr[i*w+j].blue);
    }
  }*/
  printf("Reading file %s: %i x %i\n",argv[1], w, h);
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      //arr[i*w+j].red = arr[i*w+j].red << (rand() % 2);
      //arr[i*w+j].green = arr[i*w+j].green << (rand() % 2);
      //arr[i*w+j].blue = arr[i*w+j].blue << (rand() % 2);
      arr[i*w + j].red = arr[i*w + j].green;
      arr[i*w + j].green = arr[i*w+j].blue;
      //arr[i*w + j].blue = arr[i*w+j].red;
      
    }
  }

  
  /*for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%i %i %i)",arr[i*w+j].red, arr[i*w+j].green, arr[i*w+j].blue);
    }
  }*/
  write_ppm(argv[1],arr,w,h);
  return 0;
}
