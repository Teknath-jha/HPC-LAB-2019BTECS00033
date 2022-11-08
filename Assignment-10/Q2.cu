#include <stdio.h>
#include <math.h>
#define TILE_WIDTH 2



/*matrix multiplication kernels*/

// shared
__global__ void
MatrixMulSh( float *Md , float *Nd , float *Pd , const int WIDTH )
{
	
	//Taking shared array to break the MAtrix in Tile widht and fatch them in that array per ele
	
	__shared__ float Mds [TILE_WIDTH][TILE_WIDTH] ;
	
	__shared__ float Nds [TILE_WIDTH][TILE_WIDTH] ;
	
	// calculate thread id
	unsigned int col = TILE_WIDTH*blockIdx.x + threadIdx.x ;
	unsigned int row = TILE_WIDTH*blockIdx.y + threadIdx.y ;
	
	for (int m = 0 ; m<WIDTH/TILE_WIDTH ; m++ ) // m indicate number of phase
	{
		Mds[threadIdx.y][threadIdx.x] =  Md[row*WIDTH + (m*TILE_WIDTH + threadIdx.x)]  ;
		Nds[threadIdx.y][threadIdx.x] =  Nd[ ( m*TILE_WIDTH + threadIdx.y) * WIDTH + col] ;
		__syncthreads() ; // for syncronizeing the threads
		
		// Do for tile
		for ( int k = 0; k<TILE_WIDTH ; k++ )
			Pd[row*WIDTH + col]+= Mds[threadIdx.x][k] * Nds[k][threadIdx.y] ;
		__syncthreads() ; // for syncronizeing the threads
		
	}
}

// main routine
int main ()
{
	const int WIDTH = 500;
	float array1_h[WIDTH][WIDTH] ,array2_h[WIDTH][WIDTH], M_result_array_h[WIDTH][WIDTH]  ;
	float *array1_d , *array2_d ,*result_array_d  ,*M_result_array_d ; // device array
	int i , j ;
	//input in host array
	for ( i = 0 ; i<WIDTH ; i++ )
	{
		for (j = 0 ; j<WIDTH ; j++ )
		{
			array1_h[i][j] = (i + 2*j) %500 ;
			array2_h[i][j] = (i + 3*j) %500 ;
		}
	}
	
	//create device array cudaMalloc ( (void **)&array_name, sizeofmatrixinbytes) ;
	
	cudaMalloc((void **) &array1_d , WIDTH*WIDTH*sizeof (int) ) ;
	
	cudaMalloc((void **) &array2_d , WIDTH*WIDTH*sizeof (int) ) ;
	
	
	
	//copy host array to device array; cudaMemcpy ( dest , source , WIDTH , direction )
	
	cudaMemcpy ( array1_d , array1_h , WIDTH*WIDTH*sizeof (int) , cudaMemcpyHostToDevice ) ;
	
	cudaMemcpy ( array2_d , array2_h , WIDTH*WIDTH*sizeof (int) , cudaMemcpyHostToDevice ) ;
	
	
	
	//allocating memory for resultent device array
	
	cudaMalloc((void **) &result_array_d , WIDTH*WIDTH*sizeof (int) ) ;
	
	cudaMalloc((void **) &M_result_array_d , WIDTH*WIDTH*sizeof (int) ) ;
	
	
	MatrixMulSh<<<512,32>>> ( array1_d , array2_d ,M_result_array_d , WIDTH) ;
	
	// all gpu function blocked till kernel is working
	//copy back result_array_d to result_array_h
	
	cudaMemcpy(M_result_array_h , M_result_array_d , WIDTH*WIDTH*sizeof(int) ,cudaMemcpyDeviceToHost) ;
	
    printf("Multiplication Successful using shared Memory");
	
	
}


