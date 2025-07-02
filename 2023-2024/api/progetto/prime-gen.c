#include <stdint.h>
#include <stdio.h>

// #define N 79
#define N 257

int is_prime(uint64_t n) {
    uint64_t p, i;
    p = (n < 4 ? n > 1 : n % 2 && n % 3);
    for (i = 5; p && i * i < n; i += 6) p = (n % i && n % (i + 2));
    return !!p;
}

int main(void) {
    uint64_t i;
    for (i = INT64_MAX / N - N; !is_prime(i); i--);
    printf("%lx\n", i);
    printf("%lu\n", i);
    return 0;
}
