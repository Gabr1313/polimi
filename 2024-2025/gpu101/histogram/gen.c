#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define ALPHABET_SIZE ('z' - 'a' + 1)

int rng_seed() {
    struct timespec seed;
    clock_gettime(0, &seed);
    return (int)(seed.tv_sec + seed.tv_nsec);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s file.txt n # (n is a positive inger)", argv[0]);
        exit(0);
    }
    long long len = atoll(argv[2]);
    if (len <= 0) {
        printf("Usage: %s file.txt n # (n is a positive inger)", argv[0]);
        exit(0);
    }
    FILE* f = fopen(argv[1], "w");
    assert(f);

    srand(rng_seed());
    for (long long i = 0; i < len; i++) {
        int r = rand() % (ALPHABET_SIZE + 2);
        char c;
        if (r >= ALPHABET_SIZE) {
            if (r == ALPHABET_SIZE) c = ' ';
            else c = '\n';
        } else c = r + 'a';
        putc(c, f);
    }
    fclose(f);
}
