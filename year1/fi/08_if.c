#include <stdio.h>

int main (int argc, char*argv[])
{
	int num, abs;
	scanf("%d",&num);
	if (num<0)
		abs=-num;
	else
		abs=num;
	printf("%d\n",abs);
	return 0;
}
