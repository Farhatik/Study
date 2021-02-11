#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>



int main() {
    int fd[2];
    pipe(fd);
    size_t z = 0;
    while (1) {
        char c = 'a';
        write(fd[1], &c, sizeof(c));
        ++z;
        printf("%zu\n", z);
    }
    return 0;
}