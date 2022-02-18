#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// read in file, save height, width, malloc enough space to array,
// for each rdg value make struct with r g b values, set index to struct
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int w, int h) {
  FILE *infile;
  infile = fopen(filename,"r"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    fclose(infile);
    return NULL;
  }
  char line[32];
  for (int i=0;i<3;i++){
    fgets(line,32,infile);
  }
  struct ppm_pixel* arr;
  arr = malloc(sizeof(arr)*h*w + 1);
  if(arr == NULL){
    printf("malloc error\n");
    fclose(infile);
    return NULL;
  }
  unsigned char r;
  unsigned char g;
  unsigned char b;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      fscanf(infile, " %hhu %hhu %hhu", &r, &g, &b);
      arr[i*w + j].red = r;
      arr[i*w + j].green = g;
      arr[i*w + j].blue = b;
    }
  }
  
  //free(arr);
  //arr = NULL;
  fclose(infile);
  return arr;
}

