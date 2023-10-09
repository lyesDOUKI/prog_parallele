#include <stdio.h>

__global__ void add(int* vec, int threadsParBlock) {
	long index = blockIdx.x*threadsParBlock+threadIdx.x;
	vec[index] = vec[index] + 5;
}

int main(void) {
	int vectorSize = 256;
	int numberOfBlock = 32;
	int threadsParBlock = 8;

	int *vec_cpu = (int*)malloc(sizeof(int) * vectorSize);
	int *vec_gpu;

    cudaMalloc((int**)&vec_gpu, sizeof(int) * vectorSize);

	for(int i = 0; i < vectorSize; i++) vec_cpu[i] = 10;

    cudaMemcpy(vec_gpu, vec_cpu, sizeof(int) * vectorSize, cudaMemcpyHostToDevice);

	add<<<numberOfBlock,threadsParBlock>>>(vec_gpu, threadsParBlock);

    cudaMemcpy(vec_cpu, vec_gpu, sizeof(int) * vectorSize, cudaMemcpyDeviceToHost);

	for(int i = 0; i < vectorSize; i++) {
		printf("%d ", vec_cpu[i]);
	}
	printf("\n");


    return 0;
}