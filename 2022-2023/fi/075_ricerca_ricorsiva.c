/*
Scrivere un sottoprogramma ricorsivo che riceve come parametri un array di interi
ordinati in ordine crescente (e la sua dimensione) ed un numero n. Il sottoprogramma
verifica se n è contenuto nell’array utilizzando il metodo della bisezione. In caso
affermativo restituisce 1 altrimenti 0. Scrivere un programma che chiede all’utente 10
valori interi, invoca il sottoprogramma definito e visualizza il risultato.
*/
#include <stdio.h>
#include <stdlib.h>
#define LEN 10

int cmp(const void *, const void *);
int isin(int[], int, int);

int main(int argc, char *argv[]) {
  int arr[LEN];
  int i, ris, num;

  for (i = 0; i < LEN; i++) {
    scanf("%d", &arr[i]);
  }
  qsort(arr, LEN, sizeof(int), cmp);
  scanf("%d", &num);

  ris = isin(arr, LEN, num);

  printf("%d\n", ris);
  return 0;
}

int cmp(const void *a, const void *b) { return (*(int *)a > *(int *)b) - (*(int *)a < *(int *)b); }

int isin(int arr[], int len, int num) {
  int ris, med;

  if (num == arr[0] || num == arr[len - 1])
    ris = 1;
  else {
    med = len / 2;
    if (med) {
      if (len % 2) {
        if (arr[med] == num)
          ris = 1;
        else if (num > arr[med])
          ris = isin(&arr[med + 1], med - 1, num);
        else
          ris = isin(&arr[1], med - 1, num);
      } else {
        if (num >= arr[med])
          ris = isin(&arr[med], med - 1, num);
        else
          ris = isin(&arr[1], med - 1, num);
      }
    } else
      ris = 0;
  }

  return ris;
}
