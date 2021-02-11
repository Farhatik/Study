//код с Лекции 
// https://www.youtube.com/watch?v=zJgSNtB-bGA&list=PLlcCrvAVGbWptixlTGWS71Wgdsl_CFtDU&index=6
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
int main() {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr,"fork1(): %s\n", strerror(errno));
        exit(1);
    }
    if (!pid) {
        //child
        //printf("in child\n");
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr,"fork2(): %s\n", strerror(errno));
            exit(1);
        }
        if (!pid) {
            printf("in grandchild\n");
        }
        wait(NULL);
        printf("in child\n");
        _exit(0);
    }


    wait(NULL);
    printf("in parent\n");
    return 0;

}