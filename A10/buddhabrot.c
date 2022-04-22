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

#define MAX 1000
static unsigned long long maxCount = 0;
pthread_mutex_t mutex;
pthread_barrier_t barrier;

struct thread_data {
  int rstart;
  int rend;
  int cstart;
  int cend; 
  int size; 
  float xmin; 
  float xmax; 
  float ymin; 
  float ymax;
  struct ppm_pixel *pxl; 
  bool *mandel;
  int *vcount;
  
};

void *makeBuddha(void* userdata){
  struct thread_data *data = (struct thread_data *) userdata;
  int rstart = data->rstart;
  int rend = data->rend;
  int cstart = data->cstart;
  int cend = data->cend;
  int size = data->size;
  float xmin = data->xmin;
  float xmax = data->xmax; 
  float ymin = data->ymin;
  float ymax = data->ymax; 
  struct ppm_pixel *pxl = data->pxl;
  bool *mandel = data->mandel;
  int *vcount = data->vcount;
  printf("Thread %ld) sub-image block: cols (%d, %d) to rows (%d,%d)\n", 
  pthread_self(),cstart,cend,rstart,rend);  
  

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
      int yrow;
      int xcol;
      while ((iter < MAX) &&( x*x + y*y < 2*2)){
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter=iter+1;
        
        
      }
      
      if (iter < MAX){ // escaped
        mandel[col*size+row] = false;
        
      
      }else{
        mandel[col*size+row] = true;
      }
    }
  }
  
  unsigned long long lmaxcount = 0;
  for (int row = rstart; row<rend; row++){
    for (int col = cstart; col<cend; col++){
      if (mandel[col*size+row]){continue;}

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
        if (yrow < 0 || yrow >= size) continue; // out of range
        if (xcol < 0 || xcol >= size) continue; // out of range
        
        int temp = vcount[xcol*size+yrow]+1;
        vcount[xcol*size+yrow] = temp;
        if(lmaxcount<temp){lmaxcount=temp;}
      }
    }
  }
  pthread_mutex_lock(&mutex);
  maxCount += lmaxcount;
  pthread_mutex_unlock(&mutex);


  pthread_barrier_wait(&barrier);
  //printf("maxcount=%lld\n",maxCount); 
  float gamma = 0.681;
  float factor = 1.0/gamma; 
  float value = 0;
  for (int row = rstart; row<rend; row++){
    for (int col = cstart; col<cend; col++){
      value = 0;
      int count = vcount[col*size+row];
      if(count > 0){
        value = log(count)/log(maxCount);
        value = pow(value,factor);
      }
      pxl[row*size+col].red = value * 255;
      pxl[row*size+col].green = value * 255;
      pxl[row*size+col].blue = value * 255;
      
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

  //initialize 

  srand(time(0)); 
  struct timeval tstart, tend;
  struct ppm_pixel *pxl = malloc(sizeof(struct ppm_pixel)*(size)*(size));
  
  bool *mandel = malloc(sizeof(bool)*size*size);//is the point in the set?
  int *vcount = malloc(sizeof(int)*size*size);//how many times is the point visited
  
  if((pxl==NULL)|(mandel==NULL)|(vcount==NULL)){
    printf("malloc error\n");
    exit(1);
  }  

  
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
    data[i].mandel = mandel;
    data[i].vcount = vcount;
    int rstart = (size/2)*(i%2);
    data[i].rstart = rstart;
    data[i].rend = rstart + size/2;
    int cstart = (size/2)*(floor(i/2));
    data[i].cstart = cstart;
    data[i].cend = cstart + size/2;

    pthread_barrier_init(&barrier,NULL,4);
    pthread_create(&threads[i], NULL, makeBuddha, (void*) &data[i]);
  }

  for (int i = 0; i < 4; i++) {
    pthread_barrier_destroy(&barrier);
    pthread_join(threads[i], NULL);
  }
  
  gettimeofday(&tend, NULL); 
  double timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %g seconds\n",size,size,timer);


  //write to output file
  char newfile[64];
  sprintf(newfile,"buddhabrot-<%d>-<%d>.ppm",size,(int)time(0));
  newfile[strlen(newfile)]='\0';
  write_ppm(newfile,pxl,size,size);       
  
  free(pxl);
  pxl = NULL;
  free(mandel);
  mandel = NULL;
  free(vcount);
  vcount = NULL;
}
