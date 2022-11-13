#include <stdio.h>
#define DIM 10

void stampaMat1 (int [][DIM]);
/* da errore
void stampaMat2 (int **);
 */

int main (int argc, char **argv){
    int matrice[DIM][DIM];

    matrice[0][0] = 0;
    matrice[0][1] = 1;
    matrice[0][2] = 2;
    matrice[1][0] = 3;
    matrice[1][1] = 4;
    matrice[1][2] = 5;
    matrice[2][0] = 6;
    matrice[2][1] = 7;
    matrice[2][2] = 8;

    printf("%d\n", matrice[2][1]);
    printf("%d\n", *(*(matrice + 2) + 1));
    stampaMat1(matrice);

    return 0;
}

void stampaMat1 (int mat[][DIM]){
    printf("%d\n", mat[2][1]);
    printf("%d\n", *(*(mat+ 2) + 1));
}

/*
void stampaMat2 (int **mat){
    printf("%d\n", mat[2][1]);
    printf("%d\n", *(*(mat+ 2) + 1));
}
 */

