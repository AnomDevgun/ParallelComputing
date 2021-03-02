#include<stdio.h>
#include<omp.h>

int main(){
//Barrier
	#pragma omp parallel
	{
		int id = omp_get_thread_num;
		A[id] = some_calc1(id);
		//the barrier will stop all threads from proceeding until all threads are done with the current task.
	#pragma omp barrier
		B[id] = some_calc2(id,A);
		
	}
	
//Critical section
	#pragma omp parallel
	{
		float B;int i,id,nthrds;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		for(i=id;i<niters;i+=nthrds){
			B = some_job(i);
		//critical section of code ensures only one thread can work on that block of code at any given time.
		//other threads go into waiting while the current thread completes
			#pragma omp critical
				res +=consume(B);	
		}
	}
	
	
//Atomic 	
	#pragma omp parallel
	{
		double tmp,B2;
		B2 = doingwork();
		tmp = big_task(B);
		//Atomic is very akin to critical, but is used in certain situations such as read, update wherein we may not want the limitations critical enforces.
		//Statement in atomic should be in one of the following forms: x binop= expr, x++, +=x, x--, --x; x is scalar and binop is a non overloaded buit in operator
	#pragma omp atomic
		X +=tmp;	
	}	
}
