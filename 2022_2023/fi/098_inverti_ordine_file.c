#include <stdio.h>
#include <stdlib.h>

void inverti_file(FILE *, FILE *);

int main(int argc, char *argv[]) {
  FILE *in, *out;
  if (argc == 3) {
    if ((in = fopen(argv[1], "rb")) && (out = fopen(argv[2], "wb"))) {
      inverti_file(in, out);
      fclose(in);
      fclose(out);
    } else
      printf("Problem opening the file\n");

  } else
    printf("Usage: %s file_in file_out\n", argv[0]);

  return 0;
}

void inverti_file(FILE *in, FILE *out) {
  int tmp, len, i, j;
  int *v;
  fread(&len, sizeof(int), 1, in);
  if ((v = malloc(sizeof(int) * len))) {
    fread(v, sizeof(int), len, in);
    for (i = 0, j = len - 1; i < j; i++, j--) {
      tmp = v[i];
      v[i] = v[j];
      v[j] = tmp;
    }
    fwrite(&len, sizeof(int), 1, out);
    fwrite(v, sizeof(int), len, out);
    free(v);
  } else
    printf("inverti_file: problem with memory allocation\n");
}
