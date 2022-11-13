/* Scrivere un programma in C (ANSI 89) che acquisisce una sequenza di al più 100 valori
interi e un intero strettamente positivo k. L’acquisizione della sequenza termina
quando l’utente inserisce un numero negativo o nullo, oppure quando vengono acquisiti
100 valori. Il programma visualizza 1 se la sequenza contiene almeno una coppia di
valori tali che la loro somma sia k, 0 altrimenti, seguito da un ’a-capo’.
Per realizzare la soluzione si sviluppi un sottoprogramma cercasomma che ricevuto in
ingresso k, l’array contenente i dati e qualsiasi altro parametro ritenuto strettamente
necessario, restituisce 1 o 0 nel caso trovi i due valori la cui somma è k. */
#include <stdio.h>
#define MAX_LEN 100
#define STOP 0

int cerca_somma(int[], int, int);

int main(int argc, char* argv[]) {
    int val, ris, array[MAX_LEN], i, sum;

    scanf("%d", &val);
    while (val > 0 && i < MAX_LEN) {
        array[i] = val;
        i++;
        scanf("%d", &val);
    }

    scanf("%d", &sum);

    ris = cerca_somma(array, i, sum);

    printf("%d\n", ris);
    return 0;
}

int cerca_somma(int array[], int len, int sum) {
    int i, j;
    for (i = 0; i < len - 1; i++)
        for (j = i; j < len; j++)
            if (array[i] + array[j] == sum)
                return 1;
    return 0;
}
