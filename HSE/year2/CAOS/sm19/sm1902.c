#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


volatile sig_atomic_t flag = 0;

void usr1_handler(int s) {
    printf("%d\n", X++);
    fflush(stdout);
}

void usr2_handler(int s) {
}

int main() {
    struct sigaction sa = { .sa_handler= usr1_handler, .sa_flags = SA_RESTART};
    sigaction(SIGINT, &sa, NULL);
    // struct sigaction sb = { .sa_handler= usr2_handler, .sa_flags = SA_RESTART};
    // sigaction(SIGINT, &sb, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int x;
    flag = 0;
    while (scanf("%d", &x) > 0) {
        if (!flag) {
            
        }
    }
    return 0;
}