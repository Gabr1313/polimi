#include <stdio.h>

#include "../my_library/ilist.h"

/* typedef struct ilist_s {
  int val;
  struct ilist_s * next;
} ilist_t; */

int sottoSucc(ilist_t *s1, ilist_t *s2) {
  int ris;

  if (s2 != NULL) {
    while (s1 && s2) {
      if (s1->val == s2->val) s2 = s2->next;
      s1 = s1->next;
    }
    ris = !s2;
  } else
    ris = 0;

  return ris;
}

int main(void) {
  ilist_t *s1 = NULL, *s2 = NULL;
  int val, n, i;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &val);
    s1 = listAppend(s1, val);
  }
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &val);
    s2 = listAppend(s2, val);
  }

  listPrintf(s1);
  listPrintf(s2);
  printf("%d\n", sottoSucc(s1, s2));
  listFree(s1);
  listFree(s2);

  return 0;
}
