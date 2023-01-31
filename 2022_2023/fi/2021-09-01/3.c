#include <stdio.h>

#define NC 20
#define SURP 1
#define CONT 1
#define RAD 1

void erutta(int v[][NC], int rows, int cols, int iE, int jE) {
  int i, j, iMin, jMin, iMax, jMax;

  if (iE >= 0 && iE <= --rows && jE >= 0 && jE <= --cols) {
    iMin = iE - RAD;
    iMin = (iMin > 0 ? iMin : 0);
    iMax = iE + RAD;
    iMax = (iMax < rows ? iMax : rows);
    jMin = jE - RAD;
    jMin = (jMin > 0 ? jMin : 0);
    jMax = jE + RAD;
    jMax = (jMax < cols ? jMax : cols);
    v[iE][jE] += SURP;
    for (i = iMin; i <= iMax; i++)
      for (j = jMin; j <= jMax; j++) v[i][j] += CONT;
  }
}

void visualizzaMappa(int mappa[][NC], int rows, int cols) {
  int i, j;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) printf("%d ", mappa[i][j]);
    printf("\n");
  }
}

#define NR 10
#define ROWS 8
#define COLS 10
#define ICH 1
#define JCH 3

int main(void) {
  int i, j, mat[NR][NC];

  for (i = 0; i < ROWS; i++)
    for (j = 0; j < COLS; j++) scanf("%d", &mat[i][j]);

  printf("\n");
  erutta(mat, ROWS, COLS, ICH, JCH);
  visualizzaMappa(mat, ROWS, COLS);

  return 0;
}
