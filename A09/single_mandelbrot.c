#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include <string.h>

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your work here
  srand(time(0)); 
  struct timeval tstart, tend;

  struct ppm_pixel *pxl = malloc(sizeof(struct ppm_pixel)*(size)*(size));
  if(pxl==NULL){
    printf("malloc error\n");
    exit(1);
  } 
  // generate pallet
  int color = 0;
  int colors = 100;
  int red[100];
  int green[100];
  int blue[100];

  for (int i =0;i<colors;i++){
    red[i] = rand()%255;
    green[i] = rand()%250;
    blue[i] = rand()%250;
  }
  /*int basered = rand() % 255;
  int basegreen = rand() % 255;
  int baseblue = rand() % 255;
  for (int i =0;i<colors;i++){
    red[i] = basered + rand() % 100 - 50;
    green[i] = basegreen + rand() % 100 - 50;
    blue[i] = baseblue + rand() % 100 - 50;
  }*/
  gettimeofday(&tstart, NULL);

  //write color to image at location (row,col)
  for (int row = 0; row<size;row++){
    for (int col = 0; col<size;col++){
      float xfrac = row / size;
      float yfrac = col / size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);
      float x = 0;
      float y = 0;
      int iter = 0;
      float xtmp;
      while ((iter < maxIterations) &&( x*x + y*y < 4*4)){
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter=iter+1;
      }
      
      if (iter < maxIterations){ // escaped
        pxl[row*size+col].red = red[iter%colors];
        pxl[row*size+col].green = green[iter%colors];
        pxl[row*size+col].blue = blue[iter%colors];
      }else{
        pxl[row*size+col].red = 0;
        pxl[row*size+col].green = 0;
        pxl[row*size+col].blue = 0;
      }
    }
  }
  gettimeofday(&tend, NULL);
  double timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  
  // compute image
  printf("Computed mandelbrot set (%dx%d) in %g seconds\n",size,size,timer);

  char newfile[64];
  sprintf(newfile,"mandelbrot-<%d>-<%d>.ppm",size,(int)time(0));
  newfile[strlen(newfile)]='\0';
  write_ppm(newfile,pxl,size,size);
  return 0;

}
