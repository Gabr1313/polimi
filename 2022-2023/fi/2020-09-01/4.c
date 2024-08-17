#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LI 'a'
#define LF 'z'
#define LA (LF - LI + 1)

int isPangramma(char* s) {
  int map[LA], i, c;

  memset(map, 0, sizeof(int));
  for (i = c = 0; *(s + i) && c < LA; i++)
    if (isalpha(*(s + i)) && !map[tolower(*(s + i)) - LI]) {
      map[tolower(*(s + i)) - LI] = 1;
      c++;
    }

  return c == LA;
}

#define LEN 200

int main(void) {
  char s[LEN + 1];

  fgets(s, LEN + 1, stdin);
  printf("%d\n", isPangramma(s));

  return 0;
}
