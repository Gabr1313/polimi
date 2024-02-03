#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int pid = fork();
    if (pid == 0) {
        printf("Child process\n");
        sleep(1);
        printf("Child process again\n");
        exit(8);
    } else {
        printf("Parent process\n");
        exit(0);
    }
    printf("This line should not be printed\n");
    return 0;
}
