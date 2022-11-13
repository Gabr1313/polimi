#include <stdio.h>
#define POS '+'
#define NEG '-'
#define NUL '0'

int main(int argc, char*argv[])
{
	int num;
	char val;
	scanf("%d",&num);
	if (num<0)
		val=NEG;
	else if (num>0)
		val=POS;
	else
		val=NUL;
	printf("%c\n",val);
	return 0;
}
