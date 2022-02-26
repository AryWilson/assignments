#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int *w, int *h) {
  
  //read in file and check for error
  FILE *infile;
  infile = fopen(filename,"rb"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", filename);
    fclose(infile);
    return NULL;
  }

  //read up until dimentions
  char line[64]; 
  fread(line,3,1,infile);
  fread(line,1,1,infile);
  if(line[0]=='#'){
    
    while(line[0]!='\n'){
    fread(line,1,1,infile);
    }
    fread(line,3,1,infile);
    *w = line[0] -'0';
    *h = line[2] -'0';
  }else{
    *w = line[0] - '0';
    fread(line,2,1,infile);
    *h = line[1] - '0';
  }

  //read up until colors
  fread(line,1,1,infile);
  fread(line,4,1,infile);

  //make pixel array
  struct ppm_pixel* arr;
  arr = malloc(sizeof(arr)**h**w + 1);
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

  //close file
  fclose(infile);
  return arr;
}

// TODO: Implement this function
// Feel free to change the function signature if you prefer to implement an 
// array of arrays
void write_ppm(const char* filename, struct ppm_pixel* pxs, int w, int h) {
  FILE *outfile;
  char newname[64]=" ";
  int i =0 ;
  while(filename[i]!='.'){
    newname[i]=filename[i];
    i++;
  } 
  strcat(newname,"-glitch.ppm");
  outfile = fopen (newname, "wb");
  printf("Writing file %s\n",newname);
  /*char head[64] = "P3\n";
  sprintf(head, "%d %d\n255\n", w,h);  
  fwrite(head,64,1,outfile);*/
  
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      pxs[i*w+j].red = pxs[i*w+j].red << (rand() % 2);
      pxs[i*w+j].green = pxs[i*w+j].green << (rand() % 2);
      pxs[i*w+j].blue = pxs[i*w+j].blue << (rand() % 2);
      //fwrite(&pxs[i*w + j],sizeof(struct ppm_pixel),1,outfile);
    }
  } 

  fclose(outfile);
  outfile=NULL;
  return;
}

