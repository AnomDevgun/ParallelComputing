#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define NUMTHREADS 4

int main(){
  //////////////////////////////////////SERIAL CODE
  int n;
  printf("Please input dimension N of the matrices, the matrices will be randomly filled: ");
  scanf("%d",&n);

int **a = (int **)malloc(n * sizeof(int *));
int **b = (int **)malloc(n * sizeof(int *));
int **res = (int **)malloc(n * sizeof(int *));
for (int i=0; i<n; i++)
{
  a[i] = (int *)malloc(n * sizeof(int));
  b[i] = (int *)malloc(n * sizeof(int));
  res[i] = (int *)malloc(n * sizeof(int));
}



double t5 = omp_get_wtime();
#pragma omp parallel for
  for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              a[i][j] = rand()%10;
          }
      }
double t6 = omp_get_wtime();

double t7 = omp_get_wtime();
      for(int i=0;i<n;i++)
          {
              for(int j=0;j<n;j++)
              {
                  b[i][j] = rand()%10;
              }
          }
double t8 = omp_get_wtime();

              for(int i=0;i<n;i++)
                  {
                      for(int j=0;j<n;j++)
                      {
                          res[i][j] = 0;
                      }
                  }

double t1 = omp_get_wtime();
  for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              for(int k=0;k<n;k++)
              {
                  res[i][j] = res[i][j] + (a[i][k] * b[k][j]);
              }
          }
      }
      double t2 = omp_get_wtime();
      for(int i=0;i<n;i++)
          {
              for(int j=0;j<n;j++)
              {
                  printf("%d ",res[i][j]);
              }
              printf("\n");
          }

      ////////////////////////////////////////////////////////////////// Clearing res matrix from serial calculation.
      for(int i=0;i<n;i++)
                  {
                      for(int j=0;j<n;j++)
                      {
                          res[i][j] = 0;
                      }
                  }

  /////////////////////////////////////////////////////////////////////// PARALLEL CODE
  omp_set_num_threads(NUMTHREADS);
      double t3 = omp_get_wtime();
      #pragma omp parallel for
      	for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              for(int k=0;k<n;k++)
              {
                  res[i][j] = res[i][j] + (a[i][k] * b[k][j]);
              }
          }
      }
      double t4 = omp_get_wtime();
      /////////////////////////////////////////////////////////////////Printing res matrix(not a necessary step)
      printf("\n\n\n\n\n\n");
      for(int i=0;i<n;i++)
          {
              for(int j=0;j<n;j++)
              {
                  printf("%d ",res[i][j]);
              }
              printf("\n");
          }
        printf("Time taken in serial %f\n",(t2-t1) );
      printf("Time taken in parallel %f\n",(t4-t3) );
      printf("Time taken in parallel to fill %f\n",(t6-t5) );
    printf("Time taken in serial to fill %f\n",(t8-t7) );

free(a);
free(b);
free(res);


}
