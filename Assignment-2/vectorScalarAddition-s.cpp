/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 2
*/

// SEQUENTIAL


#include <omp.h>
#include <stdio.h>
#include<stdlib.h>
#define n 10000


int main() {

    int a[n],c[n],flag[n];
    for(int i=0;i<n;i++)
    {
    	a[i]=i;
    	flag[i]=0;
	}
	int x=5;
	double start = omp_get_wtime();
	for(int i = 0;i < n;i++) {
	
			c[i]=a[i]+x;
			printf("\nThread number %d, executing iteration %d ",omp_get_thread_num(),i);	

	
	}
	
		double end = omp_get_wtime();
  double total_time = (end - start);
  printf("Time taken : %lf\n\n", total_time);
	
}
