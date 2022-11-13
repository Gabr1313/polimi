#include <stdio.h>
#define MAX_LEN 100

void accumulate (float *, float *, int);

int main (int argc, char *argv[]){
    float vect[MAX_LEN], sumVect[MAX_LEN], num;
    int dim, i;

    scanf ("%f", &num);
    dim = 0;
    while (num >= 0 && dim < MAX_LEN){
       vect[dim] = num;
       scanf("%f", &num);
       dim++;
    }
    printf ("%d\n", dim);

    accumulate (vect, sumVect, dim);
    
    for (i = 0; i < dim; i++)
        printf("%g ", sumVect[i]);
    printf("\n");

    return 0;
}

void accumulate (float *array, float *arraySum, int dim){
    int i;
    arraySum[0] = array[0];
    for (i = 1; i < dim; i++)
        arraySum[i] = arraySum[i - 1] + array[i];
}
    
    
