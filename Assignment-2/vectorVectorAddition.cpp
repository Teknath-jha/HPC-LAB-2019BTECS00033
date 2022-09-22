/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 2
*/

// PARALLEL

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define NUM_THREADS 4

int main() {
	
	printf("Parallel Program : \n");

  int n = ARRAY_SIZE;              // number of array elements
  int n_per_thread;                // elements per thread
  int total_threads = NUM_THREADS; // number of threads to use
  int i;

  int a[n], b[n], c[n];

  for (i = 0; i < n; i++) {
    a[i] = i;
  }
  for (i = 0; i < n; i++) {
    b[i] = i;
  }

  // Additional work to set the number of threads.
  omp_set_num_threads(total_threads);

  // determine how many elements each process will work on
  n_per_thread = n / total_threads;

  double start = omp_get_wtime();
#pragma omp parallel for shared(a, b, c) private(i)                            \
    schedule(static, n_per_thread)
  for (i = 0; i < n; i++) {
    c[i] = a[i] + b[i];
    // Which thread am I? Show who works on what for this samll example
    printf("Thread %d works on element %d\n", omp_get_thread_num(), i);
  }
  double end = omp_get_wtime();
  double total_time = (end - start);
  printf("Time taken : %lf\n\n", total_time);

  return 0;
}
