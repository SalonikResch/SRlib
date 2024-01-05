#include <stdio.h>
#define TILE_SIZE 32

__global__
void mm(int N, float *a, float *b, float *c)
{
  // rows are in x dimenion, cols in y dimension

  // Shared memory to store tiles for temporary reuse
  __shared__ float sA[TILE_SIZE][TILE_SIZE];
  __shared__ float sB[TILE_SIZE][TILE_SIZE];

  // The row and column of this thread (in output matrix c)
  int row = blockIdx.x*blockDim.x + threadIdx.x;
  int col = blockIdx.y*blockDim.y + threadIdx.y;

  // Each thread computes the sum for its index
  float s = 0;

  // Iterate over the number of tiles we need to bring in all relevant elements
  int T = (N + TILE_SIZE - 1) / TILE_SIZE; // number of tiles we need
  // The row of matrix A (does not change)
  int rowA = row; // same as row in c
  // The col of matrix B (does not change)
  int colB = col; // same as col in c

  for (int i=0; i<T; i++){
    // The colums of a will change as we takes tiles further right
    int colA = i*TILE_SIZE + threadIdx.y; 
    // The rows of b will change as we take tiles further down
    int rowB = i*TILE_SIZE + threadIdx.x;

    // Load tiles from matrices a and b
    if( (colA < N) && (rowB < N) ){ // only threads in tile size
      sA[threadIdx.x][threadIdx.y] = a[rowA*N+colA];
      sB[threadIdx.x][threadIdx.y] = b[rowB*N+colB];
    }else{ // Over the edge, fill with 0s
      sA[threadIdx.x][threadIdx.y] = 0;
      sB[threadIdx.x][threadIdx.y] = 0;
    }
    // Have to make sure all threads are synced
    __syncthreads(); // so we know data is ready as we use it

    // Do matrix-multiplication within tile
    for(int j=0;j<TILE_SIZE;j++)
      s += sA[threadIdx.x][j] * sB[i][threadIdx.y]; // dot-product the row and col
  }

  // Store final answers to global memory
  if( (row<N) && (col<N)){
    c[row*N+col] = s;
  }
}

__global__
void madd(int N, float *a, float *b, float *c)
{
  // The row and column of this thread (in output matrix c)
  int row = blockIdx.x*blockDim.x + threadIdx.x;
  int col = blockIdx.y*blockDim.y + threadIdx.y;

  // Store final answers to global memory
  if( (row<N) && (col<N))
    c[row*N+col] = a[row*N+col] + b[row*N+col];
}


// Matrix multiplication test
int main(void)
{
  // Size of the matrix
  int N = 256;
  // Timing variables
  float CPUtime, GPUtransferTime1, GPUtime, GPUtransferTime2;
  cudaEvent_t CPUstart, CPUstop, GPUTransfer1Start, GPUTransfer1Stop,
              GPUstart, GPUstop, GPUTransfer2Start, GPUTransfer2Stop;
  cudaEventCreate(&CPUstart);
  cudaEventCreate(&CPUstop);
  cudaEventCreate(&GPUTransfer1Start);
  cudaEventCreate(&GPUTransfer1Stop);
  cudaEventCreate(&GPUstart);
  cudaEventCreate(&GPUstop);
  cudaEventCreate(&GPUTransfer2Start);
  cudaEventCreate(&GPUTransfer2Stop);

  // Host and device variables for matrices
  float *a, *b, *c, *d_a, *d_b, *d_c, *g;

  // Allocate on host
  a = (float*)malloc(N*N*sizeof(float));
  b = (float*)malloc(N*N*sizeof(float));
  c = (float*)malloc(N*N*sizeof(float));
  g = (float*)malloc(N*N*sizeof(float));

  // Allocate on device
  cudaMalloc(&d_a, N*N*sizeof(float)); 
  cudaMalloc(&d_b, N*N*sizeof(float));
  cudaMalloc(&d_c, N*N*sizeof(float));

  // Fill in values for inputs
  for (int i=0; i<N; i++) {
    for(int j=0; j<N; j++){
      a[i*N+j] = 1.0f;
      b[i*N+j] = 2.0f;
      c[i*N+j] = 0.0f;
      g[i*N+j] = 0.0f;
    }
  }

  // Compute with CPU to check correctness and compare time
  
  cudaEventRecord(CPUstart, 0);
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      for(int k=0;k<N;k++){
        g[i*N+j] += a[i*N+k] * b[k*N+j];
      }
    }
  }
  cudaEventRecord(CPUstop, 0);
  cudaEventSynchronize(CPUstop);
  cudaEventElapsedTime(&CPUtime, CPUstart, CPUstop);

  // Copy inputs to device
  cudaEventRecord(GPUTransfer1Start, 0);
  cudaMemcpy(d_a, a, N*N*sizeof(float), cudaMemcpyHostToDevice);
  cudaMemcpy(d_b, b, N*N*sizeof(float), cudaMemcpyHostToDevice);
  cudaEventRecord(GPUTransfer1Stop, 0);
  cudaEventSynchronize(GPUTransfer1Stop);
  cudaEventElapsedTime(&GPUtransferTime1, GPUTransfer1Start, GPUTransfer1Stop);

  // Determine the gridsize
  dim3 dimBlock(TILE_SIZE, TILE_SIZE);
  dim3 dimGrid;
  dimGrid.x = (N + dimBlock.x - 1) / dimBlock.x; // # of blocks in x, round up
  dimGrid.y = (N + dimBlock.y - 1) / dimBlock.y; // # of blocks in y, round up
  dimGrid.z = 1;

  // Matrix multiply on device
  cudaEventRecord(GPUstart, 0);
  mm<<<dimGrid, dimBlock>>>(N, d_a, d_b, d_c);
  cudaDeviceSynchronize();
  cudaEventRecord(GPUstop, 0);
  cudaEventSynchronize(GPUstop);
  cudaEventElapsedTime(&GPUtime, GPUstart, GPUstop);

  // Check for any issues with kernel
  cudaError_t err = cudaGetLastError();
  if (err != cudaSuccess) 
      printf("Error: %s\n", cudaGetErrorString(err));
  

  // Copy results back
  cudaEventRecord(GPUTransfer2Start, 0);
  cudaMemcpy(c, d_c, N*N*sizeof(float), cudaMemcpyDeviceToHost);
  cudaEventRecord(GPUTransfer2Stop, 0);
  cudaEventSynchronize(GPUTransfer2Stop);
  cudaEventElapsedTime(&GPUtransferTime2, GPUTransfer2Start, GPUTransfer2Stop);

  // Compute the total error
  float totalError = 0.0f;
  for (int i = 0; i < N*N; i++){
    totalError += abs(c[i]-g[i]);
    //printf("g=%f, c=%f\n", g[i], c[i]);
  }
  printf("Total error: %f\n", totalError);

  cudaFree(d_a);
  cudaFree(d_b);
  cudaFree(d_c);
  free(a);
  free(b);
  free(c);
  free(g);

  printf("CPU: %.2f ms, GPU: %.2f ms （compute) + %.2f ms transfer\n", 
    CPUtime, GPUtime, GPUtransferTime1 + GPUtransferTime2);
}