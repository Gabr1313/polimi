/* # Esercizio 1A - appello 15/02/2022
Scrivere un sottoprogramma check che ricevute due stringhe, tentativo e soluzione,
di ugual lunghezza (è senz’altro così) rappresentanti due vocaboli, restituisce una
stringa contenente:
= se il carattere in posizione i di tentativo è uguale al carattere in posizione i di
soluzione,
+ se il carattere in posizione i di tentativo è uguale ad un carattere di soluzione in
posizione j con j 6=i,
X se il carattere in posizione i di tentativo non appartiene a soluzione.
Per esempio, se il sottoprogramma riceve in ingresso:
tentativo: “parco”
soluzione: “torre”
il sottoprogramma restituisce la stringa “XX=X+”. */

#include <stdio.h>
#define MAX_LEN 100
#define EQUAL '='
#define OTHER '+'
#define DIFF 'X'

void compare(char[], char[], char[]);

int main(int argc, char* argv[]) {
    char ris[MAX_LEN];
    if (argc == 3) {
        compare(argv[1], argv[2], ris);
        printf("%s\n", ris);
    } else
        printf("Not valid arguments");

    return 0;
}

void compare(char tentativo[], char soluzione[], char ris[]) {
    int i, j, found;
    for (i = 0; tentativo[i]; ++i)
        if (tentativo[i] == soluzione[i])
            ris[i] = EQUAL;
        else {
            found = 0;
            for (j = 0; soluzione[j] && !found; j++)
                if (soluzione[j] == tentativo[i]) {
                    found = 1;
                    ris[i] = OTHER;
                }
            if (!found)
                ris[i] = DIFF;
        }
}
