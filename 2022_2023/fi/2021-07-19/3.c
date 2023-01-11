#include <stdio.h>

#define NC 10

#define QUOTA_CENTRALE 2
#define QUOTA_BORDI 1
#define RADIUS 1

void eruzione(int mappa[][NC], int rows, int cols, int iCh, int jCh) {
  int i, j, iMin, jMin, iMax, jMax;

  if (iCh >= 0 && iCh < rows && jCh >= 0 && jCh < cols) {
    mappa[iCh][jCh] += QUOTA_CENTRALE - QUOTA_BORDI;
    iMin = (iCh - RADIUS > 0 ? iCh - RADIUS : 0);
    jMin = (jCh - RADIUS > 0 ? jCh - RADIUS : 0);
    iMax = (iCh + RADIUS + 1 < rows ? iCh + RADIUS + 1: rows);
    jMax = (jCh + RADIUS + 1 < cols ? jCh + RADIUS + 1: cols);
    for (i = iMin; i < iMax; i++)
      for (j = jMin; j < jMax; j++) mappa[i][j] += QUOTA_BORDI;
  } else
    printf("eruzione: coordinate non valide\n");
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

  /* printf("\n");
  visualizzaMappa(mat, ROWS, COLS); */
  printf("\n");
  eruzione(mat, ROWS, COLS, ICH, JCH);
  visualizzaMappa(mat, ROWS, COLS);

  return 0;
}
