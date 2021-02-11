#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <fcntl.h>


int main(int argc, char * argv[]) {
    char * cmd1 = argv[1];
    char * cmd2 = argv[2];
    char * cmd3 = argv[3];
    char * file = argv[4];
    int fds[2];
    pipe2(fds, O_CLOEXEC);
    pid_t pid;
    if (!fork()) {
        int fd =  open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, 1);
        close(fds[1]);
        dup2(fds[0], 0);
        execlp(cmd3, cmd3, NULL);
        _exit(1);
    }
    close(fds[0]);
    if (! (pid = fork())) {
        dup2(fds[1], 1);
        execlp(cmd1, cmd1, NULL);
        _exit(1);
    }
    waitpid(pid, NULL, 0);
    if (!fork()) {
        dup2(fds[1], 1);
        execlp(cmd2, cmd2, NULL);
        _exit(1); 
    }
    close(fds[1]);


    while (wait(NULL) > 0) {};
    return 0;
}