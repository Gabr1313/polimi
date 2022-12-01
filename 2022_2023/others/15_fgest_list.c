#include <stdio.h>
#include <string.h>

#include "clist.h"

void fprintfline(FILE *, clist_t *);

int main(int argc, char **argv) {
  FILE *in, *out;
  clist_t *line = NULL;
  char c;
  int i, check;

  if (argc == 3) {
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    i = 0;
    check = 1;
    while (check != EOF) {
      check = fscanf(in, "%c", &c);
      while (c != '\n' && check != EOF) {
        line = cappend(line, c);
        check = fscanf(in, "%c", &c);
      }
      if (check != EOF) {
        fprintf(out, "%3d>> ", ++i);
        fprintfline(out, line);
      }

      cfree(line);
      line = NULL;
    }

    fclose(in);
    fclose(out);
  } else
    printf("Usage: %s input_file output_file\n", argv[0]);

  return 0;
}

void fprintfline(FILE *out, clist_t *el) {
  while (el) {
    fprintf(out, "%c", el->val);
    el = el->next;
  }
  fprintf(out, "\n\n");
}
