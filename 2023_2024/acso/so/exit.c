#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int pid = fork();
    if (pid == 0) {
        printf("Child process\n");
        int pid2 = fork();
        if (pid2 == 0) {
            sleep(3);
            printf("Grandchild process\n");
            exit(2);
        }
        exit(8);
    } else {
        printf("Parent process\n");
        sleep(1);
        // kill(pid, SIGKILL);
        int status;
        wait(&status);
        printf("Child process exited with status %d\n", WEXITSTATUS(status));
        exit(0);
    }
    printf("This line should not be printed\n");
    return 0;
}
