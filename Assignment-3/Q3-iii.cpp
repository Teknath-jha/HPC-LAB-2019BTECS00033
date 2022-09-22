// If there are multiple independent loops within a parallel region,
//  you can use the nowait clause to avoid the implied barrier
//   at the end of the loop construct, as follows:


#include <math.h>
#include <omp.h>
#include <stdio.h>


void nowait_example(int n, int m, float *a, float *b, float *y, float *z) {
  int i;
#pragma omp parallel
  {
#pragma omp for nowait
    for (i = 1; i < n; i++)
      {
      	b[i] = (a[i] + a[i - 1]) / 2.0;
      	printf("From 1st loop\n");
	  }

#pragma omp for nowait
    for (i = 0; i < m; i++)
      {
      	y[i] = sqrt(z[i]);
      printf("From 2nd loop\n");
	  }
  }
}

int main() {

  int n = 5, m = 5;
  float a[] = {1, 2, 3, 4, 5};
  float b[] = {1, 2, 3, 4, 5};
  float y[] = {1, 2, 3, 4, 5};
  float z[] = {1, 2, 3, 4, 5};

  nowait_example(n, m, a, b, y, z);

  return 0;
}
