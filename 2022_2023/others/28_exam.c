/* Grazie Michele... */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define REFU "RIFIUTATO"
#define ABSE "ASSENTE"
#define FAIL "RIMANDATO"
#define LODE " e Lode"
#define GRADE_MAX 31
#define GRADE_MIN 18
#define LEN_1 128
#define LEN_2 128

typedef unsigned int u32;

u32 max(u32 n, u32 *v) {
  u32 m = 0;
  for (u32 i = 0; i < n; i++)
    if (v[i] > m) m = v[i];
  return m;
}

int main(int argc, char *argv[]) {
  char matricola[LEN_1], esito[LEN_1], corso[LEN_2];
  u32 cnt[GRADE_MAX + 1];
  memset(cnt, 0, sizeof(cnt));
  u32 vote, absent, failed, refused, total, passed, sum, lenLode;
  total = failed = passed = refused = absent = 0;
  lenLode = strlen(LODE);
  freopen(argv[1], "r", stdin);
  if (argc == 2) {
    while (scanf("%s %s", matricola, esito) != EOF) {
      fgets(corso, LEN_2, stdin);
      if (!strcmp(esito, REFU))
        refused++;
      else if (!strcmp(esito, ABSE))
        absent++;
      else if (!strcmp(esito, FAIL))
        failed++;
      else if ((vote = atoi(esito))){
        cnt[atoi(esito) + !strncmp(corso, LODE, lenLode)]++;
        passed++;
      } else 
        total--; //NON AMMESSO (che e'?)
      total++;
    }
    sum = total - passed;
    printf("\n");
    u32 m = max(GRADE_MAX - GRADE_MIN + 1, cnt + GRADE_MIN);
    for (u32 i = 18; i < 32; i++) {
      printf("%-2u: %-2u  ", i, cnt[i]);
      for (u32 j = 0; j < cnt[i]; j++) printf("*");
      for (u32 j = 0; j < m - cnt[i]; j++) printf(" ");
      printf("  better than %5.2f%%", sum * 100.f / total);
      sum += cnt[i];
      printf("\n");
    }
    printf("\n");
    printf("total:   %-3u\n", total);
    printf("absents: %-3u (%.2f%%)\n", absent, absent * 100.f / total);
    printf("refused: %-3u (%.2f%%)\n", refused, refused * 100.f / total);
    printf("fails:   %-3u (%.2f%%)\n", failed, failed * 100.f / total);
    printf("passed:  %-3u (%.2f%%)\n", passed, passed * 100.f / total);
  } else
    printf("Usage: %s inputFile\n", argv[0]);
  return 0;
}
