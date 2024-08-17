#include <ctype.h>
#include <stdio.h>

int checkISBN10(char[]);

int main(int argc, char* argv[]) {
  int ris;
  if (argc == 2) {
    ris = checkISBN10(argv[1]);
    printf("%d\n", ris);
  } else
    printf("Usage: %s ISBNcode\n", argv[0]);

  return 0;
}

int checkISBN10(char s[]) {
  int i, check, tot, part;

  check = 1;
  tot = 0;
  part = 0;
  for (i = 0; s[i] && check; i++) {
    if (isdigit(s[i])) {
      part += s[i] - '0';
      tot += part;
    } else if (s[i] != '-')
      check = 0;
  }

  if (check) check = !(tot % 11);

  return check;
}
