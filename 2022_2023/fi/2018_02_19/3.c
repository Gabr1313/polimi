#include <stdio.h>
#include <stdlib.h>

#define LEN 25

int calcola_prod(int[], int);

int main(int argc, char *argv[]) {
  int v[LEN], i, ris;

  for (i = 0; i < LEN; i++) scanf("%d", &v[i]);

  ris = calcola_prod(v, LEN);

  printf("%d\n", ris);
  return 0;
}

int calcola_prod(int v[], int len) {
  int p1, p2, max1, max2, max3, min1, min2, i;

  max1 = v[0];
  if (v[1] > max1) {
    max2 = max1;
    max1 = v[1];
  } else
    max2 = v[1];
  if (v[2] > max1) {
    max3 = max2;
    max2 = max1;
    max1 = v[2];
  } else if (v[2] > max2) {
    max3 = max2;
    max2 = v[2];
  } else
    max3 = v[2];
  min1 = max3;
  min2 = max2;

  for (i = 3; i < len; i++) {
    if (v[i] > max1) {
      max3 = max2;
      max2 = max1;
      max1 = v[i];
    } else if (v[i] > max2) {
      max3 = max2;
      max2 = v[i];
    } else if (v[i] > max3)
      max3 = v[i];
    if (v[i] < min1) {
      min2 = min1;
      min1 = v[i];
    } else if (v[i] < min2)
      min2 = v[i];
  }

  p1 = max1 * max2 * max3;
  p2 = max1 * min1 * min2;

  return (p1 > p2 ? p1 : p2);
}
