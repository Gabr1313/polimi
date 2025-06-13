#include <stdio.h>

int main(void) {
	float a = -67.875;
	float b = 15.7;
	float c = a + b;
	printf("%x", *(int*)&c);
}
