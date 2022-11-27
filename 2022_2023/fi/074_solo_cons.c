#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define VOC "aeiouAEIOU"

char* solo_cons(char*);
int isCons(char);

int main(int argc, char* argv[]) {
  char* sc;
  if (argc == 2) {
    sc = solo_cons(argv[1]);
    if (*sc) {
      printf("%s\n", sc);
      free(sc);
    }
  } else
    printf("Wrong number of arguments");
  return 0;
}

char* solo_cons(char* s) {
  int i, ncons, j;
  char* sc;
  for (i = 0, ncons = 0; *(s + i); ++i) ncons += isCons(*(s + i));
  if ((sc = malloc(ncons * sizeof(char)))) {
    j = 0;
    for (i = 0; *(s + i); ++i)
      if (isCons(*(s + i))) *(sc + j++) = *(s + i);
  } else
    printf("Problem with malloc of %d chars\n", ncons);
  return sc;
}

int isCons(char c) {
  int i, ris;

  ris = 0;
  if (isalpha(c)) {
    ris = 1;
    for (i = 0; VOC[i] && ris; ++i)
      if (c == VOC[i]) ris = 0;
  }

  return ris;
}
