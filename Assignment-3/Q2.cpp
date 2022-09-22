/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 3
*/

// PARALLEL
#include<stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4
#define ll long long int 
ll row = 500;
ll col  = 500;


int main() {

  double start = omp_get_wtime();

ll ROW = row;
ll COL = col;


  ll mat1[ROW][COL], mat2[ROW][COL], mat3[ROW][COL];
  int i, j;
  for (i = 0; i < ROW; i++) {
    for (j = 0; j < COL; j++) {
      mat1[i][j] = i;
      mat2[i][j] = j;
      mat3[i][j] = 0;
    }
  }

int total_threads = NUM_THREADS;
  omp_set_num_threads(total_threads);

  ll n_per_thread = ROW  / total_threads;
  
  #pragma omp parallel for shared(mat1,mat2,mat3) private(i,j) schedule(static, n_per_thread)
    for (i = 0; i < ROW; i++) {
      for (j = 0; j < COL; j++) {
        if (mat3[i][j] == 0) {
          mat3[i][j] = mat1[i][j] + mat2[i][j];
          printf("Calculated for mat3[%d][%d] by thread %d \n",i,j,omp_get_thread_num());
        } else {
          printf("Already calculated %d \n",omp_get_thread_num());
        }
      }
    }
  double end = omp_get_wtime();
  double total_time = end - start;
  printf("Time taken : %lf\n", total_time);
  
  //to verify ans 
//  for(i=0;i<ROW; i++){
//  	for(j=0;j<COL;j++){
//  		printf("%d + %d = %d\n",mat1[i][j],mat2[i][j],mat3[i][j]);
//	  }
//  }
  return 0;
}
