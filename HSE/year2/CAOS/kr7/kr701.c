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

enum { BASE = 4, SZ = 100000 };


int main(int argc, char * argv[]) {
    int first = 1;
    pid_t pids[argc - 1];
    for (int i = 1; i < argc; ++i) {
        pid_t pid = fork();
        pids[i - 1] = pid;
        if (pid) {
            break;
        }
        int64_t x;
        sscanf(argv[i], "%"SCNd64, &x);
        int sum = 0;
        while (x != 0) {
            int64_t temp = x % BASE;
            if (temp > 0) {
                sum += temp;
            } else {
                sum -= temp;
            }
            x = x / BASE;
            }
            if (!first) {
                waitpid(pids[i - 2], NULL, 0);
            }
            printf("%d\n", sum);
            fflush(stdout);
        first = 0;
    }
    
    while (wait(NULL) > 0) {};
    return 0;
}