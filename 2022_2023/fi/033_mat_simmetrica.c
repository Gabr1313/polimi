#include <stdio.h>
#define DIM 3

int main(int argc, char *argv[]) {
  int mat[DIM][DIM], i, j, ris;

  for (i = 0; i < DIM; i++)
    for (j = 0; j < DIM; j++) scanf("%d", &mat[i][j]);

  ris = 1;
  for (i = 0; i < DIM; i++)
    for (j = 0; j < DIM; j++)
      if (mat[i][j] != mat[j][i]) ris = 0;

  printf("%d\n", ris);
  return 0;
}
