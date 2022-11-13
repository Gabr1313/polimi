#include <stdio.h>
#define BASE 2
#define MIN 1
#define MAX 1023
#define NBIT 10 /*log_BASE ( MAX - MIN + 1) */

int main ( int argc, char * argv[]){
	int bin_1[NBIT], bin_2[NBIT], i, j,
		val_1, val_2;
	do scanf ( "%d", &val_1);
	while ( val_1 < MIN || val_1 > MAX );
	do scanf ( "%d", &val_2);
	while ( val_2 < MIN || val_2 > MAX );

	i = NBIT;
	while ( val_1 > 0 || val_2 > 0 ) {
		i--;
		bin_1[i] = val_1 % BASE;
		val_1 /= BASE;
		bin_2[i] = val_2 % BASE;
		val_2 /= BASE;
	}

	for ( j = i; j < NBIT; j++ )
		printf ( "%d", bin_1[j] );
	printf ( "\n" );
	for ( j = i; j < NBIT; j++ )
		printf ( "%d", bin_2[j] );
	printf ( "\n" );

	return 0;
}
