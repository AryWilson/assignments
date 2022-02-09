//---------------------------------------------------------------------
// magic_square.c 
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name: Ary Wilson
//
#include <stdio.h>
#include <stdlib.h>

int main() {
  int row,col;
  scanf(" %d", &row);
  scanf(" %d", &col);
  int *square = NULL;
  square = malloc(sizeof(int)*col*row);
  if (square == NULL) {
        printf("ERROR: malloc failed!\n");
        exit(1);
    } 
  int val;  
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      //printf("i=%d,j=%d\n",i,j);
      scanf(" %d",&val);
      square[i*col + j] = val;
    }
  }

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      printf(" %d",square[i*col + j]);
    }
    printf("\n");
  }

  int magic_sum = 0;
  for(int i=0;i<col;i++){
    magic_sum+=square[i];
  }
  //sum of rows 
  for(int i=0;i<col*row;i=i+col){
    int sum=0;
    for (int j = i; j<(i+col);j++){
      sum+=square[j];
    }
    if (sum != magic_sum){
      printf("M is NOT a magic square!\n");
      free(square);
      square = NULL;
      return 0;
    }
    //printf("%d\n",sum);
  }


  //sum of collumns
  for(int j=0;j<col;j++){
    int sum=0;
    for (int i = j; i<row*col;i=i+col){
      sum+=square[i];
    }
    if (sum != magic_sum){
      printf("M is NOT a magic square!\n");
      free(square);
      square = NULL;
      return 0;
    }
    //printf("%d\n",sum);
  } 
  
  printf("M is a magic square (magic constant = %i)\n",magic_sum);
  free(square);
  square = NULL;
}

