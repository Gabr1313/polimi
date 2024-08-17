#include <stdio.h>
#define GIORNI 20
#define OPZ_1 "perdita"
#define OPZ_2 "capitale insufficente"

int main(int argc, char *argv[]) {
  int cambi[GIORNI], iTemp, guadagno, guadagnoTemp, capI, preI, iStart, iFinish, i, found;

  scanf("%d", &preI);
  for (i = 0; i < GIORNI; i++) scanf("%d", &cambi[i]);
  scanf("%d", &capI);

  found = 0;
  for (i = 0; i < GIORNI && !found; i++) {
    if (preI <= capI) {
      iStart = i;
      iFinish = i;
      guadagno = cambi[i];
      guadagnoTemp = cambi[i];
      iTemp = i;
      found = 1;
    }
    preI += cambi[i];
  }

  for (; i < GIORNI; i++) {
    guadagnoTemp += cambi[i];
    if (cambi[i] > guadagnoTemp && preI <= capI) {
      guadagnoTemp = cambi[i];
      iTemp = i;
    }
    if (guadagnoTemp > guadagno) {
      guadagno = guadagnoTemp;
      iStart = iTemp;
      iFinish = i;
    }
    preI += cambi[i];
  }

  if (found)
    if (guadagno > 0)
      printf("%d %d", iStart, iFinish);
    else
      printf(OPZ_1);

  else
    printf(OPZ_2);
  printf("\n");
  return 0;
}
