#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  FILE* out;
  int i, val, tot, *val_p;
  if (argc > 1) {
    if ((out = fopen("int.bin", "wb"))) {
      tot = argc - 1;
      fwrite(&tot, 1, sizeof(int), out);
      val_p = &val;
      for (i = 1; i < argc; i++){ 
        val = atoi(argv[i]);
        fwrite(val_p, 1, sizeof(int), out);
      }
      fclose(out);
    } else
      printf("Error managing the file");
  } else
    printf("Usage: %s int int ...\n", argv[0]);
  return 0;
}
