/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 1
*/

//SEQUENTIAL
#include<stdio.h>
#include<omp.h>

int main(){
	
	double start = omp_get_wtime();
	int i;
	for( i=0;i<4;i++)
		printf("hello world %d \n",i);
	
	double end = omp_get_wtime();
	double total_time=end-start;
	printf("Time taken : %lf",total_time);
	return 0;
}
