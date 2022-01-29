/*program that takes a word and prints an altered version
* Ary Wilson
* 1/28/22
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* takes a string (char array) and replaces l's, e's, and a's with special chars 
*/
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

/*
*prompts user and recieves user input
*/
int main() { 
	char pass[100];
	printf("Enter a word: ");
	scanf("%s", pass);
	alter(pass);
	printf("Your bad password is: %s\n", pass);
	return 0;
}

