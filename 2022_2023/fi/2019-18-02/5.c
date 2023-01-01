#include <stdio.h>
#include <stdlib.h>

#define BASE 10

typedef struct ilist_s {
  int val;
  struct ilist_s * next;
} ilist_t;

ilist_t * int2list(int);
ilist_t * listAppend(ilist_t *, int);
void listFree(ilist_t *);
void listPrintf(ilist_t *);
int reverse (int, int);

int main (int argc, char * argv[]){
  ilist_t *h;
  if (argc == 2){
    h = int2list(atoi(argv[1]));
    listPrintf(h);
    listFree(h);
  } else {
    printf("Usage: %s number\n", argv[0]);
  }
  return 0;
}

ilist_t * int2list(int num){
  int i, digit;
  ilist_t *h = NULL;
  if (num < 0){
    num = -num;
  } else {
    num = reverse(num, BASE);
  }
  while (num > 0) {
    digit = num % BASE;
    for (i = 0; i < digit; i++)
      h = listAppend(h, digit);
    num /= BASE;
  }
  return h;
}

ilist_t * listAppend(ilist_t *h, int val){
  ilist_t * elem, *prev;

  if ((elem = malloc(sizeof(ilist_t)))){
    elem -> val = val;
    elem -> next = NULL;
    if (!h)
      h = elem;
    else{
      prev = h;
      while (prev -> next){
        prev = prev -> next;
      }
      prev->next = elem;
    }
  } else
    printf("listAppend: Memory allocation problem\n");
  return h;
}

void listFree(ilist_t *h){
  ilist_t * elem;
  while (h){
    elem = h;
    h = h -> next;
    free(elem);
  }
}

int reverse (int val, int base){
  int ris;
  ris = 0;
  while (val > 0){
    ris *= base;
    ris += val % base;
    val /= base;
  }
  return ris;
}

void listPrintf(ilist_t* h) {
  for (; h; h = h->next) {
    printf("%d -> ", h->val);
  }
  printf("|\n");
}

