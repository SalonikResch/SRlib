#include <stdio.h>
#include <string>
using namespace std;


__host__ __device__ inline int setBit(unsigned int x, int n){
  return x | ((unsigned int)1 << n);
}

__host__ __device__ inline int clearBit(unsigned int x, int n){
  return x & ~((unsigned int)1 << n);
}


__host__ __device__ inline int bitAt(unsigned int x, int n){
  return (x >> n) & 1;
}

struct instruction {
  string op;
  int qubit1;
  int qubit2;
};

///////////////////////////////// H
__global__
void H(int N, int j, float *a, float *b)
{
  // Thread index
  unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
  // This thread's (amplitude's) bit value at index j
  unsigned int bitAtj = bitAt(tid, j);

  // Index where bit j is 0
  unsigned int bit0 = clearBit(tid, j);
  // Index where bit j is 1
  unsigned int bit1 = setBit(tid, j);

  // Load in zero values first
  float value0 = a[bit0];
  // Then load in one values
  float value1 = a[bit1];

  //if bitAtj is 0, add them, otherwise subtract them
  int sign = pow(-1, bitAtj);
  b[tid] = (value0 + sign*value1 ) / sqrt(2.0);
  // can't sync across blocks, so store to seperate "temp" memory
}

__global__
void H_2(int N, int j, float *a, float *b)
{
  // Thread index
  unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
  // Copy all values
  a[tid] = b[tid];
  // can't sync across blocks, so store to seperate "temp" memory
}

///////////////////////////////// CNOT
__global__
void CNOT_1(int N, int j, int k, float *a, float *b)
{
  // Thread index
  unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;

  int bitAtj = bitAt(tid, j); // control qubit
  int bitAtk = bitAt(tid, k); // target qubit

  if(bitAtj == 1){ // Only take action of control qubit is 1
    int other = tid; // Swap value with index from flipping target qubit
    if(bitAtk == 0){
      other = setBit(other, k);
    }else{
      other = clearBit(other, k);
    }

    float value = a[other];
    b[tid] = value; // store in temp array
  }
}

__global__
void CNOT_2(int N, int j, int k, float *a, float *b){
    // Thread index
  unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;

  int bitAtj = bitAt(tid, j);
  if(bitAtj == 1){
    a[tid] = b[tid]; // copy into amplitudes if something changed
  }
}

///////////////////////////////// CNOT
// Swap local qubit l with non-local qubit n
__global__
void d_swapQubits_1(int N, int l, int n, float *a, float *b){
  // Thread index
  unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
  // This thread's (amplitude's) bit value at index l
  unsigned int bitAtl = (tid >> l) & 1;
  // This thread's (amplitude's) bit value at index n
  unsigned int bitAtn = (tid >> n) & 1;

  // 2 cases where we swap
  if( (bitAtl == 0) && (bitAtn == 1) ){
    unsigned int other = tid;
    other = setBit(other, l);
    other = clearBit(other, n);
    float value = a[other];
    b[tid] = value;
  }else if( (bitAtl == 1) && (bitAtn == 0) ){
    unsigned int other = tid;
    other = clearBit(other, l);
    other = setBit(other, n);
    float value = a[other];
    b[tid] = value;
  }  
}

__global__
void d_swapQubits_2(int N, int l, int n, float *a, float *b){
  // Thread index
  unsigned int tid = blockIdx.x * blockDim.x + threadIdx.x;
  // This thread's (amplitude's) bit value at index l
  unsigned int bitAtl = (tid >> l) & 1;
  // This thread's (amplitude's) bit value at index n
  unsigned int bitAtn = (tid >> n) & 1;

  // 2 cases where we swap
  if( (bitAtl == 0) && (bitAtn == 1) ){
    a[tid] = a[tid];
  }else if( (bitAtl == 1) && (bitAtn == 0) ){
    a[tid] = b[tid];
  }  
}


bool outOfBounds(int M, instruction *ins){
  return (ins->qubit1 >= M) || (ins->qubit2 >= M);
}


// Fix: The swapping of pointers in this function has to be reflected in main
void swapQubits(int N, int M, int *sigma, instruction *ins,
                int dimGrid, int dimBlock, float *d_a, float *d_b){

  // The qubits that need to be mapped to local qubits
  int j = ins->qubit1;
  int k = ins->qubit2;

  // k could be -1 if there is no second qubit
  int sigK = -1;
  if(k >= 0){
    sigK = sigma[k]; // if not, we want to know where it's mapped
  }

  // Swap j if necessary
  if(sigma[j] >= M){ // Need to swap j, it's non-local
    for(int i=0;i<M;i++){
      // Find a local qubit which is not k
      if( (sigma[i] < M) && (sigma[i] != sigK)){
        d_swapQubits_1<<<dimGrid, dimBlock>>>(N, sigma[i], sigma[j], d_a, d_b);
        d_swapQubits_2<<<dimGrid, dimBlock>>>(N, sigma[i], sigma[j], d_a, d_b);

        // Swap mappings
        int t = sigma[j];
        sigma[j] = sigma[i];
        sigma[i] = t;

        break;
      } 
    }
  }

  // Swap k if necessary
  if((k >= 0) && (sigma[k] >= M)){ // Need to swap k, it's non-local
    for(int i=0;i<M;i++){
      // Find a local qubit which is not j
      if( (sigma[i] < M) && (sigma[i] != sigma[j])){
        d_swapQubits_1<<<dimGrid, dimBlock>>>(N, sigma[i], sigma[k], d_a, d_b);
        d_swapQubits_2<<<dimGrid, dimBlock>>>(N, sigma[i], sigma[k], d_a, d_b);

        // Swap mappings
        int t = sigma[k];
        sigma[k] = sigma[i];
        sigma[i] = t;

        break;
      } 
    }
  }
}


// Matrix multiplication test
int main(void)
{
  // Number of qubits
  int n = 8;
  // Number of amplitudes
  int N = pow(2, n);
  // Number of qubits per device
  int M = 8;

  int nOperations = 8;
  instruction instructions[8] = {
    {"H", 0, -1},
    {"CNOT", 0, 1},
    {"CNOT", 1, 2},
    {"CNOT", 2, 3},
    {"CNOT", 3, 4},
    {"CNOT", 4, 5},
    {"CNOT", 5, 6},
    {"CNOT", 6, 7}
  };

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
  float *a, *d_a, *d_b, *d_t, *g;

  // Allocate on host
  a = (float*)malloc(N*sizeof(float));  // amplitudes
  g = (float*)malloc(N*sizeof(float)); // a "golden" comparison

  // Allocate on device
  cudaMalloc(&d_a, N*sizeof(float));  // amplitudes, copy 1
  cudaMalloc(&d_b, N*sizeof(float));  // amplitudes, copy 2

  // Fill in values for inputs
  a[0] = 1.0f;
  for(int i=1;i<N;i++)
    a[i] = 0;

  // Copy inputs to device
  cudaEventRecord(GPUTransfer1Start, 0);
  cudaMemcpy(d_a, a, N*sizeof(float), cudaMemcpyHostToDevice);
  cudaEventRecord(GPUTransfer1Stop, 0);
  cudaEventSynchronize(GPUTransfer1Stop);
  cudaEventElapsedTime(&GPUtransferTime1, GPUTransfer1Start, GPUTransfer1Stop);

  // Virtual to physical mapping
  int *sigma = (int*)malloc(n*sizeof(int));
  for(int i=0;i<n;i++)
    sigma[i] = i;

  // Determine the gridsize
  int dimBlock = 1024;
  int dimGrid = (N + dimBlock - 1) / dimBlock; // # of blocks in x, round up

  // Simulate on device
  cudaEventRecord(GPUstart, 0);
  for(int i=0;i<nOperations;i++){
    //Check qubit locations, swap if necessary
    if(outOfBounds(M, &instructions[i])){
      swapQubits(N, M, sigma, &instructions[i], dimGrid, dimBlock, d_a, d_b);
    }

    // Do the operation
    if( instructions[i].op == "H"){
      int qubit1 = sigma[instructions[i].qubit1];
      H<<<dimGrid, dimBlock>>>(N, qubit1, d_a, d_b);
      cudaDeviceSynchronize();
      d_t = d_a; // swap pointers, b is the new a
      d_a = d_b; // because every amplitude was updated
      d_b = d_t;
    }
    if( instructions[i].op == "CNOT"){
      int qubit1 = sigma[instructions[i].qubit1];
      int qubit2 = sigma[instructions[i].qubit2];
      CNOT_1<<<dimGrid, dimBlock>>>(N, qubit1, qubit2, d_a, d_b);
      cudaDeviceSynchronize();
      CNOT_2<<<dimGrid, dimBlock>>>(N, qubit1, qubit2, d_a, d_b);
      cudaDeviceSynchronize();
    }  
  }
  
  
  cudaEventRecord(GPUstop, 0);
  cudaEventSynchronize(GPUstop);
  cudaEventElapsedTime(&GPUtime, GPUstart, GPUstop);

  // Check for any issues with kernel
  cudaError_t err = cudaGetLastError();
  if (err != cudaSuccess) 
      printf("Error: %s\n", cudaGetErrorString(err));
  

  // Copy results back
  cudaEventRecord(GPUTransfer2Start, 0);
  cudaMemcpy(a, d_a, N*sizeof(float), cudaMemcpyDeviceToHost);
  cudaEventRecord(GPUTransfer2Stop, 0);
  cudaEventSynchronize(GPUTransfer2Stop);
  cudaEventElapsedTime(&GPUtransferTime2, GPUTransfer2Start, GPUTransfer2Stop);

  // Compute the total error
  //float totalError = 0.0f;
  for (int i = 0; i < N; i++){
    printf("a[%d] = %.3f\n", i, a[i]);
    //totalError += abs(c[i]-g[i]);
    //printf("g=%f, c=%f\n", g[i], c[i]);
  }
  //printf("Total error: %f\n", totalError);

  cudaFree(d_a);
  cudaFree(d_b);
  free(a);
  free(g);

  printf("CPU: %.2f ms, GPU: %.2f ms （compute) + %.2f ms transfer\n", 
    CPUtime, GPUtime, GPUtransferTime1 + GPUtransferTime2);
}