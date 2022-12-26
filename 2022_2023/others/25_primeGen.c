#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE 10
#define SIZE_BITS (sizeof(bitSet_t) * 8)

typedef unsigned char u8;
typedef unsigned long int u64;
typedef u64 bitSet_t;

u64 generatePrimes(u64 **, u64);
void printfArrayUl(u64 *, u64);
u64 findPrimes(bitSet_t *, u64);
void fillPrimes(u64 *, u64, bitSet_t *);
u64 crossMultiple(bitSet_t *, u64, u64);
void bit_to0(bitSet_t *, u64);
void bit_AllTo1(bitSet_t *, u64);
u8 bit_getValue(bitSet_t *, u64);

int main(int argc, char *argv[]) {
  u64 *primes, maxValue, numberOfPrimes;
  char *check;
  if (argc == 2) {
    maxValue = strtoul(argv[1], &check, BASE);
    if (!*check) {
      numberOfPrimes = generatePrimes(&primes, maxValue);
      printfArrayUl(primes, numberOfPrimes);
      printf("Total: %lu\n", numberOfPrimes);
      free(primes);
    } else
      printf("Invalid number\n");
  } else
    printf("Usage: %s number\n", argv[0]);
  return 0;
}

u64 generatePrimes(u64 **primes_p, u64 maxValue) {
  u64 *primes = NULL, numberOfElem, numberOfPrimes, len;
  bitSet_t *crossedOut;
  if (maxValue >= 2) {
    len = maxValue + 1;
    numberOfElem = len / SIZE_BITS + 1;
    crossedOut = malloc(sizeof(bitSet_t) * numberOfElem);
    if (crossedOut) {
      bit_AllTo1(crossedOut, maxValue + 1);
      numberOfPrimes = findPrimes(crossedOut, len);
      primes = malloc(sizeof(u64) * numberOfPrimes);
      if (primes)
        fillPrimes(primes, numberOfPrimes, crossedOut);
      else
        printf("generatePrimes: memory allocation problem\n");
      free(crossedOut);
    } else
      printf("generatePrimes: memory allocation problem\n");
  } else
    numberOfPrimes = 0;
  *primes_p = primes;
  return numberOfPrimes;
}

u64 findPrimes(bitSet_t *crossedOut, u64 len) {
  u64 i, numberOfPrimes, crossedNew;
  numberOfPrimes = len;
  for (i = 0; i < 2; i++) {
    bit_to0(crossedOut, i);
    numberOfPrimes--;
  }
  for (; i * i < len; i++) {
    if (bit_getValue(crossedOut, i)) {
      crossedNew = crossMultiple(crossedOut, len, i);
      numberOfPrimes -= crossedNew;
    }
  }
  return numberOfPrimes;
}

u64 crossMultiple(bitSet_t *crossedOut, u64 len, u64 multiple) {
  u64 i, crossedNew;
  crossedNew = 0;
  for (i = 2 * multiple; i < len; i += multiple) {
    if (bit_getValue(crossedOut, i)) {
      bit_to0(crossedOut, i);
      crossedNew++;
    }
  }
  return crossedNew;
}

void fillPrimes(u64 *primes, u64 numberOfPrimes, bitSet_t *crossedOut) {
  u64 i, j;
  i = 1;
  for (j = 0; j < numberOfPrimes; j++) {
    for (i++; !bit_getValue(crossedOut, i); i++)
      ;
    primes[j] = i;
  }
}

void printfArrayUl(u64 *arr, u64 len) {
  u64 i;
  for (i = 0; i < len; i++) printf("%lu ", arr[i]);
  printf("\n");
}

void bit_AllTo1(bitSet_t *bits, u64 len) {
  u64 numberOfElem, i;
  numberOfElem = len / SIZE_BITS + 1;
  for (i = 0; i < numberOfElem; i++) {
    *(bits + i) = -1;
  }
}

void bit_to0(bitSet_t *bits, u64 pos) {
  u64 bigPos, bitCompared;
  u8 smallPos;
  bigPos = pos / SIZE_BITS;
  smallPos = SIZE_BITS - pos % SIZE_BITS;
  bitCompared = -1 - ((bitSet_t)1 << smallPos);
  *(bits + bigPos) &= bitCompared;
}

u8 bit_getValue(bitSet_t *bits, u64 pos) {
  u64 bigPos, bitCompared;
  u8 smallPos;
  bigPos = pos / SIZE_BITS;
  smallPos = SIZE_BITS - pos % SIZE_BITS;
  bitCompared = (bitSet_t)1 << smallPos;
  return !!(*(bits + bigPos) & bitCompared);
}
