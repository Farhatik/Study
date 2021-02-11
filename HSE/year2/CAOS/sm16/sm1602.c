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
    // setbuf(stdout, NULL);

    int sz = 8;
    char buf[8];
    setvbuf(stdin, buf, _IOLBF, sz);
    for (int i = 0; i < QTY; ++i) {
        if (!fork()) {
            scanf("%8s", buf);
            int x;
            sscanf(buf, "%d", &x);
            //fflush(stdin);
            x *= x;
            printf("%d %d\n", i + 1, x);
            fflush(stdout);
            _exit(0);

        }
    }
    for (size_t i = 0; i < QTY; ++i) {
        wait(NULL);
    }
    return 0;
}