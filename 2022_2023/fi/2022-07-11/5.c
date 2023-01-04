#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.c"

int findRadCub(int val, int* rad) {
  int i, ris, sign;
  if (val >= 0)
    sign = 1;
  else {
    sign = -1;
    val = -val;
  }
  for (i = 0; i * i * i < val; i++)
    ;
  ris = 0;
  if (i * i * i == val) {
    *rad = (sign > 0 ? i : -i);
    ris = 1;
  }
  return ris;
}

/* typedef struct ilist_s {
  int val;
  struct ilist_s * next;
} ilist_t; */

ilist_t* addRadCub(ilist_t* h) {
  ilist_t *el, *newEl;
  int rad, status;
  el = h;
  status = 1;
  while (el && status) {
    if (findRadCub(el->val, &rad)) {
      newEl = malloc(sizeof(ilist_t));
      if (newEl) {
        newEl->val = rad;
        newEl->next = el->next;
        el->next = newEl;
        el = newEl->next;
      } else {
        printf("addRadCub: problema allocazione dinamica\n");
        status = 0;
      }
    } else {
      el = el->next;
    }
  }
  return h;
}

int main(void) {
  ilist_t* h;
  int val;
  scanf("%d", &val);
  while (val) {
    h = listAppend(h, val);
    scanf("%d", &val);
  }
  listPrintf(h);
  addRadCub(h);
  listPrintf(h);
  listFree(h);
  return 0;
}
