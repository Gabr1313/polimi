/* # Esercizio 3 - appello 26/01/2022
Scrivere un sottoprogramma che dato un array bidimensionale A di numeri interi di
dimensione NxM e un array b di dimensione inferiore al numero di colonne presenti
nell’array bi-dimensionale, e qualsiasi altro parametro necessario, verifica e
restituisce al chiamante il numero di righe in cui l’array b compare nell’array A.
Se l’array b compare in una riga dell’array A, compare una unica volta. Si assuma che
l’array bidimensionale sia stato dichiarato nel chiamante con dimensione definita con le
direttive
#define N
#define M
Ad esempio, siano dati l’array bidimensionale A e l’array b sotto riportati:
10 4 7 3 8 4 5
2 1 3 8 5 5 9
A: 1 17 6 5 4 11 6 b: 3 5 8
3 7 3 8 3 8 5
1 3 8 2 4 12 16
il sottoprogramma restituisce 2.

prova input mia:
5 7 3 10 4 7 3 8 4 5 2 1 3 8 5 5 9 1 17 6 5 4 11 6 3 7 3 8 3 8 5 1 3 8 2 4 12 16 3 8 5
*/

#include <stdio.h>
#include <stdlib.h>
#define N 100
#define M 100

int find_arr(int[][M], int, int, int[], int);
void populate_mat_vet(char *[], int[][M], int, int, int[], int);

int main(int argc, char *argv[]) {
  int mat[N][M], arr[N];
  int n, m, l;
  n = atoi(argv[1]);
  m = atoi(argv[2]);
  l = atoi(argv[3]);
  populate_mat_vet(argv, mat, n, m, arr, l);

  printf("%d\n", find_arr(mat, n, m, arr, l));

  return 0;
}

int find_arr(int mat[][M], int n, int m, int arr[], int l) {
  int i, m_min, j, k, equal, ris;

  m_min = m - l;
  ris = 0;
  for (i = 0; i < n; ++i) {
    equal = 0;
    for (j = 0; j <= m_min && !equal; ++j) {
      equal = 1;
      for (k = 0; k < l && equal; ++k) equal = (mat[i][j + k] == arr[k]);
      ris += equal;
    }
  }
  return ris;
}

void populate_mat_vet(char *argv[], int mat[][M], int n, int m, int arr[], int l) {
  int i, j;

  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++) mat[i][j] = atoi(argv[4 + i * m + j]);

  for (i = i * m + 4, j = 0; j < l; i++, j++) arr[j] = atoi(argv[i]);
}
