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

    char ** argv = NULL;
    char * str = malloc(strlen(cmd) + 1);
    strcpy(str, cmd);
    str[strlen(cmd)] = '\0';

    char * arg = strtok(str, " ");
    if (arg == NULL) {
        free(str);
        return -1;
    }

    int qty = 4;
    argv = realloc(argv, sizeof(*argv) * qty);
    argv[0] = "sh";
    argv[1] = "-c";
    argv[qty - 2] = arg;
    // printf("%s\n", arg);
    while (arg != NULL) {
        // printf("%s\n", arg);
        arg = strtok(NULL, " ");
        // char * args = malloc(strlen(arg) + 1);
        if (arg != NULL) {
            // strcpy(args, arg);
        //     args[strlen(arg)] = '\0';
        //     printf("%s\n", args);
            qty++;
            argv = realloc(argv, sizeof(*argv) * qty);
            argv[qty - 2] = arg;
        }
    }

    pid_t pid = fork();
    if (pid < 0) {
        free(str);
        free(argv);
        return -1;
    }
    // for (int i = 0; i < qty; ++i) {
        // printf("CHEROV: %s\n", argv[i]);
    // }
    // printf("qty = %d\n", qty);
    if (!pid) {
        argv[qty] = NULL;
        execvp("/bin/sh", argv);
        _exit(1);
    }
    int status = 1;
    waitpid(pid, &status, 0);
    free(str);
    // for (int i = 0; i < qty; ++i) {
        // free(argv[i]);
    // }
    free(argv);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        return WTERMSIG(status) + 1024;
    }
    return 1;
}

