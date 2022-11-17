#include <bits/stdc++.h>
using std namespace;



__global__ void prefixSum(int *v, int *v_r) {

  __shared__ int partial_sum[SHMEM_SIZE];
  // Calculate thread ID
  int tid = blockIdx.x * blockDim.x + threadIdx.x;
 
  partial_sum[threadIdx.x] = v[tid];
  __syncthreads();
  
  for (int s = 1; s < blockDim.x; s *= 2) {
   
    if (threadIdx.x % (2 * s) == 0) {
      partial_sum[threadIdx.x] += partial_sum[threadIdx.x + s];
    }
    __syncthreads();
  }
  
}


int main() {
  // Vector size
  int N = 1 << 16;
  size_t bytes = N * sizeof(int);
  // Host data
  vector<int> h_v(N);
  vector<int> h_v_r(N);
  // Initialize the input data
  generate(begin(h_v), end(h_v), []() { return rand() % 10; });
  // Allocate device memory
  int *d_v, *d_v_r;
  cudaMalloc(&d_v, bytes);
  cudaMalloc(&d_v_r, bytes);
  // Copy to device
  cudaMemcpy(d_v, h_v.data(), bytes, cudaMemcpyHostToDevice);
  // TB Size
  const int TB_SIZE = 256;
  // Grid Size (No padding)
  int GRID_SIZE = N / TB_SIZE;
  // Call kernels
  prefixSum<<<1, TB_SIZE>>>(d_v_r, d_v_r);
  // Copy to host;
  cudaMemcpy(h_v_r.data(), d_v_r, bytes, cudaMemcpyDeviceToHost);
  // Print the result
  assert(h_v_r[0] == std::accumulate(begin(h_v), end(h_v), 0));
  cout << "COMPLETED SUCCESSFULLY\n";
  return 0;
}