/*
 * calcola i giorni tra 2 date
 */

#include <stdio.h>

#define GIORNI_MESI \
  { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 }
#define GIORNI_ANNO 365

typedef struct datas {
  int giorno, mese, anno;
} data_t;

int diffGiorni(data_t *, data_t *);
int giorniInizioAnno(data_t *);
int contaGiorniAnni(int, int);
int contaBisestili(int, int);

int main(int argc, char *argv[]) {
  int ris;
  data_t day1, day2;
  scanf("%d %d %d", &day1.giorno, &day1.mese, &day1.anno);
  scanf("%d %d %d", &day2.giorno, &day2.mese, &day2.anno);
  if ((day1.anno < day2.anno) ||
      (day1.anno == day2.anno && day1.mese < day2.mese) ||
      (day1.anno == day2.anno && day1.mese == day2.mese &&
       day1.giorno <= day2.giorno))
    ris = diffGiorni(&day1, &day2);
  else
    ris = -diffGiorni(&day2, &day1);
  printf("%d\n", ris);
  return 0;
}

int diffGiorni(data_t *day1, data_t *day2) {
  int years, days1, days2, total;
  days1 = giorniInizioAnno(day1);
  days2 = giorniInizioAnno(day2);
  years = contaGiorniAnni(day1->anno, day2->anno);
  total = years + days2 - days1;
  return total;
}

int giorniInizioAnno(data_t *day) {
  int count;
  int giorniMesiInizio[] = GIORNI_MESI;
  count = day->giorno;
  count += giorniMesiInizio[day->mese - 1];
  count +=
      (((day->anno % 4 == 0 && day->anno % 100 != 0) || day->anno % 400 == 0) &&
       (day->mese > 2));
  return count;
}

int contaGiorniAnni(int anno1, int anno2) {
  int count;
  count = GIORNI_ANNO * (anno2 - anno1);
  if (anno1 != anno2) {
    count += contaBisestili(anno1, anno2 - 1);
  }
  return count;
}

int contaBisestili(int anno1, int anno2) {
  int count, diff;
  diff = anno2 - anno1;
  count = diff / 4;
  count -= diff / 100;
  count += diff / 400;
  if (anno1 % 4 == 0 || anno1 % 4 + diff % 4 >= 4) count++;
  if (anno1 % 100 == 0 || anno1 % 100 + diff % 100 >= 100) count--;
  if (anno1 % 400 == 0 || anno1 % 400 + diff % 400 >= 400) count++;
  return count;
}
