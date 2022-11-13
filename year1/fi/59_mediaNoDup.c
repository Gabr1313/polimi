/*
Si scriva un sottoprogramma medianodup che riceve in ingresso un array monodimensionale di valori interi e qualsiasi altro parametro ritenuto
strettamente necessario e restituisce la media dei valori presenti non considerando eventuali valori duplicati. Per esempio, se i valori contenuti sono
2 4 4 3 la media viene calcolata sui valori 2 4 3.
 */
#include <stdio.h>
#define MAX_LEN 100

float mediaNoDup (int [], int);

int main (int argc, char *argv[]){
    int i, dim, vect[MAX_LEN];
    float ris;
    
    do scanf("%d", &dim);
    while (dim <= 0 || dim > MAX_LEN);

    for (i = 0; i < dim; i++)
        scanf("%d", &vect[i]);

    ris = mediaNoDup(vect, dim);

    printf("%g\n", ris);
    return 0;
}

float mediaNoDup (int vect[], int dim){
    int i, j, found, sum, count;

    count = 0;
    for (i = 0; i < dim; i++){
        found = 0;
        for (j = 0; j < i && !found; j++)
            if (vect[j] == vect[i])
                found = 1;
        if (!found){
            sum += vect[i];
            count ++;
        }
    }
    
    return sum/count;
}

