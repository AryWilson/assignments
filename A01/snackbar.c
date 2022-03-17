/* snackbar lists snacks, quantities, and prices and allows user input for simulated purchases
* Ary Wilson
* 1/28/22
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* stuct that holds snack data 
*/
struct snack {
	float cost;
	int quantity;
	char name[64];
};

/*
* creates a structure array that represents the snackbar
* displays finsihed snackbar and takes user input to simulate purchases
*/
int main() {
	struct snack theSnacks[4];
	strcpy(theSnacks[0].name,"onion-banana juice");
	strcpy(theSnacks[1].name,"sea prunes         ");
	strcpy(theSnacks[2].name,"flaming fire flakes");
	strcpy(theSnacks[3].name,"fruit pies         ");
	theSnacks[0].cost = 2.90;
	theSnacks[1].cost = 8.50;
	theSnacks[2].cost = 4.50;
	theSnacks[3].cost = 1.00;
	theSnacks[0].quantity = 12;
	theSnacks[1].quantity = 8;
	theSnacks[2].quantity = 10;
	theSnacks[3].quantity = 0;
	
  float money;
	int snackID;
	printf("Welcome to Momo's Snack Bar\n");
	printf("How much money do you have? ");
	scanf(" %f",&money);
	printf("\n");
	for(int i=0;i<4;i++){
		printf("%i)\t",i);
		printf("%s \t",theSnacks[i].name);
		printf("cost: %.2f \t",theSnacks[i].cost);
		printf("quantity: %i \n",theSnacks[i].quantity);
	}	
	printf("What snack would you like to buy? [0,1,2,3] ");
	scanf(" %d",&snackID);
	printf("\n");
	if(snackID>3||snackID<0){
		printf("invalid snack ID \n");	
	}else if(money<theSnacks[snackID].cost){
		printf("You don't have enough money! \n");
	}else if(theSnacks[snackID].quantity<=0){
		printf("Sorry, we are out of %s \n",theSnacks[snackID].name);
	}else {
		printf("You have bought %s \n",theSnacks[snackID].name);
	  money = money - theSnacks[snackID].cost;
  }
	printf("You have $%.2f left\n",money);
	return 0;
}
