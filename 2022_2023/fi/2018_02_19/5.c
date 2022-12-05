#include <stdio.h>

typedef struct ilist_s {
  int val;
  struct ilist_s* next;
} ilist_t;

int kcon(ilist_t* h, int k) {
  if (!(h && h->next)) return 0;
  if (h && h->next && h->val == k && h->next->val == k) return 1;
  return kcon(h->next, k);
}

ilist_t* whereis(ilist_t* h, int k) {
  while (h && h->val != k) {
    h = h->next;
  }
  return h;
}

int knocon(ilist_t* h, int k) {
  ilist_t* num;
  if ((num = whereis(h, k)) && num->next && whereis(num->next->next, k)) return 1;
  return 0;
}
