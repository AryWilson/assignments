#include <stdio.h>
#include "read_ppm.h"
#include "read_ppm.c"
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
  if(argc != 2){
    printf("Program expects 2 command line arguments. Exiting... \n");
    exit(1);
  }
  
  int height=0;
  int width=0;
  char line[64];
  
  FILE *infile;
  infile = fopen(argv[1],"r"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", argv[1]);
    //fclose(infile);
    exit(1);
  }
  for(int i = 0; i < 10; i++){ 
  fgets(line,64,infile);
  printf("line = %s, strtok = %s \n",line,strtok(line," /t"));
  }
  //width  = atoi(strtok(line, " \t"));
  //height = atoi(strtok(line, " \t"));
  struct ppm_pixel* arr=NULL;
  arr = read_ppm(argv[1],width,height);
  
  printf("Reading file %s: %i x %i\n",argv[1], width, height);
  
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      printf("(%hhu, %hhu, %hhu)\t", arr[i*width+j].red,arr[i*width + j].green,arr[i*width + j].blue);  
      char sym = ' ';
      unsigned char r = arr[i*width+j].red;
      unsigned char g = arr[i*width+j].green;
      unsigned char b = arr[i*width+j].blue;
      int av = (r+g+b)/3;
      if(av<=25){
        sym = '@';
      }else if (av<=50){
        sym ='#';
      }else if (av<=75){
        sym ='%';
      }else if (av<=100){
        sym ='*';
      }else if (av<=125){
        sym ='o';
      }else if (av<=150){
        sym =';';
      }else if (av=175){
        sym =':';
      }else if (av<=200){
        sym =',';
      }else if (av<=225){
        sym ='.';
      }
    printf("%c",sym);
    }
  printf("\n");
  }
  
  fclose(infile);
  free(arr);
  arr = NULL;
  return 0;
}

