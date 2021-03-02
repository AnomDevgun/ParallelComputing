//Have set OMP_NUM_THREADS = 8, therefore hello world will be printed 8 times as each thread carries out an individual task.
//export OMP_NUM_THREADS=num_threads


#include<stdio.h>
#include<omp.h>

int main(){
	//What the following does is tell the system to give us the number of threads requested(in this case it will be what has been set as the default using the OMP_NUM_THREADS command)
	//Structured block that binds with the parallel pragma.
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		printf("Hello World	Thread:(%d)\n",id);
	}
	
}
