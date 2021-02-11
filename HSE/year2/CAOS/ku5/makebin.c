#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char * argv[]) {
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0777);
    int x;
    while (scanf("%d", &x) > 0) {
        write(fd, &x, sizeof(x));
    }
    close(fd);
    return 0;
}