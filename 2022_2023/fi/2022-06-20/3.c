#include <stdio.h>

#define RMAX 10
#define CMAX 10

int contaPicchi (int mat[RMAX][CMAX], int rows, int cols){
  int i, j, jMax, i2, ris, piccoRiga, isValid;

  ris = 0;
  for (i = 0; i < rows; i++){
    piccoRiga = mat[i][0];
    jMax = 0;
    isValid = 1;
    for (j = 0; j < cols; j++){
      if (mat[i][j] > piccoRiga){
         jMax = j;
         isValid = 1;
         piccoRiga = mat[i][j];
      } else if (mat[i][j] == piccoRiga)
         isValid = 0;
    }
    if (isValid){
      for (i2 = 0; i2 < rows && isValid; i2++){
        if (mat[i2][jMax] > piccoRiga || (mat[i2][jMax] == piccoRiga && i2 != i))
          isValid = 0;
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
  printf("%d\n", contaPicchi(mat, 10, 7));
  return 0;
}
