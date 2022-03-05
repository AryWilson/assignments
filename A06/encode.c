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
  if(argc != 2){
    printf("Program expects 2 command line arguments. Exiting... \n");
    exit(1);
  }
  char newname[64];
  int c =0;
  while(argv[1][c]!= '.'){
    newname[c] = argv[1][c];
    c=c+1;
  }
  newname[c]='\0';
  strcat(newname,"-encoded.ppm"); 
  int h,w;
  struct ppm_pixel *pixels = NULL;
  pixels = read_ppm(argv[1],&w,&h); 
  int char_count = (h*w*3/8);
  printf("Reading %s with width %i and height %i\n",argv[1],w,h);
  printf("Max number of characters in the image: %i\n", char_count-1);
  char *phrase;
  phrase = malloc(sizeof(char)*char_count);
  printf("Enter a phrase: ");
  scanf("%s",phrase);
  printf("\nWriting file %s\n",newname);
  char *binPhrase = sToBin(phrase);
  printf("%s",binPhrase); 
  unsigned char mask = 0b11111110;

  printf("%hhu\n",pixels[1].colors[0]);  
  printf("%hhu\n",pixels[1].colors[0]&mask);  
  printf("%hhu\n",(pixels[1].colors[0]&mask) | (binPhrase[1]-'0'));  
  printf("%hhu\n",(binPhrase[1]-'0'));  


  int idx =0;
  while(idx < strlen(binPhrase)) {
    pixels[(idx-idx%3)/3].colors[idx%3]= 
      (pixels[(idx-idx%3)/3].colors[idx%3]&mask) | (binPhrase[idx]-'0');
    idx=idx+1;
  }
  pixels[(idx-idx%3)/3].colors[idx%3]= 
      (pixels[(idx-idx%3)/3].colors[idx%3]&mask) | '\0';

  
  

  write_ppm(newname,pixels,w,h);


  free(binPhrase);
  binPhrase = NULL;
  free(phrase);
  phrase = NULL;
  return 0;

}

