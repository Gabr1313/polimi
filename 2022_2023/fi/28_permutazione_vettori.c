#include <stdio.h>
#define LEN_MAX 128

int main (int argc, char *argv[]){
    int vect1[LEN_MAX], vect2[LEN_MAX], i, j,
        len, found, ris;

    do scanf ("%d", &len);
    while (len < 0 || len > LEN_MAX);
    for (i = 0; i < len; i++)
        scanf ("%d", &vect1[i]);
    for (i = 0; i < len; i++)
        scanf ("%d", &vect2[i]);

    for (i = 0; i < len; i++){
        found = 0;
        for (j = 0; j < len && !found; j++)
            if (vect1[i] == vect2[j]){
                vect2[j] = 0;
                found = 1;
            }
    }
    
    ris = 1;
    for (j = 0; j < len && ris; j++)
        if (vect2[j] != 0)
            ris = 0;

    printf ("%d\n", ris);
    return 0;
}
