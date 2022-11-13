#include <stdio.h>

int main (int argc, char*argv[]){
	int sign, isCubo;
	unsigned long long int val, ris, prova, max, min, med;
	scanf ("%llu", &val);
	if (val == 0){
		isCubo = 1;
		ris = 0;
		sign = 0;
	} else {
		if (val < 0){
			sign = -1;
			val = -val;
		} else 	
			sign = 1;

		max = 1;
		prova = 1;
		while (prova < val){ 
			max *= 2;
			prova = max * max * max;
		}
		min = max / 2;

		if (val == prova){
			isCubo = 1;
			ris = max * sign;
		} else {
			
			isCubo = 0;
			while (!isCubo && max - min > 1){
				med = (max + min) / 2;
				prova = med * med * med;
				if (prova < val)
					min = med;
				else if (prova > val)
					max = med;
				else 
					isCubo = 1;
			}
			ris = med * sign;
		}
	}

	printf ("%d\t%llu\n", isCubo, ris);
	return 0;
}





