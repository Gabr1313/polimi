/*
Scrivere un sottoprogramma `minmaxstr` che riceve in ingresso una stringa e trasmette
al chiamante due caratteri, il minimo e il massimo nell’ordinamento alfabetico tra
quelli contenuti nella stringa. Per esempio, se la stringa in ingresso è “esempio”, il
minimo ed il massimo sono rispettivamente `e` ed `s`. La stringa contenga tutti e soli
caratteri alfabetici minuscoli.
Rivedere il sottoprogramma `minmaxstr` in modo tale che i caratteri possano essere sia
maiuscoli, sia minuscoli, e facendo in modo che il sottoprogramma trasmetta comunque
quelli minuscoli. In tal caso, se la stringa in ingresso è “Architetto”, il minimo ed
il massimo sono rispettivamente `a` ed `t`.
   */

#include <stdio.h>
#define LET_INI 'a'
#define LET_FIN 'z'
#define LET_INI_2 'A'
#define LET_FIN_2 'Z'
#define DIFF (LET_INI_2 - LET_INI)
#define LEN_MAX 100

void minMaxStr(char [], char *, char *);

int main (int argc, char *argv[]){
    char parola[LEN_MAX];
    char min, max;

    scanf("%s", parola);

    minMaxStr(parola, &min, &max);

    printf("%c %c\n", min, max);
    return 0;
}

void minMaxStr(char parola[], char *min, char *max){
    int i, lettMin, valida;

    /*
    non so cosa mettere nel caso non esista
    ma non penso sia da considerare nella soluzione questa casistica
     */
    *min = -1;
    *max = -1;

    valida = 0;
    for (i = 0; parola[i] != '\0' && !valida; i++){
        if (parola[i] >= LET_INI && parola[i] <= LET_FIN){
            *min = parola[i];
            *max = parola[i];
            valida = 1;
        }
        else if (parola[i] >= LET_INI_2 && parola[i] <= LET_FIN_2){
            *min = parola[i] - DIFF;
            *max = parola[i] - DIFF;
            valida = 1;
        }
    }
    for (; parola[i] != '\0'; i++){
        valida = 0;
        if (parola[i] >= LET_INI && parola[i] <= LET_FIN){
            lettMin = parola[i];
            valida = 1;
        }
        else if (parola[i] >= LET_INI_2 && parola[i] <= LET_FIN_2){
            lettMin = parola[i] - DIFF;
            valida = 1;
        }
        if (valida){
            if (lettMin < *min)
                *min = lettMin;
            else if (lettMin > *max)
                *max = lettMin;
        }
    }
}

