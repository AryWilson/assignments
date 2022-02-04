#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void doGame(char toGuess[32]){
  char guessString[64];
  for(int i =0;i<strlen(toGuess)*2;i=i+2){
    guessString[i]='_';
    guessString[i+1] =' ';
  } 
  int turn = 0; 
  int charsLeft = strlen(toGuess);
  int correctGuesses = 0; 
  while(correctGuesses < charsLeft){
    turn = turn +1;
    printf("Turn: %i\n",turn);
    printf("guess: %s\n",guessString);
    printf("Guess a character: ");
    char guess[1];
    scanf("%s",guess);
    printf("\n");
    int wrongGuess = 1;
    for(int i =0;i<strlen(toGuess);i++){ 
      if((toGuess[i]==guess[0])&&(guessString[i*2]!=guess[0])){
        printf("guess = %s, correctGuesses = %i\n",guess,correctGuesses);
        guessString[i*2] = guess[0];
        correctGuesses= correctGuesses +1;
        wrongGuess = 0;
      }
    }
    if(wrongGuess){
      printf("Sorry, %s not found\n", guess);
    }
  }
}


void rDoGame(char toGuess[32],char guessString[64],int correctGuesses, int turn){
  if(correctGuesses>=strlen(toGuess)-1){
   // printf("The word was: %s\n",toGuess);
    printf("guess: %s\n",guessString);
    return;
  }
  printf("Turn: %i\n",turn);
  printf("guess: %s\n",guessString);
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
      //printf("guess = %s, correctGuesses = %i\n",guess,correctGuesses);
    }
  }
  if(wrongGuess){
    printf("Sorry, %s not found\n", guess);
  }
  rDoGame(toGuess,guessString,correctGuesses,turn+1);
}


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
  printf("%s",line);
  //doGame(line);
  
  char guessString[64];
  for(int i =0;i<strlen(line)*2-2;i=i+2){
    guessString[i]='_';
    guessString[i+1] =' ';
  }
  rDoGame(line, guessString, 0,1); 
  return 0;
}
