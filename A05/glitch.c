#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"


int main(int argc, char** argv) {
  if(argc != 2){
    printf("Program expects 2 command line arguments. Exiting... \n");
    exit(1);
  }
   
  int h,w;
  struct ppm_pixel *arr = read_ppm(argv[1],&w,&h); 
  printf("Reading file %s: %i x %i\n",argv[1], w, h);
  
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      arr[i*w + j].red = arr[i*w + j].green;
      arr[i*w + j].green = arr[i*w+j].blue;
      arr[i*w + j].blue = arr[i*w+j].red;
      
    }
  }
  write_ppm(argv[1],arr,w,h);
  return 0;
}
