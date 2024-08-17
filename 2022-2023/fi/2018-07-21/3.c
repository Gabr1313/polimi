#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rot(char[], int);

int main(int argc, char *argv[]) {
  char *s;
  int n;

  if (argc == 3) {
    s = argv[1];
    n = atoi(argv[2]);
    rot(s, n);
    printf("%s\n", s);
  } else
    printf("Usage: %s string int\n", argv[0]);

  return 0;
}

void rot(char voc[], int n) {
  int i, len;
  char *tmp;

  len = strlen(voc);
  n %= len;

  if ((tmp = malloc(sizeof(char) * (n)))) {
    memcpy(tmp, voc + len - n, n);
    for (i = len - n - 1; i >= 0; i--) {
      voc[i + n] = voc[i];
    }
    memcpy(voc, tmp, n);
    free(tmp);
  } else
    printf("rot: Memory allocation problem\n");
}
