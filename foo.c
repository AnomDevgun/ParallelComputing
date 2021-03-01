#include <omp.h>
#include<stdio.h>
int main()
{
#pragma opm parallel
{
int ID = 0;
printf("hello(%d)",ID);
printf("word(%d)\n",ID);
}
}
