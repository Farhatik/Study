#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

//https://www.youtube.com/watch?v=-u0EV9E7oV0&list=PLlcCrvAVGbWptixlTGWS71Wgdsl_CFtDU&index=31
//Лекция Чернова в  1:10

int work(int serial, int rfd, int wfd, int stop) {
    while (1) {
        int x;
        read(rfd, &x, sizeof(x));
        if (x == stop) {
            close(rfd);
            close(wfd);
            return -1;
        }
        if (x > 0) {
        printf("%d %d\n", serial, x); 
        }
        ++x;
        if (write(wfd, &x, sizeof(x) > 0)) {;
            return 1;
        } else {
            return -1;
        }
    }
}

int main(int argc, char * argv[]) {
    setbuf(stdout, NULL);
    int p01[2];
    pipe(p01);
    int p10[2];
    pipe(p10);
    int x = 1;
    if (strtol(argv[1], NULL, 10) <= 1) {
        printf("Done\n");
        exit(0);
    }
    write(p10[1], &x, sizeof(x));
    int err = 1;
    if (!fork()) {
        close(p10[1]);
        close(p01[0]);
        while ((err = work(1, p10[0], p01[1], strtol(argv[1], NULL, 10))) > 0);
        _exit(0);
    }
    if (err && !fork()) {
        close(p10[0]);
        close(p01[1]);
        while (work(2, p01[0], p10[1], strtol(argv[1], NULL, 10)) > 0);
        _exit(0);
    }
    // int status;
    close(p01[1]);
    close(p01[0]);
    close(p10[1]);
    close(p10[0]);
    while (wait(NULL) > 0) {}
    printf("Done\n");
    return 0;
}