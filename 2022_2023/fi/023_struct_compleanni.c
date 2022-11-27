#include <stdio.h>
#define DIM 50

typedef struct days {
  int giorno, mese, anno;
} day_t;

int main(int argc, char *argv[]) {
  day_t db_birth[DIM], birth_0;
  int i, count_gm, count_gma;

  scanf("%d %d %d", &birth_0.giorno, &birth_0.mese, &birth_0.anno);
  for (i = 0; i < DIM; i++)
    scanf("%d %d %d", &db_birth[i].giorno, &db_birth[i].mese, &db_birth[i].anno);

  count_gm = 0;
  count_gma = 0;
  for (i = 0; i < DIM; i++)
    if (birth_0.giorno == db_birth[i].giorno, birth_0.mese == db_birth[i].mese) {
      count_gm++;
      if (birth_0.anno == db_birth[i].anno) count_gma++;
    }
  printf("%d %d\n", count_gm, count_gma);
  return 0;
}
