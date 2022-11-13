/*
Scrivere un programma che chiede all’utente di inserire un numero reale e conta e visualizza i) il numero complessivo di cifre decimali usate, e ii) per ogni cifra visualizza il numero di volte che essa compare nella parte
frazionaria.
Esempio: Ingresso: 1244.635329
Uscita: 6 cifre decimali
2 -> 1
3 -> 2
5 -> 1
6 -> 1
9 -> 1
 */
#include <stdio.h>
#define NCIFRE 10
#define INIZIO '0'
#define MAX_LEN 100
#define SEPARATORE '.'

int main (int argc, char *argv[]){
    /*
     * non capisco come sia possibile fare il programma con i problemi di approssimazione.... 
     * quindi io prendo il numero come fosse una stringa...
     */
    char num[MAX_LEN + 1];
    int cifreDecimali[NCIFRE], i, j, count;

    scanf("%s", num);

    for (i = 0; num[i] && num[i] != SEPARATORE; i ++)
        ;
    if (num[i]){
        for (j = 0; j < NCIFRE; j ++)
            cifreDecimali[j] = 0;

        count = 0;
        for (i ++; num[i]; i ++, count++)
            cifreDecimali[num[i] - INIZIO] ++;

        printf("%d cifre decimali\n", count);
        for (j = 0; j < NCIFRE; j++)
            if (cifreDecimali[j])
                printf("%d -> %d\n", j, cifreDecimali[j]);
    } 
    return 0;
}
