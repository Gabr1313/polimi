#include <stdio.h>
#define DIM 10

int main (int argc, char *argv[]){
    int vect[DIM], i, j, ris;

    for (i = 0; i < DIM; i++)
        scanf ("%d", &vect[i]);

    ris = 1;
    for (i = 0; i < DIM && ris; i++)
        for (j = i + 1; j < DIM && ris; j++)
            if (vect[i] == vect[j])
                ris = 0;

    printf ("%d\n", ris);
    return 0;
}

