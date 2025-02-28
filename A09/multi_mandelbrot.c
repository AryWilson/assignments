#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include "read_ppm.h"
#include <string.h>
#include <sys/types.h>


#define MAX 1000


void makeMandel(int rstart, int cstart, int rend, int cend, int size, float xmin,
float xmax, float ymin, float ymax, struct ppm_pixel *pxl, int *red, int *green, int *blue){

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
        pxl[col*size+row].red = red[iter%100];
        pxl[col*size+row].green = green[iter%100];
        pxl[col*size+row].blue = blue[iter%100];
      }else{
        pxl[col*size+row].red = 0;
        pxl[col*size+row].green = 0;
        pxl[col*size+row].blue = 0;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;

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
  printf("  Num processes = 4\n");
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // todo: your work here
  srand(time(0)); 
  struct timeval tstart, tend;
  int shmid = shmget(IPC_PRIVATE, sizeof(struct ppm_pixel)*size*size, 0644 | IPC_CREAT);
  if (shmid == -1) {
    perror("Error: cannot initialize shared memory\n");
    exit(1);
  }
  struct ppm_pixel *pxl = shmat(shmid, NULL, 0);
  if (pxl == (void*) -1) {
    perror("Error: cannot access shared memory\n");
    exit(1);
  } 
  
  /*struct ppm_pixel *pxl = malloc(sizeof(struct ppm_pixel)*(size)*(size));
  if(pxl==NULL){
    printf("malloc error\n");
    exit(1);
  }*/ 
  
  // generate pallet
  int red[100];
  int green[100];
  int blue[100];

  int basered = rand() % 255;
  int basegreen = rand() % 255;
  int baseblue = rand() % 255;
  for (int i =0;i<100;i++){
    red[i] = basered + rand() % 100 - 50;
    green[i] = basegreen + rand() % 100 - 50;
    blue[i] = baseblue + rand() % 100 - 50;
  }
  float width = abs(xmax-xmin)/2;
  float height = abs(ymax-ymin)/2;
  
  pid_t pid;
  gettimeofday(&tstart, NULL);
  pid = fork();
  int child_status;  
  if(pid == 0){
    pid = fork();
    if(pid == 0){
      printf("Launched child process: %d\n",getpid());
      printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n",getpid(),0,size/2,0,size/2);
      makeMandel(0,0,size/2,size/2,size, xmin, xmax, ymin, ymax, pxl, red, green, blue);
    }else{
      printf("Launched child process: %d\n",getpid());
      printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n",getpid(),0,size/2,size/2,size);
      makeMandel(0,size/2,size/2,size,size, xmin, xmax, ymin, ymax, pxl, red, green, blue);
    }
    printf("Child process complete: %d\n",getpid());
    exit(0);
  }else{  
    pid = fork();
    if (pid ==0){
      printf("Launched child process: %d\n",getpid());
      printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n",getpid(),size/2,size,0,size/2);
      makeMandel(size/2,0,size,size/2,size, xmin, xmax, ymin, ymax, pxl, red, green, blue);
    }else{
      printf("Parent process: %d\n",getpid());
      printf("%d) Sub-image block: cols (%d, %d) to rows (%d, %d)\n",getpid(),size/2,size,size/2,size);
      makeMandel(size/2,size/2,size,size,size, xmin, xmax, ymin, ymax, pxl, red, green, blue);
    }
  }
  if(pid==0){
    printf("Child process complete: %d\n",getpid());
    exit(0);
  }
  //wait(&child_status);
  while(wait(&child_status)>0){
    //printf("Child process complete: %d",getpid());
  }
  gettimeofday(&tend, NULL);
  double timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  // compute image
  printf("Computed mandelbrot set (%dx%d) in %g seconds\n",size,size,timer);

  char newfile[64];
  sprintf(newfile,"multi_mandelbrot-<%d>-<%d>.ppm",size,(int)time(0));
  newfile[strlen(newfile)]='\0';
  write_ppm(newfile,pxl,size,size);
  
  
  if (shmdt(pxl) == -1) {
    perror("Error: cannot detatch from shared memory\n");
    exit(1);
  }

  if (shmctl(shmid, IPC_RMID, 0) == -1) {
    perror("Error: cannot remove shared memory\n");
    exit(1);
  }  
   
  printf("parent process complete: %d\n",getpid());
  return 0;
}
