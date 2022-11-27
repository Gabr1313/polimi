#include <stdio.h>

int main(int argc, char* argv[]) {
  int num, ris, base, potenza, sign;
  scanf("%d", &num);
  if (num < 0) {
    sign = -1;
    num = -num;
  } else
    sign = 1;
  base = 0;
  potenza = base;
  while (num > potenza) {
    base++;
    potenza = base * base * base;
  }
  if (potenza == num)
    ris = 1;
  else
    ris = 0;
  base *= sign;
  printf("%d\t%d\n", ris, base);
  return 0;
}
