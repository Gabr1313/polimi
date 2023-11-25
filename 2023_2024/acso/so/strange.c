#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/wait.h>
#include <unistd.h>

#define WAIT_TO_KILL 8
#define WAIT_AFTER_SPAWN 5
#define MAX_DEPTH 4
#define DEPTH_TO_KILL 1

int depth = 0;

void build_tree() {
    printf("Hello from %d\n", getpid());
    fflush(stdout);
    sleep(WAIT_AFTER_SPAWN);
    if (++depth > MAX_DEPTH) {
        printf("Goodbye from %d\n", getpid());
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        build_tree();
    } else {
        printf("%d gave birth to %d\n", getpid(), pid);
        fflush(stdout);
        if (depth == DEPTH_TO_KILL) {
            printf("%d (parent) will kill %d (child) in %ds\n", getpid(), pid, WAIT_TO_KILL);
            fflush(stdout);
            sleep(WAIT_TO_KILL);
            kill(pid, SIGKILL);
            printf("%d killed %d\n", getpid(), pid);
            fflush(stdout);
        } else waitpid(pid, NULL, 0);
    }
    printf("Goodbye from %d\n", getpid());
    fflush(stdout);
}

int main(void) { build_tree(); }
