#include <gmp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  mpz_t a, b, c, d;
  mpz_init_set_ui(a, 3);
  mpz_init_set_ui(b, 4);
  mpz_init(c);
  mpz_init(d);
  mpz_add(c, a, b);
  mpz_mul(d, a, b);
  gmp_printf("%Zd %Zd %Zd %Zd\n", a, b, c, d);

  return 0;
}
