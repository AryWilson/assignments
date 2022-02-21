#include <stdio.h>
#include "read_ppm.c"
#include <string.h>
#include <stdlib.h>

int main() {
  
  int height=0;
  int width=0;
  char line[32];
  
  FILE *infile;
  infile = fopen("feep-ascii.ppm","r"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", "feep-ascii.ppm");
    fclose(infile);
    exit(1);
  }
  fgets(line,32,infile);  
  fgets(line,32,infile);
  printf("line = %s\n", line);
  fgets(line,32,infile);  
  printf("line = %s\n", line);
  width  = atoi(strtok(line, " \t"));
  height = atoi(strtok(line, " \t"));
  //printf("num0 = %i, num1 = %i, line = %s\n", width,height,line);
  struct ppm_pixel* arr=NULL;
  /*arr = malloc(sizeof(arr)*height*width + 1);
  if(arr == NULL){
    printf("malloc error\n");
    exit(0);
  }*/
  int *w = malloc(sizeof(int));
  int *h = malloc(sizeof(int));
  *w = width;
  *h = height;
  arr = read_ppm("feep-ascii.ppm",w,h);
  
  printf("Testing file feep-ascii.ppm: %i x %i\n", width, height);// todo: call read_ppm
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("(%hhu, %hhu, %hhu)\t", arr[i*width+j].red,arr[i*width + j].green,arr[i*width + j].blue);
    }
    printf("\n");
  }
  fclose(infile);
  free(h);
  free(w);
  h=NULL;
  w=NULL;
  free(arr);
  arr = NULL;
  return 0;
}

