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
  char *line;
  line = malloc(sizeof(char)*64+1);
  FILE *infile;
  infile = fopen(argv[1],"r"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", argv[1]);
    free(line);
    line = NULL;
    exit(1);
  }
  for(int i = 0; i < 3; i++){ 
    fgets(line,64,infile);
    //printf("line = %s", line);
  }
  char w_str[32] = " ";
  char h_str[32] = " ";
  char *token = strtok(line," ");
  strcpy(w_str,token);
  token = strtok(NULL, " ");
  strcpy(h_str,token);
  //printf("%s %s \n",w,h);
  width  = atoi(w_str);
  height = atoi(h_str);
  //printf("%i %i \n",width,height);
  struct ppm_pixel* arr=NULL;
  
  int *h = malloc(sizeof(int));
  int *w = malloc(sizeof(int));
  *h = height;
  *w = width;
  arr = read_ppm(argv[1],w,h);
  
  
  //printf("(%hhu, %hhu, %hhu)\t", arr[0].red,arr[0].green,arr[0].blue);  
  printf("Reading file %s: %i x %i\n",argv[1], width, height);
  
  for(int i = 0; i < height; i++){
    for(int j = 0; j < width; j++){
      //printf("(%hhu, %hhu, %hhu)\t", arr[i*width+j].red,arr[i*width + j].green,arr[i*width + j].blue);  
      char sym = ' ';
      unsigned char r = arr[i*width+j].red;
      unsigned char g = arr[i*width+j].green;
      unsigned char b = arr[i*width+j].blue;
      int av = (r+g+b)/3;
      //printf("%i ",av);
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
      }else if (av<=175){
        sym =':';
      }else if (av<=200){
        sym =',';
      }else if (av<=225){
        sym ='.';
      }else if (av>225){
        sym = ' ';
      }
    printf("%c",sym);
    }
  printf("\n");
  }
  free(h);
  free(w);
  h=NULL;
  w=NULL;
  free(line);
  fclose(infile);
  free(arr);
  arr = NULL;
  return 0;
}

