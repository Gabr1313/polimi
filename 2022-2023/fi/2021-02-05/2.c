#include <stdio.h>

#define NOT_FOUND -1

int baricentro(int arr[], int len) {
  int i, found, sumEnd, sumStart;

  for (i = sumEnd = 0; i < len; i++) sumEnd += arr[i];

  len--;
  for (i = found = sumStart = 0; i < len && !found; i++) {
    sumStart += arr[i];
    sumEnd -= arr[i];
    found = (sumStart == sumEnd);
  }

  if (found)
    i--;
  else
    i = NOT_FOUND;

  return i;
}

int main(void) {
  int arr[] = {2, 1, 4, 1, 1, 1, 1, 1, 1, 1};

  printf("%d\n", baricentro(arr, 10));

  return 0;
}
