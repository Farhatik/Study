#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char * argv[]) {
    int fd = open(argv[1], O_RDONLY);
    int x;
    while (read(fd, &x, sizeof(x)) > 0) {
        printf("%d\n", x);
    }
    close(fd);
    return 0;
}