/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 2
*/

// PARALLEL

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100000
#define NUM_THREADS 4

int main() {

  int n = ARRAY_SIZE;
  int a[n], c[n], flag[n];
  int i;

  for (i = 0; i < n; i++) {
    a[i] = i;
    flag[i] = 0;
  }

  int n_per_thread;                // elements per thread
  int total_threads = NUM_THREADS; // number of threads to use
  // Additional work to set the number of threads.
  omp_set_num_threads(total_threads);

  // determine how many elements each process will work on
  n_per_thread = n / total_threads;

  int x = 5;

  double start = omp_get_wtime();
#pragma omp parallel for shared(a, c, x) private(i)                            \
    schedule(static, n_per_thread)
  for (i = 0; i < n; i++) {
    if (!flag[i]) {
      c[i] = a[i] + x;
      flag[i] = 1;
      printf("\nThread number %d, executing iteration %d first time",
             omp_get_thread_num(), i);

    } else {
      printf("\nThread number %d, executing iteration %d already computed",
             omp_get_thread_num(), i);
    }
  }

  double end = omp_get_wtime();
  double total_time = (end - start);
  printf("Time taken : %lf\n\n", total_time);
}
