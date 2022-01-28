
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
	float cost;
	int quantity;
	char name[64];
};

void makeSnack(){
	struct snack obj, sp, fff, fp;
	strcpy(obj.name,"onion-bannana juice");
	strcpy(sp.name,"sea prunes");
	strcpy(fff.name,"flaming fire flakes");
	strcpy(fp.name, "fruit pies");
	obj.cost = 2.90;
	sp.cost = 8.50;
	fff.cost = 4.50;
	fp.cost = 1.00;
	obj.quantity = 12;
	sp.quantity = 8;
	fff.quantity = 10;
	fp.quantity = 0;
	//printf("name: %s, cost: %.2f",obj.name,obj.cost);
}

int main(){
	float money;
	int quant;
	makeSnack();
	printf("Welcome to Momo's Snack Bar\n");
	printf("How much money do you have? ");
	scanf("%f \n",&money);
	printf("What snack would you like to buy? [0,1,2,3] ");
	scanf("%d \n",&quant);
	return 0;
}
