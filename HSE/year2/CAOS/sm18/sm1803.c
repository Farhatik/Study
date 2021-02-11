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
    int fds[2]; 
    if (pipe2(fds, O_CLOEXEC) < 0) {
        fprintf(stderr, "pipe: %s\n", strerror(errno));
        exit(1);
    }
    // if (argc != 5) {
    //     fprintf(stderr, "wrong number of args\n");
    //     exit(1);   
    // }

    char * cmd1 = argv[1];
    char * cmd2 = argv[2];
    char * cmd3 = argv[3];
    char * file = argv[4];

    pid_t pid1 = fork();

    if (pid1 < 0) {
        fprintf(stderr, "fork1: %s\n", strerror(errno));
        exit(1);
    }
    if (!pid1) {
        dup2(fds[1], 1);
        execlp(cmd1, cmd1, NULL);
        _exit(1);
    }

    waitpid(pid1, NULL, 0);
    
    pid_t pid2 = fork();
    if (pid2 < 0) {
        fprintf(stderr, "fork2: %s\n", strerror(errno));
        exit(1);
    }

    if (!pid2) {
        dup2(fds[1], 1);
        execlp(cmd2, cmd2, NULL);
        _exit(1);
    }
    waitpid(pid2, NULL, 0);

    pid_t pid3 = fork();
    if (pid3 < 0) {
        fprintf(stderr, "fork3: %s\n", strerror(errno));
        exit(1);
    }

    if (!pid3) {
        int fd = open(file, O_WRONLY | O_CLOEXEC | O_CREAT | O_TRUNC, 0644);
        dup2(fds[0], 0);
        dup2(fd, 1);
        execlp(cmd3, cmd3, NULL);
        _exit(1);
    }
    // waitpid(pid3, NULL, 0);
    // close(fds[0]);
    // close(fds[1]);
    while (wait(NULL) > 0) {};
    return 0;
}