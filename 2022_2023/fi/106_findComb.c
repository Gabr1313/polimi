#include <stdio.h>

#define UNK 'x'

int main(int argc, char* argv[]) {
  char* word;
  int i, n, m;

  if (argc == 2) {
    word = argv[1];
    for (i = 0, n = 1; word[i]; i++)
      if (word[i] == UNK) {
        n <<= 1;
      }

    for (n--; n >= 0; n--) {
      m = n;
      for (i = 0; word[i]; i++)
        if (word[i] == UNK) {
          printf("%d", m & 1);
          m >>= 1;
        } else
          printf("%c", word[i]);
      printf("\n");
    }
  } else
    printf("Usage: %s string\n", argv[0]);

  return 0;
}
