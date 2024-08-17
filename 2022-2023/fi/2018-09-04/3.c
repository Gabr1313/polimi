#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rot(char[], int, int);

int main(int argc, char *argv[]) {
  char *s;

  if (argc == 4) {
    s = argv[1];
    rot(s, atoi(argv[2]), atoi(argv[3]));
    printf("%s\n", s);
  } else
    printf("Usage: %s string int int\n", argv[0]);
  return 0;
}

void rot(char s[], int shift, int dir) {
  char *piece;
  int len, inv_shift;

  len = strlen(s);
  inv_shift = len - shift;
  shift %= len;
  if (dir == 0) {
    if ((piece = malloc(sizeof(char) * shift))) {
      memcpy(piece, s + len - shift, shift);
      memmove(s + shift, s, inv_shift);
      memmove(s, piece, shift);
      free(piece);
    } else
      printf("rot: memory allocation problem\n");
  } else if (dir == 1) {
    if ((piece = malloc(sizeof(char) * shift))) {
      memcpy(piece, s, shift);
      memmove(s, s + shift, inv_shift);
      memmove(s + inv_shift, piece, shift);
      free(piece);
    } else
      printf("rot: memory allocation problem\n");
  }
}
