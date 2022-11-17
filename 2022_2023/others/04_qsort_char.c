#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *, const void  *);

int main(int argc, char *argv[]) {
    if (argc == 2) {
        qsort(argv[1], strlen(argv[1]), sizeof(char), cmp);
        printf("%s\n", argv[1]);
    } else {
        printf("Insert 2 args\n");
    }
    return 0;
}

int cmp(const void *a, const void *b) { return (*(char*)a > *(char*)b) - (*(char*)a < *(char*)b); }
