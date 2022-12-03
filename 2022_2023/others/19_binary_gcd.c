#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long int u8;
typedef unsigned char u1;

u8 bin_gcd(u8, u8);

int main(int argc, char* argv[]) {
  char* useless;
  u8 ris;
  if (argc == 3) {
    ris = bin_gcd(strtoul(argv[1], &useless, 10), strtoul(argv[2], &useless, 10));
    printf("%lu\n", ris);
  } else
    printf("Usage: %s int int\n", argv[0]);
  return 0;
}

u8 bin_gcd(u8 a, u8 b) {
  u1 za = 0, zb = 0, zm;
  u8 t;

  if (!a) return b;
  if (!b) return a;
  while (!(a & 1)) {
    a >>= 1;
    za++;
  }
  while (!(b & 1)) {
    b >>= 1;
    zb++;
  }
  zm = (za < zb ? za : zb);

  while (1) {
    if (a < b) {
      t = a;
      a = b;
      b = t;
    }
    a -= b;
    if (a == 0)
      return b << zm;
    while (!(a & 1)) a >>= 1;
  }
}
