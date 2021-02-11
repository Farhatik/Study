#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int fds[2];
    if (pipe(fds) < 0) {
        //FIXME: error, handle it
    }

    if (!fork()) {
        int x;
        close(fds[1]);
        while (read(fds[0], &x, sizeof(x)) > 0) {
            printf("%d\n", x);
            fflush(stdout);
        }
        close(fds[0]);
        _exit(0);
    }
    close(fds[0]);
    for (int i = 0; i < 10; ++i) {
        write(fds[1], &i, sizeof(i));
    }
    close(fds[1]);
    wait(NULL);
    
    return 0;

}