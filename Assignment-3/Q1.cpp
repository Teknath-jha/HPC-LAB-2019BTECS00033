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

int main()
{
	//fill the code;
	int i,tid,n,psum;
	int threads = 4;
	cout<<"Enter Size of Array: ";
	cin>>n;
	int arr1[n], arr2[n];
	cout<<"Enter Elements of First Array:\n";
	for(i = 0; i < n ; i++)
	{
		cin>>arr1[i];
	}
	cout<<"Enter Elements of Second Array:\n";
	for(i = 0; i < n ; i++)
	{
		cin>>arr2[i];
	}
	sort(arr1, n);
	sort_des(arr2, n);
	int sum = 0;
	#pragma omp parallel private(i,tid,psum) num_threads(threads)
	{
		psum=0;
		tid = omp_get_thread_num();
		#pragma omp for reduction(+:sum)
		for(int i=0; i<n; i++)
		{
			sum += arr1[i] * arr2[i];
			psum+=sum;
		}
		printf("Thread %d partial sum = %d\n",tid,psum);
	}
	cout<<"Sum: "<<sum<<endl;
	
	return 0;
}
