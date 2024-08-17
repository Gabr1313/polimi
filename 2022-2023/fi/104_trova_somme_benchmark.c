/*
Scrivere un programma che dati 10 numeri interi inseriti dall’utente, ed
acquisito un ulteriore numero intero strettamente positivo, determini quali sono
le combinazioni dei 10 numeri che hanno come somma il numero inserito. Si
supponga che esistano numeri ripetuti tra i 10 inseriti. ESEMPIO: in: 0, 1, 2,
3, 4, 5, 6, 7, 8, 9
3
out: 4
poiché le combinazioni sono: [0, 1, 2], [0, 3], [1, 2], [3]

1 2 4 6 3 5 9 8 0 7 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LEN 20

int cmp(const void *, const void *);
int *ordina(int[], int);
int trova_somme(int[], int, int);

int main(int argc, char *argv[]) {
  int seq[LEN];
  int *seq_ordinata;
  int i, sum, ris;
  clock_t start, end;
  double cpu_time_used;

  for (i = 0; i < LEN; i++) scanf("%d", &seq[i]);
  do scanf("%d", &sum);
  while (sum <= 0);

  start = clock();
  if ((seq_ordinata = ordina(seq, LEN))) {
    ris = trova_somme(seq_ordinata, LEN, sum);
    free(seq_ordinata);
    printf("%d\n", ris);
  }
  end = clock();
  cpu_time_used = (double)(end - start) / CLOCKS_PER_SEC * 1000;
  printf("Time: %g\n", cpu_time_used);

  return 0;
}

int cmp(const void *a, const void *b) {
  return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b);
}

int *ordina(int seq[], int len) {
  int *seq_cpy;
  if ((seq_cpy = malloc(sizeof(int) * len))) {
    memcpy(seq_cpy, seq, sizeof(int) * len);
    qsort(seq_cpy, len, sizeof(int), cmp);
  } else
    printf("Memory allocation problem of %d int\n", len);
  return seq_cpy;
}

int trova_somme(int seq[], int len, int sum) {
  int ris, i;

  ris = 0;
  if (sum == 0) ris = 1;
  else {
    for (i = 0; i < len && seq[i] <= sum; i++)
      ris += trova_somme(&seq[i + 1], len - i - 1, sum - seq[i]);
    }

  return ris;
}
