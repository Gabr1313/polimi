#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define ALPHABET_SIZE ('z' - 'a' + 1)

#define CHECK(call)                                                                       \
    do {                                                                                  \
        const cudaError_t err = call;                                                     \
        if (err != cudaSuccess) {                                                         \
            printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__); \
            exit(1);                                                                      \
        }                                                                                 \
    } while (0)

#define CHECK_KERNELCALL()                                                                \
    do {                                                                                  \
        const cudaError_t err = cudaGetLastError();                                       \
        if (err != cudaSuccess) {                                                         \
            printf("%s in %s at line %d\n", cudaGetErrorString(err), __FILE__, __LINE__); \
            exit(1);                                                                      \
        }                                                                                 \
    } while (0)

inline long long get_time() {
    struct timespec r;
    clock_gettime(0, &r);
    return r.tv_sec * (long long)1e9 + r.tv_nsec;
}

__global__ void histogramKernelSlow(const char *__restrict__ data,
                                    unsigned int *__restrict__ histogram, const int length) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if (tid < length) {
        int pos = (data[tid] | 0x20) - 'a';
        if (pos >= 0 && pos < ALPHABET_SIZE) atomicAdd(&histogram[pos], 1);
    }
}

__global__ void histogramKernel(const char *__restrict__ data, unsigned int *__restrict__ histogram,
                                const int length) {
    int tid    = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    __shared__ unsigned int histogramLocal[ALPHABET_SIZE];

#pragma unroll
    for (int i = threadIdx.x; i < ALPHABET_SIZE; i += blockDim.x) histogramLocal[i] = 0;
    __syncthreads();

    for (int i = tid; i < length; i += stride) {
        int pos = (data[i] | 0x20) - 'a';
        if (pos >= 0 && pos < ALPHABET_SIZE) atomicAdd(&histogramLocal[pos], 1);
    }
    __syncthreads();

#pragma unroll
    for (int i = threadIdx.x; i < ALPHABET_SIZE; i += blockDim.x) {
        unsigned int val = histogramLocal[i];
        if (val) atomicAdd(&histogram[i], val);
    }
}

void histogramSequential(char *data, unsigned int *histogram, int length) {
    for (int i = 0; i < length; i++) {
        int pos = (data[i] | 0x20) - 'a';  // lower case
        if (pos >= 0 && pos < ALPHABET_SIZE) histogram[pos]++;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "read");
    if (fp == NULL) exit(1);
    fseek(fp, 0L, SEEK_END);
    int   sz   = ftell(fp);
    char *text = (char *)malloc(sizeof(char) * sz);
    rewind(fp);
    fread(text, sizeof(char), sz, fp);
    fclose(fp);

    struct cudaDeviceProp prop;
    CHECK(cudaGetDeviceProperties(&prop, 0));
    int blockDim = prop.maxThreadsPerMultiProcessor;
    int gridDim  = prop.multiProcessorCount;
    // int blockDim = 32 * 1;
    // int gridDim  = (prop.maxThreadsPerMultiProcessor * prop.multiProcessorCount - 1) / blockDim + 1;

    unsigned int histogramCPU[ALPHABET_SIZE] = {0};
    unsigned int histogramGPU[ALPHABET_SIZE];
    unsigned int histogramGPU2[ALPHABET_SIZE];
    long long    start, end, elapsedCPU, elapsedGPU, elapsedGPU2;
    {
        start = get_time();
        histogramSequential(text, histogramCPU, sz);
        end        = get_time();
        elapsedCPU = end - start;
    }
    {
        start = get_time();
        char         *textCUDA;
        unsigned int *histogramCUDA;
        CHECK(cudaMalloc(&textCUDA, sizeof(*textCUDA) * sz));
        CHECK(cudaMemcpy(textCUDA, text, sizeof(*textCUDA) * sz, cudaMemcpyHostToDevice));
        CHECK(cudaMalloc(&histogramCUDA, sizeof(*histogramCUDA) * ALPHABET_SIZE));
        CHECK(cudaMemset(histogramCUDA, 0, sizeof(*histogramCUDA) * ALPHABET_SIZE));
        dim3 blocksPerGrid((sz - 1) / blockDim + 1, 1, 1);
        dim3 threadsPerBlock(blockDim, 1, 1);

        histogramKernelSlow<<<blocksPerGrid, threadsPerBlock>>>(textCUDA, histogramCUDA, sz);
        CHECK_KERNELCALL();
        CHECK(cudaDeviceSynchronize());
        CHECK(cudaMemcpy(histogramGPU, histogramCUDA, ALPHABET_SIZE * sizeof(*histogramGPU),
                         cudaMemcpyDeviceToHost));
        cudaFree(textCUDA);
        cudaFree(histogramCUDA);
        end        = get_time();
        elapsedGPU = end - start;
    }
    {
        start = get_time();
        char         *textCUDA;
        unsigned int *histogramCUDA;
        CHECK(cudaMalloc(&textCUDA, sizeof(*textCUDA) * sz));
        CHECK(cudaMemcpy(textCUDA, text, sizeof(*textCUDA) * sz, cudaMemcpyHostToDevice));
        CHECK(cudaMalloc(&histogramCUDA, sizeof(*histogramCUDA) * ALPHABET_SIZE));
        CHECK(cudaMemset(histogramCUDA, 0, sizeof(*histogramCUDA) * ALPHABET_SIZE));
        dim3 blocksPerGrid(gridDim, 1, 1);
        dim3 threadsPerBlock(blockDim, 1, 1);
        histogramKernel<<<blocksPerGrid, threadsPerBlock>>>(textCUDA, histogramCUDA, sz);
        CHECK_KERNELCALL();
        CHECK(cudaDeviceSynchronize());
        CHECK(cudaMemcpy(histogramGPU2, histogramCUDA, ALPHABET_SIZE * sizeof(*histogramGPU),
                         cudaMemcpyDeviceToHost));
        cudaFree(textCUDA);
        cudaFree(histogramCUDA);
        end         = get_time();
        elapsedGPU2 = end - start;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (histogramCPU[i] != histogramGPU[i]) {
            printf("Result differs:\n");
            printf("CPU: ");
            for (int i = 0; i < ALPHABET_SIZE; i++) printf("%c:%d ", i + 'a', histogramCPU[i]);
            printf("\nGPU: ");
            for (int i = 0; i < ALPHABET_SIZE; i++) printf("%c:%d ", i + 'a', histogramGPU[i]);
            printf("\n");
            return 0;
        }
        if (histogramCPU[i] != histogramGPU2[i]) {
            printf("Result differs:\n");
            printf("CPU: ");
            for (int i = 0; i < ALPHABET_SIZE; i++) printf("%c:%d ", i + 'a', histogramCPU[i]);
            printf("\nGPU 2: ");
            for (int i = 0; i < ALPHABET_SIZE; i++) printf("%c:%d ", i + 'a', histogramGPU2[i]);
            printf("\n");
            return 0;
        }
    }

    printf("Time CPU     : %ld ns\n", elapsedCPU);
    printf("Time CUDA    : %ld ns\n", elapsedGPU);
    printf("Time CUDA2   : %ld ns\n", elapsedGPU2);
    printf("Ratio CPU/CUDA   : %.2f\n", (double)elapsedCPU / elapsedGPU);
    printf("Ratio CPU/CUDA2  : %.2f\n", (double)elapsedCPU / elapsedGPU2);

    free(text);

    return 0;
}
