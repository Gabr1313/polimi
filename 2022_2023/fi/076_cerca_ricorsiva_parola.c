/*
Scrivere un sottoprogramma ricorsivo che riceve come parametri due stringhe a e b; il
sottoprogramma verifica se in b sono presenti tutti i caratteri presenti in a, nello
stesso ordine, più eventualmente qualche altro carattere. In caso affermativo il
sottoprogramma restituisce 1 altrimenti 0. Scrivere un programma che acquisisce da riga
di comando due stringhe, invoca il sottoprogramma definito e visualizza il risultato.
VARIANTE: Scrivere la versione iterativa del sottoprogramma.
ESEMPIO:
in: a=”acca” b=”baracca”				out: 1
in: a=”acca” b=”racchetta”				
out: 1
in: a=”acca” b=”amaca” 					
out: 0

acca baracca

*/

#include <stdio.h>
#include <string.h>

int cercalettere (char[], char[]);

int main (int argc, char *argv[])
{
    int ris;

    if (argc == 3){
        ris = cercalettere(argv[2], argv[1]);
        printf("%d\n", ris);
    } else
        printf("usage: %s word1 word2\n", argv[0]);

    return 0;
}

int cercalettere (char a[], char b[]){
    int ris;
    char *pos;

    if (!b[0])
        ris = 1;
    else {
        if ((pos = strchr(a, b[0])))
            ris = cercalettere (pos + 1, &b[1]);
        else
            ris = 0;
    }

    return ris;
}
