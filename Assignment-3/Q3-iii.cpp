// If there are multiple independent loops within a parallel region,
//  you can use the nowait clause to avoid the implied barrier
//   at the end of the loop construct, as follows:

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{	
    int n = 200, i ,j=99;
    
    int arr1[n], answer[n];
    
	for(i = 0; i < n; i++)
	{
        arr1[i] = rand()%100;
    }    
    
    double time = omp_get_wtime();
    
	#pragma omp parallel 
    {
	    #pragma omp for nowait
	    for(i = 0; i < n; i++)
	    {
	        answer[i] = arr1[i] + j;
	    }
    }
    
    printf("\nDone In %f Seconds\n\n", omp_get_wtime() - time);
    
    printf("\nArray 1: \n");
    for(i = 0; i < n; i++){
        printf("\t %d", arr1[i]);
    }

    printf("\nAnswer: \n");
    for(i = 0; i < n; i++){
        printf("\t %d", answer[i]);
    }
    return 0;
}

