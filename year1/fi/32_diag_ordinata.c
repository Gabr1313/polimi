#include <stdio.h>
#define DIM 4

int main (int argc, char *argv[]){
    int mat[DIM][DIM], i, j, ris;

    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            scanf ("%d", &mat[i][j]);

    ris = 1;
    for (i = 1; i < DIM && ris; i++)
        if (mat[i][i] <= mat [i-1][i-1])
            ris = 0;

    printf ("%d\n", ris);
    return 0;
}


