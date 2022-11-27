/* use gcc -lgmp to compile */

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#define DER_MAX 1024

typedef unsigned long int ui;

void stampa_coeff(ui);
void deriva(mpz_t[], mpz_t[], ui);
void stampa_min_termini(mpz_t, ui);

int main(int argc, char *argv[]) {
  int prova;
  ui depth;

  if (argc == 2) {
    prova = atoi(argv[1]);
    if (prova >= 0 && prova <= DER_MAX) {
      depth = prova;
      stampa_coeff(depth);
    } else
      printf("Not a valid argumet\n");
  } else
    printf("Usage: %s num\n", argv[0]);

  return 0;
}

void stampa_coeff(ui depth) {
  ui der, i;
  /* vett_coeff = [a,b,c...] ovvero a + b*tg(x) + c*tg(x)^2 ... */
  mpz_t *vett_coeff, *vett_coeff_nuovi;

  /* la derivata 1 ha bisogno di 3 spazi in memoria... e cosi' via: per questo uso depth + 2*/
  if ((vett_coeff = malloc(sizeof(mpz_t) * (depth + 2))) &&
      (vett_coeff_nuovi = malloc(sizeof(mpz_t) * (depth + 2)))) {
    for (i = 0; i < depth + 2; ++i) mpz_init(vett_coeff[i]);
    for (i = 0; i < depth + 2; ++i) mpz_init(vett_coeff_nuovi[i]);
    mpz_set_ui(vett_coeff[1], 1);

    for (der = 1; der <= depth; ++der) {
      deriva(vett_coeff, vett_coeff_nuovi, der + 2);
      stampa_min_termini(vett_coeff[0], der);
    }

    for (i = 0; i < depth + 2; ++i) mpz_clear(vett_coeff[i]);
    for (i = 0; i < depth + 2; ++i) mpz_clear(vett_coeff_nuovi[i]);
    free(vett_coeff);
    free(vett_coeff_nuovi);
  } else
    printf("Problem with memory allocation");
}

void deriva(mpz_t vett_coeff[], mpz_t vett_coeff_nuovi[], ui len) {
  ui i;
  mpz_t coeff;

  mpz_init(coeff);

  for (i = 0; i < len; ++i) mpz_set_ui(vett_coeff_nuovi[i], 0);

  for (i = 1; i < len - 1; ++i) {
    /* la derivata di a*tg(x)^b = a*b*tg(x)^(b-1) + a*b*tg(x)^(b+1) */
    mpz_mul_ui(coeff, vett_coeff[i], i);
    mpz_add(vett_coeff_nuovi[i - 1], vett_coeff_nuovi[i - 1], coeff);
    mpz_add(vett_coeff_nuovi[i + 1], vett_coeff_nuovi[i + 1], coeff);
  }

  for (i = 0; i < len; i++) mpz_set(vett_coeff[i], vett_coeff_nuovi[i]);
  mpz_clear(coeff);
}

void stampa_min_termini(mpz_t num, ui der) {
  ui i, mul;
  mpz_t den;

  mpz_init(den);
  mpz_set_ui(den, 1);

  for (i = der; i > 1; --i) {
    mul = mpz_gcd_ui(NULL, num, i);
    mpz_cdiv_q_ui(num, num, mul);
    mpz_mul_ui(den, den, i / mul);
  }

  if (mpz_cmp_ui(num, 0)) {
    gmp_printf("%Zd/%Zd", num, den);
    printf(" x^%lu\n", der);
  }
  /* else
      printf("0 x^%lu\n", der); */
  mpz_clear(den);
}
