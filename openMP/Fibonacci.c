#include<stdio.h>
int main()
{
 long long int n1=0,n2=1,n3=0,i,number;
 printf("Enter the number of elements:");
 scanf("%lld",&number);
 for(i=2;i<number;++i)//loop starts from 2 because 0 and 1 are already printed
 {
  n3=n1+n2;
  n1=n2;
  n2=n3;
 }
 printf("Last Fibonacci number in the sequence: %lld",n3);
  return 0;
 }








//////FOR FIBONACCI SEQ

// int fib(int n)
// {
//   int x,y;
//   if(n<2)return n;
//   #pragma omp task shared(x)
//     x=fib(n-1);
//   #pragma omp task shared(y)
//     y=fib(n-2);
//   #pragma omp taskwait
//     return x+y;
// }
