#include <stdio.h>

void shift(char s[]) {
  char c;
  int i;

  c = s[0];
  for (i = 1; s[i]; i++) s[i - 1] = s[i];
  s[i - 1] = c;
}
