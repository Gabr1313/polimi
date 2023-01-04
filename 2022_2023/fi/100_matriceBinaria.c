/* matrice di interi 1000x1000 di 0 e 1
trovare la sottomatrice quadrata piu' grande formata da soli 1
resituirne l'ordine */

#include <stdio.h>

#define DIM 1000

int checkColonna(int mat[DIM][DIM], int colonna, int rigaInizio, int rigaFine) {
  int i, check;
  for (i = rigaInizio, check = 1; check && i <= rigaFine; i++) {
    check = mat[i][colonna];
  }
  return check;
}

int checkRiga(int mat[DIM][DIM], int riga, int colonnaInizio, int colonnaFine) {
  int i, check;
  for (i = colonnaInizio, check = 1; check && i <= colonnaFine; i++) {
    check = mat[riga][i];
  }
  return check;
}

int trovaOrdine(int mat[DIM][DIM], int nRighe, int nColonne, int rigaInizio,
                int colonnaInizio) {
  int ok, ordine, rigaFine, colonnaFine;
  ordine = 0;
  colonnaFine = colonnaInizio;
  rigaFine = rigaInizio;
  while (ok && (++colonnaFine < nColonne) && (++rigaFine < nRighe)) {
    ordine++;
    ok = (checkColonna(mat, colonnaFine, rigaInizio, rigaFine) &&
          checkRiga(mat, rigaFine, colonnaInizio, colonnaFine - 1));
  }
  return (ok ? ordine : ordine - 1);
}

int ordine(int mat[DIM][DIM], int nRighe, int nColonne) {
  int ordineRis, ordine, i, j;
  ordineRis = 0;
  for (i = 0; i < nRighe; i++)
    for (j = 0; j < nColonne; j++)
      if (mat[i][j]) {
        ordine = trovaOrdine(mat, nRighe, nColonne, i, j);
        if (ordine > ordineRis) ordineRis = ordine;
      }
  return ordineRis;
}
