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


int main(int argc, char** argv) {
    pid_t root_pid = getpid();
    // setbuf(stdin, NULL);
    int num, st;
    // int x = 0;
    while ((st = scanf("%d", &num)) == 1) {
        // x++;
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        }
        if (pid) {
            break;
        }
    }
    int status = 0;
    wait(&status);
    //printf("%d %d %d\n", WEXITSTATUS(status), getpid(), getppid());
    // printf("%d", 2);
    getpid();
    getppid();
    // fflush(stdout);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        if (st <= 0) {
            exit(0);
        }

        printf("%d", num);
        fflush(stdout);
        if (root_pid == getpid()) {
            printf("\n"); fflush(stdout);
        } else {
            printf(" "); fflush(stdout);
        }
        exit(0);
    } else {
        if (root_pid == getpid()) {
            printf("-1\n"); fflush(stdout);
            exit(0);
        } else {
            exit(1);
        }
    }
    return 0;
}