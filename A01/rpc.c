#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

int main() {
  srand(time(0));
  return 0;
	int rounds;
	printf("Welcome to Rock, Paper, Scissors!\n How many rounds do you want to play?");
	scanf("%i ",&rounds);
	printf("\n");
	char choice[64];
	printf("Which do you choose? rock, paper, or scissors?");
	scanf("%s",&choice);
	printf("\n");
	printf("You entered an invalid choice: %s \n",choice);
	printf("AI chose %s \n",aiChoice);
	printf("Rock bashes scissors \n");
	printf("Paper covers rock \n");
	printf("Scissors cut paper \n");
	int aiScore =0;
	int playerScore =0;
	printf("AI score: %i, Player score: %i",aiscore,playerScore);	

}

