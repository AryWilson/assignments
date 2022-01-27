#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int alter(char pw[100]){
	for(int i =0;i<strlen(pw);i++){
		if(pw[i] == 'l'|| pw[i] == 'L'){
			pw[i]='1';
		}else if (pw[i]=='e'||pw[i]=='E'){
			pw[i] = '3';
		}else if (pw[i]=='a'||pw[i]=='A'){
			pw[i] = '@';
		}
	}
	return 0;
}


int main() { 
	char pass[100];
	printf("Enter a word: ");
	scanf("%s", pass);
	alter(pass);
	printf("Your bad password is: %s\n", pass);
	return 0;
}

