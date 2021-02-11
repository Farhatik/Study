#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

int IS_OK(char * cmd) {
    pid_t pid = fork();
    if (pid < 0) {
        return 0;
    }
    if (!pid) {
        execlp("/bin/sh", "sh", "-c", cmd, NULL);
        _exit(1);
    }
    int status = 1;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char * argv[]) {
    if (argc < 4) {
        fprintf(stderr, "few args\n");
        exit(1);
    }
    if (IS_OK(argv[1])) {
        return 1 - IS_OK(argv[3]);
    } else {
        if (IS_OK(argv[2])) {
            return 1 - IS_OK(argv[3]);
        } else {
            return 1;
        }
    }
    return 0;
}