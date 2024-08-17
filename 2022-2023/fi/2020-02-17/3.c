#include <stdio.h>

#define NR 5
#define NC 6
#define RAD 1

void mod(float image[][NC], float filtro[][NC], int rows, int cols) {
  float sum;
  int div, i, j, k, h, kS, hS, kE, hE;

  div = (RAD * 2 + 1) * (RAD * 2 + 1);
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++) {
      kS = (i - RAD > 0 ? i - RAD : 0);
      kE = (i + RAD + 1 < rows ? i + RAD + 1 : rows);
      hS = (j - RAD > 0 ? j - RAD : 0);
      hE = (j + RAD + 1 < cols ? j + RAD + 1 : cols);
      sum = 0;
      for (k = kS; k < kE; k++)
        for (h = hS; h < hE; h++) sum += image[k][h];
      filtro[i][j] = sum / div;
    }
}

int main(void) {
  int i, j;
  float image[NR][NC], filtro[NR][NC];

  for (i = 0; i < NR; i++)
    for (j = 0; j < NC; j++) scanf("%f", &image[i][j]);

  mod(image, filtro, NR, NC);

  printf("\n");
  for (i = 0; i < NR; i++) {
    for (j = 0; j < NC; j++) printf("%4.1f ", filtro[i][j]);
    printf("\n");
  }

  return 0;
}
