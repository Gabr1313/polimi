/*
lavoro a gruppi
sicuramente molto migliorabile,
ma una prima esperienza apprezabile
(io mi sono dedicato alle funzioni new_game e print)
*/
#define DIM 9
#define BLOCK 3

#define OPTIONS 7

#include <stdio.h>

void menu(void);                            /* stampa menu OK */
int choose(void);                           /* scelta dal menu OK */
int check(int[DIM][DIM]);                   /* controlla la validità dell'input */
void new_game(int[DIM][DIM]);               /* nuova partita OK */
void insert(int[DIM][DIM]);                 /* inserisci valore OK*/
void delete (int[DIM][DIM], int[DIM][DIM]); /* rimuovi valore, vuole entrambe le matrici OK*/
void print(int[DIM][DIM], int[DIM][DIM]);   /* stampa input OK*/
void load(int[DIM][DIM], int[DIM][DIM]);    /* copia matrici; se NULL, prende da input OK */
int complete(int[DIM][DIM]);                /* controlla se la partita è finita OK*/
int isempty(int[DIM][DIM]);                 /* controlla se la partita è vuota OK */
void clear(int[DIM][DIM]);                  /* svuota la matrice OK */

int main(int argc, char *argv[]) {
  int initial[DIM][DIM], current[DIM][DIM];
  int choice;
  clear(initial);
  do {
    if (choice == 1 || isempty(initial)) {
      new_game(initial);
      if (!check(initial)) {
        fprintf(stderr, "ERROR: invalid input\n");
        clear(initial);
      } else
        load(initial, current);
    } else if (choice == 2) {
      insert(current);
    } else if (choice == 3) {
      delete (current, initial);
    } else if (choice == 4) {
      if (check(current)) {
        if (complete(current))
          printf("CORRECT\n");
        else
          printf("VALID\n");
      } else {
        printf("WRONG\n");
      }
    } else if (choice == 5) {
      load(NULL, current);
      if (check(current)) {
        if (complete(current))
          printf("CORRECT\n");
        else
          printf("VALID\n");
      } else {
        printf("WRONG\n");
      }
    } else if (choice == 6) {
      load(initial, current);
    }
    print(current, initial);
    if (complete(current) && check(current)) {
      printf("CONGRATULATIONS!\n");
      clear(initial);
    }
  } while ((isempty(initial) && !isempty(current)) || (choice = choose()));
  return 0;
}

/* Utilità: */
void get_matrix(int m[DIM][DIM]) { new_game(m); }
int validcoord(int row, int col, int mat[DIM][DIM]) {
  int ris;
  ris = 1;
  if (row - 1 < 0 || row - 1 > DIM - 1) {
    ris = 0;
    printf("riga non valida  (tra 1 e 9)\n");
  }
  if (col - 1 < 0 || col - 1 > DIM - 1) {
    ris = 0;
    printf("colonna non valida  (tra 1 e 9)\n");
  }
  if (ris && mat[row - 1][col - 1]) { /*Controlla che non ci sia già stato un errore e
                                     che la casella non sia occupata da un val!=0*/
    printf("coordinate non valide: casella non selezionabile\n");
    ris = 0;
  }
  return ris;
}
int validval(int val) {
  int ris;
  if (val < 1 || val > 9) {
    printf("valore non ammissibile (tra 1 e 9)\n");
    ris = 0;
  } else
    ris = 1;
  return ris;
}

int isempty(int mat[DIM][DIM]) {
  int i, j, ris;
  ris = 1;
  for (i = 0; i < DIM && ris; i++) {
    for (j = 0; j < DIM && ris; j++) {
      if (mat[i][j] != 0) {
        ris = 0;
      }
    }
  }
  return ris;
}

int complete(int mat[DIM][DIM]) {
  int i, j, ris;
  ris = 1;
  for (i = 0; i < DIM && ris; i++) {
    for (j = 0; j < DIM && ris; j++) {
      if (mat[i][j] == 0) {
        ris = 0;
      }
    }
  }
  return ris;
}

void clear(int mat[DIM][DIM]) {
  int i, j;
  for (i = 0; i < DIM; i++)
    for (j = 0; j < DIM; j++) mat[i][j] = 0;
}

void menu() {
  printf("\nSeleziona una opzione:\n");
  printf("1 - avvia una nuova partita\n");
  printf("2 - inserisci valore\n");
  printf("3 - cancella valore\n");
  printf("4 - verifica la soluzione attuale\n");
  printf("5 - carica una soluzione e verificala\n");
  printf("6 - riavvia partita attuale\n");
  printf("0 - esci\n");
}

int choose(void) {
  int scelta;
  do {
    menu();
    fflush(stdin);
    printf("Inserisci il numero corrispondente: ");
    scanf("%d", &scelta);
  } while (scelta < 0 || scelta >= OPTIONS);
  return scelta;
}

void load(int from[DIM][DIM], int to[DIM][DIM]) {
  int i, j;
  if (from == NULL) {
    get_matrix(to);
  } else {
    for (i = 0; i < DIM; i++) {
      for (j = 0; j < DIM; j++) {
        to[i][j] = from[i][j];
      }
    }
  }
}

void new_game(int m[DIM][DIM]) {
  char c;
  char p[DIM * DIM + 1];
  int i, j, k;

  fflush(stdin);
  scanf("%s", p);
  k = 0;
  for (i = 0; i < DIM; i++) {
    for (j = 0; j < DIM; j++) {
      c = p[k++];
      if (c >= '0' && c <= '9')
        m[i][j] = c - '0';
      else
        m[i][j] = 0;
    }
  }
  fflush(stdin);
}
void insert(int mat[DIM][DIM]) {
  int row, col, val;
  printf("Inserire coordinate (riga colonna)\n");
  do scanf("%d%d", &row, &col);
  while (!validcoord(row, col, mat));
  printf("Inserire valore da mettere nella casella\n");
  do scanf("%d", &val);
  while (!validval(val));
  mat[row - 1][col - 1] = val;
  return;
}

void delete (int mat[DIM][DIM], int startinput[DIM][DIM]) {
  int row, col;
  printf("Inserire coordinate del valore da cancellare\n");
  do scanf("%d%d", &row, &col);
  while (!validcoord(row, col, startinput));
  mat[row - 1][col - 1] = 0;
  return;
}

void print_frame(void) {
  int i, j;
  printf("+");
  for (i = 0; i < BLOCK; i++) {
    for (j = 0; j < 10; j++) /* 10 vale solo perche' la cifra massima e' 9, altrimenti...  */
      printf("-");
    printf("+");
  }
  printf("\n");
}
void print(int m[DIM][DIM], int t[DIM][DIM]) {
  int i1, j1, i2, j2;
  char c, d;
  print_frame();
  for (i1 = 0; i1 < BLOCK; i1++) {
    for (i2 = 0; i2 < BLOCK; i2++) {
      printf("|");
      for (j1 = 0; j1 < BLOCK; j1++) {
        printf(" ");
        for (j2 = 0; j2 < BLOCK; j2++) {
          if (m[i1 * 3 + i2][j1 * 3 + j2])
            d = m[i1 * 3 + i2][j1 * 3 + j2] + '0';
          else
            d = ' ';
          if (t[i1 * 3 + i2][j1 * 3 + j2])
            c = '*';
          else
            c = ' ';
          printf("%c%c ", d, c);
        }
        printf("|");
      }
      printf("\n");
    }
    print_frame();
  }
}

int val(int num) {
  int ris, i;
  ris = 0;
  for (i = 0; i <= DIM && ris == 0; i++) {
    if (num == i) ris = 1;
  }
  if (ris == 0)
    return 0;
  else
    return 1;
}

int quadrato(int mat[DIM][DIM], int x, int y) {
  int out, n[DIM];
  int i, j, k;
  for (k = 0; k < DIM; k++) n[k] = 0;
  for (i = x; i < x + BLOCK; i++)
    for (j = y; j < y + BLOCK; j++)
      if (mat[i][j]) n[mat[i][j] - 1]++;
  out = 1;
  for (k = 0; k < DIM; k++) {
    if (n[k] > 1) out = 0;
  }
  return out;
}

int riga(int mat[DIM][DIM], int r) {
  int k, out;
  int n[DIM];
  for (k = 0; k < DIM; k++) n[k] = 0;
  out = 1;
  for (k = 0; k < DIM; k++) {
    if (mat[r][k]) {
      n[mat[r][k] - 1]++;
    }
  }
  out = 1;
  for (k = 0; k < DIM; k++) {
    if (n[k] > 1) out = 0;
  }
  return out;
}

int colonna(int mat[DIM][DIM], int c) {
  int k, out;
  int n[DIM];
  for (k = 0; k < DIM; k++) n[k] = 0;
  out = 1;
  for (k = 0; k < DIM; k++) {
    if (mat[k][c]) {
      n[mat[k][c] - 1]++;
    }
  }
  out = 1;
  for (k = 0; k < DIM; k++) {
    if (n[k] > 1) out = 0;
  }
  return out;
}

int check(int sudoku[DIM][DIM]) {
  int i, j, ris;
  ris = 1;
  for (i = 0; i < DIM && ris; i++) {
    if (!riga(sudoku, i) || !colonna(sudoku, i)) ris = 0;
  }
  for (i = 0; i < DIM && ris; i += 3) {
    for (j = 0; j < DIM && ris; j += 3) ris = quadrato(sudoku, i, j);
  }
  return ris;
}
