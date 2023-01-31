#include <stdio.h>
#include <string.h>

#define LEN 80
#define SYM '*'

int mediaUn(char fileName[]) {
  FILE* file;
  char ns[LEN + 1];
  int i, cnt, sum, ris;

  file = fopen(fileName, "r");
  cnt = sum = 0;
  if (file) {
    while (fscanf(file, "%s", ns) == 1) {
      sum += strlen(ns);
      cnt++;
    }
    fclose(file);
  } else
    printf("file %s non apribile", fileName);

  ris = (cnt ? sum / cnt : 0);
  for (i = 0; i < ris; i++) printf("%c", SYM);
  printf("\n");

  return ris;
}

int main(int argc, char* argv[]) {
  if (argc == 2) mediaUn(argv[1]);
  return 0;
}
