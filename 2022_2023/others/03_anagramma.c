#include <stdio.h>
#include <string.h>

#define BYTE 256

int anagramma(char[], char[]);

int main(int argc, char *argv[]) {
  int ris;

  if (argc == 3) {
    ris = anagramma(argv[1], argv[2]);
    printf("%d\n", ris);
  } else {
    printf("Wrong number of arguments\n");
  }

  return 0;
}

int anagramma(char a[], char b[]) {
  int map[BYTE], i, ris;

  memset(map, 0, sizeof(map));
  for (i = 0; a[i]; ++i) ++map[(int)a[i]];
  for (i = 0; b[i]; ++i) --map[(int)b[i]];
  for (i = 0, ris = 1; i < BYTE && ris; ++i) ris = !map[i];

  return ris;
}
