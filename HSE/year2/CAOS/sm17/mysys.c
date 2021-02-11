#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int mysys(const char *str) {
    pid_t pid = fokr();
    if (pid < 0) {
        return -1;
    }
    if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(1);
    }
    int status = 0;
    int res = waitpid(pid, &status, 0);
}

