
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include <stdbool.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>

int main(){
  
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  
  struct ppm_pixel *pxl = malloc(sizeof(struct ppm_pixel)*size*size); 
  bool *mandel = malloc(size*size*sizeof(bool));
  int *vcount = malloc(size*size*sizeof(int));
  int maxcount = 0;
  for (int row = 0; row<size; row++){
    for (int col = 0; col<size; col++){
      float xfrac = (float) row / size;
      float yfrac = (float) col / size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);
      float x = 0;
      float y = 0;
      int iter = 0;
      float xtmp;
      while ((iter < maxIterations) &&( x*x + y*y < 2*2)){
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter=iter+1;
      }
      
      if (iter < maxIterations){ // escaped
        mandel[col*size+row] = false;
      }else{
        mandel[col*size+row] = true;
      }
    }
  }

  for (int row = 0; row<size; row++){
    for (int col = 0; col<size; col++){
      if (mandel[col*size+row]){
        continue;
      }
      float xfrac = (float) row / size;
      float yfrac = (float) col / size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);
      float x = 0;
      float y = 0;
      float xtmp;
      int yrow;
      int xcol;
      while ( x*x + y*y < 2*2){
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
      
        yrow = round(size * (y - ymin)/(ymax - ymin));
        xcol = round(size * (x - xmin)/(xmax - xmin));
        if (yrow < 0 || yrow >= size) {
          continue;
        } // out of range
        if (xcol < 0 || xcol >= size) {
          continue; 
        }// out of range
        
        int temp = vcount[xcol*size+yrow]+1;
        vcount[xcol*size+yrow] = temp;
        if(maxcount<temp){
          maxcount=temp;
        }
      }
    }
  }
  

  
  float gamma = 0.681;
  float factor = 1.0/gamma; 
  float value = 0;
  int count = 0;
  for (int row = 0; row<size; row++){
    for (int col = 0; col<size; col++){
      count = vcount[col*size+row];
      if(count > 0){
        
        value = log(count)/log(maxcount);
        value = pow(value,factor);
      }
      pxl[row*size+col].red = value * 255;
      pxl[row*size+col].green = value * 255;
      pxl[row*size+col].blue = value * 255;
      
    }
  }
 
  char newfile[64];
  sprintf(newfile,"butest-<%d>-<%d>.ppm",size,(int)time(0));
  newfile[strlen(newfile)]='\0';
  write_ppm(newfile,pxl,size,size);       
  
  free(pxl);
  pxl = NULL;
  free(mandel);
  mandel = NULL;
  free(vcount);
  vcount = NULL;
  return 0;
} 
