#include <stdio.h>

int main(int argc, char * argv[])
{
	int a, l, lato, n;
	scanf("%d%d%d",&a,&l,&lato);
	n=a*l/(lato*lato);
	printf("%d\n",n);
	return 0;
}