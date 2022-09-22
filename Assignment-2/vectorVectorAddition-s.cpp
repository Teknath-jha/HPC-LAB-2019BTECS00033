/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 2
*/

// Sequential


#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000

int main() {
	printf("Sequential Program : \n");

  int n = ARRAY_SIZE;
  int i;

  int a[n], b[n], c[n];

  // initializing both vectors
  for (i = 0; i < n; i++) {
    a[i] = i;
  }
  for (i = 0; i < n; i++) {
    b[i] = i;
  }

  double start = omp_get_wtime();
  for (i = 0; i < n; i++) {
    c[i] = a[i] + b[i];
    printf("Thread %d works on element %d\n", omp_get_thread_num(), i);
  }
  double end = omp_get_wtime();
  double total_time = (end - start) / CLOCKS_PER_SEC;
  printf("Time taken : %lf\n\n", total_time);

  return 0;
}
