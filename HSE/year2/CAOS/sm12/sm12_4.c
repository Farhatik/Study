#include <endian.h>
#include <fcntl.h>
#include <memory.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>


enum { SNODE = 3, SBYTE = 12 };

void dfs(int fd) {
    int32_t buf[SNODE];
    if (read(fd, buf, SBYTE) != SBYTE) {
        return;
    };

    if (buf[2] != 0) {
        lseek(fd, buf[2] * SBYTE, SEEK_SET);
        dfs(fd);
    }
    
    printf("%"PRId32" ", buf[0]);

    if (buf[1] != 0) {
        lseek(fd, buf[1] * SBYTE, SEEK_SET);
        dfs(fd);
        return;
    }

}


int main(int argc, char * argv[]) {
    int fd = open(argv[1], O_RDONLY);
    dfs(fd);
    printf("\n");
    close(fd);
    return 0;
}