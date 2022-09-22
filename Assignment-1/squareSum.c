/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 1
*/

//PARALLEL
//finding sum of squares of 1 to 100
#include<omp.h>
#include<time.h>

int main(){
	
	
	int id;
	long long int sum=0;
	long long  int square=0;
	long long  int pointer=0;
	double start = omp_get_wtime();
	#pragma omp parallel
	{
		
		while(pointer <101){
			 square = pointer*pointer;
			sum+=square;
			
			printf("\nSquare of %d: %d sum till here %d from thread %d \n",pointer,square,sum ,omp_get_thread_num() );
			
			pointer++;
			
		}
		
		printf("\nSum : %d from thread %d \n\n",sum ,omp_get_thread_num() );
		
	}
	double end = omp_get_wtime();
	double total_time=(end-start)/CLOCKS_PER_SEC;
	printf("Time taken : %lf\n\n",total_time);
	return 0;
}
