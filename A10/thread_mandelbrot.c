#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <pthread.h>
#include "read_ppm.h"
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>

#define MAX 1000

struct thread_data {
  int rstart, rend;
  int cstart, cend; 
  int size; 
  float xmin, xmax; 
  float ymin, ymax;
  struct ppm_pixel *pxl; 
  struct ppm_pixel *pal; 
};

void *makeMandel(void* userdata){
  struct thread_data *data = (struct thread_data *) userdata;
  int rstart = data->rstart;
  int rend = data->rend;
  int cstart = data->cstart;
  int cend = data->cstart;
  int size = data->size;
  float xmin = data->xmin;
  float xmax = data->xmax; 
  float ymin = data->ymin;
  float ymax = data->ymax; 
  struct ppm_pixel *pxl = data->pxl;
  struct ppm_pixel *pal = data->pal;
  printf("Thread %ld) sub-image block: cols (%d, %d) to rows (%d,%d)\n", 
  pthread_self(),rstart,rend,cstart,cend);  

  //write color to image at location (row,col)
  for (int row = rstart; row<rend; row++){
    for (int col = cstart; col<cend; col++){
      float xfrac = (float) row / size;
      float yfrac = (float) col / size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);
      float x = 0;
      float y = 0;
      int iter = 0;
      float xtmp;
      while ((iter < MAX) &&( x*x + y*y < 2*2)){
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter=iter+1;
      }
      
      if (iter < MAX){ // escaped
        pxl[col*size+row].red = pal[iter%100].red;
        pxl[col*size+row].green = pal[iter%100].green;
        pxl[col*size+row].blue = pal[iter%100].blue;
      }else{
        pxl[col*size+row].red = 0;
        pxl[col*size+row].green = 0;
        pxl[col*size+row].blue = 0;
      }
    }
  }
  printf("Thread %ld) finished\n",pthread_self());
  return (void*)NULL;
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your code here
  srand(time(0)); 
  struct timeval tstart, tend;
 struct ppm_pixel *pxl = malloc(sizeof(struct ppm_pixel)*(size)*(size));
  // generate pallet
  struct ppm_pixel palette[100];

  int basered = rand() % 255;
  int basegreen = rand() % 255;
  int baseblue = rand() % 255;
  for (int i =0;i<100;i++){
    palette[i].red = basered + rand() % 100 - 50;
    palette[i].green = basegreen + rand() % 100 - 50;
    palette[i].blue = baseblue + rand() % 100 - 50;
  }
  float width = abs(xmax-xmin)/2;
  float height = abs(ymax-ymin)/2;
  // compute image
  
  gettimeofday(&tstart, NULL);
  pthread_t threads[4];
  struct thread_data data[4];
  for (int i = 0; i < 4; i++) {
    data[i].size = size;
    data[i].xmin = xmin;
    data[i].xmax = xmax;
    data[i].ymin = ymin;
    data[i].ymax = ymax;
    data[i].pxl = pxl;
    data[i].pal = palette;
    int rstart = (size/2)*(i%2);
    int cstart = (size/2)*((i+1)%2);
    data[i].rstart = rstart;
    data[i].rend = rstart + size/2;
    data[i].cstart = cstart;
    data[i].cend = cstart + size/2;

    pthread_create(&threads[i], NULL, makeMandel, (void*) &data[i]);
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
  }
   
  gettimeofday(&tend, NULL);
  double timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  // compute image
  printf("Computed mandelbrot set (%dx%d) in %g seconds\n",size,size,timer);

  char newfile[64];
  sprintf(newfile,"multi_mandelbrot-<%d>-<%d>.ppm",size,(int)time(0));
  newfile[strlen(newfile)]='\0';
  write_ppm(newfile,pxl,size,size);


}
