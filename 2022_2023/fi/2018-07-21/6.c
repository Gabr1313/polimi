/* #include <stdio.h>

typedef struct elem_s{
  int val;
  struct elem_s * next;
} elem;

elem * selectItems (elem*h, int min, int max){
  elem * ris = NULL;

  while (h){
    if (h -> val < min || h -> val > max)
      ris = insertdown(ris, h -> val);
    h = h -> next;
  }

} */

/* modified so it is compatible with my library */
#include <stdio.h>

#include "../my_library/ilist.h"

ilist_t* selectItems(ilist_t* h, int min, int max) {
  ilist_t* ris = NULL;

  while (h) {
    /* consapevolissimo che linsert_in_order() inserisca in ordine inverso rispetto a quello
     * richiesto */
    if (h->val < min || h->val > max) ris = listInsertInOrder(ris, h->val);
    h = h->next;
  }
  return ris;
}

int main(void) {
  int val, min, max;
  ilist_t *h = NULL, *ris;

  scanf("%d", &val);
  while (val > 0) {
    h = listAppend(h, val);
    scanf("%d", &val);
  }
  listPrintf(h);
  scanf("%d", &min);
  scanf("%d", &max);

  ris = selectItems(h, min, max);
  listPrintf(ris);

  listFree(h);
  listFree(ris);

  return 0;
}
