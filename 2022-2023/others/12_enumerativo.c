#include <stdio.h>

typedef enum {mon, tue, wed, thu, fri, sat, sun} week_t;

int main(){
  week_t pos;

  scanf("%d", &pos);
  /* il compilatore da problemi, ma non saprei come fare altrimenti
  scanf("%c", &pos);
  sarebbe identico ai fini del programma */

  switch (pos) {
    case mon:
      printf("day0");
      break;
    case tue:
      printf("day1");
      break;
    case wed:
      printf("day2");
      break;
    case thu:
      printf("day3");
      break;
    case fri:
      printf("day4");
      break;
    case sat:
      printf("day5");
      break;
    case sun:
      printf("day6");
      break;
    default:
      printf("Invalid code");
  }
  printf("\n");

  printf("%d\n", pos - pos);
  printf("%d\n", pos + pos);

  return 0;
}

/* #include <stdio.h>

enum week { Mon, Tue, Wed, Thur, Fri, Sat, Sun };

int main() {
  enum week day;
  day = Wed;
  printf("%d\n", day);
  return 0;
} */
