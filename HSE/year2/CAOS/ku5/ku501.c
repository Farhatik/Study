#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>



int my_read(int fd, int * buf, size_t offset) {
    int need_r = sizeof(int);
    if (lseek(fd, offset, SEEK_SET) < 0) {
        return -1;
    };
    while (need_r > 0) {
        int was_r = read(fd, buf, need_r);
        if (was_r < 0) {
            return -1;
        }
        need_r -= was_r; 
    }
    return 0;
}


int my_write(int fd, int * buf, size_t offset) {
    int has_w = 0, need_w = sizeof(int);
    if (lseek(fd, offset, SEEK_SET) < 0) {
        return -1;
    };
    while (has_w != sizeof(int)) {
        int was_w = write(fd, buf, need_w);
        if (was_w < 0) {
            return -1;
        }
        need_w -= was_w; has_w += was_w;
    }
    return 0;
}

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "wrong number args\n");
        return 1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "open: %s\n", strerror(errno));
        return 1;
    }
    size_t end_l = lseek(fd, 0, SEEK_END);
    size_t st_l = lseek(fd, 0, SEEK_SET);
    size_t sz = end_l - st_l;
    if (st_l < 0 || end_l < 0) {
        fprintf(stderr, "lseek: %s\n", strerror(errno));
        return 1;
    }

    if (end_l - st_l < 2 * sizeof(int)) {
        fprintf(stderr, "small size:\n");
        return 1;
    }
    int buf1_r, buf2_r;
    if (my_read(fd, &buf1_r, 0) < 0 || my_read(fd, &buf2_r, sz - (size_t)sizeof(int)) < 0 || 
    my_write(fd, &buf2_r, 0) < 0 || my_write(fd, &buf1_r, sz - (size_t)sizeof(int)) < 0) {
        return 1;
    }
    close(fd);
    return 0;
}