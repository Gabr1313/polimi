#ifndef ILIST_T_LIB
#define ILIST_T_LIB

#include <stdio.h>
#include <stdlib.h>

typedef struct ilist_s {
  int val;
  struct ilist_s* next;
} ilist_t;

ilist_t* lappend(ilist_t*, int);
ilist_t* lpush(ilist_t*, int);
ilist_t* linsert_in_order(ilist_t*, int);
ilist_t* lfind(ilist_t*, int);
ilist_t* ldelete(ilist_t*, int);
ilist_t* lfree(ilist_t*);
int llen(ilist_t*);
void lprintf(ilist_t*);
ilist_t* pop(ilist_t**);
ilist_t* lremove(ilist_t*, int);

#endif
