#include <stdio.h>
#include <stdlib.h>

#define NR 10
#define NC 10

int dominanti(int mat[][NC], int rows, int cols) {
  int app[NR][NC], i, j, maxCol, maxRow, count;

  maxRow = rows - 1;
  maxCol = cols - 1;
  app[maxRow][maxCol] = mat[maxRow][maxCol];
  for (i = maxRow - 1; i >= 0; i--)
    app[i][maxCol] = (mat[i][maxCol] > app[i + 1][maxCol] ? mat[i][maxCol]
                                                          : app[i + 1][maxCol]);
  for (j = maxCol - 1; j >= 0; j--)
    app[maxRow][j] = (mat[maxRow][j] > app[maxRow][j + 1] ? mat[maxRow][j]
                                                          : app[maxRow][j + 1]);
  count = 0;
  maxRow--;
  maxCol--;
  for (i = maxRow; i >= 0; i--)
    for (j = maxCol; j >= 0; j--) {
      if (mat[i][j] > app[i + 1][j + 1]) {
        count++;
      }
      app[i][j] =
          (app[i + 1][j] > app[i][j + 1] ? app[i + 1][j] : app[i][j + 1]);
      app[i][j] = (app[i][j] > mat[i][j] ? app[i][j] : mat[i][j]);
    }

  return count;
}

#define ROWS 4
#define COLS 8

int main(void) {
  int i, j, mat[NR][NC];

  for (i = 0; i < ROWS; i++)
    for (j = 0; j < COLS; j++) scanf("%d", &mat[i][j]);

  printf("%d\n", dominanti(mat, ROWS, COLS));

  return 0;
}
