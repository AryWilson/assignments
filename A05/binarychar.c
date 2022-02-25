#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ipow(int base, int exp){
  int rtrn = 1;
  for(int i = 0; i<exp;i++){
    rtrn = rtrn*base;
  }
  //printf("base= %i, exp = %i, return = %i\n",base,exp,rtrn);
  return rtrn;
}

int main() {
  char bits[9];
  printf("Enter 8 bits: ");
  scanf(" %s",bits);
  bits[8] = '\0';
  printf("\n");
  int sum = 0;
  for(int i=0;i<8;i++){
    int bin = bits[i] - '0';
    int mult = ipow(2,7-i);
    int toAdd = bin*mult;

    sum = (sum + toAdd);
  }
  printf("Your character is: %c (%i)\n",sum,sum);
  return 0;
}
