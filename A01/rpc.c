#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

void doGame(int *userScore, int *aiScore){
	char choice[64];
	int aiC = rand()%3;
	char aiChoice[10];
	int aiRock = (aiC == 0);
	int aiPaper = (aiC == 1);
	int aiSciss = (aiC == 2);
	if(aiC == 0){
		strcpy(aiChoice,"rock");
	}else if (aiC == 1){
		strcpy(aiChoice,"paper");
	}else {
		strcpy(aiChoice, "scissors");
	}
	//int aiScore =0;
	//int userScore =0;
	printf("Which do you choose? rock, paper, or scissors? ");
	scanf("%s",choice);
	printf("\n");
	for(int i =0; i<strlen(choice);i++){
		choice[i] = tolower((unsigned char) choice[i]);
	}
	int userRock = (strcmp(choice,"rock")==0);
	int userPaper = (strcmp(choice,"paper")==0);
	int userSciss = (strcmp(choice,"scissors")==0);

	printf("AI chose %s \n",aiChoice);
	if(strcmp(choice,aiChoice)==0){
		printf("It's a tie \n");
	} else if(aiRock && userSciss){
		*aiScore = *aiScore + 1;
		//printf("aiScore = %i\n",*aiScore);		
		printf("Rock bashes scissors \n");
	} else if (aiRock && userPaper){
		*userScore = *userScore +1;
		//printf("aiScore = %i\n",*aiScore);
		printf("Paper covers rock \n");
	} else if (aiPaper && userSciss){
		*userScore= *userScore+1;
		printf("Scissors cut paper \n");
	} else if (aiPaper && userRock){
		*aiScore=*aiScore +1;
		printf("Paper covers rock \n");
	} else if (aiSciss && userPaper){
		*aiScore =*aiScore +1;
		printf("Scissors cut paper \n");
	} else if (aiSciss && userRock){
		*userScore=*userScore +1;
		printf("Rock bashes scissors \n");
	} else {
		printf("You entered an invalid choice: %s \n",choice);
	}

	printf("AI score: %i, Player score: %i \n",*aiScore,*userScore);	
	return;
}


int main() {
  	srand(time(0));
	int rounds;
	printf("Welcome to Rock, Paper, Scissors!\n");
	printf("How many rounds do you want to play? ");
	scanf("%i",&rounds);
	printf("\n");
	int *userScore;
	int *aiScore;
	userScore = malloc(sizeof(int));
	aiScore = malloc(sizeof(int));
	if(userScore == NULL||aiScore==NULL){
		printf("error bad memory\n");
		exit(0);
	}
	*userScore =0;
	*aiScore =0;
	for(int i = 0;i<rounds;i++){
		doGame(userScore,aiScore);
	}
	return 0;
}

