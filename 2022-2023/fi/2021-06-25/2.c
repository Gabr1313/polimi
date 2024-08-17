#include <stdio.h>

#define NC 10
#define NR 10

void trovaSegOrizz(int mat[][NC], int row, int col, int *cRis, int *iRis,
                   int *jRis) {
  int i, j, count, countMax, jProva, iMax, jMax;

  for (i = countMax = 0; i < row; i++)
    for (j = jProva = count = 0; j < col; j++)
      if (mat[i][j]) {
        count++;
        if (count > countMax) {
          countMax = count;
          iMax = i;
          jMax = jProva;
        }
      } else {
        count = 0;
        jProva = j + 1;
      }

  *cRis = countMax;
  *iRis = iMax;
  *jRis = jMax;
}

#define ROW 7
#define COL 8

int main (void) {
  int i, j, cRis, iRis, jRis;
  int mat[NR][NC];

  for (i = 0; i < ROW; i++)
    for (j = 0; j < COL; j++)
      scanf("%d", &mat[i][j]);

  for (i = 0; i < ROW; i++){
    for (j = 0; j < COL; j++)
      printf("%d", mat[i][j]);
    printf("\n");
  }

  trovaSegOrizz(mat, ROW, COL, &cRis, &iRis, &jRis);
  printf("%d %d %d\n", iRis, jRis, cRis);
  return 0;
}
