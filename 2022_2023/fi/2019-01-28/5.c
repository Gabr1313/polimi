#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCAN_ERROR -1
#define BASE 10

int getMaxDigit(int);

int fileMaxDigit (FILE * file){
  int val, ris, check;
  check = fread(&val, sizeof(int), 1, file);
  if (check == 1){
    ris = getMaxDigit(val);
  } else 
    ris = SCAN_ERROR;
  return ris;
}

int getMaxDigit(int val){
  int map[BASE], digit, i, maxDigit, repMax;

  val = abs(val);
  memset(map, 0, sizeof(int) * BASE);
  while (val > 0){
    digit = val % BASE;
    map[digit]++;
    val /= BASE;
  }
  
  maxDigit = 0;
  repMax = map[0];
  for (i = 1; i < BASE; i++){
    printf("%d %d | ", map[i], i);
    if (map[i] >= repMax){
      maxDigit = i;
      repMax = map[i];
    }
  }
  
  return maxDigit;
}

int main(int argc, char *argv[]) {
  FILE * file;
  int ris;
  if (argc == 2) {
    file = fopen (argv[1], "r");
    ris = fileMaxDigit(file);
    printf("%d\n", ris);
    fclose (file);
  }
  return 0;
}




