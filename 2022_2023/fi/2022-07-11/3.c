#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
1 -4 7 3 8 -4 5
-2 3 2 7 1 -5 -9
1 3 1 2 2 -4 -9
-2 3 3 -9 2 -1 -8
2 0 3 1 2 1 8
1 1 6 1 1 9 6
1 -5 3 2 4 0 6
3 7 3 1 1 1 2
-1 3 0 5 3 9 6
1 1 1 7 1 6 6
*/
#define RMAX 10
#define CMAX 10

int contaPozzi(int mat[RMAX][CMAX], int rows, int cols) {
  int i, j, ris, min, isValid, indexCol;
  ris = 0;
  for (i = 0; i < rows; i++) {
    min = mat[i][0];
    indexCol = 0;
    isValid = 1;
    for (j = 1; j < cols; j++) {
      if (mat[i][j] < min) {
        min = mat[i][j];
        indexCol = j;
        isValid = 1;
      } else if (mat[i][j] == min) {
        isValid = 0;
      }
    }
    if (isValid) {
      for (j = 0; j < rows && isValid; j++) {
        if (mat[j][indexCol] < min || (mat[j][indexCol] == min && i != j)) {
          isValid = 0;
        }
      }
    }
    ris += isValid;
  }
  return ris;
}

int main(void) {
  int mat[RMAX][CMAX], i, j;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 7; j++) {
      scanf("%d", &mat[i][j]);
    }
  }
  printf("%d\n", contaPozzi(mat, 10, 7));
  return 0;
}
