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
///http://ru.manpages.org/strtok_r/3 
// Чекал на это сайте как юзать strok
//http://ru.manpages.org/getaddrinfo_a/3
//https://ru.wikipedia.org/wiki/Strtok
enum { SZ = 10000 }; 


int mysystem(const char *cmd) {
    if (cmd == NULL) {
        return -1;
    }
    char ** argv = NULL;
    char * str = malloc(strlen(cmd) + 1);
    strcpy(str, cmd);
    str[strlen(cmd)] = '\0';
    
    char * arg = strtok(str, " ");
    if (arg == NULL) {
        free(str);
        return -1;
    }

    int qty = 2;
    argv = realloc(argv, sizeof(*argv) * qty);
    // argv[0] = "sh";
    // argv[1] = "-c";
    argv[qty - 2] = arg;

    while (arg != NULL) {
        arg = strtok(NULL, " ");
        if (arg != NULL) {
            char * temp_arg = malloc(strlen(arg) + 1); 
            strcpy(temp_arg, arg);
            qty++;
            argv = realloc(argv, sizeof(*argv) * qty);
            argv[qty - 2] = temp_arg;
        }
    }

    pid_t pid = fork();
    if (pid < 0) {
        free(str);
        for (int i = 1; i < qty - 1; ++i) {
            free(argv[i]);
        }
        free(argv);
        return -1;
    }

    if (!pid) {
        // printf("%d\n", qty);
        argv[qty - 1] = NULL;
        execvp(argv[0], argv);
        _exit(1);
    }
    int status = 1;
    waitpid(pid, &status, 0);
    free(str);
    for (int i = 1; i < qty - 1; ++i) {
        free(argv[i]);
    }
    free(argv);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        return WTERMSIG(status) + 1024;
    } else {
        return -1;
    }
}

// int main() {
//     char buf[10000];
//     fgets(buf, 1000, stdin);
//     buf[strlen(buf) - 1] = '\0';
//     printf("%d\n", mysystem(buf));
//     return 0;
// }