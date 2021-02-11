#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char * argv[]) 
{
    const char *prog = argv[1];
    const char *inf = argv[2];
    const char *outf = argv[3];
    const char *errf = argv[4];
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork(): %s\n", strerror(errno));
        exit(1);
    }
    if (!pid) {
        int ifd = open(inf, O_RDONLY | O_CLOEXEC, 0);
        if (ifd < 0) {
            fprintf(stderr, "error: %s\n", strerror(errno));
            _exit(1);
        }
        int ofd = open(outf, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0600);
        int efd = open(errf, O_WRONLY | O_CREAT | O_APPEND| O_CLOEXEC, 0600);
        dup2(ifd, 0);
        dup2(ofd, 1);
        dup2(efd, 2);
        close(ifd); close(ofd); close(efd);
        chdir("/");
        umask(0);
        execlp(prog, prog, NULL);
        _exit(1);
    }
    wait(NULL);
    return 0;
}