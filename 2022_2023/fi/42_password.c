#include <stdio.h>

#define LEN 100
#define LEN_MIN 8
#define L_MIN_INIZIO 'a'
#define L_MIN_FINE 'z'
#define L_MAI_INIZIO 'A'
#define L_MAI_FINE 'Z'
#define NUM_INIZIO '0'
#define NUM_FINE '9'

int verPsw (char []);

int main (int argc, char *argv[]){
    char psw[LEN];
    int isValid;

    gets(psw);

    isValid = verPsw (psw);

    printf ("%d\n", isValid);
    return 0;
}

int verPsw (char psw[]){
    int isCifra, isStrano, isCon, i;

    isCifra = 0;
    isStrano = 0;
    isCon = 0;
    for (i = 0; psw[i] != '\0'; i++){
        if (psw[i] >= NUM_INIZIO && psw[i] <= NUM_FINE)
            isCifra = 1;
        else if (!(psw[i] >= L_MIN_INIZIO && psw[i] <= L_MIN_FINE) && !(psw[i] >= L_MAI_INIZIO && psw[i] <= L_MAI_FINE))
            isStrano = 1;
        if (!i)
            if (psw[i] == psw[i - 1])
                isCon = 1;
    }
    
    return !(i < LEN_MIN || !isCifra || !isStrano || isCon);
}
    

    


    

