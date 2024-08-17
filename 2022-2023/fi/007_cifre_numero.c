#include <stdio.h>
#define BASE 10

int main(int argc, char* argv[]) {
  int num, cifra, cifraMax, i;
  scanf("%d", &num);
  cifraMax = num % BASE;
  num = num / BASE;
  i = 1;
  while (num > 0) {
    cifra = num % BASE;
    num = num / BASE;
    if (cifra > cifraMax) {
      cifraMax = cifra;
    }
    i = i + 1;
  }
  printf("%d %d", i, cifraMax);

  return 0;
}
