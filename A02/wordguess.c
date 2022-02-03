#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int main() {
  FILE *infile;
  infile = fopen("smallWords.txt","r"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", "smallWords.txt");
    exit(1);
  }
  srand(time(0));
  char line[32];
  int num;
  fgets(line,32,infile);
  num = atoi(line);
  int rNum = (rand()%num) + 1;
  for(int i=0;i<rNum;i++){
    fgets(line,32,infile);
  } 
  printf("Welcome to Word Guess!\n");
 
  int turn = 1; 
  printf("Turn; %i\n",turn);
  pr
  return 0;
}
