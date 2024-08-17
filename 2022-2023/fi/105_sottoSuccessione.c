#include <stdio.h>

#include "my_library/ilist.h"

int sottoSuccessione(ilist_t* seq1, ilist_t* seq2) {
  int ris;
  if (seq2) {
    while (seq1 && seq2) {
      if (seq1->val == seq2->val) {
        seq2 = seq2->next;
      }
      seq1 = seq1->next;
    }
    ris = !seq2;
  } else
    ris = 0;
  return ris;
}

int main(void) {
  ilist_t *seq1, *seq2;
  int val;
  scanf("%d", &val);

  while (val) {
    seq1 = listAppend(seq1, val);
    scanf("%d", &val);
  }
  scanf("%d", &val);
  while (val) {
    seq2 = listAppend(seq2, val);
    scanf("%d", &val);
  }

  listPrintf(seq1);
  listPrintf(seq2);
  printf("%d\n", sottoSuccessione(seq1, seq2));
  listFree(seq1);
  listFree(seq2);
  return 0;
}
