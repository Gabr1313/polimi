#include <stdio.h>
#include <string.h>

int isPal(char[], int);

int main(int argc, char* argv[]) {
  if (argc == 2)
    printf("%d\n", isPal(argv[1], strlen(argv[1])));
  else
    printf("Usage: %s string\n", argv[0]);
  return 0;
}

int isPal(char s[], int len) {
  if (len < 2) return 1;
  if (s[0] == s[--len]) return isPal(&s[1], --len);
  return 0;
}
