/*
# Esercizio 6A - appello 01/09/2021
Una applicazione richiede di scegliere il proprio nome utente nel rispetto di alcune
regole e si vuole realizzare un programma che acquisisca e verifichi il nome scelto.
Scrivere il sottoprogramma valido che ricevuti in ingresso il nome scelto (usrname),
due interi (min e max) e una stringa (speciali) verifica che esso rispetti le seguenti
regole:
+ deve essere di almeno min caratteri,
+ non deve superare la lunghezza di max caratteri,
+ deve contenere almeno un carattere appartenente ai caratteri presenti nella stringa
speciali.
Nel caso in cui tutte le regole siano rispettate, il nome utente scelto è valido e il
sottoprogrammarestituisce 1, in caso contrario il sottoprogramma restituisce 0.
*Nota: non effettuare elaborazioni inutili e/o inefficienti: la soluzione proposta verrà
valutata anche in relazione a questo aspetto.*

# Esercizio 6B - appello 01/09/2021
Scrivere un programma che acquisisce dall’utente una stringa di al più 20 caratteri
e verifica che questa contenga un nome utente valido (avvalendosi del sottoprogramma
valido), e fino a che non è tale continua a richiederla. Quando le regole sono
rispettate il programma chiama il sottoprogramma StartApp che riceve in ingresso
il nome utente (il prototipo è riportato di seguito) e realizza la funzionalità
desiderata.
int StartApp(char []);
I vincoli per la validità del nome utente sono una lunghezza compresa nell’intervallo
[8; 15] e un insieme dei caratteri speciali costituito dai caratteri ’$’ ’#’ ’%’ ’&’.
 */

#include <stdio.h>
#define MIN 8
#define MAX 15
#define MAX_LEN 20
#define SPECIAL "$#%&"

int valido(char[], int, int, char[]);

int main(int argc, char *argv[]) {
    char username[MAX_LEN + 1], isValid;

    do {
        scanf("%s", username);
        isValid = valido(username, MIN, MAX, SPECIAL);
    } while (!isValid);

    /*
    StartApp(username);
     */

    return 0;
}

int valido(char username[], int min, int max, char speciali[]) {
    int i, j, ris, isSpec;

    isSpec = 0;
    for (i = 0; username[i] != '\0' && i < max; i++)
        for (j = 0; speciali[j] != '\0' && !isSpec; j++)
            if (username[i] == speciali[j])
                isSpec = 1;

    if (i == max || i < min)
        ris = 0;
    else
        ris = isSpec;

    return ris;
}
