#include <stdio.h>

int main(int argc, char* argv[]) {
  int a, b, c, ris, max;
  scanf("%d%d%d", &a, &b, &c);
  if (a > b) {
    if (a > c) {
      ris = a;
      max = 1;
    } else {
      ris = c;
      max = 3;
    }
  } else {
    if (b > c) {
      ris = b;
      max = 2;
    } else {
      ris = c;
      max = 3;
    }
  }
  printf("%d %d\n", ris, max);
  return 0;
}
