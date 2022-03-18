#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

char* sToBin(char *string){
  int len = strlen(string);
  char *ret;
  ret = malloc(sizeof(char)*len*8+1);
  ret[len*8]='\0';
  for(int i =0;i<len;i++){

    char bin[9] = "00000000";
    int dig =7;
    
    for(int k=string[i];k>0;k=k/2){
      char ne =k%2 + '0';
      bin[dig] = ne;
      dig= dig-1;
    }
    bin[8] = '\0';
    ret[i*8]='\0';
    strcat(ret,bin);
  }
  return ret;
}

int main(int argc, char** argv) {
  //usage
  if(argc != 2){
    printf("Program expects 2 command line arguments. Exiting... \n");
    exit(1);
  }
  //set up name change for file to write
  char newname[64]=" ";
  int c =0;
  while(argv[1][c]!= '.'){
    newname[c] = argv[1][c];
    c=c+1;
  }
  newname[c]='\0';
  strcat(newname,"-encoded.ppm"); 
  //create pixel array
  int h,w;
  struct ppm_pixel *pixels = NULL;
  pixels = read_ppm(argv[1],&w,&h); 
  if(pixels == NULL){return 1;}
  int char_count = (h*w*3/8);
  
  //output statements
  printf("Reading %s with width %i and height %i\n",argv[1],w,h);
  printf("Max number of characters in the image: %i\n", char_count-1);
  
  //get message for encoding
  char *phrase;
  phrase = malloc(sizeof(char)*char_count);//MALLOC
  printf("Enter a phrase: ");
  fgets(phrase,char_count,stdin);
  printf("\nWriting file %s\n",newname);
  char *binPhrase = sToBin(phrase);//MALLOC
  //add message to pixel array
  unsigned char mask = 0b11111110;
  int idx =0;
  while(idx < strlen(binPhrase)) {
    pixels[(idx-idx%3)/3].colors[idx%3]= 
      (pixels[(idx-idx%3)/3].colors[idx%3]&mask) | (binPhrase[idx]-'0');
    idx=idx+1;
  }
  //add null character to the end
  for(int a = 0;a<8;a++){
    pixels[(idx-idx%3)/3].colors[idx%3]= 
        (pixels[(idx-idx%3)/3].colors[idx%3]&mask) | '\0';
    idx = idx+1;
  }
  //write file with encoded message
  write_ppm(newname,pixels,w,h);


  free(binPhrase);//free 2
  binPhrase = NULL;
  free(phrase);//free 1
  phrase = NULL;
  return 0;

}

