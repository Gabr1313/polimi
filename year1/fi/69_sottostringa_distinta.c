/* Scrivere un programma in C (ANSI 89) che acquisita una stringa di al più 30 caratteri,
individui la sottostringa più lunga in essa contenuta, senza caratteri ripetuti. Il
programma visualizza la lunghezza di tale sottostringa, seguita da un carattere a-capo.
Realizzare la propria soluzione organizzandola in sottoprogrammi, come ritenuto più
opportuno. */
#include <stdio.h>
#define LEN_MAX 30

int main(int argc, char *argv[]) {
    char str[LEN_MAX];
    int i, max, prova, i_max, i_prova;

    scanf("%s", str);

    max     = 1;
    prova   = 1;
    i_max   = 0;
    i_prova = 0;
    for (i = 1; str[i]; i++) {
        if (str[i] != str[i - 1]) {
            prova++;
            if (prova > max) {
                max   = prova;
                i_max = i_prova;
            }
        } else {
            prova   = 1;
            i_prova = i;
        }
    }

    for (i = i_max; i < max + i_max; i++) printf("%c", str[i]);
    printf("\n");

    return 0;
}
