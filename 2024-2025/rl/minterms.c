#include <stdio.h>

typedef unsigned long u64;

#define N 5
#define A (i & v[N - 1])
#define B (i & v[N - 2])
#define C (i & v[N - 3])
// #define D (i & v[N - 4])
// #define E (i & v[N - 5])

// #define FORMULA ((!B && C) || (A && B) || (B && !C))
#define FORMULA ((!B && C) || (A && C) || (B && !C))

int main() {
    u64 v[N];
    for (u64 i = 0; i < N; i++) v[i] = (1 << i);
    for (u64 i = 0; i < (1 << N); i++)
        if (FORMULA) printf("%lu ", i);
    printf("\n");
    return 0;
}
