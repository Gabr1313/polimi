#include <stdio.h>
#include <stdlib.h>

float *cercaBassi(float[], int, int *);
void analizzaBassi(float[], int);

int main(int argc, char *argv[]) {
  float *arr, *bassi;
  int dim, i, dimBassi;

  do scanf("%d", &dim);
  while (dim < 1);

  arr = malloc(sizeof(float) * dim);
  if (arr) {
    for (i = 0; i < dim; i++) scanf("%f", &arr[i]);

    bassi = cercaBassi(arr, dim, &dimBassi);
    if (bassi) {
      analizzaBassi(bassi, dimBassi);
      free(bassi);
    }

    free(arr);
  } else
    printf("main: problema allocazione dinamica\n");

  return 0;
}

float *cercaBassi(float arr[], int dim, int *tot) {
  int i, j, count;
  float *ris;

  dim--;
  for (i = 1, count = 0; i < dim; i++)
    if (arr[i] < arr[i - 1] && arr[i] < arr[i + 1]) count++;
  *tot = count;

  ris = malloc(sizeof(float) * count);
  if (ris) {
    for (j = 0, i = 1; i < dim; i++)
      if (arr[i] < arr[i - 1] && arr[i] < arr[i + 1]) ris[j++] = arr[i];
  } else
    printf("cercaBassi: problema allocazione dinamica\n");

  return ris;
}

void analizzaBassi(float arr[], int dim) {
  int i;

  for (i = 0; i < dim; i++) printf("%g ", arr[i]);
  printf("\n");
}
