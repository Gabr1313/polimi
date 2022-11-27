#include <stdio.h>
#define MAX_LEN 128
#define STOP '*'
#define INIZIO 'a'
#define FINE 'z'
#define SUB '*'
#define VOC (FINE - INIZIO + 1)

int main(int argc, char *argv[]) {
  char frase[MAX_LEN], fraseS[MAX_LEN], letter;
  int i, pos, maxPos, freq[VOC], len;

  scanf("%c", &frase[0]);
  fraseS[0] = frase[0];
  i = 1;
  while (letter != STOP && i < MAX_LEN) {
    scanf("%c", &letter);
    frase[i] = letter;
    fraseS[i] = letter;
    i++;
  }
  if (letter == STOP) len = i - 1;

  for (i = 0; i < VOC; i++) freq[i] = 0;

  maxPos = 0;
  for (i = 0; i < len; i++) {
    if (frase[i] >= INIZIO && frase[i] <= FINE) {
      pos = frase[i] - INIZIO;
      freq[pos]++;
      if (freq[pos] > freq[maxPos] || freq[pos] == freq[maxPos] && pos > maxPos) maxPos = pos;
    }
  }

  letter = maxPos + INIZIO;
  for (i = 0; i < len; i++) {
    if (fraseS[i] == letter) fraseS[i] = SUB;
  }

  for (i = 0; i < len; i++) {
    printf("%c", fraseS[i]);
  }
  printf("\n");

  return 0;
}
