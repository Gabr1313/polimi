#include <stdio.h>

#define DIM 5
#define LIM_MIN 1
#define LIM_MAX 5

int check(int mat[DIM][DIM], int rows, int columns){
  int i, j, ris;

  ris = 1;
  for (i = 0; i < rows && ris; i++)
    for (j = 0; j < columns && ris; j++)
      if (mat[i][j] < LIM_MIN || mat[i][j] > LIM_MAX)
        ris = 0;

  return ris;
}
