#include <stdio.h>

int main() {

  char word[8];
  printf("enter 4 characters: ");
  scanf(" %s",word);
  printf("\n");
  //unsigned int base = 0x000000FF;
  unsigned int lets[4];
  unsigned int fin=0;
  for (int j =0; j < 4; j++){
    int i = 3-j;
    lets[j] = word[i] << j*8;
    printf("Debug: %c = %08X\n",word[i],lets[j]);
    fin = fin|lets[j];
  }
  printf("Your number is: %i (0x%08x)\n",fin,fin);
  
  return 0;
}
