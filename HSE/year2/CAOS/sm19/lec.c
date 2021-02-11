#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


void fpe_handler(int s) {
    printf("FPE\n");
}

void int_handler(int s) {
    sleep(10);
    printf("INT\n");
}

int main() {
    signal(SIGSEGV, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    
    signal(SIGFPE, fpe_handler);
    signal(SIGINT, int_handler);

    while (1) {
        int a, b, c;
        scanf("%d%d", &a, &b);
        c = a / b;
        printf("%d\n", c);
    }

    return 0;
}