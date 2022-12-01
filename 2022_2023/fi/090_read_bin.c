#include <stdio.h>
#include <stdlib.h>

int pop_arr_file(FILE *, int **);

int main(int argc, char *argv[]) {
  FILE *in;
  int *v, ris;

  if (argc == 2) {
    if ((in = fopen(argv[1], "rb"))) {
      ris = pop_arr_file(in, &v);
      printf("%d\n", ris);
      free(v);
    } else
      printf("Error reading file %s\n", argv[1]);
  } else
    printf("Usage: %s file\n", argv[0]);

  return 0;
}

int pop_arr_file(FILE *in, int **p_v) {
  int tot, ris;
  ris = fread(&tot, sizeof(int), 1, in);
  if ((*p_v = malloc(tot * sizeof(int)))) {
    ris += fread(*p_v, sizeof(int), tot, in);
  } else
    printf("Memory allocation error\n");
  return ris;
}
