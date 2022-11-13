/*
Un numero in una base b, con 1 ≤ b ≤ 36, può essere scritto utilizzando i primi b caratteri dell’insieme dei simboli SIMBOLI = {’0’,.
. . , ’9’, ’A’,. . . , ’Z’}. Ad esempio, un numero in base 24 può essere espresso utilizzando i caratteri {’0’,. .
. , ’9’, ’A’,. . . , ’N’}. Una qualsivoglia stringa s è valida rispetto alla base b soltanto se utilizza i primi b caratteri di
SIMBOLI. Ad esempio, "AB8" è una stringa valida per la base 14 ma non per la base 11.
Si scriva un sottoprogramma che ricevuta in ingresso una stringa s contenente un valore in base b calcoli e restituisca al chiamante il valore
corrispondente alla base minima cui appartiene la stringa. La stringa conterrà senz’altro solo caratteri numerici e caratteri alfabetici maiuscoli.
Per esempio, se il sottoprogramma riceve in ingresso la stringa AB8 restituisce il valore 12, facendo riferimento alla base 12 e all’alfabeto di simboli
{’0’,. . . , ’9’, ’A’, ’B’}.
 */

#include <stdio.h>
#define MAX_LEN 100
#define INIZIO_NUM '0'
#define FINE_NUM '9'
#define INIZIO_LET 'A'
#define FINE_LET 'Z'
/* macro
*/
#define NUM(i) num[i] - INIZIO_NUM + 1
#define LET(i) num[i] - INIZIO_LET + 11
#define ISNUM(i) num[i] >= INIZIO_NUM && num[i] <= FINE_NUM
#define ISLET(i) num[i] >= INIZIO_LET && num[i] <= FINE_LET

int baseMin (char []);

int main (int argc, char *argv[]){
    char num[MAX_LEN + 1];
    int ris;

    scanf("%s", num);

    ris = baseMin(num);

    printf("%d\n", ris);
    return 0;
}
    
int baseMin (char num[]){
    int base, i, baseMin;
    
    i = 0;
    if (ISNUM(i))
        baseMin = NUM(i);
    else if (ISLET(i))
        baseMin = LET(i);
    for (i = 1; num[i] != '\0'; i++){
        if (ISNUM(i))
            base = NUM(i);
        else if (ISLET(i))
            base = LET(i);
        if (base > baseMin)
            baseMin = base;
    }

    return baseMin;
}


