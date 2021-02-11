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


enum { SST = 10 };

struct Data
{
    int16_t x;
    int64_t y;
};

void marshall(unsigned char *out, const struct Data *in) {
    
};
void unmarshall(struct Data *out, const unsigned char *in){
};

ssize_t get_data_count(int fd) {
    return (lseek(fd, 0, SEEK_END) - lseek(fd, 0, SEEK_SET)) / 10;
};

int get_data(int fd, size_t pos, struct Data* out) {
    lseek(fd, pos * SST, SEEK_SET);
    char buf[10];
    if (read(fd, buf, SST) != SST) {
        exit(2);
    }

    int16_t x = 0;

    memcpy(&x, buf, sizeof(x));

    int64_t y = 0;
    memcpy(&y, buf + sizeof(x), sizeof(y));

    x = le16toh(x);
    y = le64toh(y);
    out->x = x;
    out->y = y;


    return 1;
};

int set_data(int fd, size_t pos, struct Data* in) {
    
    lseek(fd, pos * SST, SEEK_SET);

    int16_t x = htole16(in->x);
    int64_t y = htole64(in->y);
    
    char buf[10];
    memcpy(buf, &x, sizeof(x));
    memcpy(buf + sizeof(x), &y, sizeof(y));

    if (write(fd, buf, SST) != SST) {
        exit(2);
    } 
    return 1;
};

int modify(struct Data* temp, int32_t a) {
    int64_t c = (int64_t)(temp->x) * (int64_t)a;
    int64_t res;

    if (__builtin_add_overflow(temp->y, c, &res)) {
        exit(3);
    }
    temp->y = res;

    return 0;
}

int run(int fd, int32_t in_a) {
    ssize_t res = get_data_count(fd);
    if (res < 0) {
        return -1;
    }
    size_t size = (size_t)res;
    for (size_t i = 0; i < ((size + 1) >> 1); i++) {
        size_t j = size - i - 1;
        struct Data a, b;
        int status = (
            get_data(fd, i, &a) != -1
            && get_data(fd, j, &b) != -1
            && modify(&a, in_a) != -1
            && modify(&b, in_a) != -1
            && set_data(fd, i, &b) != -1
            && set_data(fd, j, &a) != -1
        );
        if (!status) {
            return -1;
        }
    }
    return 1;
}

int main(int argc, char * argv[]) {
    char* path_out = argv[1];
    int fd_out = -1;
    int32_t a;
    sscanf(argv[2], "%d", &a);
    fd_out = open(
            path_out, O_RDWR
        );
    if (fd_out > 0) {
        run(fd_out, a);
    }

    if (fd_out != -1) {
        close(fd_out);
    }

    return 0;
}