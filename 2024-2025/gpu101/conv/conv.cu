#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int32_t  i32;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float    f32;

// @todo decide when to call what funcion:
// - filter radius > 50          => run time error for saving input
// - filter radius in [2, 30]    => saving input is faster, otherwise slower
// - the most robust is the "no if" version -> a graph woulb be nice
// - saving filter is never faster (it is stays in cache by default)
// try iterate over filters (no I would not do this: in my mind it is useless)

u32 FILTER_RADIUS = 15;
u32 SIZE          = 500;
u32 LOOP_CPU      = 1;
u32 LOOP_GPU      = 100;

// better not to change
u32 BLOCK_DIM   = 8;  // becomes 64 because it is 2D
f32 EPS         = 0.00001;
u32 BLOCK_DIM_X = BLOCK_DIM;
u32 BLOCK_DIM_Y = BLOCK_DIM;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

u32 rng_seed() {
	struct timespec seed;
	clock_gettime(0, &seed);
	return (u32)(seed.tv_sec + seed.tv_nsec);
}

inline u64 get_time() {
	struct timespec r;
	clock_gettime(0, &r);
	return r.tv_sec * (u64)1e9 + r.tv_nsec;
}

void convolution_cpu(f32 *input, const f32 *filter, f32 *output, const u32 width, const u32 height,
                     const u32 filter_size, const u32 filter_radius) {
	assert(filter_size == filter_radius * 2 + 1);

	for (u32 outRow = 0; outRow < width; outRow++) {
		for (u32 outCol = 0; outCol < height; outCol++) {
			f32 value = 0.0f;
			for (u32 row = 0; row < filter_size; row++) {
				for (u32 col = 0; col < filter_size; col++) {
					i32 inRow = outRow - filter_radius + row;
					i32 inCol = outCol - filter_radius + col;
					if (inRow >= 0 && inRow < height && inCol >= 0 && inCol < width) {
						value += filter[col + row * filter_size] * input[inCol + inRow * width];
					}
				}
			}
			output[outCol + outRow * width] = value;
		}
	}

	/* for (u32 outRow = 0; outRow < width; outRow++) {
	    for (u32 outCol = 0; outCol < height; outCol++) {
	        f32 value     = 0.0f;
	        u32 row_start = MAX(0, (i32)(filter_radius - outRow));
	        u32 row_end   = MIN(filter_size, (i32)(height + filter_radius - outRow));
	        u32 col_start = MAX(0, (i32)(filter_radius - outCol));
	        u32 col_end   = MIN(filter_size, (i32)(width + filter_radius - outCol));
	        for (u32 row = row_start; row < row_end; row++) {
	            for (u32 col = col_start; col < col_end; col++) {
	                i32 inRow  = outRow - filter_radius + row;
	                i32 inCol  = outCol - filter_radius + col;
	                value     += filter[col + row * filter_size] * input[inCol + inRow * width];
	            }
	        }
	        output[outCol + outRow * width] = value;
	    }
	} */
}

__global__ void convolution_gpu_basic(f32 *input, const f32 *filter, f32 *output, const u32 width,
                                      const u32 height, const u32 filter_size,
                                      const u32 filter_radius) {
	const u32 outCol = blockIdx.x * blockDim.x + threadIdx.x;
	const u32 outRow = blockIdx.y * blockDim.y + threadIdx.y;
	if (outCol < width && outRow < height) {
		f32 value = 0.0f;
		for (u32 row = 0; row < filter_size; row++) {
			for (u32 col = 0; col < filter_size; col++) {
				i32 inRow = outRow - filter_radius + row;
				i32 inCol = outCol - filter_radius + col;
				if (inRow >= 0 && inRow < height && inCol >= 0 && inCol < width) {
					value += filter[col + row * filter_size] * input[inCol + inRow * width];
				}
			}
		}
		output[outRow * width + outCol] = value;
	}
}

__global__ void convolution_gpu_no_if(f32 *input, const f32 *filter, f32 *output, const u32 width,
                                      const u32 height, const u32 filter_size,
                                      const u32 filter_radius) {
	const u32 outCol = blockIdx.x * blockDim.x + threadIdx.x;
	const u32 outRow = blockIdx.y * blockDim.y + threadIdx.y;
	if (outCol < width && outRow < height) {
		f32 value     = 0.0f;
		u32 row_start = MAX(0, (i32)(filter_radius - outRow));
		u32 row_end   = MIN(filter_size, (i32)(height + filter_radius - outRow));
		u32 col_start = MAX(0, (i32)(filter_radius - outCol));
		u32 col_end   = MIN(filter_size, (i32)(width + filter_radius - outCol));
		for (u32 row = row_start; row < row_end; row++) {
			for (u32 col = col_start; col < col_end; col++) {
				i32 inRow  = outRow - filter_radius + row;
				i32 inCol  = outCol - filter_radius + col;
				value     += filter[col + row * filter_size] * input[inCol + inRow * width];
			}
		}
		output[outCol + outRow * width] = value;
	}
}

__global__ void convolution_gpu_shared_filter(f32 *input, const f32 *filter, f32 *output,
                                              const u32 width, const u32 height,
                                              const u32 filter_size, const u32 filter_radius) {
	const u32 outCol = blockIdx.x * blockDim.x + threadIdx.x;
	const u32 outRow = blockIdx.y * blockDim.y + threadIdx.y;

	extern __shared__ f32 local_filter[];
	for (u32 i = threadIdx.y; i < filter_size; i += blockDim.y) {
		for (u32 j = threadIdx.x; j < filter_size; j += blockDim.x) {
			local_filter[i * filter_size + j] = filter[i * filter_size + j];
		}
	}
	__syncthreads();

	if (outCol < width && outRow < height) {
		f32 value     = 0.0f;
		u32 row_start = MAX(0, (i32)(filter_radius - outRow));
		u32 row_end   = MIN(filter_size, (i32)(height + filter_radius - outRow));
		u32 col_start = MAX(0, (i32)(filter_radius - outCol));
		u32 col_end   = MIN(filter_size, (i32)(width + filter_radius - outCol));
		for (u32 row = row_start; row < row_end; row++) {
			for (u32 col = col_start; col < col_end; col++) {
				i32 inRow  = outRow - filter_radius + row;
				i32 inCol  = outCol - filter_radius + col;
				value     += local_filter[row * filter_size + col] * input[inRow * width + inCol];
			}
		}
		output[outCol + outRow * width] = value;
	}
}

__global__ void convolution_gpu_shared_input(f32 *input, const f32 *filter, f32 *output,
                                             const u32 width, const u32 height,
                                             const u32 filter_size, const u32 filter_radius) {
	const u32 outCol = blockIdx.x * blockDim.x + threadIdx.x;
	const u32 outRow = blockIdx.y * blockDim.y + threadIdx.y;

	extern __shared__ f32 local_input[];

	u32 local_input_x_size = blockDim.x + 2 * filter_radius;
	u32 local_input_y_size = blockDim.y + 2 * filter_radius;
	for (u32 i = threadIdx.x; i < local_input_x_size; i += blockDim.x) {
		for (u32 j = threadIdx.y; j < local_input_y_size; j += blockDim.y) {
			i32 inCol = blockIdx.x * blockDim.x + i - filter_radius;
			i32 inRow = blockIdx.y * blockDim.y + j - filter_radius;
			if (inCol >= 0 && inCol < width && inRow >= 0 && inRow < height) {
				local_input[i + j * local_input_x_size] = input[inCol + inRow * width];
			}
		}
	}
	__syncthreads();

	if (outCol < width && outRow < height) {
		f32 value     = 0.0f;
		u32 row_start = MAX(0, (i32)(filter_radius - outRow));
		u32 row_end   = MIN(filter_size, (i32)(height + filter_radius - outRow));
		u32 col_start = MAX(0, (i32)(filter_radius - outCol));
		u32 col_end   = MIN(filter_size, (i32)(width + filter_radius - outCol));
		for (u32 row = row_start; row < row_end; row++) {
			for (u32 col = col_start; col < col_end; col++) {
				i32 inCol  = threadIdx.x + col;
				i32 inRow  = threadIdx.y + row;
				value     += filter[col + row * filter_size] *
				         local_input[inCol + inRow * local_input_x_size];
			}
		}
		output[outCol + outRow * width] = value;
	}
}

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

#define CALL_CPU(func, elapsed, output, input, filter, width, height, filter_size, filter_radius) \
	do {                                                                                          \
		u64 start = get_time();                                                                   \
		for (int i = 0; i < LOOP_CPU; i++) {                                                      \
			func(input, filter, output, width, height, filter_size, filter_radius);               \
		}                                                                                         \
		u64 end = get_time();                                                                     \
		elapsed = (end - start) / LOOP_CPU;                                                       \
	} while (0)

#define CALL_KERNELL(func, shared_mem, elapsed, output, input, filter, width, height, filter_size, \
                     filter_radius)                                                                \
	do {                                                                                           \
		f32 *input_cuda, *output_cuda;                                                             \
		f32 *filter_cuda;                                                                          \
		CHECK(cudaMalloc(&input_cuda, sizeof(*input_cuda) * width * height));                      \
		CHECK(cudaMemcpy(input_cuda, input, sizeof(*input_cuda) * width * height,                  \
		                 cudaMemcpyHostToDevice));                                                 \
		CHECK(cudaMalloc(&filter_cuda, sizeof(*filter_cuda) * filter_size * filter_size));         \
		CHECK(cudaMemcpy(filter_cuda, filter, sizeof(*filter_cuda) * filter_size * filter_size,    \
		                 cudaMemcpyHostToDevice));                                                 \
		CHECK(cudaMalloc(&output_cuda, sizeof(*output_cuda) * width * height));                    \
                                                                                                   \
		u32  gridDimX = (width - 1) / BLOCK_DIM_X + 1;                                             \
		u32  gridDimY = (height - 1) / BLOCK_DIM_Y + 1;                                            \
		dim3 blocksPerGrid(gridDimX, gridDimY, 1);                                                 \
		dim3 threadsPerBlock(BLOCK_DIM_X, BLOCK_DIM_Y, 1);                                         \
                                                                                                   \
		u64 start = get_time();                                                                    \
		for (int i = 0; i < LOOP_GPU; i++) {                                                       \
			func<<<blocksPerGrid, threadsPerBlock, shared_mem>>>(                                  \
			    input_cuda, filter_cuda, output_cuda, width, height, filter_size, filter_radius);  \
			CHECK_KERNELCALL();                                                                    \
			CHECK(cudaDeviceSynchronize());                                                        \
		}                                                                                          \
		u64 end = get_time();                                                                      \
		elapsed = (end - start) / LOOP_GPU;                                                        \
                                                                                                   \
		CHECK(cudaMemcpy(output, output_cuda, sizeof(*output) * width * height,                    \
		                 cudaMemcpyDeviceToHost));                                                 \
                                                                                                   \
		CHECK(cudaFree(output_cuda));                                                              \
		CHECK(cudaFree(input_cuda));                                                               \
		CHECK(cudaFree(filter_cuda));                                                              \
	} while (0)

#define CHECK_EQUAL_RESULT(to_print, output_cpu, output_gpu, i, width, height, seed)             \
	do {                                                                                         \
		if (fabs(output_cpu[i] - output_gpu[i]) > EPS) {                                         \
			fprintf(stderr,                                                                      \
			        to_print                                                                     \
			        "Output differs (index = %u (%u %u), width = %u, height = %u, seed = %u)"    \
			        ": %f != %f\n",                                                              \
			        i, i / width, i % width, width, height, seed, output_cpu[i], output_gpu[i]); \
			exit(1);                                                                             \
		}                                                                                        \
	} while (0)

i32 main(i32 argc, char **argv) {
	// if (argc != 2) {
	// 	printf("Please specify matrix dimensions\n");
	// exit(1);
	// }
	// const u32 size   = atoi(argv[1]);
	const u32 width = SIZE, height = SIZE;
	const u32 filter_radius = FILTER_RADIUS;
	const u32 filter_size   = filter_radius * 2 + 1;

	f32 *input            = (f32 *)malloc(sizeof(*input) * width * height);
	f32 *filter           = (f32 *)malloc(sizeof(*filter) * filter_size * filter_size);
	f32 *output_cpu       = (f32 *)malloc(sizeof(*output_cpu) * width * height);
	f32 *output_gpu_basic = (f32 *)malloc(sizeof(*output_gpu_basic) * width * height);
	f32 *output_gpu_no_if = (f32 *)malloc(sizeof(*output_gpu_no_if) * width * height);
	f32 *output_gpu_shared_filter =
	    (f32 *)malloc(sizeof(*output_gpu_shared_filter) * width * height);
	f32 *output_gpu_shared_input = (f32 *)malloc(sizeof(*output_gpu_shared_input) * width * height);

	u32 seed = rng_seed();
	srand(seed);
	for (u32 i = 0; i < filter_size * filter_size; i++) filter[i] = (f32)rand() / RAND_MAX;
	for (u32 i = 0; i < width * height; i++) input[i] = (f32)rand() / RAND_MAX;

	u64 elapsed_cpu, elapsed_gpu_basic, elapsed_gpu_shared_filter, elapsed_gpu_no_if,
	    elapsed_gpu_shared_input;

	CALL_CPU(convolution_cpu, elapsed_cpu, output_cpu, input, filter, width, height, filter_size,
	         filter_radius);
	CALL_KERNELL(convolution_gpu_basic, 0, elapsed_gpu_basic, output_gpu_basic, input, filter,
	             width, height, filter_size, filter_radius);
	CALL_KERNELL(convolution_gpu_no_if, 0, elapsed_gpu_no_if, output_gpu_no_if, input, filter,
	             width, height, filter_size, filter_radius);
	CALL_KERNELL(convolution_gpu_shared_filter, sizeof(*filter_cuda) * filter_size * filter_size,
	             elapsed_gpu_shared_filter, output_gpu_shared_filter, input, filter, width, height,
	             filter_size, filter_radius);
	CALL_KERNELL(
	    convolution_gpu_shared_input,
	    sizeof(*input_cuda) * (BLOCK_DIM_X + 2 * filter_radius) * (BLOCK_DIM_Y + 2 * filter_radius),
	    elapsed_gpu_shared_input, output_gpu_shared_input, input, filter, width, height,
	    filter_size, filter_radius);

	for (u32 i = 0; i < width * height; i++) {
		CHECK_EQUAL_RESULT("Basic: ", output_cpu, output_gpu_basic, i, width, height, seed);
		CHECK_EQUAL_RESULT("No if: ", output_cpu, output_gpu_no_if, i, width, height, seed);
		CHECK_EQUAL_RESULT("Shared filter: ", output_cpu, output_gpu_shared_filter, i, width,
		                   height, seed);
		CHECK_EQUAL_RESULT("Shared input:", output_cpu, output_gpu_shared_input, i, width, height,
		                   seed);
	}

	printf("Time CPU               : %lu ns\n", elapsed_cpu);
	printf("Time CUDA basic        : %lu ns (ratio: %lu)\n", elapsed_gpu_basic,
	       elapsed_cpu / elapsed_gpu_basic);
	printf("Time CUDA no if        : %lu ns (ratio: %lu)\n", elapsed_gpu_no_if,
	       elapsed_cpu / elapsed_gpu_no_if);
	printf("Time CUDA shared filter: %lu ns (ratio: %lu)\n", elapsed_gpu_shared_filter,
	       elapsed_cpu / elapsed_gpu_shared_filter);
	printf("Time CUDA shared input : %lu ns (ratio: %lu)\n", elapsed_gpu_shared_input,
	       elapsed_cpu / elapsed_gpu_shared_input);

	free(input);
	free(filter);
	free(output_cpu);
	free(output_gpu_basic);
	free(output_gpu_no_if);
	free(output_gpu_shared_input);
	free(output_gpu_shared_filter);

	return 0;
}
