#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"
#include <string.h> 
unsigned int leastSig(unsigned int bin){
  return bin%2;
}
int main(int argc, char** argv) {
  if(argc != 2){
    printf("Program expects 2 command line arguments. Exiting... \n");
    exit(1);
  }

  //get pixel array   
  int h,w;
  struct ppm_pixel *pixels = NULL;
  pixels = read_ppm(argv[1],&w,&h); 
  int char_count = (h*w*3/8);
  printf("Reading %s with width %i and height %i\n",argv[1],w,h);
  printf("Max number of characters in the image: %i\n", char_count);
  
  //iterate over every bit in array, every 8 bits, print the character
  int count =0;
  unsigned int let=0;
  for(int i =0;i<h*w*3;i++){
    //for first 8 bits (char length) construct let through bit shifting
    // (i-i%3)/3 iterates every 3 increases of i, i%3 get's each of 3 color vals 
    if(count<8){
      let = let << 1;
      let = let + leastSig(pixels[(i-i%3)/3].colors[i%3]);
    }
    count=count+1;
    //every 8 bits, print the char and reset variables for next 8 bits:
    if(count >= 8){
      if(let == '\0'){break;}
      printf("%c",let);
      count=0;
      let = 0;
    }
  }
  printf("\n");
  free(pixels);
  pixels = NULL;
  return 0;
}

