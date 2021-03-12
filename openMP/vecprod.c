#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

/* Define length of dot product vectors and number of OpenMP threads */
#define VECLEN 999999
#define NUMTHREADS 1

int main (int argc, char* argv[])
{
int i, tid, len=VECLEN, threads=NUMTHREADS;
int *a, *b;
int sum,sums;

printf("Starting omp_dotprod_openmp. Using %d threads\n",threads);

/* Assign storage for dot product vectors */
a = (int*) malloc (len*sizeof(int));
b = (int*) malloc (len*sizeof(int));

/* Initialize dot product vectors */
for (i=0; i<len; i++) {
  a[i]=rand()%10;
  b[i]=rand()%10;
  }
/* Initialize global sum */
sum = 0.0;

/*
   Perform the dot product in an OpenMP parallel region for loop with a sum reduction
     - Explicitly sets number of threads
     - Each thread keeps track of its partial sum
*/
omp_set_num_threads(NUMTHREADS);
double t = omp_get_wtime();
#pragma omp parallel
{
#pragma omp for reduction(+:sum)
  for (i=0; i<len; i++)
    {
      sum += (a[i] * b[i]);
    }
}
t = omp_get_wtime() - t;
//SERIAL CODE
double ts = omp_get_wtime();
sums = 0.0;
for (i=0; i<len; i++)
  {
    sums += (a[i] * b[i]);
  }
  ts = omp_get_wtime()-ts;

printf ("Serial version: sum  =  %d \n", sums);
printf ("Serial version: time  =  %f \n", ts);
printf ("Parralel version: sum  =  %d \n", sum);
printf ("Parralel version: time  =  %f \n", t);
free (a);
free (b);
}
