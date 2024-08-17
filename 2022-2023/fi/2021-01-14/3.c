#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
  return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b);
}

int trovaQuartili(int arr[], int len, int *q1, int *q2, int *q3) {
  int *copia, index, ris;

  copia = malloc(sizeof(int) * len);
  if (copia) {
    ris = 0;
    memcpy(copia, arr, sizeof(int) * len);
    qsort(copia, len, sizeof(int), cmp);
    index = len / 4;
    *q1 = copia[index];
    index = len / 2;
    *q2 = copia[index];
    index = len * 3 / 4;
    *q3 = copia[index];
    free(copia);
  } else {
    printf("TrovaQuartili: problema allocazione dinamica\n");
    ris = 1;
  }
  return ris;
}

#define LEN 7

int main(void) {
  int i, arr[LEN], q1, q2, q3;

  for (i = 0; i < LEN; i++) {
    scanf("%d", &arr[i]);
  }
  trovaQuartili(arr, LEN, &q1, &q2, &q3);
  printf("%d %d %d\n", q1, q2, q3);

  return 0;
}
