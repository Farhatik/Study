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

    // struct sigaction sa = { .sa_handler= int_handler, .sa_flags = SA_RESTART};
    // sigaction(SIGINT, &sa, NULL);

    // sigaction(SIGINT, &(strct sigaction))


    while (1) {
        int a, b, c;
        scanf("%d%d", &a, &b);
        c = a / b;
        printf("%d\n", c);
    }

    return 0;
}