#include <stdio.h>

#define SEP ' '

char* longestWord(char phrase[]) {
  int i, actualLen, maxLen;
  char *actual_p, *max_p;
  maxLen = 0;
  actualLen = 0;
  actual_p = phrase;
  max_p = phrase;
  for (i = 0; phrase[i]; i++) {
    if (phrase[i] == SEP) {
      actualLen = 0;
      actual_p = &phrase[i + 1];
    } else {
      actualLen++;
      if (actualLen > maxLen) {
        maxLen = actualLen;
        max_p = actual_p;
      }
    }
  }
  return max_p;
}

int main(int argc, char *argv[]) {
  char phrase[201];
  fgets(phrase, 201, stdin);
  printf("%s\n", longestWord(phrase));
  return 0;
}
