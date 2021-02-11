#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
//https://github.com/freepvps/hseos/blob/master/src/fork/recursive-fork2/main.c


int main(int argc, char * argv[]) {
    int p1[2];
    pipe(p1);
    pid_t pid1 = fork();
    if (!pid1) {
        close(p1[0]);
        FILE * ptr = fopen(argv[1], "r");
        int sum = 0;
        int x = 0;
        while (fscanf(ptr, "%d", &x) > 0) {
            sum += x;
        }
        fclose(ptr);
        write(p1[1], &sum, sizeof(sum));
        close(p1[1]);
        _exit(0);
    }
    close(p1[1]);
    int sum1;
    read(p1[0], &sum1, sizeof(sum1));
    close(p1[0]);

    int p2[2];
    pipe(p2);
    pid_t pid2 = fork();
    if (!pid2) {
        close(p2[0]);
        FILE * ptr = fopen(argv[2], "r");
        int sum = 0;
        int x = 0;
        while (fscanf(ptr, "%d", &x) > 0) {
            sum += x;
        }
        fclose(ptr);
        write(p2[1], &sum, sizeof(sum));
        close(p2[1]);
        _exit(0);
    }
    close(p2[1]);
    int sum2;
    read(p2[0], &sum2, sizeof(sum2));
    close(p2[0]);
    while (wait(NULL) > 0) {};
    printf("%d\n%d\n%d\n", sum2, sum1, sum2 + sum1);
    return 0;
}