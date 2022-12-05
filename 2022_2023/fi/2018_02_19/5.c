#include <stdio.h>

typedef struct ilist_s {
  int val;
  struct ilist_s* next;
} ilist_t;

int kcon(ilist_t* h, int k) {
  int ris;
  if (!(h && h->next))
    ris = 0;
  else if (h && h->next && h->val == k && h->next->val == k)
    ris = 1;
  else
    ris = kcon(h->next, k);
  return ris;
}

int knocon_n(ilist_t* h, int k, int rip) {
  int ris;
  if (h) {
    if (h->val == k) {
      if (rip == 1)
        ris = 1;
      else if (h->next)
        ris = knocon_n(h->next->next, k, --rip);
      else
        ris = 0;
    } else
      ris = knocon_n(h->next, k, rip);
  } else
    ris = 0;
  return ris;
}

int knocon(ilist_t* h, int k) { return knocon_n(h, k, 2); }
