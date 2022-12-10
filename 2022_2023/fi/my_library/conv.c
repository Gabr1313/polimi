#define HELP "-h"
#define INTEGER 'i'
#define FLOAT 'f'
#define BINARY 'b'
#define DECIMAL 'd'
#define HEXADECIMAL 'x'
#define PLUS '+'
#define MINUS '-'

#define TO_CHAR(str, ch, err) \
  do {                        \
    if (strlen(str) == 1)     \
      sscanf(str, "%c", &ch); \
    else {                    \
      wrong_input(err);       \
      return;                 \
    }                         \
  } while (0)

#define TO_NUM(num, str, check, base) \
  do {                                \
    num = strtol(str, &check, base);  \
    if (*check) {                     \
      wrong_input(s0);                \
      return;                         \
    }                                 \
  } while (0)

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
void convertion(char *, char *, char *, char *, char *);
void operation(char *, char *, char *, char *, char *, char *, char *);

int main(int argc, char *argv[]) {
  switch (argc) {
    case 2:
      if (!strcmp(argv[1], HELP))
        help(argv[0]);
      else
        wrong_input(argv[0]);
      break;
    case 5:
      convertion(argv[0], argv[1], argv[2], argv[3], argv[4]);
      break;
    case 7:
      operation(argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
      break;
    default:
      wrong_input(argv[0]);
  }

  return 0;
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

void wrong_input(char *s) {
  printf("Wrong input. For help digit:\n");
  printf("%s %s\n", s, HELP);
}

void convertion(char *s0, char *s1, char *s2, char *s3, char *s4) {
  char type, format_1, format_2;
  int num; /* essendo anche i float a 32 bit, non ho problemi */
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
            return;
          }
          for (i = 1; s3[i]; i++)
            if (s3[i] < '0' || s3[i] > '9') {
              wrong_input(s0);
              return;
            }

          sscanf(s3, "%f", (float *)&num);
          break;
        default:
          wrong_input(s0);
          return;
      }
      break;
    case HEXADECIMAL:
      TO_NUM(num, s3, check, 16);
      break;
    default:
      wrong_input(s0);
      return;
  }

  switch (format_2) {
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
          return;
      }
      break;
    case HEXADECIMAL:
      printf("%X\n", num);
      break;
    default:
      wrong_input(s0);
      return;
  }
}

void operation(char *s0, char *s1, char *s2, char *s3, char *s4, char *s5, char *s6) { /* TODO */
  printf("TO DO\n");
}
