//https://www.youtube.com/watch?v=3UzePQ90Pmk&list=PLlcCrvAVGbWptixlTGWS71Wgdsl_CFtDU&index=4
//Лекция Чернова, код оттуда 51 минута
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char * argv[]) {
    if (argc != 4) {
        fprintf(stderr, "few args\n");
    }
    const char * prog = argv[1];
    const char * inf = argv[2];
    const char * outf = argv[3];

    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "frok(): %s\n", strerror(errno));
        exit(1);
    }
    if (!pid) {
        int infd = open(inf, O_RDONLY, 0);
        int outfd = open(outf, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (infd < 0 || outfd < 0) {
            fprintf(stderr, "open: %s\n", strerror(errno));
            _exit(1);
        }
        dup2(infd, 0);
        dup2(outfd, 1);
        if (close(infd) < 0 || close(outfd) < 0) {
            fprintf(stderr, "close: %s\n", strerror(errno));
            _exit(1);
        }
        execlp(prog, prog, NULL);
        _exit(1);

    }
    wait(NULL);
    return 0;
}