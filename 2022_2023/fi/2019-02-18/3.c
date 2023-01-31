#include <stdio.h>
#define NCOL 10

void findIndexSum(int mat[][NCOL], int rows, int cols, int val, int* iRis,
                  int* jRis) {
  int i, j, found, sum;

  found = 0;
  sum = 0;
  *iRis = -1;
  *jRis = -1;
  for (i = 0; i < rows && !found; i++)
    for (j = 0; j < cols && !found; j++) {
      sum += mat[i][j];
      if (sum > val) {
        *iRis = i;
        *jRis = j;
        found = 1;
      }
    }
}

int main(void) {
  int mat[NCOL][NCOL], val, i, j, iMax, jMax, iRis, jRis;

  scanf("%d", &val);
  scanf("%d%d", &iMax, &jMax);
  for (i = 0; i < iMax; i++)
    for (j = 0; j < jMax; j++) {
      scanf("%d", &mat[i][j]);
    }

  findIndexSum(mat, iMax, jMax, val, &iRis, &jRis);
  printf("%d %d\n", iRis, jRis);

  return 0;
}
