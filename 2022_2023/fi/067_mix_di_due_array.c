/* Scrivere un sottoprogramma mixarr in C (ANSI C) che, ricevuti come parametri tre array,
a1, a2 e a3, e qualsiasi altro parametro ritenuto strettamente necessario, salva in
a3 una copia dei valori contenuti in a1 ed a2 ordinandoli in ordine crescente e senza
ripetizioni e restituisce il numero di elementi effettivamente scritti in a3. Nella
realizzazione del sottoprogramma è necessario tener conto dei seguenti aspetti:
+ il sottoprogramma può modificare i dati contenuti negli array di partenza;
+ si assuma che a3 abbia abbastanza spazio per memorizzare la sequenza risultante.
Nello sviluppo della soluzione realizzare un sottoprogramma sortarr che ricevuti in
ingresso un array, un intero updown e qualsiasi altro parametro ritenuto strettamente
necessario, ordina il contenuto dell’array in senso crescente se updown vale 1,
in senso decrescente se vale -1. In caso updown contenga un valore diverso il
sottoprogramma non effettua alcuna modifica.
Sviluppare infine un programma che chiede all’utente i dati per popolare due array da
20 elementi, invoca il sottoprogramma sopra definito e visualizza il risultato (la
visualizzazione non viene fatta nel sottoprogramma mixarr). */
#include <stdio.h>

#define MAX_LEN 3

void sortarr(int[], int, int);
void input_array(int[], int);
void mix(int[], int[], int[], int, int *);
void view_arr(int[], int);

int main(int argc, char *argv[]) {
    int a[MAX_LEN], b[MAX_LEN], c[MAX_LEN * 2], len_c;

    input_array(a, MAX_LEN);
    input_array(b, MAX_LEN);
    mix(a, b, c, MAX_LEN, &len_c);

    view_arr(c, len_c);

    return 0;
}

void input_array(int array[], int len) {
    int i;
    for (i = 0; i < len; i++) scanf("%d", &array[i]);
}

void mix(int a[], int b[], int c[], int len, int *len_c) {
    int i, pos_a, pos_b;

    sortarr(a, len, 1);
    sortarr(b, len, 1);

    pos_a = 0;
    pos_b = 0;
    i     = 0;

    if (a[pos_a] < b[pos_b])
        c[i++] = a[pos_a++];
    else
        c[i++] = b[pos_b++];
    while (pos_a < len || pos_b < len) {
        while (pos_a < len && a[pos_a] == c[i - 1]) pos_a++;
        while (pos_b < len && b[pos_b] == c[i - 1]) pos_b++;
        if (pos_a < len && pos_b < len) {
            if (a[pos_a] < b[pos_b])
                c[i++] = a[pos_a++];
            else
                c[i++] = b[pos_b++];
        } else if (pos_a == len)
            c[i++] = b[pos_b++];
        else /* if pos_b == len */
            c[i++] = a[pos_a++];
    }

    *len_c = i;
}

void sortarr(int array[], int len, int updown) {
    int i, j, temp;

    if (updown == 1) {
        for (i = 1; i < len; i++)
            for (j = i - 1; j >= 0; j--)
                if (array[j] > array[j + 1]) {
                    temp         = array[j];
                    array[j]     = array[j + 1];
                    array[j + 1] = temp;
                }
    } else if (updown == -1) {
        for (i = 1; i < len; i++)
            for (j = i - 1; j >= 0; j--)
                if (array[j] < array[j + 1]) {
                    temp         = array[j];
                    array[j]     = array[j + 1];
                    array[j + 1] = temp;
                }
    }
}

void view_arr(int array[], int len) {
    int i;
    for (i = 0; i < len; i++) printf("%d ", array[i]);
    printf("\n");
}
