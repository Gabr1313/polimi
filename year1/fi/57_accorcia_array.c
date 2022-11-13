#include <stdio.h>
#define LEN_MAX 50
#define STOP 0

void accorcia(int [], int [], int, int *);

int main (int argc, char *argv[]){
    int val, vect[LEN_MAX], i, ris[LEN_MAX], dim, dim2;

    dim = 0;
    scanf("%d", &val);
    while (val > STOP && dim < LEN_MAX){
        vect[dim] = val;
        dim++;
        scanf("%d", &val);
    }

    accorcia(vect, ris, dim, &dim2);

    for (i = 0; i < dim2; i++)
        printf("%d ", ris[i]);
    printf("\n");
    return 0;
}

void accorcia (int array[], int ris[], int dim, int *dim2){
    int i, j, found;

    *dim2 = 0;
    for(i = 0; i < dim; i++){
        found = 0; 
        for(j = 0; j < *dim2 && !found; j++)
            if (array[i] == ris[j])
                found = 1;
        if (!found){
            ris[*dim2] = array[i];
            (*dim2)++;
        }
    }

}
            
