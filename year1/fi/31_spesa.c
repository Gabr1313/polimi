#include <stdio.h>
#define MAX 50

int main (int argc, char *argv[]){
    float vect[MAX], spesa, item, temp;
    int i, j, dim, nProd;

    scanf ("%f", &item);
    dim = 0;
    while (dim < MAX && item > 0){
        vect[dim] = item;
        dim++;
        scanf ("%f", &item);
    }
    scanf ("%f", &spesa);

    for (i = 1; i < dim; i++)
        for (j = i ; j > 0; j--)
            if (vect[j - 1] > vect [j]){
                temp = vect[j];
                vect[j] = vect[j - 1];
                vect[j - 1] = temp;
            }

    for (i = 0; i < dim && spesa >= 0; i++)
        spesa -= vect[i];
    nProd = i - 1;

    printf ("%d\n", nProd);
    return 0;
}





