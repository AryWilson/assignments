#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// read in file, save height, width, malloc enough space to array,
// for each rdg value make struct with r g b values, set index to struct
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  FILE *infile;
  infile = fopen(filename,"r"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    fclose(infile);
    return NULL;
  }
  
  int height = 0;
  int width = 0;
  char line[32];

  fgets(line,32,infile);
  fgets(line,32,infile);  
  printf("line = %s\n", line);
  int num0 = atoi(strtok(line, " \t"));
  printf("num0 = %i, line = %s\n", num0,line);
  int num1 = atoi(strtok(line, " \t"));
  printf("num0 = %i, num1 = %i, line = %s\n", num0,num1,line);
  
  struct ppm_pixel* arr;
  arr = malloc(sizeof(arr)*height*width + 1);
  if(arr == NULL){
    printf("malloc error\n");
    return NULL;
  }
  unsigned char r;
  unsigned char g;
  unsigned char b;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      fscanf(infile, " %hhu %hhu %hhu", &r, &g, &b);
      arr[i*width + j].red = r;
      arr[i*width + j].green = g;
      arr[i*width + j].blue = b;
    }
  }
  free(arr);
  arr = NULL;
  fclose(infile);
  return arr;
}

