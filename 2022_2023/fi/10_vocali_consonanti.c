#include <stdio.h>
#define CONSONANTE 'c'
#define VOCALE 'v'
#define ALTRO ' '

int main (int argc, char*argv[]){
	char c, ris;
	scanf("%c",&c);
	if (c>'a'&&c<'z'){
		if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')
			ris=VOCALE;
		else
			ris=CONSONANTE;
	} else if (c>'A'&&c<'Z') {
		if(c=='A'||c=='E'||c=='I'||c=='O'||c=='U')
			ris=VOCALE;
		else 
			ris=CONSONANTE;
	} else
		ris=ALTRO;
	printf("%c\n",ris);
	return 0;
}
			
	
