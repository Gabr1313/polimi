#include <stdio.h>
#include "../my_library/ilist.h"

void completeList (ilist_t * prev){
  ilist_t * next;
  if (prev){
    next = prev -> next;
    while (next){
      if (next -> val != prev -> val + 1){
        next = listPush(next, prev -> val + 1);
        prev->next = next;
      }
      prev = next;
      next = prev -> next;
    }
  }
}

int main(void) {
  int val;
  ilist_t *h = NULL;

  scanf("%d", &val);
  while (val > 0) {
    h = listAppend(h, val);
    scanf("%d", &val);
  }
  listPrintf(h);
  completeList(h);
  listPrintf(h);

  listFree(h);
  return 0;
}
