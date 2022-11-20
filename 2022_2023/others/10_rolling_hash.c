/*
 * data una stringa di parole, trovare quante volte compare una sottostringa
 */

#define P1 257
#define P2 263
#define PM 269

#include <stdio.h>
#include <string.h>
#include <math.h>

int num_repetition(char[], char[]);
int add_hash (int, char, int, int);
int del_hash (int, char, int, int);

int main(int argc, char* argv[]) {
  int ris;
  if (argc == 3) {
    ris = num_repetition(argv[1], argv[2]);
    printf("%d\n", ris);
  } else
    printf("Usage: %s string, string\n", argv[0]);
  return 0;
}

int num_repetition(char a[], char b[]) {
  int ris, len_a, len_b, i;
  int hash_a_1, hash_a_2, hash_b_1, hash_b_2, exp_1, exp_2;

  len_a = strlen(a);
  len_b = strlen(b);
  if (len_a < len_b) return 0;

  hash_a_1 = 0;
  hash_a_2 = 0;
  hash_b_1 = 0;
  hash_b_2 = 0;
  for (i = 0; i < len_b; i++) {
    hash_a_1 = add_hash(hash_a_1, a[i], P1, PM);
    hash_a_2 = add_hash(hash_a_2, a[i], P2, PM);
    hash_b_1 = add_hash(hash_b_1, b[i], P1, PM);
    hash_b_2 = add_hash(hash_b_2, b[i], P2, PM);
  }

  len_b --;
  exp_1 = 1;
  exp_2 = 1;
  for (i = 0; i < len_b; i++){
    exp_1 = (exp_1 * P1) % PM;
    exp_2 = (exp_2 * P2) % PM;
  }
  len_b ++;

  printf("%d %d\n", hash_a_1, hash_a_2);

  ris = 0;
  if (hash_a_1 == hash_b_1 && hash_a_2 == hash_b_2) ris++;
  for (i = len_b; i < len_a; i++) {
    hash_b_1 = del_hash(hash_b_1, b[i - len_a - 1], exp_1, PM);
    hash_b_2 = del_hash(hash_b_2, b[i - len_a - 1], exp_2, PM);
    hash_b_1 = add_hash(hash_b_1, b[i], P1, PM);
    hash_b_2 = add_hash(hash_b_2, b[i], P2, PM);

    printf("%d %d %c %d\n", hash_b_1, hash_b_2, b[i - len_a - 1], i);

    if (hash_a_1 == hash_b_1 && hash_a_2 == hash_b_2) ris++;
  }

  return ris;
}

int add_hash (int hash, char c, int p, int q){
  return ((hash * p) % q + c) % q;
}

int del_hash (int hash, char c, int k, int q){
  hash -= ((k * c) % q);
  if (hash > 0)
    return hash;
  return hash + q;
}
