#include <stdio.h>

void view_vec_int(int[], int);
void view_vec_float(float[], int);
void pop_vec_int(int[], int);
void pop_vec_float(float[], int);

void view_vec_int(int v[], int len) {
  int i;
  for (i = 0; i < len; i++) printf("%d ", v[i]);
  printf("\n");
}

void view_vec_float(float v[], int len) {
  int i;
  for (i = 0; i < len; i++) printf("%g ", v[i]);
  printf("\n");
}

void pop_vec_int(int v[], int len) {
  int i;
  for (i = 0; i < len; i++) scanf("%d", &v[i]);
}

void pop_vec_float(float v[], int len) {
  int i;
  for (i = 0; i < len; i++) scanf("%f", &v[i]);
}
