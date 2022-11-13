#include <stdio.h>
#define BASE 10

int main (int argc, char * argv[]){
	int num, cpy, rev, ris, cifra;
	do {
		scanf ("%d", &num);
	} while (num < 0);	
	cpy = num;
	cifra = cpy % BASE;
	if (cifra == 0)
		ris = 0;
	else {
		cpy = num;
		rev = 0;

		while (cpy > 0) {
			cifra = cpy % BASE;
			rev = rev * BASE + cifra;
			cpy /= BASE;
		} 

		if (rev == num)
			ris = 1;
		else 
			ris = 0;
	}
	printf ("%d\n", ris);
	return 0;
}
		
