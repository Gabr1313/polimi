#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *conta(char[], char[]);

int main(int argc, char *argv[]) {
  int *ris, i;

  if (argc == 3) {
    ris = conta(argv[1], argv[2]);
    for (i = 0; argv[2][i]; i++) printf("%c %d\n", argv[2][i], ris[i]);
    free(ris);
  } else
    printf("Usage: %s string string\n", argv[0]);

  return 0;
}

int *conta(char info[], char cars[]) {
  int *ris, i, j, found;

  ris = calloc(sizeof(int), strlen(cars));
  for (i = 0; info[i]; i++) {
    found = 0;
    for (j = 0; !found && cars[j]; j++)
      if (cars[j] == info[i]) {
        found = 1;
        ris[j]++;
      }
  }
  return ris;
}
