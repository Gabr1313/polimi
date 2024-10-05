#include <assert.h>
#include <stdio.h>

typedef unsigned long u64;

#define N 4
#define A (i & v[N - 1])
#define B (i & v[N - 2])
#define C (i & v[N - 3])
#define D (i & v[N - 4])
// #define E (i & v[N - 5])

#define FORMULA_1 (!(A || (A && !B) || (C && D)))
#define FORMULA_2 ((!A && !C) || (!A && !D))

#define FORMULA_3 (A && B && !C || B && C || !A && !B && C)
#define FORMULA_4 (A && B || !A && C)

int main() {
    u64 v[N];
    for (u64 i = 0; i < N; i++) v[i] = (1 << i);
    for (u64 i = 0; i < (1 << N); i++) assert(FORMULA_1 == FORMULA_2);
    for (u64 i = 0; i < (1 << N); i++) assert(FORMULA_3 == FORMULA_4);
    printf("\n");
    return 0;
}
