#ifndef LIST_H
#define LIST_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LEN 30

typedef struct wlist_s {
  char word[WORD_LEN + 1];
  struct wlist_s *next;
} wlist_t;

wlist_t *list_append(wlist_t *, char[]);
wlist_t *list_push(wlist_t *, char[]);
void list_free(wlist_t *);
void list_printf(wlist_t *);
wlist_t *list_tail(wlist_t *);
wlist_t *list_copy(wlist_t *);
char list_del(wlist_t **, char[]);
wlist_t *list_pop_head(wlist_t **);
wlist_t *list_pop_tail(wlist_t **);

#endif
