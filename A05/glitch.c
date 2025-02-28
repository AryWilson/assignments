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
  if (arr == NULL){return 1;} 
  
  
  /*for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%i %i %i)",arr[i*w+j].red, arr[i*w+j].green, arr[i*w+j].blue);
    }
  }*/
  printf("Reading file %s: %i x %i\n",argv[1], w, h);
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      /*arr[i*w+j].red = arr[i*w+j].red << (rand() % 2);
      arr[i*w+j].green = arr[i*w+j].green << (rand() % 2);
      arr[i*w+j].blue = arr[i*w+j].blue << (rand() % 2);
      */

      /*struct ppm_pixel copy = arr[i*w+j];
      arr[i*w + j].red = arr[i*w + j].green;
      arr[i*w + j].green = arr[i*w+j].blue;
      arr[i*w + j].blue = copy.red;*/
      arr[i*w+j].red = arr[i*w+j].red << (rand() % w/h);
      arr[i*w+j].green = arr[i*w+j].green << (rand() % h/w);
      arr[i*w+j].blue = arr[i*w+j].blue << (rand() % w/5);
      
      
      
    }
  }

  
  /*for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%i %i %i)",arr[i*w+j].red, arr[i*w+j].green, arr[i*w+j].blue);
    }
  }*/

  char newname[64];
  strcpy(newname," ");
  int i = 0;
  while ((i<strlen(argv[1]))&&(argv[1][i]!='.')){
    newname[i] = argv[1][i];
    i=i+1;
  }  
  newname[i]='\0';
  strcat(newname,"-glitch.ppm");
  write_ppm(newname,arr,w,h);
  return 0;
}
