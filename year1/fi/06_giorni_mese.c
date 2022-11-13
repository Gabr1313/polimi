#include <stdio.h>

int main(int argc, char*argv[])
{
	int anno, mese, giorni;
	do
		scanf("%d",&mese);
	while (mese>12||mese<1);
	scanf("%d",&anno);
	if (mese==11||mese==4||mese==6||mese==9)
		giorni=30;
	else if (mese==2)
	{
		if ((anno%4==0 && anno%100!=0) || anno%400==0)		
			giorni=29;
		else
			giorni=28;
	}
	else 
		giorni=31;
			printf("%d\n",giorni);

	return 0;
}

