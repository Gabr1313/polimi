#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 10

int cifra(int val) {
  int map[BASE], digit, i, digMax;
  memset(map, 0, sizeof(int) * BASE);
  while (val > 0) {
    digit = val % BASE;
    map[digit]++;
    val /= BASE;
  }
  digMax = 0;
  for (i = 1; i < BASE; i++) {
    if (map[digMax] <= map[i]) digMax = i;
  }
  return digMax;
}

int cifraStrana(int val) {
  int map[BASE], digit, i, digMax;
  memset(map, 0, sizeof(int) * BASE);
  while (val > 0) {
    digit = val % BASE;
    map[digit]++;
    val /= BASE;
  }
  digMax = 0;
  for (i = 1; i < BASE; i++) {
    if (map[digMax] < map[i])
      digMax = i;
    else if (map[digMax] == map[i]) {
      if (digMax % 2 == 0) {
        if (i % 2 == 0 && i < digMax) digMax = i;
      } else {
        if (i % 2 == 0)
          digMax = i;
        else if (i > digMax)
          digMax = i;
      }
    }
  }
  return digMax;
}

int main(int argc, char* argv[]) {
  if (argc == 2) {
    printf("%d\n", cifra(atoi(argv[1])));
    printf("%d\n", cifraStrana(atoi(argv[1])));
  } else
    printf("Usage: %s int\n", argv[0]);
  return 0;
}
