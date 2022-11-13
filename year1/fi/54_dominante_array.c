/*
In un array bidimensionale di valori interi, si definisce dominante ogni elemento
dell’array che è strettamente maggiore di tutti gli elementi dell’array bidimensionale
che si trova in basso a destra rispetto all’elemento stesso (si veda la figura), non
considerando però tutti gli elementi presenti nell’ultima colonna e nell’ultima
riga. Si realizzi un sottoprogramma che ricevuto in ingresso un array bidimensionale
e qualsiasi altro parametro ritenuto strettamente necessario calcoli e restituisca
al chiamante il numero di elementi dominanti presenti. Nel contesto di utilizzo del
sottoprogramma, sono presenti le seguenti direttive/istruzioni riportate di seguito.

4
8
5 9 2 4 1 7 2 4
3 5 6 2 5 6 1 2
1 3 4 7 8 8 3 0
1 3 5 6 7 8 2 1
 */

#include <stdio.h>
#define NR 100
#define NC 100

int contaDominanti(int [][NC], int, int);

int main (int argc, char *argv[]){
    int mat[NR][NC], nR, nC, i, j, ris;

    do scanf("%d", &nR);
    while (nR <= 1 && nR > NR);
    do scanf("%d", &nC);
    while (nC <= 1 && nC > NC);
    for (i = 0; i < nR; i++)
        for (j = 0; j < nC; j++)
            scanf("%d", &mat[i][j]);

    ris = contaDominanti(mat, nR, nC);

    printf("%d\n", ris);
    return 0;
}
    
int contaDominanti(int mat[][NC], int nR, int nC){
    int i, j, jPrec, arrC[NC], nC1, nC2, nR1, nR2, count, prec;

    nC1 = nC - 1;
    nR1 = nR - 1;
    jPrec = nC;
    arrC[nC1] = mat[nR1][nC1];
    for (j = nC1; j >= 0; j--){
        arrC[j] = mat[nR1][j];
        if (arrC[j] < arrC[jPrec])
            arrC[j] = arrC[jPrec];
        jPrec = j;
    }

    count = 0;
    nR2 = nR - 2;
    nC2 = nC - 2;
    for (i = nR2; i >= 1; i--){
        prec = arrC[nC1];
        if (arrC[nC1] < mat[i][nC1])
            arrC[nC1] = mat[i][nC1];
        jPrec = nC1;
        for (j = nC2; j >= 0; j--){
            if (mat[i][j] > prec)
                count++;
            
            prec = arrC[j];
            if (arrC[j] < mat[i][j])
                arrC[j] = mat[i][j];
            if (arrC[j] < arrC[jPrec])
                arrC[j] = arrC[jPrec];
            jPrec = j;
        }
    }
    
    jPrec = nC1;
    for (j = nC2; j>= 0; j--){
        if (mat[i][j] > arrC[jPrec])
            count++;
        jPrec = j;
    }

    return count;
}





    


        

