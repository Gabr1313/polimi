#include <stdio.h>
#include <string.h>

#define FILE_MAX 100
#define LINE_MAX 3 

int main() {
  FILE *in, *out;
  char in_name[FILE_MAX + 1], out_name[FILE_MAX + 1], line[LINE_MAX + 1], *status;
  int i;

  scanf("%s", in_name);
  scanf("%s", out_name);

  in = fopen(in_name, "r");
  out = fopen(out_name, "w");

  for (i = 0, status = fgets(line, LINE_MAX + 1, in); status;
       status = fgets(line, LINE_MAX + 1, in)) {
    if (line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = 0;
    fprintf(out, "%3d>> %s\n\n", ++i, line);
  }

  fclose(in);
  fclose(out);

  return 0;
}
