#include <stdio.h>
#define TOT 20

int main (int argc, char*argv[]){
	int sentinella, num, counter, max, min, sum;
	float avg;
	scanf("%d", &sentinella);
	scanf("%d", &num);
	sum = num;
	max = num;
	min = num;
	counter = 1;
	if (num != sentinella) {
		scanf("%d", &num);
		while (num != sentinella) {
			sum += num;
			if (max < num)
				max = num;
			if (min > num)
				min = num;
			counter ++;
			scanf("%d", &num);
		}
	}
	avg = (float) sum / counter;
	printf("%d\t%d\t%g\n", min, max, avg);
	return 0;
}

