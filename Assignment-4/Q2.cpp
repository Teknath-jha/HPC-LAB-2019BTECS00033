/*
Author - Teknath jha
PRN    - 2019BTECS00033
HPC-Lab- 4



Q2: Analyse and implement a Parallel code for below programs using OpenMP
considering synchronization requirements. (Demonstrate the use of different
clauses and constructs wherever applicable). Producer Consumer Problem:
*/

#include <stdio.h>
#include <stdlib.h>

int mutex = 1, full = 0, empty = 10, x = 0;

void producer() {

  --mutex;

  ++full;

  --empty;

  x++;
  printf("\nProducer produces"
         "item %d",
         x);

  ++mutex;
}

void consumer() {

  --mutex;

  --full;

  ++empty;
  printf("\nConsumer consumes "
         "item %d",
         x);
  x--;

  ++mutex;
}

int main() {
  int n, i;
  printf("\n1. Press 1 for Producer"
         "\n2. Press 2 for Consumer"
         "\n3. Press 3 for Exit");

#pragma omp critical
  for (i = 1; i > 0; i++) {
    printf("\nEnter your choice:");
    scanf("%d", &n);
 
    if(n==1){
      if ((mutex == 1) && (empty != 0)) {
        producer();
      }

      else {
        printf("Buffer is full!");
      }
      if(n==2)
{

      if ((mutex == 1) && (full != 0)) {
        consumer();
      }

      else {
        printf("Buffer is empty!");
      }}
    else if(n==3){
	
      exit(0);
      
   } }
  }
}
