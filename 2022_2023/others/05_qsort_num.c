#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *, const void *);
void view_arr(int[], int);

int main(int argc, char *argv[]) {
    int i, len;
    int *arr;

    len = argc - 1;
    if (len > 1) {

        if ((arr = malloc((len) * sizeof(int)))) {
            for (i = 0; i < len; i++) {
                arr[i] = atoi(argv[i + 1]);
            }
            qsort(arr, len, sizeof(int), cmp);
            view_arr(arr, len);
            free(arr);

        } else
            printf("Problem allocating %d int", len);

    } else
        printf("Usage: %s val1 val2 ...\n", argv[0]);

    return 0;
}

int cmp(const void *a, const void *b) { return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b); }

void view_arr(int array[], int len) {
    int i;

    printf("\n");
    for (i = 0; i < len; i++) printf("%d ", array[i]);
    printf("\n");
}
