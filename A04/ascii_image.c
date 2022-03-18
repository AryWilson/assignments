#include <stdio.h>
#include "read_ppm.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  if(argc != 2){
    printf("Program expects 2 command line arguments. Exiting... \n");
    exit(1);
  }
  
  int h,w;
  struct ppm_pixel *arr;
  arr = read_ppm(argv[1],&w,&h);
  
  if (arr == NULL){
    return 1;
  }
   
  printf("Reading file %s: %i x %i\n",argv[1], w, h);
  
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      unsigned char r = arr[i*w + j].red;
      unsigned char g = arr[i*w + j].green;
      unsigned char b = arr[i*w + j].blue;
      int av = (r+g+b)/3;
     //printf("%i ",av);
      if(av<=25){
        printf("@");
      }else if (av<=50){
        printf("#");
      }else if (av<=75){
        printf("%%");
      }else if (av<=100){
        printf("*");
      }else if (av<=125){
        printf("o");
      }else if (av<=150){
        printf(":");
      }else if (av<=175){
        printf(":");
      }else if (av<=200){
        printf(",");
      }else if (av<=225){
        printf(".");
      }else if(av>225){
        printf(" ");
      }
    }
    printf("\n");
  }
  free(arr);
  arr = NULL;
  return 0;
}

