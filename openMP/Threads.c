#include<stdio.h>
#include<omp.h>
// int main(){
//   int arr[1000];
//   omp_set_num_threads(4);
//   #pragma omp parallel
//   {
//     int ID = omp_get_thread_num();
//     pooh(ID,arr);
//   }
// }
static long num_steps = 100000;
double step=6.0;
int main(){
  int i;
  double x,pi,sum=0.0;
  for(i=0;i<num_steps;i++){
    x = (i+0.5)*step;
    sum = sum+4.0/(1.0+x*x);
  }
  pi = step*sum;
  printf("%f\n",pi);
}

//use omp get num omp_set_num_threads, omp get thread num and omp get wtime
