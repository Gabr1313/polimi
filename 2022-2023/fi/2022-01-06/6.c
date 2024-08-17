#include <stdio.h>

#define N 10
#define M 10

int findSubRow(int m[][M], int rows, int cols, int v[], int len) {
  int c, i, j, r, k;

  cols -= len - 1;
  for (i = c = 0; i < rows; i++)
    for (j = 0; j < cols; j++) {
      r = 1;
      for (k = 0; r && k < len; k++) r = (m[i][j + k] == v[k]);
      c += r;
    }

  return c;
}

int main(void) {
  int mat[N][M], i, j, rows, cols, v[M], len;

  do scanf("%d%d", &rows, &cols);
  while (rows <= 0 || rows > N || cols <= 0 || cols > M);
  for (i = 0; i < rows; i++)
    for (j = 0; j < cols; j++) {
      scanf("%d", &mat[i][j]);
    }
  do scanf("%d", &len);
  while (len <= 0 || len > M);
  for (i = 0; i < len; i++) scanf("%d", &v[i]);

  printf("\n%d\n", findSubRow(mat, rows, cols, v, len));

  return 0;
}
