#include <stdio.h>
#include <math.h>

void meanVarStd(int seq[], int len, float *med_p, float *var_p, float *dev_p) {
  int i, sum;
  float p, sumF;

  for (i = sum = 0; i < len; i++) sum += seq[i];
  *med_p = (float)sum / len;

  for (i = sumF = 0; i < len; i++) {
    p = *med_p - seq[i];
    sumF += p * p;
  }
  *var_p = sumF / len;
  *dev_p = sqrt(*var_p);
}

void meanVarStd2(int seq[], int len, float *med_p, float *var_p, float *dev_p) {
  int i, j, sum, sumPos;
  float p, sumF, medPos;

  for (i = sum = 0; i < len; i++) {
    sum += seq[i];
    if (seq[i] > 0) {
      sumPos += seq[i];
      j++;
    }
  }
  *med_p = (float)sum / len;
  medPos = (float)sumPos / j;

  for (i = sumF = 0; i < len; i++) {
    if (seq[i] > 0) {
      p = medPos - seq[i];
      sumF += p * p;
    }
  }
  *var_p = sumF / j;
  *dev_p = sqrt(*var_p);
}

#define LEN 10

int main(void) {
  int i, v[LEN];
  float med, var, dev;

  for (i = 0; i < LEN; i++) scanf("%d", &v[i]);
  meanVarStd(v, LEN, &med, &var, &dev);
  printf("%10f %10f %10f\n", med, var, dev);
  meanVarStd2(v, LEN, &med, &var, &dev);
  printf("%10f %10f %10f\n", med, var, dev);

  return 0;
}
