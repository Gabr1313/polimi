#include <stdio.h>
#define MAX_LEN 100

int main (int argc, char *argv[]){
    int vect[MAX_LEN], i, j, vectCut[MAX_LEN], 
        len, lenCut, val, valMax, nRip, nRipMax;

    do scanf ("%d", &len);
    while (len < 1 || len > MAX_LEN);
    for (i=0; i < len; i++)
        scanf ("%d", &vect[i]);

    valMax = vect[0];
    nRipMax = 1;
    for (i = 1; i < len; i++)
        if (vect[i] == valMax)
            nRipMax ++;

    for (i = 1; i < len; i++){
        val = vect[i];
        nRip = 1;
        for (j = i + 1; j < len; j++)
            if (vect[j] == val)
                nRip++;
        if (nRip > nRipMax || nRip == nRipMax && val < valMax){
            valMax = val;
            nRipMax = nRip;
        }
    }

    lenCut = len - nRipMax;
    for (i = 0, nRip = 0; i < len; i++)
        if (vect[i] == valMax)
            nRip++;
        else
            vectCut[i - nRip] = vect[i];

    printf ("%d\n", nRipMax);
    for (i = 0; i < lenCut; i++)
        printf ("%d ", vectCut[i]);
    printf ("\n");

    return 0;
}
                
    

