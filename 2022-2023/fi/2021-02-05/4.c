#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 30
#define VOCABULARY "vocabolario.txt"

typedef struct slista_s {
  char parola[LEN];
  struct slista_s* next;
} slista_t;

void cerca(char word[], FILE* vocabulary) {
  char prova[LEN + 1];

  while (fscanf(vocabulary, "%s", prova) == 1)
    if (prova[0] != word[0] && !strcmp(&prova[1], &word[1]))
      printf("%s\n", word);
}

slista_t* push(slista_t* head, char word[]) {
  slista_t* el;

  el = malloc(sizeof(slista_t));
  if (el) {
    strcpy(el->parola, word);
    el->next = head;
    head = el;
  } else
    printf("push: errore allocazione dinamica\n");
  return head;
}

slista_t* calcolaAlternative(char word[], FILE* vocabulary) {
  slista_t* head = NULL;
  char prova[LEN + 1];

  while (fscanf(vocabulary, "%s", prova) == 1)
    if (prova[0] != word[0] && !strcmp(&prova[1], &word[1]))
      head = push(head, prova);

  return head;
}

void listFree(slista_t* h) {
  slista_t* el;
  while (h) {
    el = h;
    h = h->next;
    free(el);
  }
}

int main(int argc, char* argv[]) {
  FILE* vocabulary;
  slista_t *altern, *el;
  int count;

  if (argc == 2) {
    vocabulary = fopen(VOCABULARY, "r");
    if (vocabulary) {
      altern = calcolaAlternative(argv[1], vocabulary);
      for (count = 0, el = altern; el; el = el->next, count++)
        printf("%s\n", el->parola);
      printf("%d\n", count);
      listFree(altern);
    } else
      printf("Can't open file %s\n", VOCABULARY);
  } else
    printf("Usage: %s string\n", argv[0]);

  return 0;
}
