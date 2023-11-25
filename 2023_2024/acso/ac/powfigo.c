#include <stdio.h>

int powfigo(int b, int e) {
  int ans = 1;
  for (int i = 1; i <= e; i <<= 1) {
    if (e & i)
      ans *= b;
    b *= b;
  }
  return ans;
}

int main(void) {
  int b = 2, e = 5;
  int p = powfigo(b, e);
  printf("%d^%d = %d\n", b, e, p);
  return 0;
}
