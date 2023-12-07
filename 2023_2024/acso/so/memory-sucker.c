#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alloc_memory() {
	int mb = 0;
	char* buffer;
	while ((buffer = malloc(1024 * 1024)) != NULL) {
		memset(buffer, 0, 1024 * 1024);
		mb++;
		printf("Allocated %d MB\n", mb);
	}
}

int main(int argc, char** argv) {
	alloc_memory();
	return 0;
}
