#include <stdio.h>

void shift(char s[]) {
  char c;
  int i;

  c = s[0];
  for (i = 1; s[i]; i++) s[i - 1] = s[i];
  s[i - 1] = c;
}

int main(int argc, char* argv[]) {
  char* s;
  if (argc == 2) {
    s = argv[1];
    shift(s);
    printf("%s\n", s);
  } else
    printf("Usage: %s string\n", argv[0]);

  return 0;
}
