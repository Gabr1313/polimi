#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  pid_t pid;
  pid = fork();
  if (pid < 0) {
    printf("fork error\n");
  } else if (pid == 0) {
    printf("I am child process, pid = %d\n", getpid());
  } else {
    printf("I am parent process, pid = %d\n", getpid());
  }
  return 0;
}
