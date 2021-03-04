//We are going to integrate the function 4.0/(1+X^2) in the limits 0->1, the exact integral is pi.


#include<stdio.h>
#include<omp.h>
#include<time.h>


static long num_steps = 100000;
double step;
#define NUM_THREADS 4
void main(){
  int i,nthreads;
  double pi=0.0;     
  step = 1.0/(double)num_steps;
  omp_set_num_threads(NUM_THREADS);//Setting the number of threads
  double sum=0.0;     
  omp_set_schedule(omp_sched_dynamic,1);
  double t1 = omp_get_wtime();
  #pragma omp parallel for schedule(static) reduction(+:sum)
	  for(i=0;i<num_steps;i++){
	  	double x = (i+0.5)*step;
	  	sum = sum + 4.0/(1.0+x*x);
	  }
  double t2 = omp_get_wtime();	  
  pi += sum*step;	  
  printf("%f\n",pi);
  printf("Time taken: %f\n",(t2-t1));
}
