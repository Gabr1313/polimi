#include <bits/stdc++.h>

using namespace std;

typedef int32_t i32;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;

// @todo decide when to call what funcion:
// - filter radius > 50          => run time error for saving input
// - filter radius in [2, 30]    => saving input is faster, otherwise slower
// - the most robust is the "no if" version -> a graph woulb be nice
// - saving filter is never faster (it is stays in cache by default)
// try iterate over filters (no I would not do this: in my mind it is useless)

u32 FILTER_RADIUS = 15;
u32 SIZE = 500;
u32 LOOP_CPU = 1;
u32 LOOP_GPU = 100;

// better not to change
f32 EPS = 0.00001;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

u32 rng_seed() {
	struct timespec seed;
	clock_gettime(0, &seed);
	return (u32)(seed.tv_sec + seed.tv_nsec);
}

static inline u64 get_time() {
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

void fft(vector<complex<double>> &a) {
	i32 n = a.size(), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);  // (10% faster if double )
	static vector<complex<double>> rt(2, 1);
	for (static i32 k = 2; k < n; k *= 2) {
		R.resize(n);
		rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		for (i32 i = k; i < 2 * k; i++) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
	}
	vector<i32> rev(n);
	for (i32 i = 0; i < n; i++) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	for (i32 i = 0; i < n; i++)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (i32 k = 1; k < n; k *= 2)
		for (i32 i = 0; i < n; i += 2 * k)
			for (i32 j = 0; j < k; j++) {
				complex<double> z = rt[j + k] * a[i + j + k];  // (25% faster if hand−rolled)
				a[i + j + k] = a[i + j] - z;
				a[i + j] += z;
			}
}
vector<double> conv_fft(const vector<double> &a, const vector<double> &b) {
	if (a.empty() || b.empty()) return {};
	vector<double> res(a.size() + b.size() - 1);
	i32 L = 32 - __builtin_clz(res.size()), n = 1 << L;
	vector<complex<double>> in(n), out(n);
	copy(begin(a), end(a), begin(in));
	for (i32 i = 0; i < b.size(); i++) in[i].imag(b[i]);
	fft(in);
	for (complex<double> &x : in) x *= x;
	for (i32 i = 0; i < n; i++) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	for (i32 i = 0; i < res.size(); i++) res[i] = imag(out[i]) / (4 * n);
	return res;
}

void convolution_fft(f32 *input, const f32 *filter, f32 *output, const u32 width, const u32 height,
                     const u32 filter_size, const u32 filter_radius) {
	assert(filter_size == filter_radius * 2 + 1);
	for (u32 outRow = 0; outRow < width; outRow++) {
		for (u32 outCol = 0; outCol < height; outCol++) {
			f32 value = 0.0f;
			u32 row_start = MAX(0, (i32)(filter_radius - outRow));
			u32 row_end = MIN(filter_size, (i32)(height + filter_radius - outRow));
			u32 col_start = MAX(0, (i32)(filter_radius - outCol));
			u32 col_end = MIN(filter_size, (i32)(width + filter_radius - outCol));
			for (u32 row = row_start; row < row_end; row++) {
				for (u32 col = col_start; col < col_end; col++) {
					i32 inRow = outRow - filter_radius + row;
					i32 inCol = outCol - filter_radius + col;
					value += filter[col + row * filter_size] * input[inCol + inRow * width];
				}
			}
			output[outCol + outRow * width] = value;
		}
	}
}

#define CALL_CPU(func, elapsed, output, input, filter, width, height, filter_size, filter_radius) \
	do {                                                                                          \
		u64 start = get_time();                                                                   \
		for (i32 i = 0; i < LOOP_CPU; i++) {                                                      \
			func(input, filter, output, width, height, filter_size, filter_radius);               \
		}                                                                                         \
		u64 end = get_time();                                                                     \
		elapsed = (end - start) / LOOP_CPU;                                                       \
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
	const u32 filter_size = filter_radius * 2 + 1;

	f32 *input = (f32 *)malloc(sizeof(*input) * width * height);
	f32 *filter = (f32 *)malloc(sizeof(*filter) * filter_size * filter_size);
	f32 *output_cpu = (f32 *)malloc(sizeof(*output_cpu) * width * height);

	u32 seed = rng_seed();
	srand(seed);
	for (u32 i = 0; i < filter_size * filter_size; i++) filter[i] = (f32)rand() / RAND_MAX;
	for (u32 i = 0; i < width * height; i++) input[i] = (f32)rand() / RAND_MAX;

	u64 elapsed_cpu;

	CALL_CPU(convolution_cpu, elapsed_cpu, output_cpu, input, filter, width, height, filter_size,
	         filter_radius);

	for (u32 i = 0; i < width * height; i++) {
		CHECK_EQUAL_RESULT("Self: ", output_cpu, output_cpu, i, width, height, seed);
	}

	printf("Time CPU               : %lu ns\n", elapsed_cpu);

	free(input);
	free(filter);
	free(output_cpu);

	return 0;
}
