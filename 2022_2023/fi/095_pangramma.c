/* Una stringa costituisce un pangramma se ogni lettera dell’alfabeto compare almeno una volta. Si
scriva un sottoprogramma che ricevuta in ingresso una stringa restituisce 1 se la stringa è un
pangramma, 0 altrimenti. La stringa può contenere caratteri maiuscoli, minuscoli e spazi; non
importa se il carattere compare come maiuscola o minuscola. Si considerino stringhe di senso
compiuto in inglese, in modo tale da non aver il problema delle lettere j, k, w, x, e y, che quindi
devono comparire anch’esse. Esempio: Ingresso: A quick brown fox jumps over the lazy dog Valore
restituito: 1 Ingresso: There is no easy way out of a problem Valore restituito: 0 */

#define LEN 127
#define START_LOW 'a'
#define END_LOW 'z'
#define START_UPP 'A'
#define END_UPP 'Z'
#define LEN_ALPHA (END_LOW - START_LOW + 1)

#include <stdio.h>
#include <string.h>

int is_pangramma(char[]);

/* il main non e' richiesto dall'esercizio */
int main(int argc, char* argv[]) {
  char s[LEN + 1];

  fgets(s, LEN + 1, stdin);

  printf("%d\n", is_pangramma(s));

  return 0;
}

int is_pangramma(char s[]) {
  int i, pos, tot;
  int map[LEN_ALPHA];

  /* uguale a un ciclo for che assegna a ogni valore dell'array, zero */
  memset(map, 0, sizeof(int) * LEN_ALPHA);

  tot = 0;
  for (i = 0; s[i] && tot < LEN_ALPHA; i++) {
    if (s[i] >= START_LOW && s[i] <= END_LOW) {
      pos = s[i] - START_LOW;
      if (!map[pos]) {
        map[pos] = 1;
        tot++;
      }
    } else if (s[i] >= START_UPP && s[i] <= END_UPP) {
      pos = s[i] - START_UPP;
      if (!map[pos]) {
        map[pos] = 1;
        tot++;
      }
    }
  }

  return (tot == LEN_ALPHA);
}
