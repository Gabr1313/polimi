#include <stdio.h>

#define LEN 35

int isTypo (char dig[], char voc[]){
  int i, j;

  for (i = j = 0; dig[i] && voc[j]; i++) {
    if (dig[i] == voc[j])
      j++;
  }
  
  return (!voc[j]);
}

void scorriEStampaCorr (char dig[], FILE * dizionario) {
  int count;
  char voc[LEN + 1];
  
  count = 0;
  while ((fscanf(dizionario, "%s", voc)) == 1){
    if (isTypo (dig, voc)) {
      printf("%s\n", voc);
      count ++;
  }
}
  printf("%d alternative\n", count);
}



int main (int argc, char * argv[]){
  FILE * dizionario;

  if (argc == 3) {
    dizionario = fopen(argv[2], "r");
    if (dizionario) {
      scorriEStampaCorr (argv[1], dizionario);
      fclose (dizionario);
    } else 
      printf("File %s non apribile\n", argv[2]);
  } else 
    printf("Uso: %s stringa file\n", argv[0]);

  return 0;
}
    
