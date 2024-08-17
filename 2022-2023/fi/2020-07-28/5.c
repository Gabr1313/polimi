#include <stdio.h>
#include <string.h>

#define LEN 100

int diff(FILE *f1, FILE *f2) {
  char c1[LEN], c2[LEN];
  int ris, n1, n2;

  ris = n1 = n2 = LEN;
  while (ris && n1 == LEN && n2 == LEN) {
    n1 = fread(c1, sizeof(char), LEN, f1);
    n2 = fread(c2, sizeof(char), LEN, f2);
    ris = !memcmp(c1, c2, LEN);
  }
  ris = !((n1 == n2) && !memcmp(c1, c2, n1));

  return ris;
}

int main(void) {
  char nomeFile1[LEN + 1], nomeFile2[LEN + 1];
  FILE *file1, *file2;

  scanf("%s", nomeFile1);
  file1 = fopen(nomeFile1, "r");
  if (file1) {
    scanf("%s", nomeFile2);
    file2 = fopen(nomeFile2, "r");
    if (file2) {
      printf("%d\n", diff(file1, file2));
      fclose(file2);
    }
    fclose(file1);
  }

  return 0;
}
