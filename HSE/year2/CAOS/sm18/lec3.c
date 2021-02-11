#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>


int main() {
    signal(SIGPIPE, SIG_IGN);
    int fd[2];
    pipe(fd);

    //Переключение в не блокирующий режим

    int f = fcntl(fd[1], F_GETFL);
    fcntl(fd[1], F_SETFL, O_NONBLOCK | f);


    // close(fd[0]);
    size_t z = 0;
    while (1) {
        char c = 'a';
        int r = write(fd[1], &c, sizeof(c));
        if (r < 0) {
            fprintf(stderr, "error: %s\n", strerror(errno));
            return 1;
        }
        ++z;
        printf("%zu\n", z);
    }
    return 0;
}