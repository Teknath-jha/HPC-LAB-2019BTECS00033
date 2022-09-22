/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 4

Q1: Analyse and implement a Parallel code for below programs using OpenMP
considering synchronization requirements. (Demonstrate the use of different
clauses and constructs wherever applicable).

*/

// PARALLEL

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int fib(int n) {
	printf("running for %d \n",n);
  int i, j;
  if (n < 2)
    return n;
  else {
#pragma omp task shared(i)
    i = fib(n - 1);
#pragma omp task shared(j)
    j = fib(n - 2);
#pragma omp taskwait
    return i + j;
  }
}
int main() {
  int n=10, result;
  double start = omp_get_wtime();
#pragma omp parallel
  {
#pragma omp single
    result = fib(n);
  }
  double end = omp_get_wtime();
  double total_time=(end-start)/CLOCKS_PER_SEC;
 
  printf("Time taken : %lf\n\n",total_time);
  printf("%d th fib is :  %d\n",n, result);
}
