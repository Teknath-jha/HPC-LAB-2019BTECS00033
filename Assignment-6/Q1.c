// Q1: Implement a MPI program to give an example of Deadlock.

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    
    int myRank;
    MPI_Status status;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    int msgtag=1;
    
    //Here i've used synchronous send 
    
    if(myRank==0){
        int data = 10;
        printf("P0 process will send data to P1 \n ");
        MPI_Ssend(&data,1,MPI_INT,1,msgtag,MPI_COMM_WORLD);
        printf("P0 process after sent \n ");
        printf("P0 process will receive \n ");
        MPI_Recv(&data,1,MPI_INT,1,msgtag,MPI_COMM_WORLD,&status);
        printf("P0 process received from P1: %d \n ",data);
        printf("MPI process %d received value %d from rank %d, with tag %d .\n", 
               myRank,
               data,
               status.MPI_SOURCE,
               status.MPI_TAG);
    }else  {
        int data = 20;
        printf("P1 process will send data to P0 \n ");
        MPI_Ssend(&data,1,MPI_INT,0,msgtag,MPI_COMM_WORLD);
        printf("P1 process after sent \n ");
        printf("P1 process will receive \n ");
        MPI_Recv(&data,1,MPI_INT,0,msgtag,MPI_COMM_WORLD,&status);
        printf("P1 process received from P0: %d \n ",data);
        printf("MPI process %d received value %d from rank %d, with tag %d .\n", 
               myRank,
               data,
               status.MPI_SOURCE,
               status.MPI_TAG);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
