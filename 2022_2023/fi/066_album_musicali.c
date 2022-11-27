/* Si vuole realizzare un programma in C (C89) per la gestione di un archivio di album
musicali (al massimo 100). Ogni album è caratterizzato da un titolo ed un autore
(entrambe stringhe di al massimo 30 caratteri), un anno di pubblicazione, il numero di
tracce, la durata complessiva (in termini di ore, minuti, secondi); infine, si vuole
memorizzare anche il prezzo del album (un valore float).
Definire un tipo di dato per rappresentare l’archivio di album. In seguito scrivere un
programma che chiede all’utente prima il numero di album da inserire e poi i dati di
ciascun album (assumendo che l’utente inserisca correttamente i dati). Il programma
visualizza i dati del album di durata massima; se sono presenti più album di stessa
durata massima il programma visualizzerà i dati del primo di essi (VARIANTE: il
programma visualizza i dati di tutti gli album di durata massima, se ne sono stati
trovati più di uno). In seguito il programma chiede il nome di un autore e visualizza i
titoli di tutti gli album pubblicati da questo. Infine il programma visualizza l’autore
che ha pubblicato più album; se più autori autori hanno lo stesso numero massimo di
album, si visualizzi il primo. */

#include <stdio.h>
#include <string.h>
#define MAX_LEN 30
#define MAX_ALBUM 100

typedef struct {
  int ore, minuti, secondi;
} tempo_t;

typedef struct {
  char titolo[MAX_LEN + 1], autore[MAX_LEN + 1];
  int anno, ntracce;
  tempo_t durata;
  float prezzo;
} album;

void fill_album(album[], int);
void vis_dur_max(album[], int);
void vis_album(album[], int, char[]);
void vis_aut_max(album[], int);

int main(int argc, char *argv[]) {
  int num;
  char autore[MAX_LEN + 1];
  album array[MAX_ALBUM];

  scanf("%d", &num);
  fill_album(array, num);

  vis_dur_max(array, num);

  scanf("%s", autore);
  vis_album(array, num, autore);

  vis_aut_max(array, num);

  return 0;
}

void fill_album(album array[], int num) {
  int i;
  for (i = 0; i < num; i++) {
    scanf("%s", array[i].titolo);
    scanf("%s", array[i].autore);
    scanf("%d", &array[i].anno);
    scanf("%d", &array[i].ntracce);
    scanf("%d", &array[i].durata.ore);
    scanf("%d", &array[i].durata.minuti);
    scanf("%d", &array[i].durata.secondi);
    scanf("%f", &array[i].prezzo);
  }
}

void vis_dur_max(album array[], int num) {
  int i, max;

  max = 0;
  for (i = 1; i < num; i++) {
    if (array[max].durata.ore < array[i].durata.ore)
      max = i;
    else if (array[max].durata.ore == array[i].durata.ore &&
             array[max].durata.minuti < array[i].durata.minuti)
      max = i;
    else if (array[max].durata.ore == array[i].durata.ore &&
             array[max].durata.minuti == array[i].durata.minuti &&
             array[max].durata.secondi < array[i].durata.secondi)
      max = i;
  }
  printf("\n");
  printf("%s ", array[max].titolo);
  printf("%s ", array[max].autore);
  printf("%d ", array[max].anno);
  printf("%d ", array[max].ntracce);
  printf("%d ", array[max].durata.ore);
  printf("%d ", array[max].durata.minuti);
  printf("%d ", array[max].durata.secondi);
  printf("%g ", array[max].prezzo);
  printf("\n");
}

void vis_album(album array[], int num, char autore[]) {
  int i;

  for (i = 0; i < num; i++) {
    if (!strcmp(array[i].autore, autore)) printf("%s ", array[i].titolo);
  }
  printf("\n");
}

void vis_aut_max(album array[], int num) {
  int nalbum[MAX_ALBUM], found, i, j, len, j_max;
  char nome[MAX_ALBUM][MAX_LEN + 1];

  for (i = 0; i < num; i++) nalbum[i] = 0;

  for (i = 0, len = 0, j_max = 0; i < num; i++) {
    found = 0;
    for (j = 0; j < len && !found; j++)
      if (!strcmp(nome[j], array[i].autore)) {
        found = 1;
        ++nalbum[j];
        if (nalbum[j] > nalbum[j_max]) j_max = j;
      }
    if (!found) {
      nalbum[len] = 1;
      strcpy(nome[len], array[i].autore);
      ++len;
    }
  }

  printf("%s\n", nome[j_max]);
}
