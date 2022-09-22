/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 3
*/

// PARALLEL
#include <omp.h>
int ROW = 2;
int COL = 2;
#define NUM_THREADS 4

int main() {

  double start = omp_get_wtime();
  int id;

  int n_per_thread;
  int total_threads = NUM_THREADS;

  int mat1[ROW][COL], mat2[ROW][COL], mat3[ROW][COL];
  int i, j;
  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COL; j++) {
      mat1[i][j] = i + j;
      mat2[i][j] = i + j;
      mat3[i][j] = 0;
    }
  }

  // Additional work to set the number of threads.
  omp_set_num_threads(total_threads);

  // determine how many elements each process will work on
  n_per_thread = ROW * COL / total_threads;
#pragma omp parallel for shared(a, b, c) private(i)                            \
    schedule(static, n_per_thread)
  {
    id = omp_get_thread_num();

    for (i = 0; i < ROW; i++) {
      for (j = 0; j < COL; j++) {
        mat3[i][j] = mat1[i][j] + mat2[i][j];
      }
    }
  }
  double end = omp_get_wtime();
  double total_time = end - start;
  printf("Time taken : %lf", total_time);
  return 0;
}
