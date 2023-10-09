 #include <stdio.h>
  2 
  3 __global__ void add(int* vec,int * vec2, int * vec3,  int threadsParBlock) {
  4     long index = blockIdx.x*threadsParBlock+threadIdx.x;
  5     vec3[index] = vec[index] + vec2[index];
  6 }
  7 
  8 int main(void) {
  9     int vectorSize = 5;
 10     int numberOfBlock = 32;
 11     int threadsParBlock = 8;
 12  
 13     int *vec_cpu = (int*)malloc(sizeof(int) * vectorSize);
 14     int *vec_gpu;
 15 
 16     int *vec_cpu2 = (int*)malloc(sizeof(int) * vectorSize);
 17     int *vec_gpu2;
 18 
 19     int *vec_cpu3 = (int*)malloc(sizeof(int) * vectorSize);
 20     int *vec_gpu3;
 21 
 22     cudaMalloc((int**)&vec_gpu, sizeof(int) * vectorSize);
 23     cudaMalloc((int**)&vec_gpu2, sizeof(int) * vectorSize);
 24     cudaMalloc((int**)&vec_gpu3, sizeof(int) * vectorSize);
 25 
 26     for(int i = 0; i < vectorSize; i++) vec_cpu[i] = 3;
 27     for(int i = 0; i < vectorSize; i++) vec_cpu2[i] = 3;
 28     for(int i = 0; i < vectorSize; i++) vec_cpu3[i] = 0;
 29 
 30     cudaMemcpy(vec_gpu, vec_cpu, sizeof(int) * vectorSize, cudaMemcpyHostToDevice);
 31     cudaMemcpy(vec_gpu2, vec_cpu2, sizeof(int) * vectorSize, cudaMemcpyHostToDevice);
 32     cudaMemcpy(vec_gpu3, vec_cpu3, sizeof(int) * vectorSize, cudaMemcpyHostToDevice);
 33 
 34 
 35     add<<<numberOfBlock,threadsParBlock>>>(vec_gpu, vec_gpu2, vec_gpu3, threadsParBlock);
 36 
 37     cudaMemcpy(vec_cpu3, vec_gpu3, sizeof(int) * vectorSize, cudaMemcpyDeviceToHost);
 38 
 39     for(int i = 0; i < vectorSize; i++) {
 40         printf("%d ", vec_cpu3[i]);
 41     }
 42     printf("\n");
 43 
 44 
 45     return 0;
 46 }
~                                                                                                                                                                                                                                                            
~            