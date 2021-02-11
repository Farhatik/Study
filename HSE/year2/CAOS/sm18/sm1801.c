#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
//https://github.com/dbeliakov/hse-os-2018/blob/master/seminars/18/code/pipe/main.c
// Чекал учебные материалы Белякова


int main(int argc, char * argv[]) {
    if (argc != 3) {
        fprintf(stderr, "wrong number of args\n");
        exit(1);   
    }
    char * cmd1 = argv[1];
    char * cmd2 = argv[2];
    int fds[2]; 
    if (pipe(fds) < 0) {
        fprintf(stderr, "pipe: %s\n", strerror(errno));
        exit(1);
    }
    pid_t pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "fork1: %s\n", strerror(errno));
        exit(1);
    }
    if (!pid1) {
        if (dup2(fds[1], 1) < 0) {
            fprintf(stderr, "dup2: %s\n", strerror(errno));
            _exit(1);
        };
        close(fds[0]);
        close(fds[1]);
        execlp(cmd1, cmd1, NULL);
        _exit(1);
    }
    
    pid_t pid2 = fork();

    if (pid2 < 0) {
        fprintf(stderr, "fork1: %s\n", strerror(errno));
        exit(1);
    }

    if (!pid2) {
        if (dup2(fds[0], 0) < 0) {
            fprintf(stderr, "dup2: %s\n", strerror(errno));
            _exit(1);
        };
        close(fds[0]);
        close(fds[1]);
        execlp(cmd2, cmd2, NULL);
        _exit(1);
    }
    close(fds[0]); close(fds[1]);
    while (wait(NULL) > 0);
    
    return 0;

}