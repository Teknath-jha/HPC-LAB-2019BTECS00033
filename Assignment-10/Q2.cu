include<stdio.h>
#define row1 20
#define col1 30
#define row2 30
#define col2 20

    __global__ void matproductsharedmemory(int *l, int *m, int *n) {
  int x = blockIdx.x;
  int y = blockIdx.y;
  __shared__ int p[col1];
  int i;
  int k = threadIdx.x;
  n[col2 * y + x] = 0;
  p[k] = l[col1 * y + k] * m[col2 * k + x];
  __syncthreads();
  for (i = 0; i < col1; i++)
    n[col2 * y + x] = n[col2 * y + x] + p[i];
}
int main() {
  int a[row1][col1];
  int b[row2][col2];
  int c[row1][col2];
  int *d, *e, *f;
  int i, j;
  for (i = 0; i < row1; i++) {
    for (j = 0; j < col1; j++) {
      a[i][j] = 2;
    }
  }
  for (i = 0; i < row2; i++) {
    for (j = 0; j < col2; j++) {
      b[i][j] = 3;
    }
  }
  cudaMalloc((void **)&d, row1 * col1 * sizeof(int));
  cudaMalloc((void **)&e, row2 * col2 * sizeof(int));
  cudaMalloc((void **)&f, row1 * col2 * sizeof(int));
  cudaMemcpy(d, a, row1 * col1 * sizeof(int), cudaMemcpyHostToDevice);
  cudaMemcpy(e, b, row2 * col2 * sizeof(int), cudaMemcpyHostToDevice);
  dim3 grid(col2, row1);
  matproductsharedmemory<<<grid, col1>>>(d, e, f);
  cudaDeviceSynchronize();
  cudaMemcpy(c, f, row1 * col2 * sizeof(int), cudaMemcpyDeviceToHost);
  for (i = 0; i < row1; i++) {
    for (j = 0; j < col2; j++) {
      if (c[i][j] != 180) {
        printf("False\n");
        return -1;
      }
    }
  }
  cudaFree(d);
  cudaFree(e);
  cudaFree(f);
  printf("True\n");
  return 0;
}