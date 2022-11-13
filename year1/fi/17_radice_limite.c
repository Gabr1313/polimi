#include <stdio.h>
#define EPS 0.0000001
#define PERFETTA 1
#define NON_PERFETTA 0

int main (int argc, char*argv[]) {
	int indice, indice_2, sign, i, ris, radice_int;
	double radicando, indice_3, radicando_2, radice, x, y, z, diff, diff_2; 
	do 
		scanf ( "%d", &indice);
	while ( indice < 1);
	scanf ( "%lf", &radicando);
	if (radicando < 0 && indice % 2 == 0) {
		ris = NON_PERFETTA;
		radice = 0;
	} else {
		if ( radicando < 0){
			radicando = -radicando;
			sign = -1;
		} else 
			sign = 1;
		indice_2 = indice - 1;
		indice_3 = (double)indice_2 / indice;
		radicando_2 = radicando / indice;
		y = 1;
		do {
			x = y;
			z = 1;
			for ( i = 0; i < indice_2; i++)
				z *= x;
			y = indice_3 * x + radicando_2 / z;
			diff = y - x;
			if ( diff < 0 )
				diff = -diff;
		} while ( diff > EPS);
		radice = x;
		radice_int = radice;
		diff_2 = radice - radice_int ;
		if ( diff_2 < EPS * 2 ) {
			radice = radice_int;
			ris = PERFETTA;
		} else if ( diff <= 1 && diff >= 1 - EPS * 2) {
			radice = radice_int + 1;
			ris = PERFETTA;
		} else
			ris = NON_PERFETTA;
		radice = radice * sign;
	}
	printf ( "%d\t%g\n", ris, radice);
	return 0;
}
