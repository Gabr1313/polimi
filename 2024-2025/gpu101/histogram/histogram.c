#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define ALPHABET_SIZE ('z' - 'a' + 1)

typedef long int ll;

ll get_time() {
    struct timespec r;
    clock_gettime(0, &r);
    return r.tv_sec * (ll)1e9 + r.tv_nsec;
}

void sequential_histogram(char *data, unsigned int *histogram, int length) {
    for (int i = 0; i < length; i++) {
        int pos = (data[i] | 0x20) - 'a';  // lower case
        if (pos >= 0 && pos < ALPHABET_SIZE) histogram[pos]++;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide a filename as an argument.\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "read");
    if (fp == NULL) exit(EXIT_FAILURE);

    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    rewind(fp);

    char        *text                     = (char *)malloc(sizeof(char) * sz);
    unsigned int histogram[ALPHABET_SIZE] = {0};

    fread(text, sizeof(char), sz, fp);
    fclose(fp);

    ll start = get_time();
    sequential_histogram(text, histogram, sz);
    ll end = get_time();

    printf("Time: %ld ns\n", end - start);
    for (int i = 0; i < ALPHABET_SIZE; i++) printf("%c:%d ", i + 'a', histogram[i]);
    printf("\n");

    free(text);

    return 0;
}
