#include <stdio.h>
#include <stdlib.h>

int read_file(FILE *, int **);

int main(int argc, char *argv[]) {
  FILE *in;
  int *v, len, i;

  if (argc == 2) {
    if ((in = fopen(argv[1], "rb"))) {
      len = read_file(in, &v);

      printf("%d\n", len);
      for (i = 0; i < len; i++)
        printf("%d ", v[i]);
      printf("\n");

      fclose(in);
      free(v);
    } else
      printf("Error reading file %s\n", argv[1]);
  } else
    printf("Usage: %s file\n", argv[0]);

  return 0;
}

int read_file(FILE *in, int **p_v) {
  int len;
  fread(&len, sizeof(int), 1, in);
  if ((*p_v = malloc(len * sizeof(int)))) {
    fread(*p_v, sizeof(int), len, in);
  } else
    printf("Memory allocation error\n");
  return len;
}
