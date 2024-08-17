#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PAGE_SIZE (1024 * 4)
#define STACK_ITERATION 35
int alloc_stack(int iterations) {
	char local[PAGE_SIZE];
	if (iterations > 0) return alloc_stack(iterations - 1);
	else return 0;
}

int main(void) {
	alloc_stack(STACK_ITERATION);
	char command[100];
	snprintf(command, sizeof(command), "pmap %d", getpid());
	system(command);
	return 0;
}
