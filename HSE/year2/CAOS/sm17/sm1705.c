#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h> 
#include <limits.h>
// #include <linux/limits.h>

enum { SZ = 10000 }; 


int mysys(const char *cmd) {
    int first_space = 0;
    int skip_first_spaces = 1;
    char buf[SZ];
    int st_f = 0;
    int end_f = 0;
    char ** argv = NULL;
    int argc = 0;
    for (int i = 0; i < strlen(cmd); ++i) {
        if (skip_first_spaces && isspace(cmd[i])) {
            continue;
        }
        if (!isspace(cmd[i] && !end_f)) {
            buf[st_f] = cmd[i];
            skip_first_spaces = 0;
            st_f++;
        } else {
            char * arg = malloc(st_f);
            arg[st_f] = '\0';
            argc++;
            argv = realloc(argv, sizeof(*argv) * argc);
            argv[argc - 1] = arg
            st_f = 0;
            end_f = 1;
            
            
        }
    }

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