/* Un k-mer è una sequenza di k caratteri.
Il sottoprogramma conta calcola e restituisce il numero di volte in cui un k-mer kmer
compare nella sequenza (di Dna) seq. Per esempio, il k-mer ACTAT compare 3 volte nella
sequenza di Dna ACAACTATGCATACTATCGGGAACTATCCT.
Si noti che il k-mer ATA compare 3 volte (non 2) nella sequenza CGATATATCCATAG, poiché
ci sono due sottosequenze parzialmente sovrapposte.
Si sviluppi il sottoprogramma conta, il cui prototipo (con anche il nome dei parametri
formali) è:
int conta(char seq[], char kmer[]);
In alcuni contesti, non è necessario trovare la sottosequenza esatta, ma è sufficiente
una approssimata, ossia che differisce da quella esatta di d elementi. La differenza
tra due sequenze di ugual dimensione viene misurata in termini di distanza di Hamming
ossia il numero di elementi diversi in posizione pos_cor nelle due sequenze. Per
esempio, le sequenze ATA e ATC hanno una distanza pari a 1 (questa nozione di distanza
di applica a sequenze di qualsiasi tipo).
Si realizzi un sottoprogramma distanza che ricevute in ingresso due stringhe calcoli e
restituisca la distanza di Hamming.
Nella realizzazione si tenga presente che nell’impiego del sottoprogramma le due
stringhe potrebbero avere lunghezze diverse.
int distanza(char seq1[], char seq2[]);
Si realizzi un sottoprogramma contad che conta e restituisce il numero di volte in cui
un k-mer kmer compare nella sequenza seq, accettando anche delle forme approssimate
purché a distanza minore o uguale a d. La valutazione deve tenere presente che l’intero
k-mer deve essere contenuto nella sequenza, per cui: ATA non è contenuto in modo
approssimato nella sequenza CCAT con d = 1.
int contad(char seq[], char kmer[], int d);
Sviluppare un programma in C (ANSI 89) che acquisiti in ingresso una sequenza di
Dna di al più 100 caratteri, il k-mer (di al più 10 caratteri) e il livello di
approssimazione accettabile, calcola e visualizza (mediante i sottoprogrammi prima
specificati) il numero di k-mer esatti trovati nella sequenza seguito dal numero di
quelli approssimati.
Esempi:
input: ACAACTATGCATACTATCGGGAACTATCCT ACTAT 3
output: 3 5
input: ACAACTATGCATACTATCGGGAACTATCCT ACTAT 0
output: 3 0
input: ACGTTGCATGTCGCATGATGCATGAGAGCT GCAT 1
output: 3 0
input: ACGTTGCATGTCGCATGATGCATGAGAGCT GCAT 2
output: 3 2       */

#include <stdio.h>
#include <string.h>
#define BASI 4
#define LEN_MAX_SEQ 100
#define LEN_MAX_KMER 10

int distanza(char[], char[]);
int conta(char[], char[]);
int distanza_mag(char[], char[], int, int);
int conta_d(char[], char[], int);

int main(int argc, char *argv[]) {
  char seq[LEN_MAX_SEQ], kmer[LEN_MAX_KMER];
  int d, ris1, ris2;

  scanf("%s %s %d", seq, kmer, &d);

  ris1 = conta(seq, kmer);
  ris2 = conta_d(seq, kmer, d) - ris1;
  printf("%d %d\n", ris1, ris2);
  return 0;
}

int conta(char seq[], char kmer[]) {
  int diff, count, i, len_seq, len_kmer;
  char test[LEN_MAX_KMER];

  len_seq = strlen(seq);
  len_kmer = strlen(kmer);
  diff = len_seq - len_kmer;

  count = 0;
  for (i = 0; i <= diff; i++) {
    strncpy(test, seq + i, len_kmer);
    count += (!strcmp(test, kmer));
  }

  return count;
}

int distanza(char seq1[], char seq2[]) {
  /* non capisco perche' le due stringhe potrebbero avere lunghezze diverse... */
  int diff, dist_min, len1, len2;

  len1 = strlen(seq1);
  len2 = strlen(seq2);
  diff = len1 - len2;
  if (diff == 0)
    dist_min = distanza_mag(seq1, seq2, len2, diff);
  else if (diff > 0)
    dist_min = distanza_mag(seq1, seq2, len2, diff);
  else
    dist_min = distanza_mag(seq2, seq1, len1, -diff);

  return dist_min;
}

int distanza_mag(char seqA[], char seqB[], int lenB, int diff) {
  int i, j, dist_prova, dist_min;

  dist_min = 0;
  for (j = 0; j < lenB; ++j) dist_min += (seqA[j] != seqB[j]);

  for (i = 1; i <= diff; i++) {
    dist_prova = 0;
    for (j = 0; j < lenB; j++) dist_prova += (seqA[i + j] != seqB[j]);
    if (dist_prova < dist_min) dist_min = dist_prova;
  }

  return dist_min;
}

int conta_d(char seq[], char kmer[], int d) {
  int hamming, diff, count, i, len_seq, len_kmer;
  char test[LEN_MAX_KMER];

  len_seq = strlen(seq);
  len_kmer = strlen(kmer);
  diff = len_seq - len_kmer;

  count = 0;
  for (i = 0; i <= diff; i++) {
    strncpy(test, seq + i, len_kmer);
    hamming = distanza(test, kmer);
    if (hamming <= d) count++;
  }

  return count;
}
