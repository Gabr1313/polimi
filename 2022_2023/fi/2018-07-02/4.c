#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isBuffa(char[]);

int main(int argc, char* argv[]) {
  if (argc == 2)
    printf("%d\n", isBuffa(argv[1]));
  else
    printf("Usage: %s string\n", argv[0]);

  return 0;
}

int isBuffa(char s[]) {
  int i, ris, max, stop;

  max = strlen(s) - 1;

  stop = (max) / 2;
  ris = 1;
  for (i = 0; i < stop && ris; i++)
    if (abs(s[i] - s[i + 1]) != abs(s[max - i] - s[max - i - 1])) ris = 0;

  return ris;
}
