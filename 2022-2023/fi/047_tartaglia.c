#include <stdio.h>
#define MAX 10

int main(int argc, char *argv[]) {
  int depth, i, j, mat[MAX][MAX];

  do scanf("%d", &depth);
  while (depth <= 0 || depth > MAX);

  mat[0][0] = 1;
  for (i = 1; i < depth; i++) {
    mat[i][0] = 1;
    mat[i][i] = 1;
    for (j = 1; j < i; j++) mat[i][j] = mat[i - 1][j - 1] + mat[i - 1][j];
  }

  for (i = 0; i < depth; i++) {
    for (j = 0; j <= i; j++) printf("%d ", mat[i][j]);
    printf("\n");
  }

  return 0;
}
