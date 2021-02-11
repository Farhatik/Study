#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>


volatile sig_atomic_t flag = 0;

void usr3_handler(int sig) {
    if (sig == SIGUSR1) {
        flag = 0;
    } else if (sig == SIGUSR2) {
        flag = 1;
    }
}

int main() {
    struct sigaction sa = { .sa_handler= usr3_handler, .sa_flags = SA_RESTART};
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int x;
    while (scanf("%d", &x) > 0) {
        if (!flag) {
            printf("%d\n", -x);
            fflush(stdout);
        } else {
            printf("%d\n", x * x);
            fflush(stdout);
        }
    }
    return 0;
}
