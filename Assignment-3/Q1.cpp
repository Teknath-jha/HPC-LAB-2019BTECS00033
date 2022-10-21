/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 3
AIM : Sorting techniques 
*/
// C Program to find the minimum scalar product of two vectors (dot product)
#include<bits/stdc++.h>
#include <omp.h>

using namespace std;

int sort(int arr[], int n)
{
	int i, j;
	#pragma omp parallel shared(arr) private(j)
	#pragma omp for schedule(dynamic)
	for (i = 0; i < n-1; i++)
		for (j = 0; j < n-i-1; j++)
			if (arr[j] > arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
}

int sort_des(int arr[], int n)
{
	int i,j;
	#pragma omp parallel shared(arr) private(j)
	#pragma omp for schedule(dynamic)
	for (i = 0; i < n; ++i)
	{
		for (j = i + 1; j < n; ++j)
		{
			if (arr[i] < arr[j])
			{
				int a = arr[i];
				arr[i] = arr[j];
				arr[j] = a;
			}
		}
	}
}
int main() {
	
  int n=1000,i;
  
int arr1[n] , arr2[n];
for(int i=0;i<n;i++){
	arr1[i]=n-i;
	arr2[i]=i+1;
}
    
//    double start = omp_get_wtime();
  
  n_per_thread = n/NUM_THREADS;
  sort(arr1, n);
  sort_des(arr2, n);
  int sum = 0;
   printf("\n\n");
  
//   for(i=0;i<n;i++)printf("%d ",arr1[i]);
//   printf("\n\n");
//   
//   for(i=0;i<n;i++)printf("%d ",arr2[i]);
//   printf("\n\n");
//   
   int num1 ,num2 ;
  	double start = omp_get_wtime();
  #pragma omp parallel for reduction(+:sum)  shared(arr1,arr2) private(i) schedule(static, n_per_thread)
  for (i = 0; i < n; i++) {
  	 num1 = arr1[i];
  	 num2 = arr2[i];
    sum += (num1*num2);
    printf("Sum : %d for ",sum,i)
  }
  
  double end = omp_get_wtime();
	double total_time=(end-start)/CLOCKS_PER_SEC;
  
  printf("% d \n\n", sum);
  printf("Time taken : %lf\n\n",total_time);
  return 0;
}
