#include <stdio.h>

#define NCOL 10

int indexColMaxDiff(int mat[][NCOL], int rowSize, int colSize) {
  int i, j, diff, max, min, jMax, diffMax;

  j = 0;
  min = mat[0][j];
  max = mat[0][j];
  for (i = 0; i < rowSize; i++) {
    if (mat[i][j] < min) {
      min = mat[i][j];
    } else if (mat[i][j] > max) {
      max = mat[i][j];
    }
  }
  diffMax = max - min;
  jMax = 0;
  printf("%d ", diffMax);

  for (j = 1; j < colSize; j++) {
    min = mat[0][j];
    max = mat[0][j];
    for (i = 0; i < rowSize; i++) {
      if (mat[i][j] < min) {
        min = mat[i][j];
      } else if (mat[i][j] > max) {
        max = mat[i][j];
      }
    }
    diff = max - min;
    if (diff > diffMax) {
      diffMax = diff;
      jMax = j;
    }
    printf("%d ", diffMax);
  }

  return jMax;
}

/* for testing */

void pop_mat_int(int v[][NCOL], int row, int col) {
  int i, j;
  for (i = 0; i < row; i++)
    for (j = 0; j < col; j++) scanf("%d", &v[i][j]);
}

void view_mat_int(int v[][NCOL], int row, int col) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) printf("%d ", v[i][j]);
    printf("\n");
  }
}

int main(void) {
  int mat[10][10];

  pop_mat_int(mat, 3, 3);
  view_mat_int(mat, 3, 3);

  printf("%d\n", indexColMaxDiff(mat, 3, 3));
  return 0;
}
