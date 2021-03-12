#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define NUMTHREADS 4

int main(){
  int n=0,i,j,search=0,count=0,counts=0;
  printf("\nPlease enter the size of the matrix to be dynamically created and filled: ");
  scanf("%d",&n);
  int **arr = (int **)malloc(n * sizeof(int *));


  for(j=0;j<n;j++){
    arr[j] = (int *)malloc(n* sizeof(int *));
  }

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      arr[i][j] = rand()%10;
    }
  }

  printf("\nEnter a number between 0 and 9 to count number of occurences in the matrix: ");
  scanf("%d",&search);




  omp_set_num_threads(NUMTHREADS);
  double t1 = omp_get_wtime();
  #pragma omp parallel
    #pragma omp single
    #pragma omp task
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
        if(arr[i][j]==search){
            count+=arr[i][j];
        }
      }
    }

    double t2= omp_get_wtime();
      for(i=0;i<n;i++){
        for(j=0;j<n;j++){
          if(arr[i][j]==search){
            counts+=arr[i][j];
          }
        }
      }
      t2 = omp_get_wtime() - t2;


    t1 = omp_get_wtime()-t1;
    printf("\nTime taken in parallel: %f\n",t1);
    printf("\nTime taken in serial: %f\n",t2);
    printf("\nNumber of occurences found in parallel: %d\n",count);
    printf("\nNumber of occurences found in serial: %d\n",counts);
    free(arr);
}
