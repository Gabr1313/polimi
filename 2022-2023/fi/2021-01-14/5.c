#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WRONG -1

int cercacerniera(char[], char[]);
char *cerniera(char[], char[], int);

int main(int argc, char *argv[]) {
  int pos;
  char *ris;

  if (argc == 3) {
    pos = cercacerniera(argv[1], argv[2]);
    if (pos != WRONG) {
      ris = cerniera(argv[1], argv[2], pos);
      printf("%s\n", ris);
      free(ris);
    }
  } else
    printf("Usage: %s string1 string2\n", argv[0]);

  return 0;
}

int cercacerniera(char s1[], char s2[]) {
  int i, j;

  if (s2[0]) {
    j = 0;
    for (i = 1; s2[i + j - 1]; i++) {
      j = 0;
      while (s1[j] == s2[i + j] && s1[j]) j++;
    }
  }

  if (!j || !s2[0])
    i = WRONG;
  else
    i--;

  return i;
}

char *cerniera(char s1[], char s2[], int pos) {
  int delta, len3, len1;
  char *s3;

  delta = strlen(s2) - pos;
  len1 = strlen(s1) - delta;
  len3 = pos + len1;
  s3 = malloc(sizeof(char) * (len3 + 1));
  if (s3) {
    strncpy(s3, &s1[delta], len1);
    strncpy(&s3[len1], s2, pos);
    s3[len3] = '\0';
  } else
    printf("cerniera: Problema allcazione dinamica\n");

  return s3;
}
