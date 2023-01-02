#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BASE 10
#define SIZE_BITS (sizeof(bitSet_t) * 8)

typedef unsigned char u8;
typedef unsigned long int u64;
typedef u64 bitSet_t;

u64 generatePrimes(bitSet_t **, u64);
void printfArrayUl(bitSet_t *, u64);
u64 findPrimes(bitSet_t *, u64);
u64 crossMultiple(bitSet_t *, u64, u64);
void bit_to0(bitSet_t *, u64);
void bit_AllTo1(bitSet_t *, u64);
u8 bit_getValue(bitSet_t *, u64);

int main(int argc, char *argv[]) {
  u64 maxValue, numberOfPrimes;
  char *check;
  bitSet_t *primesBool;
  if (argc == 2) {
    maxValue = strtoul(argv[1], &check, BASE);
    if (!*check) {
      numberOfPrimes = generatePrimes(&primesBool, maxValue);
      printfArrayUl(primesBool, numberOfPrimes);
      printf("Total: %lu\n", numberOfPrimes);
      free(primesBool);
    } else
      printf("Invalid number\n");
  } else
    printf("Usage: %s number\n", argv[0]);
  return 0;
}

u64 generatePrimes(u64 **primesBool_p, u64 maxValue) {
  u64 numberOfElem, numberOfPrimes, len;
  bitSet_t *primesBool = NULL;
  if (maxValue >= 2) {
    len = maxValue + 1;
    numberOfElem = len / SIZE_BITS + 1;
    primesBool = malloc(sizeof(bitSet_t) * numberOfElem);
    if (primesBool) {
      bit_AllTo1(primesBool, maxValue + 1);
      numberOfPrimes = findPrimes(primesBool, len);
    } else
      printf("generatePrimes: memory allocation problem\n");
  } else
    numberOfPrimes = 0;
  *primesBool_p = primesBool;
  return numberOfPrimes;
}

u64 findPrimes(bitSet_t *primesBool, u64 len) {
  u64 i, numberOfPrimes, crossedNew;
  numberOfPrimes = len;
  for (i = 0; i < 2; i++) {
    bit_to0(primesBool, i);
    numberOfPrimes--;
  }
  for (; i * i < len; i++) {
    if (bit_getValue(primesBool, i)) {
      crossedNew = crossMultiple(primesBool, len, i);
      numberOfPrimes -= crossedNew;
    }
  }
  return numberOfPrimes;
}

u64 crossMultiple(bitSet_t *primesBool, u64 len, u64 multiple) {
  u64 i, crossedNew;
  crossedNew = 0;
  for (i = 2 * multiple; i < len; i += multiple) {
    if (bit_getValue(primesBool, i)) {
      bit_to0(primesBool, i);
      crossedNew++;
    }
  }
  return crossedNew;
}

void printfArrayUl(u64 *primesBool, u64 numberOfPrimes) {
  u64 i, j;
  i = 1;
  for (j = 0; j < numberOfPrimes; j++) {
    for (i++; !bit_getValue(primesBool, i); i++)
      ;
    printf("%lu ", i);
  }
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

