#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#define DER_MAX 1024

typedef unsigned long int ui;

void stampa_coeff(ui);
void inizializza(mpz_t[], ui);
void deriva(mpz_t[], mpz_t[], ui);
void stampa_min_termini(mpz_t, ui);
void copia(mpz_t[], mpz_t[], ui);
ui min_com_mul(mpz_t, ui);
void libera(mpz_t[], ui);

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
    ui der;
    /* vett_coeff = [a,b,c...] ovvero a + b*tg(x) + c*tg(x)^2 ... */
    mpz_t *vett_coeff, *vett_coeff_nuovi;

    /* la derivata 1 ha bisogno di 3 spazi in memoria*/
    if ((vett_coeff = malloc(sizeof(mpz_t) * (depth + 2))) &&
        (vett_coeff_nuovi = malloc(sizeof(mpz_t) * (depth + 2)))) {
        inizializza(vett_coeff, depth + 2);
        inizializza(vett_coeff_nuovi, depth + 2);
        mpz_set_ui(vett_coeff[1], 1);

        for (der = 1; der <= depth; ++der) {
            deriva(vett_coeff, vett_coeff_nuovi, der + 2);
            stampa_min_termini(vett_coeff[0], der);
        }
        libera(vett_coeff, depth + 2);
        libera(vett_coeff_nuovi, depth + 2);
        free(vett_coeff);
        free(vett_coeff_nuovi);
    } else
        printf("Problem with memory allocation of %lu * 2 mpz_t", depth + 2);
}

void inizializza(mpz_t vett[], ui len) {
    ui i;
    for (i = 0; i < len; ++i) mpz_init(vett[i]);
}

void libera(mpz_t vett[], ui len) {
    ui i;
    for (i = 0; i < len; ++i) mpz_clear(vett[i]);
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
    copia(vett_coeff, vett_coeff_nuovi, len);
    mpz_clear(coeff);
}

void copia(mpz_t v1[], mpz_t v2[], ui len) {
    ui i;

    for (i = 0; i < len; i++) mpz_swap(v1[i], v2[i]);
    /*     for (i = 0; i < len; i++) mpz_set(v1[i], v2[i]); */
}

void stampa_min_termini(mpz_t num, ui der) {
    ui i, mul;
    mpz_t den;

    mpz_init(den);
    mpz_set_ui(den, 1);

    for (i = der; i > 1; --i) {
        mul = min_com_mul(num, i);
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

ui min_com_mul(mpz_t a, ui b) {
    ui resto, c;
    mpz_t useless;
    mpz_init(useless);

    resto = mpz_mod_ui(useless, a, b);
    while (resto) {
        c = b;
        b = resto;
        resto = c % b;
    }

    mpz_clear(useless);

    return b;
}
