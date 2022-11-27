#include <stdio.h>
#define DIM 3

int main(int argc, char *argv[]) {
  char mat[DIM][DIM], sym1, sym2;
  int i, j, ris, ris1, ris2;

  for (i = 0; i < DIM; i++)
    for (j = 0; j < DIM; j++) scanf("%c", &mat[i][j]);

  for (i = 0; i < DIM; i++) {
    for (j = 0; j < DIM; j++) printf("%c ", mat[i][j]);
    printf("\n");
  }

  sym1 = mat[0][0];
  sym2 = mat[DIM - 1][0];
  ris1 = 1;
  ris2 = 1;
  ris = 1;
  for (i = 1; i < DIM && ris; i++) {
    if (ris1 && mat[i][i] != sym1) ris1 = 0;
    if (ris2 && mat[DIM - i - 1][i] != sym2) ris2 = 0;
    ris = ris1 || ris2;
  }

  if (!ris) {
    for (i = 0; i < DIM && !ris; i++) {
      sym1 = mat[i][0];
      sym2 = mat[0][i];
      ris1 = 1;
      ris2 = 1;
      ris = 1;
      for (j = 1; j < DIM && ris; j++) {
        if (ris1 && sym1 != mat[i][j]) ris1 = 0;
        if (ris2 && sym2 != mat[j][i]) ris2 = 0;
        ris = ris1 || ris2;
      }
    }
  }

  printf("%d\n", ris);
  return 0;
}
