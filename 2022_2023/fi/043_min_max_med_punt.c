#include <stdio.h>
#define LEN 10

void populatea(float[], int);
void minMaxMed(float[], int, int *, int *, float *);

int main(int argc, char *argv[]) {
  float array[LEN], med;
  int iMin, iMax;

  populatea(array, LEN);
  minMaxMed(array, LEN, &iMin, &iMax, &med);

  printf("%g %g %g\n", array[iMin], array[iMax], med);
  return 0;
}

void populatea(float array[], int dim) {
  int i;
  for (i = 0; i < dim; i++) scanf("%f", &array[i]);
}

void minMaxMed(float array[], int dim, int *iMin, int *iMax, float *med) {
  float sum;
  int i;

  *iMin = 0;
  *iMax = 0;
  sum = array[0];
  for (i = 1; i < dim; i++) {
    if (array[i] < array[*iMin])
      *iMin = i;
    else if (array[i] > array[*iMax])
      *iMax = i;
    sum += array[i];
  }
  *med = sum / dim;
}
