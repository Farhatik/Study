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

enum { QTY = 3 }; 

int main(int argc, char * argv[]) {
    setbuf(stdout, NULL);
    for (int i = 0; i < QTY; ++i) {
        pid_t pid1 = fork();
        if (pid1)
    }

    while (wait(NULL) > 0) {};

    return 0;
}