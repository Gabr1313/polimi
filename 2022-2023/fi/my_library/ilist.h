#ifndef ILIST_T_LIB
#define ILIST_T_LIB

#include <stdio.h>
#include <stdlib.h>

typedef struct ilist_s {
  int val;
  struct ilist_s* next;
} ilist_t;

ilist_t* listAppend(ilist_t*, int);
ilist_t* listPush(ilist_t*, int);
ilist_t* listInsertInOrder(ilist_t*, int);
ilist_t* listFind(ilist_t*, int);
ilist_t* listRemoveInt(ilist_t*, int);
ilist_t* listRemovePos(ilist_t*, int);
void listFree(ilist_t*);
int listLen(ilist_t*);
void listPrintf(ilist_t*);
ilist_t* listPopHead(ilist_t**);
ilist_t* listPopTail(ilist_t**);

#endif
