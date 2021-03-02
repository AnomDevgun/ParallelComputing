#include<stdio.h>
#include<omp.h>

int main(){
	#pragma omp parallel
	{
		#pragma omp for
		{
			for(i=0;i<N;i++){
				do_work(i);
			}
		}
	}
}
