/*
La cerniera è uno schema enigmistico che segue una formula del tipo ZX / YZ = XY, ossia date due
stringhe s1 e s2 cerca una sottostringa Z presente in entrambe, in s1 all’inizio, in s2 alla fine, e
se esiste crea una nuova stringa concatenando ciò che avanza da s1 e s2. Per esempio, se s1 = mare e
s2 = tema, la sottostringa ma rispetta i vincoli e viene creata la stringa rete; se s1 = flauto e s2
= golf, la sottostringa t rispetta i vincoli e viene creata la stringa lautogol. Non consideriamo
valide soluzioni in cui Y non esista, ossia s2 è una sottostringa di s1, come per esempio in s1 =
autoscuola e s2 = auto. (5 pti) Scrivere un sottoprogramma cercacerniera che riceve in ingresso due
stringhe e restituisce l’indice della posizione in cui comincia in s2 la sottostringa Z, se esiste,
-1 se non esiste. Con questa informazione il chiamante potrà creare la stringa risultante. Con
riferimento agli esempi precedenti, se s1 = mare e s2 = tema il sottoprogramma cercacerniera
restituisce 2. Naturalmente non è importante in questo frangente che il vocabolo che risulterebbe
dalla cerniera abbia senso in italiano. (4 pti) Scrivere un sottoprogramma cerniera che riceve in
ingresso due stringhe s1 e s2 ed un valore intero inizio. Il sottoprogramma crea e restituisce una
nuova stringa che si ottiene concatenando i caratteri di s1 che seguono la sottostringa di s2 a
partire dalla posizione inizio, ai caratteri di s2 che precedono inizio. Senz’altro il valore di
inizio è compatibile con le dimensioni di s1 e s2. (2 pti) Scrivere un programma che acquisisce da
riga di comando due stringhe e calcola, se esiste, la cerniera visualizzandola (chiamando i
sottoprogrammi di cui sono state indicate le funzionalità precedentemente). Nel caso in cui la
cerniera non esista, il programma non visualizza nulla.
 */

#include <stdio.h>
#include <string.h>
#define LEN_MAX 100

int cercaCerniera(char[], char[]);
void cerniera(char[], char[], char[], int);

int main(int argc, char *argv[]) {
  char s1[LEN_MAX + 1], s2[LEN_MAX + 1], ris[LEN_MAX + 1];
  int pos;

  scanf("%s", s1);
  scanf("%s", s2);

  pos = cercaCerniera(s1, s2);
  if (pos != -1) {
    cerniera(s1, s2, ris, pos);
    printf("%s\n", ris);
  }
  if (ris[0]) return 0;
}

int cercaCerniera(char s1[], char s2[]) {
  int i, pos, found, len2;

  found = 0;
  pos = 0;
  len2 = strlen(s2);
  while (s1[pos] != '\0' && pos < len2 && !found) {
    found = 1;
    for (i = 0; i <= pos; i++) {
      if (s1[i] != s2[len2 - 1 - pos + i]) found = 0;
    }
    pos++;
  }

  if (!found || pos == len2) return -1;
  return pos;
}

void cerniera(char s1[], char s2[], char cerniera[], int pos) {
  int i, j;

  for (i = pos, j = 0; s1[i] != '\0'; i++, j++) cerniera[j] = s1[i];
  for (i = 0; i < pos; i++, j++) cerniera[j] = s2[i];
  cerniera[j] = '\0';
}
