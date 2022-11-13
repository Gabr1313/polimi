/* # Esercizio 2 - appello 26/01/2022
Con formato si intende una stringa che contiene soltanto tre possibili caratteri: V,
che indica una vocale, C, che indica una consonante e D che indica una cifra.
Scrivere un sottoprogramma check che ricevute due stringhe, stin e form, restituisce 1
se il contenuto della stringa stin rispetta il formato form, 0 altrimenti. I caratteri
alfabetici della stringa stin sono esclusivamente minuscoli. Per esempio, se il
sottoprogramma riceve in ingresso:
stin: “check23”
formato: “CCVCCDD”
il sottoprogramma restituisce 1.
Può essere conveniente sviluppare ulteriori sottoprogrammi.

# Esercizio 2B - appello 26/01/2022
Scrivere un programma che acquisisce da riga di comando due stringhe e avvalendosi del
sottoprogramma check visualizza OK se la prima stringa rispetta il formato indicato
dalla seconda stringa, KO in caso contrario. */

#include <stdio.h>
#include <string.h>
#define VOC_ARR "aeiou"
#define S_C 'a'
#define E_C 'z'
#define S_N '0'
#define E_N '9'
#define NUM 'D'
#define VOC 'V'
#define CON 'C'
#define OK "OK"
#define KO "KO"

int check(char[], char[]);

int main(int argc, char* argv[]) {
    if (argc == 3) {
        if (check(argv[1], argv[2]))
            printf(OK);
        else
            printf(KO);
        printf("\n");
    } else
        printf("Not valid arguments");

    return 0;
}

int check(char stin[], char form[]) {
    int i, j, ris, c_form;
    char array_voc[] = VOC_ARR;

    ris = 1;
    for (i = 0; stin[i] && ris; ++i) {
        if (stin[i] >= S_N && stin[i] <= E_N)
            c_form = NUM;
        else if (stin[i] >= S_C && stin[i] <= E_C) {
            c_form = CON;
            for (j = 0; array_voc[j] && c_form != VOC; ++j)
                if (array_voc[j] == stin[i]) c_form = VOC;
        } else
            ris = 0;
        if (ris) ris = (form[i] == c_form);
    }

    return ris;
}
