/* Scrivere un sottoprogramma chericevute in ingresso due liste (iltipo degli elementi della lista
èlist_t) nerestituisce una nuova creata alternando gli elementi delle due liste, e poi mettendo in
coda tutti quelli della lista più lunga. Ad esempio, se le liste in ingresso sono fatte come segue,
1 3 5 7 9 11
2 4 6 8
la lista creata sarà fatta come segue
1 2 3 4 5 6 7 8 9 11 */

#include <stdio.h>

#include "ilist.h"

/* typedef struct ilist_s {
  int val;
  struct ilist_s * next;
} ilist_t; */

ilist_t *merge_list(ilist_t *a, ilist_t *b) {
  ilist_t *c = NULL;

  while (a && b) {
    c = lappend(c, a->val);
    c = lappend(c, b->val);
    a = a->next;
    b = b->next;
  }
  while (a) {
    c = lappend(c, a->val);
    a = a->next;
  }
  while (b) {
    c = lappend(c, b->val);
    b = b->next;
  }

  return c;
}

int main(void) {
  int val;
  ilist_t *a = NULL, *b = NULL, *c = NULL;

  scanf("%d", &val);
  while (val > 0) {
    a = lappend(a, val);
    scanf("%d", &val);
  }
  scanf("%d", &val);
  while (val > 0) {
    b = lappend(b, val);
    scanf("%d", &val);
  }

  c = merge_list(a, b);
  lprintf(c);

  lfree(a);
  lfree(b);
  lfree(c);

  return 0;
}
