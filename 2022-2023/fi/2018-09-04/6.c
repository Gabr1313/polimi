#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.h"

int isBuffa(ilist_t *headOrig) {
  ilist_t *headCopy = NULL, *elemOrig, *elemCopy;
  int currOrig, currCopy, prevOrig, prevCopy, ris;

  elemOrig = headOrig;
  while (elemOrig) {
    headCopy = listPush(headCopy, elemOrig->val);
    elemOrig = elemOrig->next;
  }

  elemOrig = headOrig;
  elemCopy = headCopy;
  if (elemOrig) {
    prevOrig = elemOrig->val;
    prevCopy = elemCopy->val;
    elemOrig = elemOrig->next;
    elemCopy = headCopy->next;
  }

  ris = 1;
  while (elemOrig && ris) {
    currOrig = elemOrig->val;
    currCopy = elemCopy->val;
    if (abs(currOrig - prevOrig) != abs(currCopy - prevCopy)) ris = 0;
    elemOrig = elemOrig->next;
    elemCopy = elemCopy->next;
  }

  listFree(headCopy);

  return ris;
}

/* lo so, la lista non prende interi... ma troppo sbatti adesso cambiarla! */

int main(void) {
  int val, ris;
  ilist_t *h = NULL;

  scanf("%d", &val);
  while (val > 0) {
    h = listAppend(h, val);
    scanf("%d", &val);
  }
  listPrintf(h);

  ris = isBuffa(h);
  printf("%d\n", ris);

  listFree(h);
  return 0;
}
