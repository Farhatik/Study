#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>


volatile sig_atomic_t X = 0;

void int_handler(int s) {
    printf("%d\n", X++);
    fflush(stdout);
}



int main() {
    struct sigaction sa = { .sa_handler= int_handler, .sa_flags = SA_RESTART};
    sigaction(SIGINT, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (X < 4) {
        pause();
    }
    return 0;
}