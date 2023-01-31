#include <stdio.h>
#include <stdlib.h>

#define BASE 10

int contaCifreDiv(int n) {
  int d, t, cnt;

  t = (n > 0 ? n : -n);
  cnt = 0;
  while (t > 0) {
    d = t % BASE;
    if (d) cnt += !(n % d);
    t /= BASE;
  }

  return cnt;
}

int main(int argc, char* argv[]) {
  if (argc == 2) printf("%d\n", contaCifreDiv(atoi(argv[1])));
  return 0;
}
