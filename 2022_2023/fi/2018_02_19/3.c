#include <stdio.h>
#include <stdlib.h>

#define LEN 25

int cmp(const void *, const void *);
int calcola_prod(int[], int);

int main(int argc, char *argv[]) {
  int v[LEN], i, ris;

  for (i = 0; i < LEN; i++) scanf("%d", &v[i]);

  ris = calcola_prod(v, LEN);

  printf("%d\n", ris);
  return 0;
}

int cmp(const void *a, const void *b) { return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b); }

int calcola_prod(int v[], int len) {
  int *copia, i, p1, p2;

  if ((copia = malloc(sizeof(int) * len))) {
    for (i = 0; i < len; i++) copia[i] = v[i];
    qsort(copia, len, sizeof(int), cmp);
    p1 = copia[len - 1] * copia[len - 2] * copia[len - 3];
    p2 = copia[0] * copia[1] * copia[len - 1];
    printf("%d %d\n", p1, p2);
    free (copia);
  } else {
    printf("Memory allocation problem\n");
    return -1;
  }

  return (p1 > p2 ? p1 : p2);
}
