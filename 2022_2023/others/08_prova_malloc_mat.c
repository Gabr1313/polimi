#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLUMNS 10

void programma(int **, int, int);

int main(int argc, char *argv[]) {
  int **mat;
  int i;

  if ((mat = malloc(sizeof(int *) * ROWS))) {
    for (i = 0; i < ROWS && (mat[i] = malloc(sizeof(int) * COLUMNS)); i++)
      ;
    if (mat[i]) {
      programma(mat, ROWS, COLUMNS);
    } else {
      for (i--; i >= 0; i++) free(mat[i]);
      free(mat);
    }
  } else
    printf("Problem with malloc");

  return 0;
}

void programma(int **mat, int rows, int columns) {
  int i, j;

  for (i = 0; i < rows; i++)
    for (j = 0; j < columns; j++) mat[i][j] = i + j;

  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns; j++) printf("%5d", mat[i][j]);
    printf("\n");
  }
}
