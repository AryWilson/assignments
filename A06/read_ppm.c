#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
FILE *infile;
  infile = fopen(filename,"rb"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    fclose(infile);
    return NULL;
  }
  char line[64];

  //read up to dimentions
  for (int i=0;i<2;i++){
    fgets(line,64,infile);
    //printf("%s \n",line);
  }
  if(line[0] == '#'){
    fgets(line,64,infile);
  }
  char w_str[32] = " ";
  char h_str[32] = " ";
  char *token = strtok(line," ");
  strcpy(w_str,token);
  token = strtok(NULL, " ");
  strcpy(h_str,token);
  *w  = atoi(w_str);
  *h = atoi(h_str);
  //read up to colors
  fgets(line,64,infile);
  
  //make pixel array
  struct ppm_pixel* arr;
  arr = malloc(sizeof(struct ppm_pixel)**h**w + 1);
  if(arr == NULL){
    printf("malloc error\n");
    fclose(infile);
    return NULL;
  }

  //add colors to pixel array
  for (int i = 0; i < *h; i++) {
    for (int j = 0; j < *w; j++) {
      fread(&arr[i**w + j],sizeof(struct ppm_pixel),1,infile);
    }
  } 
  for (int i = 0; i < *h; i++) {
    for (int j = 0; j < *w; j++) {
      printf("(%hhu, %hhu, %hhu)\t", arr[i**w+j].red,arr[i**w + j].green,arr[i**w + j].blue);
    }
    printf("\n");
  }
  //close file
  fclose(infile);
  return arr;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
extern void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
  FILE *outfile = fopen(filename, "wb");
  printf("Writing file %s\n",filename);
  char head[32];

  sprintf(head, "P6\n#comment\n%i %i\n255\n", w,h);  
  fwrite(head,32,1,outfile);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      fwrite(&pxs[i*w + j],sizeof(struct ppm_pixel),1,outfile);
    }
  } 

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      printf("(%hhu, %hhu, %hhu)\t", pxs[i*w+j].red,pxs[i*w + j].green,pxs[i*w + j].blue);
    }
    printf("\n");
  }

  free(pxs);
  pxs = NULL;
  fclose(outfile);
  outfile=NULL;
  return;
}
