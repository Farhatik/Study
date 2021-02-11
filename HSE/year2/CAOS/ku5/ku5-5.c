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
#include <limits.h>


int main(int argc, char * argv[]) {
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        exit(1);
    }
    size_t sz = lseek(fd, 0, SEEK_END) - lseek(fd, 0, SEEK_SET);
    if (sz == 0) {
        return 0;
    }
    size_t qty = sz / sizeof(long long);
    long long min = LLONG_MAX;
    int64_t index = 0;
    long long cur;
    for (size_t i = 0; i < qty; ++i) {
        read(fd, &cur, sizeof(cur));
        if (cur < min) {
            min = cur;
            index = i;
        }
    }
    if (min != LLONG_MIN) {
        lseek(fd, index * sizeof(cur), SEEK_SET);
        min *= -1;
        write(fd, &min, sizeof(min));
    }
    close(fd);
    return 0;
}