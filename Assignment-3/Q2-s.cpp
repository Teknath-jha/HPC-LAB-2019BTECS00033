/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 3
*/
#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

int main()
{
	
	int tid, nthreads , i, j;
	int n=100;
	while(1){
		if(n==500)
			break;
		else
			n+=100;
		nthreads=4;
		int a[n][n], b[n][n], c[n][n];
			
		int index = 0;
			
		for (i = 0; i < n; i++)
		{
			
			for (j = 0; j < n; j++)
			{
				a[i][j] = b[i][j] = (i+j);
			}
		}
			
		printf("Time Required to do Matrix Multiplication of size %d\nUsing Threads: %d",n,nthreads);
		
		double time = omp_get_wtime();
			
		#pragma omp parallel shared(a, b, c, nthreads) private(tid, i, j) num_threads(nthreads)
		{
			# pragma omp parallel for
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					c[i][j] = a[i][j] + b[i][j];
				}
			}
		}
		
		printf("\nDone In %f Seconds\n\n", omp_get_wtime() - time);
		
	}
	return 0;
}






Output:
