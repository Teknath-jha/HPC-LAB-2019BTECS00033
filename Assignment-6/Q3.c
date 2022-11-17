// Q3. Write a MPI program to find the sum of all the elements of an array A of size n.
// Elements of an array can be divided into two equals groups.
// The first [n/2] elements are added by the first process, P0, and last [n/2] elements the by second process, P1.
// The two sums then are added to get the final result.

#include <mpi.h>
#include <stdio.h>

int sizeOfArray = 15;
int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

int main(int argc, char *argv[])
{
    

    int myRank,tag=1;
    MPI_Status status;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&myRank);

    if(myRank==0){

        int size = sizeOfArray/2;
        int sum=0;
        for(int i=0;i<size;i++){
            sum+=arr[i];
        }

        printf("sum of half array at P0 is %d \n\n",sum);
        printf("P0 sending sum of half to P1 \n\n");
        MPI_Send(&sum,1,MPI_INT,1,tag,MPI_COMM_WORLD);

    }else if(myRank==1){

        int size = sizeOfArray/2;
        int restSum=0;
        for(int i=size;i<sizeOfArray;i++){
            restSum+=arr[i];
        }
        int restHalfSum;
        MPI_Recv(&restHalfSum,1,MPI_INT,0,tag,MPI_COMM_WORLD,&status);

        printf("\nSum received from P0 = %d \nsum calculated rest of half array at P1 = %d \n\n so sum of array = %d\n",restHalfSum,restSum,restHalfSum+restSum);
    }

    MPI_Finalize();

}