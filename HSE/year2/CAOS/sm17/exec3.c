#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

extern char **environ;

int main() 
{
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork: %s\n", strerror(errno));
        exit(1);
    }

    if (!pid) {
        // char * envs[] = {"A=1", "B=2", NULL};
        // char * args[] = {"/usr/bin/ls", "-l", "/", NULL};
        execlp("ls", "ls", "-l", "--color=auto", "/", NULL);
        fprintf(stderr, "execve() : %s\n", strerror(errno));
        _exit(1);
    }
    wait(NULL);
}