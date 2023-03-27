/* Una stringa costituisce un pangramma se ogni lettera dell’alfabeto compare
almeno una volta. Si scriva un sottoprogramma che ricevuta in ingresso una
stringa restituisce 1 se la stringa è un pangramma, 0 altrimenti. La stringa può
contenere caratteri maiuscoli, minuscoli e spazi; non importa se il carattere
compare come maiuscola o minuscola. Si considerino stringhe di senso compiuto in
inglese, in modo tale da non aver il problema delle lettere j, k, w, x, e y, che
quindi devono comparire anch’esse. Esempio: Ingresso: A quick brown fox jumps
over the lazy dog Valore restituito: 1 Ingresso: There is no easy way out of a
problem Valore restituito: 0 */

#include <ctype.h>
#include <stdio.h>

#define LEN 255
#define START 'a'
#define END 'z'

int is_pangramma(char[]);
int initBit();

/* il main non e' richiesto dall'esercizio */
int main(void) {
  char s[LEN + 1];
  fgets(s, LEN + 1, stdin);
  printf("%d\n", is_pangramma(s));
  return 0;
}

int is_pangramma(char s[]) {
  char c;
  int i, bitSet, bitCmp;
  bitCmp = 0x7fffffe; /* bitCmp = initBit(); */
  bitSet = 0;
  for (i = 0; s[i] && bitSet != bitCmp; i++) {
    c = tolower(s[i]);
    if (c >= START && c <= END) bitSet |= (1 << (c % 32));
  }
  return bitSet == bitCmp;
}

int initBit() {
  int bitCmp;
  char i;
  bitCmp = 0;
  for (i = 'a'; i <= 'z'; i++) bitCmp |= (1 << (i % 32));
  return bitCmp;
}
