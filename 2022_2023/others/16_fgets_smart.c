#include <stdio.h>
#include <string.h>

#define LINE_MAX 127

int main(int argc, char *argv[]) {
  FILE *in, *out;
  char line[LINE_MAX + 1], *status;
  int i, new;

  if (argc == 3) {
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    new = 1;
    i = 0;
    for (status = fgets(line, LINE_MAX + 1, in); status; status = fgets(line, LINE_MAX + 1, in)) {
      if (new) fprintf(out, "%3d>> ", ++i);
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = 0;
        fprintf(out, "%s\n\n", line);
        new = 1;
      } else {
        fprintf(out, "%s", line);
        new = 0;
      }
    }

  } else
    printf("Usage: %s input_file output_file\n", argv[0]);

  return 0;
}
