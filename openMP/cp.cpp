#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<omp.h>
#include<vector>

using namespace std;


#define n 1000

int main(){
  //////////////////////////////////////SERIAL CODE
  // int n;
  // printf("Please input dimension N of the matrices, the matrices will be randomly filled: ");
  // scanf("%d",&n);
  // long long int a[n][n];
  // long long int b[n][n];
  // long long int res[n][n];

  vector<vector<int>> a[n];
  vector<vector<int>> b[n];
  vector<vector<int>> res[n];


double t5 = omp_get_wtime();
#pragma omp parallel for
  for(int i=0;i<n;i++)
      {
          for(int j=0;j<a[i].size();j++)
          {
              a[i][j].push_back(rand()%10);
          }
      }
double t6 = omp_get_wtime();

double t7 = omp_get_wtime();
      for(int i=0;i<n;i++)
          {
              for(int j=0;j<b[i].size();j++)
              {
                  b[i][j].push_back(rand()%10);
              }
          }
double t8 = omp_get_wtime();

              for(int i=0;i<n;i++)
                  {
                      for(int j=0;j<res[i].size();j++)
                      {
                          res[i][j].push_back(0);
                      }
                  }

double t1 = omp_get_wtime();
  for(int i=0;i<n;i++)
      {
          for(int j=0;j<n;j++)
          {
              for(int k=0;k<a[i].size();k++)
              {
                  res[i][j] = res[i][j] + (a[i][k] * b[k][j]);
              }
          }
      }
      double t2 = omp_get_wtime();
      for(int i=0;i<n;i++)
          {
              for(int j=0;j<res[i].size();j++)
              {
                  printf("%d ",res[i][j]);
              }
              printf("\n");
          }

      //////////////////////////////////////////////////////////////////
  //     for(int i=0;i<n;i++)
  //                 {
  //                     for(int j=0;j<n;j++)
  //                     {
  //                         res[i][j].push_back(0);
  //                     }
  //                 }
  //
  // ///////////////////////////////////////////////////////////////////////
  // omp_set_num_threads(omp_get_num_procs());
  //     double t3 = omp_get_wtime();
  //     #pragma omp parallel for
  //     	for(int i=0;i<n;i++)
  //     {
  //         for(int j=0;j<n;j++)
  //         {
  //             for(int k=0;k<n;k++)
  //             {
  //                 res[i][j] = res[i][j] + (a[i][k] * b[k][j]);
  //             }
  //         }
  //     }
  //     double t4 = omp_get_wtime();
  //     /////////////////////////////////////////////////////////////////
  //     printf("\n\n\n\n\n\n");
  //     for(int i=0;i<n;i++)
  //         {
  //             for(int j=0;j<n;j++)
  //             {
  //                 printf("%d ",res[i][j]);
  //             }
  //             printf("\n");
  //         }
  //       printf("Time taken in serial %f\n",(t2-t1) );
  //     printf("Time taken in parallel %f\n",(t4-t3) );
      printf("Time taken in parallel to fill %f\n",(t6-t5) );
    printf("Time taken in serial to fill %f\n",(t8-t7) );



}
