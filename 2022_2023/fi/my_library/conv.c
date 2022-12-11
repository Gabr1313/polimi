#define HELP "-h"
#define INTEGER 'i'
#define FLOAT 'f'
#define BINARY 'b'
#define DECIMAL 'd'
#define HEXADECIMAL 'x'
#define PLUS '+'
#define MINUS '-'

#define TO_CHAR(str, ch, err)     \
  do {                            \
    if (strlen(str) == 1)         \
      sscanf((str), "%c", &(ch)); \
    else {                        \
      wrong_input(err);           \
      return 1;                   \
    }                             \
  } while (0)

#define TO_NUM(num, str, check, base)        \
  do {                                       \
    (num) = strtol((str), &(check), (base)); \
    if (*(check)) {                          \
      wrong_input(s0);                       \
      return 1;                              \
    }                                        \
  } while (0)

#define COUNT_SHIFT(num, count, t)                              \
  do {                                                          \
    count = 0;                                                  \
    t = num;                                                    \
    if ((t) < 0)                                                \
      while ((t)&0x80000000) { /* while the first bit is one */ \
        (count)++;                                              \
        (t) <<= 1;                                              \
      }                                                         \
    else                                                        \
      while (~(t)&0x80000000) {                                 \
        (count)++;                                              \
        (t) <<= 1;                                              \
      }                                                         \
  } while (0)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help(char *);
void wrong_input(char *);
int convertion(char *, char *, char *, char *, char *, char *, char *, int *);
int operation(char *, char *, char *, char *, char *, char *, char *, char *, char *, char *,
              int *);
int print_num(char *, char, char, int);
int check_of(char *, char *, char *, char *, char *, int, int, int);

int main(int argc, char *argv[]) {
  char format, type, check = 0;
  int num;
  switch (argc) {
    case 2:
      if (!strcmp(argv[1], HELP))
        help(argv[0]);
      else
        wrong_input(argv[0]);
      break;

    case 5:
      check = convertion(argv[0], argv[1], argv[2], argv[3], argv[4], &type, &format, &num);
      if (check) return 0;
      print_num(argv[0], type, format, num);
      break;

    case 8:
      check = operation(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
                        &type, &format, &num);
      if (check) return 0;
      print_num(argv[0], type, format, num);
      break;

    default:
      wrong_input(argv[0]);
  }

  return 0;
}

void wrong_input(char *s) {
  printf("Wrong input. For help digit:\n");
  printf("%s %s\n", s, HELP);
}

int convertion(char *s0, char *s1, char *s2, char *s3, char *s4, char *type_in, char *format_in,
               int *num_in) {
  char type, format_1, format_2, point_counter;
  int num; /* also floats have 32 bit, so there's no problem */
  int i;
  char *check;

  TO_CHAR(s1, type, s0);
  TO_CHAR(s2, format_1, s0);
  TO_CHAR(s4, format_2, s0);

  switch (format_1) {
    case BINARY:
      if (s3[0] == '0' || s3[0] == '+' || s3[0] == '-')
        num = 0;
      else if (s3[0] == '1')
        num = -1;
      else {
        wrong_input(s0);
        return 1;
      }

      for (i = 1; s3[i]; i++) {
        num <<= 1;
        if (s3[i] == '1')
          num += 1;
        else if (s3[i] != '0') {
          wrong_input(s0);
          return 1;
        }
      }
      if (s3[0] == '-') num = -num;
      break;

    case DECIMAL:
      switch (type) {
        case INTEGER:
          TO_NUM(num, s3, check, 10);
          break;

        case FLOAT:
          if ((s3[0] < '0' || s3[0] > '9') && s3[0] != '+' && s3[0] != '-') {
            wrong_input(s0);
            return 1;
          }
          point_counter = 0;
          for (i = 1; s3[i]; i++) {
            if (s3[i] == '.') {
              if (point_counter) {
                wrong_input(s0);
                return 1;
              }
              point_counter = 1;
              continue;
            }
            if ((s3[i] < '0' || s3[i] > '9')) {
              printf("arrived %d\n", s3[i]);
              wrong_input(s0);
              return 1;
            }
          }
          sscanf(s3, "%f", (float *)&num);
          break;

        default:
          wrong_input(s0);
          return 1;
      }
      break;

    case HEXADECIMAL:
      TO_NUM(num, s3, check, 16);
      break;

    default:
      wrong_input(s0);
      return 1;
  }

  *format_in = format_2;
  *type_in = type;
  *num_in = num;
  return 0;
}

int print_num(char *s0, char type, char format, int num) {
  int tmp;
  char count, i, tot;
  switch (format) {
    case BINARY:
      switch (type) {
        case INTEGER:
          COUNT_SHIFT(num, count, tmp);
          tmp = num << (--count); /* also print the sign */
          tot = 32 - count;
          for (i = 0; i < tot; i++, tmp <<= 1) printf("%d", tmp & 0x80000000 ? 1 : 0);
          printf("\n");
          tmp <<= 1;
          break;
        case FLOAT:
          tmp = num;
          printf("%d", tmp & 0x80000000 ? 1 : 0);
          tmp <<= 1;
          printf(" ");
          for (i = 0; i < 8; i++, tmp <<= 1) printf("%d", tmp & 0x80000000 ? 1 : 0);
          printf(" ");
          for (i = 0; i < 23; i++, tmp <<= 1) printf("%d", tmp & 0x80000000 ? 1 : 0);
          printf("\n");
          break;
        default:
          wrong_input(s0);
          return 1;
      }
      break;

    case DECIMAL:
      switch (type) {
        case INTEGER:
          printf("%d\n", num);
          break;

        case FLOAT:
          printf("%g\n", *(float *)&num);
          break;

        default:
          wrong_input(s0);
          return 1;
      }
      break;

    case HEXADECIMAL:
      printf("%X\n", num);
      break;

    default:
      wrong_input(s0);
      return 1;
  }
  return 0;
}

int operation(char *s0, char *s1, char *s2, char *s3, char *s4, char *s5, char *s6, char *s7,
              char *type_in, char *format_in, int *num_in) {
  char type, format, operator, check;
  int num1, num2, ris;
  float num1f, num2f, risf;

  TO_CHAR(s4, operator, s0);

  check = convertion(s0, s1, s2, s3, s7, &type, &format, &num1);
  if (check) return 1;
  check = convertion(s0, s1, s5, s6, s7, &type, &format, &num2);
  if (check) return 1;

  switch (operator) {
    case PLUS:
      switch (type) {
        case INTEGER:
          ris = num1 + num2;
          if (check_of(s0, s2, s3, s5, s6, num1, num2, ris)) printf("OF\n");
          break;

        case FLOAT:
          memcpy(&num1f, &num1, 4);
          memcpy(&num2f, &num2, 4);
          risf = num1f + num2f;
          memcpy(&ris, &risf, 4);
          break;

        default:
          wrong_input(s0);
          return 1;
      }
      break;

    case MINUS:
      switch (type) {
        case INTEGER:
          num2 = -num2;
          ris = num1 + num2;
          if (check_of(s0, s2, s3, s5, s6, num1, num2, ris)) printf("OF\n");
          break;

        case FLOAT:
          memcpy(&num1f, &num1, 4);
          memcpy(&num2f, &num2, 4);
          risf = num1f - num2f;
          memcpy(&ris, &risf, 4);
          break;

        default:
          wrong_input(s0);
          return 1;
      }
      break;

    default:
      wrong_input(s0);
      return 1;
  }

  *type_in = type;
  *format_in = format;
  *num_in = ris;
  return 0;
}

int check_of(char *s0, char *s2, char *s3, char *s5, char *s6, int num1, int num2, int ris) {
  int tmp;
  char count_1, count_2, count_r, type;

  if ((num1 < 0 && num2 > 0) || (num1 > 0 && num2 < 0) || num1 == 0 || num2 == 0) return 0;

  TO_CHAR(s2, type, s0);
  if (type == 'b')
    count_1 = 33 - strlen(s3);
  else
    COUNT_SHIFT(num1, count_1, tmp);

  TO_CHAR(s5, type, s0);
  if (type == 'b')
    count_2 = 33 - strlen(s6);
  else
    COUNT_SHIFT(num2, count_2, tmp);

  COUNT_SHIFT(ris, count_r, tmp);

  return (count_r < count_1 && count_r < count_2);
}

void help(char *s) {
  printf("Basic usage:\n");
  printf("%s <type> <format> <number> <format>\n", s);
  printf("Valid <type>:\n");
  printf("  i = integer\n");
  printf("  f = float\n");
  printf("\n");
  printf("Valid <format>:\n");
  printf("  b = binary\n");
  printf("  d = decimal\n");
  printf("  x = hexadecimal\n");
  printf("\n");

  printf("With <format> b and x you can also use the MS base putting a + or - before the number\n");
  printf("If not specified the default base is 2c2");
  printf("\n");

  printf("For example:\n");
  printf("%s f d 10 x\n", s);
  printf("Converts the float 10 form decimal to hexadecimal\n");
  printf("\n");

  printf("Advanced usage:\n");
  printf("%s <type> <format> <number> <sign> <format> <number> <format>\n", s);
  printf("Valid <sign>:\n");
  printf("  +\n");
  printf("  -\n");
  printf("\n");

  printf("For example:\n");
  printf("%s i d 10 - x 1B b\n", s);
  printf("Subtraction with integers: decimal 10, hexadecimal 1B, prints the result in binary\n");
}
