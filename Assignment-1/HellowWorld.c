/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 1
*/

//PARALLEL
#include<time.h>
#include <omp.h>

int main() {
	printf("Parallel program : \n");
	double start = omp_get_wtime();
	#pragma omp parallel 
  {
    printf("hello world from 2019BTECS00033 by thread %d \n",omp_get_thread_num());
  }
  
  double end = omp_get_wtime();
	double total_time=(end-start)/CLOCKS_PER_SEC;
	printf("Time taken : %lf\n\n",total_time);
  return 0;
}
