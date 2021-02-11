#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>


int main() {
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);
    int fds[2]; 

    if (pipe(fds) < 0) {
        fprintf(stderr, "pipe: %s\n", strerror(errno));
        exit(1);
    }

    if (!fork()) {
        close(fds[1]);
        pid_t pid = fork();
        if (!pid) {
            int64_t sum = 0;
            int x = 0;
            while (read(fds[0], &x, sizeof(x)) > 0) {
                sum += x;
            }
            printf("%"PRId64"\n", sum);
            close(fds[0]);
            _exit(0);
        }
        close(fds[0]);
        waitpid(pid, NULL, 0);
        _exit(0);
    }
    close(fds[0]);
    int x = 0;
    while (scanf("%d", &x) > 0) {
        write(fds[1], &x, sizeof(x));
    }
    close(fds[1]);

    while (wait(NULL) > 0) {};
    return 0;
}