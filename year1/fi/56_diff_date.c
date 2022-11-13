/*
calcola i giorni di differenza tra 2 date
 */
#include <stdio.h>

#define GIORNI_ANNO 365
#define MESE_ANNO 12 

typedef struct datas{
    int giorno, mese, anno;
} data_T;


int diffGiorni (data_T *, data_T *);
int dayInMonth (int, int);
int giorniFineAnno (data_T *);
int giorniFineMese (data_T *);
int giorniInizioAnno (data_T *);
int isBisestile (int);
int contaGiorniAnni(int, int);

int main (int argc, char *argv[]){
    int ris;
    data_T day1, day2;

    scanf("%d %d %d", &day1.giorno, &day1.mese, &day1.anno);
    scanf("%d %d %d", &day2.giorno, &day2.mese, &day2.anno);

    if (day2.anno > day1.anno || (day2.anno == day1.anno && day2.mese > day1.mese) 
        || (day2.anno == day1.anno && day2.mese == day1.mese && day2.giorno >= day1.giorno))
        ris = diffGiorni(&day1, &day2);
    else 
        ris = - diffGiorni(&day2, &day1);

    printf("%d\n", ris);
    return 0;
}

int diffGiorni (data_T *day1, data_T *day2){
    int count, diff;

    count = 0;
    count += giorniFineAnno(day1);
    count += giorniInizioAnno(day2);
    diff = day2 -> anno - day1 -> anno; 
    if (!diff)
        count -= (GIORNI_ANNO + isBisestile(day1 -> anno));
    else if (diff > 1)
        count += (contaGiorniAnni (day1 -> anno + 1, day2 -> anno - 1));

    return count;
}

int giorniFineAnno (data_T *day){
    int count, i;
    
    count = giorniFineMese(day);
    for (i = day -> mese + 1; i <= MESE_ANNO; i++)
        count += dayInMonth (i, day -> anno);

    return count;
}

int giorniFineMese (data_T *day){
    int count, fine;

    fine = dayInMonth(day -> mese, day -> anno);
    count = fine - day -> giorno;

    return count;
}

int dayInMonth (int month, int year){
    int count;

    if (month == 2){
        if (isBisestile (year))
            count = 29;
        else 
            count = 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11)
        count = 30;
    else 
        count = 31;

    return count;
}

int giorniInizioAnno (data_T *day){
    int count, i;
    
    count = day -> giorno;
    for (i = day -> mese - 1; i > 0; i--)
        count += dayInMonth (i , day -> anno);

    return count;
}

int isBisestile(int anno){
    return ((anno % 4 == 0 && anno % 100 != 0) || anno % 400 == 0);
}

int contaGiorniAnni(int anno1, int anno2){
    int count, diff, anno1_4, anno1_100, anno1_400;

    count = GIORNI_ANNO * (anno2 - anno1 + 1);
    diff = anno2 - anno1;
    count += diff / 4;
    count -= diff / 100;
    count += diff / 400;

    anno1_4 = anno1 % 4;
    anno1_100 = anno1 % 100;
    anno1_400 = anno1 % 400;
    if (anno1_4 == 0 || anno1_4 + diff % 4 >= 4)
        count ++;
    if (anno1_100 == 0 || anno1_100 + diff % 100 >= 100)
        count --;
    if (anno1_400 == 0 || anno1_400 + diff % 400 >= 400)
        count ++;

    return count;
}
