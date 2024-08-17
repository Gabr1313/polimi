#include <stdio.h>
#include <stdlib.h>

#define LEN (sizeof(char) * 8)

char* charToAscii(char c) {
  char* s;
  int i;

  s = malloc(LEN + 1);
  if (s) {
    s[LEN] = '\0';
    for (i = LEN - 1; i >= 0; i--) {
      s[i] = c % 2 + '0';
      c /= 2;
    }
  } else
    printf("charToAscii: problema allocazione dinamica\n");

  return s;
}

int main(int argc, char* argv[]) {
  char* s;
  int i;

  if (argc == 2) {
    for (i = 0; argv[1][i]; i++) {
      s = charToAscii(argv[1][i]);
      printf("%s", s);
      free(s);
    }
    printf("\n");
  } else
    printf("Uso: %s parola\n", argv[0]);

  return 0;
}
