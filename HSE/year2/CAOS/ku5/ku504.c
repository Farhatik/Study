#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>


int main(int argc, char * argv[]) { 
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0600);
    uint32_t x;
    while (scanf("%"SCNu32, &x) > 0) {
        uint32_t buf;
        memcpy((char *)&buf, (char *)&x + 3, sizeof(char));
        memcpy((char *)&buf + 1, (char *)&x + 2, sizeof(char));
        memcpy((char *)&buf + 2, (char *)&x + 1, sizeof(char));
        memcpy((char *)&buf + 3, (char *)&x, sizeof(char));
        write(fd, &buf, sizeof(buf));   
    }
    close(fd);
    return 0;
}
