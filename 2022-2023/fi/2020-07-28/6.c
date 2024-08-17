#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.h"

/* typedef struct ilist_s {
  int val;
  struct ilist_s *next;
} ilist_t; */

ilist_t *push(ilist_t *, int);

ilist_t *sopraSoglia(int seq[], int len, int soglia) {
  int i;
  ilist_t *h = NULL;

  soglia = soglia * soglia;
  for (i = len - 1; i >= 0; i--) {
    if (seq[i] > soglia) h = push(h, i);
  }

  return h;
}

ilist_t *push(ilist_t *h, int i) {
  ilist_t *el;
  el = malloc(sizeof(ilist_t));
  if (el) {
    el->val = i;
    el->next = h;
    h = el;
  } else
    printf("push: problemi allocazione dinamica\n");

  return h;
}

#define LEN 10

int main(void) {
  int i, v[LEN], s;
  ilist_t * h;

  scanf("%d", &s);
  for (i=0;i<LEN;i++)
    scanf("%d", &v[i]);

  h = sopraSoglia (v, LEN, s);
  listPrintf(h);
  listFree(h);
  
  return 0;
}
