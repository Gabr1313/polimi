#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.c"

/*
typedef struct ilist_s {
  int val;
  struct ilist_s *next;
} ilist_t;
*/
ilist_t *listAppend2(ilist_t *h, int num) {
  ilist_t *elem, *prev;

  elem = malloc(sizeof(ilist_t));
  if (elem) {
    elem->val = num;
    elem->next = NULL;
    if (!h)
      h = elem;
    else {
      prev = h;
      while (prev->next) prev = prev->next;
      prev->next = elem;
    }
  } else
    printf("listAppend: Errore allocazione dinamica\n");

  return h;
}

ilist_t *removeElem(ilist_t *seq, ilist_t *subseq) {
  ilist_t *ris = NULL;

  while (seq) {
    if (!subseq || seq->val != subseq->val)
      ris = listAppend2(ris, seq->val);
    else
      subseq = subseq->next;
    seq = seq->next;
  }

  return ris;
}

int main(void) {
  int val;
  ilist_t *new, *h = NULL, *sub = NULL;

  scanf("%d", &val);
  while (val > 0) {
    h = listAppend2(h, val);
    scanf("%d", &val);
  }
  scanf("%d", &val);
  while (val > 0) {
    sub = listAppend2(sub, val);
    scanf("%d", &val);
  }

  listPrintf(h);
  listPrintf(sub);
  new = removeElem(h, sub);
  listPrintf(new);

  listFree(h);
  listFree(sub);
  listFree(new);

  return 0;
}
