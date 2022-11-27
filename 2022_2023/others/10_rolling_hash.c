#define P1 257
#define P2 263
#define PM 269
#define HASH_CMP(a, b) (a.val1 == b.val1 && a.val2 == b.val2)

#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct hash_s {
  int val1, val2, exp1, exp2;
} hash_t;

int num_repetition(char[], char[]);
void init_hash(hash_t *, char[], int);
void hash_add(hash_t *, char);
void hash_del(hash_t *, char);

int main(int argc, char *argv[]) {
  int ris;
  if (argc == 3) {
    ris = num_repetition(argv[1], argv[2]);
    printf("%d\n", ris);
  } else
    printf("Usage: %s string, string\n", argv[0]);
  return 0;
}

int num_repetition(char a[], char b[]) {
  int i, ris, len_a, len_b, diff;
  hash_t hash_a, hash_b;

  len_a = strlen(a);
  len_b = strlen(b);

  ris = 0;
  diff = len_a - len_b;
  if (diff >= 0) {
    init_hash(&hash_a, a, len_b);
    init_hash(&hash_b, b, len_b);

    ris += HASH_CMP(hash_a, hash_b);

    for (i = 0; i < diff; i++) {
      hash_del(&hash_a, a[i]);
      hash_add(&hash_a, a[i + len_b]);
      ris += HASH_CMP(hash_a, hash_b);
    }
  }

  return ris;
}

void init_hash(hash_t *hash, char a[], int len) {
  int i;

  hash->val1 = 0;
  hash->val2 = 0;
  hash_add(hash, a[0]);
  hash->exp1 = 1;
  hash->exp2 = 1;
  for (i = 1; i < len; i++) {
    hash_add(hash, a[i]);
    hash->exp1 = (hash->exp1 * P1) % PM;
    hash->exp2 = (hash->exp2 * P2) % PM;
  }
}

void hash_add(hash_t *hash, char c) {
  hash->val1 = (hash->val1 * P1 + c) % PM;
  hash->val2 = (hash->val2 * P2 + c) % PM;
}

void hash_del(hash_t *hash, char c) {
  hash->val1 = (hash->val1 - (hash->exp1 * c)) % PM;
  hash->val2 = hash->val2 - (hash->exp2 * c) % PM;
  if (hash->val1 < 0) hash->val1 += PM;
  if (hash->val2 < 0) hash->val2 += PM;
}
