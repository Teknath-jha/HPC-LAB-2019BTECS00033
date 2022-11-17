// Q2. Implement blocking MPI send & receive to demonstrate Nearest neighbor exchange of data in a ring topology.

#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[])
{

int numOfTasks, myRank , next , prev , buf[2] , tag1=1,tag2=2;
MPI_Request reqs[4];   // for non-blocking 
MPI_Status stats[4];   //for waitall routine

MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&numOfTasks);
MPI_Comm_rank(MPI_COMM_WORLD, &myRank);


// determine nearest neighbour 
prev = myRank-1;
next = myRank+1;

if(myRank==0) prev = numOfTasks-1;
if(myRank == (numOfTasks-1))next=0;


//post non-blocking receives and sends for neighbours
printf("%d process receving from %d \n",myRank,prev);
MPI_Irecv(&buf[0],1,MPI_INT,prev,tag1,MPI_COMM_WORLD,&reqs[0]);

printf("%d process receving from %d \n",myRank,next);
MPI_Irecv(&buf[1],1,MPI_INT,next,tag2,MPI_COMM_WORLD,&reqs[1]);

printf("%d process sending to %d \n",myRank,prev);
MPI_Isend(&myRank,1,MPI_INT,prev,tag2,MPI_COMM_WORLD,&reqs[2]);

printf("%d process sending to %d \n",myRank,next);
MPI_Isend(&myRank,1,MPI_INT,next,tag1,MPI_COMM_WORLD,&reqs[3]);

//wait for all non-blocking operations to complete 
MPI_Waitall(4,reqs,stats);

MPI_Finalize();

}