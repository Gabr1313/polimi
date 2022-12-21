#include <stdio.h>

#define NAME_LEN 80
#define SIZE_CPY 128

void concatena(FILE *, FILE *, FILE *);

int main(int argc, char *argv[]) {
  char file1Name[NAME_LEN], file2Name[NAME_LEN], fileEndName[NAME_LEN];
  FILE *file1, *file2, *fileEnd;
  int choice;

  scanf("%s", file1Name);
  if ((file1 = fopen(file1Name, "r"))) {
    scanf("%s", file2Name);
    if ((file2 = fopen(file2Name, "r"))) {
      scanf("%s", fileEndName);
      if ((fileEnd = fopen(fileEndName, "w"))) {
        scanf("%d", &choice);
        switch (choice) {
          case 0:
            concatena(file1, file2, fileEnd);
            break;
          case 1:
            concatena(file2, file1, fileEnd);
            break;
        }
        fclose(file1);
        fclose(file2);
        fclose(fileEnd);
      } else
        printf("Problem opening file %s\n", fileEndName);
    } else
      printf("Problem opening file %s\n", file2Name);
  } else
    printf("Problem opening file %s\n", file1Name);

  return 0;
}

void concatena(FILE *file1, FILE *file2, FILE *fileEnd) {
  char cpyBuffer[SIZE_CPY];
  int check;
  do {
    check = fread(cpyBuffer, sizeof(char), SIZE_CPY, file1);
    fwrite(cpyBuffer, sizeof(char), check, fileEnd);
  } while (check == SIZE_CPY);
  do {
    check = fread(cpyBuffer, sizeof(char), SIZE_CPY, file2);
    fwrite(cpyBuffer, sizeof(char), check, fileEnd);
  } while (check == SIZE_CPY);
}
