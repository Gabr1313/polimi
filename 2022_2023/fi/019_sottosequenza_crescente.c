#include <stdio.h>
#define STOP 0

int main(int argc, char* argv[]) {
  int val, max, pre, counter;

  scanf("%d", &val);
  if (val <= STOP)
    max = 0;
  else {
    pre = val;
    counter = 1;
    max = 1;
    scanf("%d", &val);

    while (val > STOP) {
      if (val > pre) {
        counter++;
        if (counter > max) max = counter;
      } else
        counter = 1;
      pre = val;
      scanf("%d", &val);
    }
  }

  printf("%d\n", max);
  return 0;
}
