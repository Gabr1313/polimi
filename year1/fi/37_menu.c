#include <stdio.h>
#define BASE 10
#define V "Vero"
#define F "Falso"

void menu ();
int sceltamenu ();
int inVal ();
int isPrime (int);
int fact (int);
int isPal (int, int);
void stampa (int, int);

int main (int argc, char *argv[]){
    int scelta, val, ris;

    scelta = sceltamenu ();
    while (scelta != 0){
        if (scelta == 1)
            val = inVal ();
        else {
            if (scelta == 2)
                ris = isPrime (val);
            else if (scelta == 3)
                ris = fact (val);
            else if (scelta == 4)
                ris = isPal (val, BASE);
            stampa (ris, scelta);
        }
        scelta = sceltamenu ();
    }
    
    return 0;
}
    
void menu (){
    printf ("1. acquisizione valore\n");
    printf ("2. numero primo       \n");
    printf ("3. fattoriale         \n");
    printf ("4. palindromo         \n");
    printf ("0. termina            \n");
}

int sceltamenu (){
    int scelta;

    do {
        menu ();
        scanf ("%d", &scelta);
    }
    while (scelta < 0 || scelta > 4);

    return scelta;
}

int inVal (){
    int val;

    do scanf ("%d", &val);
    while (val <= 0);

    return val;
}

int isPrime (int num){
    int ris, div, meta;
    
    if (num == 1 || num == 2)
        ris = 1;
    else if (num % 2 == 0)
        ris = 0;
    else {
        ris = 1;
        meta = num / 2;
        for (div = 3; div < meta && ris; div += 2)
            if (num % div == 0)
                ris = 0;
    }
    
    return ris;
}

int fact (int num){
    int ris, i;
    
    ris = 1;
    for (i = 2; i <= num; i++)
        ris *= i;

    return ris;
}

int isPal (int num, int base){
    int rev, ris, temp;

    temp = num;
    rev = 0;
    while (temp > 0) {
        rev *= base;
        rev += temp % base;
        temp /= base;
    }
    
    if (rev == num)
        ris = 1;
    else 
        ris = 0;

    return ris;
}

void stampa (int ris, int scelta){
    if (scelta == 2 || scelta == 4) {
        if (ris)
            printf (V);
        else
            printf (F);
    }
    else printf ("%d", ris);
    printf ("\n");
}
        


