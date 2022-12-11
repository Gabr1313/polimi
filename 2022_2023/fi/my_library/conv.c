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

#define COUNT_SHIFT(num, count)                                 \
  if ((num) < 0)                                                \
    while ((num)&0x80000000) { /* while the first bit is one */ \
      (num) <<= 1;                                              \
      (count)++;                                                \
    }                                                           \
  else                                                          \
    while (~(num)&0x80000000) {                                 \
      (num) <<= 1;                                              \
      (count)++;                                                \
    }

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                                           \
  (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'),     \
      (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), \
      (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

#define PRINTF_BYTE_4(num)                                                               \
  printf(BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN    \
                                " " BYTE_TO_BINARY_PATTERN "\n",                         \
         BYTE_TO_BINARY(num >> 24), BYTE_TO_BINARY(num >> 16), BYTE_TO_BINARY(num >> 8), \
         BYTE_TO_BINARY(num))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help(char *);
void wrong_input(char *);
int convertion(char *, char *, char *, char *, char *, char *, char *, int *);
int operation(char *, char *, char *, char *, char *, char *, char *, char *, char *, char *,
              int *);
int print_num(char *, char, char, int);
int check_of(int, int, int);

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
  char type, format_1, format_2;
  int num; /* also floats have 32 bit, so there's no problem */
  int i;
  char *check;

  TO_CHAR(s1, type, s0);
  TO_CHAR(s2, format_1, s0);
  TO_CHAR(s4, format_2, s0);

  switch (format_1) {
    case BINARY:
      TO_NUM(num, s3, check, 2);
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
          for (i = 1; s3[i]; i++)
            if (s3[i] < '0' || s3[i] > '9') {
              wrong_input(s0);
              return 1;
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
  switch (format) {
    case BINARY:
      PRINTF_BYTE_4(num);
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
          if (check_of(num1, num2, ris)) printf("OF\n");
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
          ris = num1 - num2;
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

int check_of(int a, int b, int c) {
  int count_a = 0, count_b = 0, count_c = 0;

  if ((a < 0 && b > 0) || (a > 0 && b < 0) || a == 0 || b == 0) return 0;

  COUNT_SHIFT(a, count_a);
  COUNT_SHIFT(b, count_b);
  COUNT_SHIFT(c, count_c);

  return (count_c < count_b && count_c < count_a);
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
