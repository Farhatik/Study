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
        fprintf(stderr,"for(): %s\n", strerror(errno));
        exit(42);
    }
    if (!pid) {
        //child
        printf("in child\n");
        pause();
        _exit(0);
    }    
    //wait as synchr primirive
    int status;
    wait(&status);
    //printf("in parent\n");
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("succes\n");
    } else {
        prinf("fail\n"); 
    }
    return 0;

}