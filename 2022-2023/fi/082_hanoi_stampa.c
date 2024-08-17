#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 3
#define AIR ' '
#define DISK '_'
#define STICK '|'

void stampa(int **, int, int, int);
void hanoi(int **, int, int, int, int, int, int, int);
void inizializza(int **, int, int);
void aggiorna(int **, int, int, int);

int main(int argc, char *argv[]) {
  int **mat;
  int i, depth, rows;
  if (argc == 2 && (depth = atoi(argv[1])) > 0) {
    rows = depth + 1;
    if ((mat = malloc(sizeof(int *) * rows))) {
      for (i = 0; i < rows && (mat[i] = malloc(sizeof(int) * COLUMNS)); i++)
        ;
      if (i == rows && mat[--i]) {
        inizializza(mat, rows, COLUMNS);
        stampa(mat, rows - 1, COLUMNS, depth);
        hanoi(mat, depth, 0, 2, 1, rows - 1, COLUMNS, depth);
        for (; i >= 0; i--) free(mat[i]);
      } else
        printf("Problem with malloc");
      free(mat);
    } else
      printf("Problem with malloc");

  } else
    printf("Usage: %s int\n", argv[0]);

  return 0;
}

void hanoi(int **mat, int depth, int start, int finish, int temp, int rows, int columns,
           int max_radius) {
  if (depth == 1) {
    printf("Move from %d to %d\n", start, finish);
    aggiorna(mat, start, finish, rows);
    stampa(mat, rows, columns, max_radius);

  } else {
    hanoi(mat, depth - 1, start, temp, finish, rows, columns, max_radius);

    printf("Move from %d to %d\n", start, finish);
    aggiorna(mat, start, finish, rows);
    stampa(mat, rows, columns, max_radius);

    hanoi(mat, depth - 1, temp, finish, start, rows, columns, max_radius);
  }
}

void inizializza(int **mat, int rows, int columns) {
  int i, j;

  j = 0;
  for (i = 0; i < rows - 1; i++) mat[i][j] = i + 1;
  mat[i][j] = 0;

  for (j++; j < columns; j++) {
    for (i = 0; i < rows - 1; i++) mat[i][j] = 0;
    mat[i][j] = i;
  }
}

void stampa(int **mat, int rows, int columns, int max_radius) {
  int i, j, n_air, n_disk, k;

  max_radius--;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < columns; j++) {
      if (mat[i][j])
        n_disk = mat[i][j] - 1;
      else
        n_disk = mat[i][j];
      n_air = max_radius - n_disk;
      for (k = 0; k < n_air; k++) printf("%c", AIR);
      for (k = 0; k < n_disk; k++) printf("%c", DISK);
      if (mat[i][j])
        printf("%c", DISK);
      else
        printf("%c", STICK);
      for (k = 0; k < n_disk; k++) printf("%c", DISK);
      for (k = 0; k < n_air; k++) printf("%c", AIR);
      printf("%c", AIR);
    }
    printf("\n");
  }
}

void aggiorna(int **mat, int start, int finish, int rows) {
  int pos_start, pos_finish;

  pos_start = mat[rows][start];
  pos_finish = --mat[rows][finish];
  mat[pos_finish][finish] = mat[pos_start][start];
  mat[pos_start][start] = 0;
  mat[rows][start]++;
}
