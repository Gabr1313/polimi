#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b) { return *(int *)a - *(int *)b; }

int binary_search(int *v, int len, int s) {
    int lb = 0;
    int ub = len - 1;
    while (lb < ub) {
        int mid = (lb + ub) / 2;
        mid = mid + (lb == mid);
        if (v[mid] < s) lb = mid + 1;
        else if (v[mid] > s) ub = mid - 1;
        else lb = mid;
    }
    return v[lb] == s ? lb : -1;
}

int main() {
    int n = 10;
    int *v = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 5;
    }
    qsort(v, n, sizeof(int), cmp);
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    printf("%d -> %d\n", v[3], binary_search(v, n, v[3]));
    free(v);
    return 0;
}
