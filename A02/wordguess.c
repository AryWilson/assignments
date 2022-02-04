#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int rDoGameUtil(char toGuess[32],char guessString[64],int correctGuesses, int turn);

int doGame(char toGuess[32]){
  int len = strlen(toGuess);
  char *guessString = NULL;
  guessString = malloc(sizeof(char)*strlen(toGuess)*2);
  if(guessString == NULL){
    printf("malloc error\n");
    exit(1);
  }
  guessString[strlen(toGuess)*2]='\0';
  
  for(int i =0;i<len*2-2;i=i+2){
    guessString[i]='_';
    guessString[i+1] =' ';
  }
  int turns = rDoGameUtil(toGuess, guessString, 0,1); 
  free(guessString);
  guessString = NULL;
  return turns;
}

int rDoGameUtil(char toGuess[32],char *guessString,int correctGuesses, int turn){
  
  if(correctGuesses>=strlen(toGuess)-1){//base case, break recursion
    printf("%s\n",guessString);
    return turn;
  }
  printf("Turn: %i\n",turn);
  printf("%s\n",guessString);
  printf("Guess a character: ");
  char guess[1];
  scanf("%s",guess);
  printf("\n");

  int wrongGuess = 1;
  for(int i =0;i<strlen(toGuess);i++){ 
    if((toGuess[i]==guess[0])&&(guessString[i*2]!=guess[0])){
      guessString[i*2] = guess[0];
      correctGuesses= correctGuesses +1;
      wrongGuess = 0;
    }
  }
  if(wrongGuess){
    printf("Sorry, %s not found\n", guess);
  }
  return rDoGameUtil(toGuess,guessString,correctGuesses,turn+1);
}


int main() {
  FILE *infile;
  infile = fopen("words.txt","r"); 
  if (infile == NULL) {
    printf("Error: unable to open file %s\n", "words.txt");
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
  //printf("%s",line);
  
  printf("You won in %i turns!\n",doGame(line)-1); 
  return 0;
}
