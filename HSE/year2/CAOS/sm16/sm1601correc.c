//код с Лекции 
// https://www.youtube.com/watch?v=zJgSNtB-bGA&list=PLlcCrvAVGbWptixlTGWS71Wgdsl_CFtDU&index=6
//Семы Чернова Александра Владимировича
//https://www.youtube.com/watch?v=QTFcUhDQpLw
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
int main() {
    setbuf(stdout, NULL);
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr,"fork(): %s\n", strerror(errno));
        exit(1);
    }
    if (pid == 0) {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            printf("3");
            exit(0);
        }
        waitpid(pid2, NULL, 0);
        if (pid2 != 0){
            printf(" 2");
        }
        exit(0);
    }    
    //wait as synchr primirive
    wait(NULL);

    printf(" 1\n");
    return 0;

}
