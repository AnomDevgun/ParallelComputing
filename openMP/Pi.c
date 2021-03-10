//We are going to integrate the function 4.0/(1+X^2) in the limits 0->1, the exact integral is pi.


#include<stdio.h>
#include<omp.h>
#include<time.h>


static long num_steps = 100000;
double step;
#define NUM_THREADS 60
#define PAD 8 //assume 64 byte L1 cache size line, 8 is the number of double precision words in a cache line, this avoids false sharing.
void main(){
  int i,nthreads;
  double pi,sum[NUM_THREADS][PAD];     //Since all threads have their own stack and access shared local memory, to avoid race condition we create a sum array that stores individual thread sums
  step = 1.0/(double)num_steps;
  //////// Testing in serial code

    double x,sum2=0.0;
    clock_t t = clock();
    for(i=0;i<num_steps;i++){
    	x = (i+0.5)*step;
    	sum2 = sum2 + 4.0/(1.0+x*x);
    }
    t = clock() - t;
    pi=0;
    pi=step*sum2;
    printf("(%f)\n",pi);
    printf("Time taken in serial = %f\n",((double)t)/CLOCKS_PER_SEC);
    ///////////////////////////////////////////////////
  omp_set_num_threads(NUM_THREADS);     //Setting the number of threads
  double t1 = omp_get_wtime();
  #pragma omp parallel
  {
    int i,id,nthrds;
    double x;
    id = omp_get_thread_num();                //get the thread id (for each thread)
    nthrds = omp_get_num_threads();           //nthrds is the actual number of threads allocated in the parallel space
    if(id==0){                          //id 0 is the master or main thread.
      nthreads = nthrds;            //you may not actually get all the requested number of threads, therefore this condition checks the number acually given and stores it in a locally shared variable
    }
    for (i=id,sum[id][0]=0.0;i<num_steps;i=i+nthrds){        //allot chunks of data to each thread to work on in a cyclic fashion, ex: thread 0 gets chunk 0,8,16,24,etc if we assume nthrds=8
      x = (i+0.5)*step;
      sum[id][0]+=4.0/(1.0+x*x);
    }
  }
  double t2 = omp_get_wtime();
  for(i=0,pi=0.0;i<nthreads;i++)              //outside the parallel pragma now we sum the array to get the final answer
      pi += sum[i][0]*step;
  printf("(%f)\n",pi);
  printf("Time taken in parallel = %f\n",(t2-t1));


}
