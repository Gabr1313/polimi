#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define DER_MAX 64 /* dopo il 26 va in OF */

typedef unsigned long int ul;
/* uso tutti ul per non avere problemi col compilatore: non puoi comparare ul a int */

void stampa_coeff(ul);
void inizializza(ul[], ul);
int deriva(ul[], ul);
void stampa_min_termini(ul, ul);
void copia(ul[], ul[], ul);
int min_com_mul(ul, ul);

int main(int argc, char *argv[]) {
  int try;
  ul depth;

  if (argc == 2) {
    try = atoi(argv[1]);
    if (try >= 0 && try <= DER_MAX) {
      depth = try;
      stampa_coeff(depth);
    } else
      printf("Not a valid argumet\n");
  } else
    printf("Specify only one argument\n");

  return 0;
}

void stampa_coeff(ul depth) {
  ul vett_coeff[DER_MAX + 2], der;
  /* vett_coeff = [a,b,c...] ovvero a + b*tg(x) + c*tg(x)^2 ... */

  vett_coeff[0] = 0;
  vett_coeff[1] = 1;

  /* printf("0\n"); */
  for (der = 1; der <= depth; ++der) {
    if (!deriva(vett_coeff, der + 2))         /* la derivata 1 ha bisogno di 3 spazi in memoria*/
      stampa_min_termini(vett_coeff[0], der); /* der mi serve per il fattoriale al denominatore */
    else
      return;
  }
}

int deriva(ul vett_coeff[], ul len) {
  ul i, vett_coeff_nuovi[DER_MAX + 2], coeff;

  inizializza(vett_coeff_nuovi, len);

  for (i = 1; i < len - 1; ++i) {
    /* check overflow */
    if (ULONG_MAX / i < vett_coeff[i]) {
      printf("OVERFLOW on %lu * %lu\n", vett_coeff[i], i);
      return 1;
    } else {
      /* la derivata di a*tg(x)^b = a*b*tg(x)^(b-1) + a*b*tg(x)^(b+1) */
      coeff = vett_coeff[i] * i;
      vett_coeff_nuovi[i - 1] += coeff;
      vett_coeff_nuovi[i + 1] += coeff;
    }
  }
  copia(vett_coeff, vett_coeff_nuovi, len);
  return 0;
}

void inizializza(ul vett[], ul len) {
  ul i;
  for (i = 0; i < len; ++i) vett[i] = 0;
}

void copia(ul v1[], ul v2[], ul len) {
  ul i;

  for (i = 0; i < len; i++) v1[i] = v2[i];
}

void stampa_min_termini(ul num, ul der) {
  ul den, i, mul;

  den = 1;
  for (i = der; i > 1; --i) {
    mul = min_com_mul(num, i);
    num /= mul;
    den *= (i / mul);
  }

  if (num) printf("%lu/%lu x^%lu\n", num, den, der);
  /* else
      printf("0 x^%lu\n", der); */
}

int min_com_mul(ul a, ul b) {
  ul resto;

  resto = a % b;
  while (resto != 0) {
    a = b;
    b = resto;
    resto = a % b;
  }

  return b;
}
