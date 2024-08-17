#include <stdio.h>

#define NR 3
#define NC 3

void centra(int m[NR][NC], float c[NR][NC], int rows, int cols) {
  int i, j, s;
  float a;

  for (j = 0; j < cols; j++) {
    for (i = s = 0; i < rows; i++) s += m[i][j];
    a = (float)s / rows;
    for (i = 0; i < rows; i++) c[i][j] = (a + m[i][j]) / 2;
  }
}

int main(void) {
  int i, j, m[NR][NC];
  float c[NR][NC];

  for (i = 0; i < NR; i++)
    for (j = 0; j < NC; j++) scanf("%d", &m[i][j]);

  printf("finito\n");

  centra(m, c, NR, NC);

  printf("\n");
  for (i = 0; i < NR; i++) {
    for (j = 0; j < NC; j++) printf("%4.1f ", c[i][j]);
    printf("\n");
  }

  return 0;
}
