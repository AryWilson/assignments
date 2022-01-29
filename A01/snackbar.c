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
	struct snack obj, sp, fff, fp;
	struct snack theSnacks[4];
	strcpy(obj.name,"onion-banana juice");
	strcpy(sp.name,"sea prunes         ");
	strcpy(fff.name,"flaming fire flakes");
	strcpy(fp.name,"fruit pies         ");
	obj.cost = 2.90;
	sp.cost = 8.50;
	fff.cost = 4.50;
	fp.cost = 1.00;
	obj.quantity = 12;
	sp.quantity = 8;
	fff.quantity = 10;
	fp.quantity = 0;
	theSnacks[0] = obj;
	theSnacks[1] = sp;
	theSnacks[2] = fff;
	theSnacks[3] = fp;
	//printf("name: %s, cost: %.2f",obj.name,obj.cost);
	float money;
	int snackID;
	printf("Welcome to Momo's Snack Bar\n");
	printf("How much money do you have? ");
	scanf("%f",&money);
	printf("\n");
	//printf("%f \n",money);
	for(int i=0;i<4;i++){
		printf("%i)\t",i);
		printf("%s \t",theSnacks[i].name);
		printf("cost: %.2f \t",theSnacks[i].cost);
		printf("quantity: %i \n",theSnacks[i].quantity);
	}	
	printf("What snack would you like to buy? [0,1,2,3] ");
	scanf("%d",&snackID);
	printf("\n");
	//printf("snackID= %d, money= %f \n",snackID,money);
	//printf("theSnacks[snackID].cost = %f, theSnacks[snackID].quantity= %i \n",theSnacks[snackID].cost,theSnacks[snackID].quantity);
	if(snackID>3||snackID<0){
		printf("invalid snack ID \n");	
	}else if(money<theSnacks[snackID].cost){
		printf("You don't have enough money! \n");
	}else if(theSnacks[snackID].quantity<=0){
		printf("Sorry, we are out of %s \n",theSnacks[snackID].name);
	}else {
		printf("You have bought %s \n",theSnacks[snackID].name);
	}
	return 0;
}
