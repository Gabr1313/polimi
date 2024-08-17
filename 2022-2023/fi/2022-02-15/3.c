/*
10 7
3 4
1 -4 7 3 8 -4 5
-2 3 3 7 1 -5 9
1 3 1 2 2 -4 -9
-2 3 3 3 2 -1 -8
2 0 3 1 2 1 8
1 1 6 1 1 9 6
1 -1 3 2 4 0 6
3 7 3 1 1 1 2
-1 3 0 5 3 9 6
1 1 1 7 1 6 6
*/
#include <stdio.h>

#define RMAX 20
#define CMAX 20

int countPosSubMatrix(int map[RMAX][CMAX], int rows, int cols, int dimh,
                      int dimv) {
  int i, j, k, h, check, count, rowEnd, colEnd, rowStartMax, colStartMax;

  rowStartMax = rows - dimh;
  colStartMax = cols - dimv;
  count = 0;
  for (i = 0; i <= rowStartMax; i++)
    for (j = 0; j <= colStartMax; j++) {
      rowEnd = i + dimh;
      colEnd = j + dimv;
      check = 1;
      for (k = i; k < rowEnd && check; k++)
        for (h = j; h < colEnd && check; h++) check = (map[k][h] > 0);
      count += check;
    }

  return count;
}

int main(void) {
  int row, col, i, j, mat[RMAX][CMAX], dimh, dimv;

  scanf("%d %d", &row, &col);
  scanf("%d %d", &dimh, &dimv);
  for (i = 0; i < row; i++)
    for (j = 0; j < col; j++) scanf("%d", &mat[i][j]);

  printf("%d\n", countPosSubMatrix(mat, row, col, dimh, dimv));

  return 0;
}
