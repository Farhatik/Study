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
    for (int i = 0; i < ; ++i) {
        num++;
        pid_t pid = fork();
        if ((pid < 0) || (i == 23)) {
            exit(1);
        }
        if (pid) {
            break;
        }
    }
    int status;
    wait(&status);
    //printf("in parent\n");
    // if (WIFEXITED(status)) {
    //     printf("exit status: %d\n", WEXITSTATUS(status));
    // } else if (WIFSIGNALED(status)) {
    //     printf("terminated: %d\n", WTERMSIG(status));
    // } else {
    //         abort();
    // }
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        // if (st <= 0) {
        //     _exit(0);
        // }
        printf("%d", num);
        fflush(stdout);
        if (root_pid == getpid()) {
            printf("\n", num); fflush(stdout);
        } else {
            printf(" ", num); fflush(stdout);
        }
    } else {
        if (root_pid == getpid()) {
            printf("-1\n");
            fflush(stdout);
            exit(0);
        } else {
            exit(1);
        }
    }
    return 0;
}