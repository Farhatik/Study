//код с Лекции 
// https://www.youtube.com/watch?v=zJgSNtB-bGA&list=PLlcCrvAVGbWptixlTGWS71Wgdsl_CFtDU&index=6
//Семы Чернова Александра Владимировича
//https://www.youtube.com/watch?v=QTFcUhDQpLw
//Также смотрел наши семы
//github.com/freepvps/hseos/blob/master/src/fork/recursive-fork/main.c
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main() {
    int num;
    scanf("%d", &num);
    
    for (int i = 1; i <= num; ++i) {
        if (i != 1) {
            printf(" ");
        };
        printf("%d", i);
        if (i == num) {
            printf("\n");
        }

        fflush(stdout);
        pid_t pid = fork();
        if (pid) {
            // printf("%d\n", getppid());
            // fflush(stdout);
            break;
        }
    }

    while (wait(NULL) > 0) {}

    return 0;
}