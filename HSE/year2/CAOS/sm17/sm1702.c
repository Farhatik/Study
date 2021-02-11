#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>

int mysys(const char *str) {
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    }
    if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }
    int status = 1;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) >= 0 && (WEXITSTATUS(status) <= 127)) {
            return WEXITSTATUS(status);
        }
    } else if (WIFSIGNALED(status)) {
        return WTERMSIG(status) + 128;
    }
    return 0;
}

// int main(int argc, char * argv[]) {
//     printf("%d\n", mysys(argv[1]));
//     return 0;
// }