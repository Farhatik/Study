#include <stdint.h>
#include <stdio.h>
#include <endian.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>


int main(int argc, char * argv[]) {
    uint16_t x;
    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    while (scanf("%"SCNu16, &x) == 1) {
        x = htobe16(x);
        if (write(fd, &x, sizeof(x)) != sizeof(x)) {
            return -1;
        }
    };
    close(fd);
    return 0;
}