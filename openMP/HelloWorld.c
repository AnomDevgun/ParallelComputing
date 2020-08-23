//Have set OMP_NUM_THREADS = 8, therefore hello world will be printed 8 times as each thread carries out an individual task.

#include<stdio.h>
#include<omp.h>
int main(){
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		printf("Hello%d",id);
		printf("World%d\n",id);
	}
}
