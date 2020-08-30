#include<stdio.h>
#include<omp.h>
static long num_steps = 100000;
double step;
#define NUM_THREADS 2
#define PAD 8
//assume 64 byte L1 cache size line
void main(){
  int i,nthreads;
  double pi,sum[NUM_THREADS][PAD];     //Since all threads have their own stack and access shared local memory, to avoid race condition we create a sum array that stores individual thread sums
  step = 1.0/(double)num_steps;
  omp_set_num_threads(NUM_THREADS);     //Setting the number of threads
  #pragma omp parallel
  {
    int i,id,nthrds;
    double x;
    id = omp_get_thread_num();                //get the thread id (for each thread)
    nthrds = omp_get_num_threads();           //nthrds is the actual number of threads allocated in the parallel space
    if(id==0){                          //id 0 is the master or main thread.
      nthreads = nthrds;            //you may not actually get all the requested number of threads, therefore this condition checks the number acually given and stores it in a locally shared variable
    }
    for (i=id,sum[id][0]=0.0;i<num_steps;i=i+nthrds){        //allot chunks of data to each thread to work on 
      x = (i+0.5)*step;
      sum[id][0]+=4.0/(1.0+x*x);
    }
  }
  for(i=0,pi=0.0;i<nthreads;i++)              //outside the parallel pragma now we sum the array to get the final answer
      pi += sum[i][0]*step;
printf("(%f)\n",pi);
}
