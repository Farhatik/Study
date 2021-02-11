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


enum { SBUF = 4096 };

// struct FileContent
// {
//     ssize_t size;
//     char *data;
// };

struct FileContent read_file(int fd) {
    struct FileContent res = {-1, NULL};
    int readed = 0;
    char * data = NULL;
    char * ptr2 = NULL;
    char buf[SBUF];
    ssize_t counter = 0;
    while ((readed = read(fd, buf, SBUF)) > 0) {
        counter += readed;
        ptr2 = realloc(data, counter);
        if (ptr2 == NULL) {
            free(data);
            return res;
        } else {
            data = ptr2;
        }
        memcpy(data + counter - readed, buf, readed);
    }
    if (readed < 0) {
        free(data);
        return res;
    }
    ptr2 = realloc(data, counter + 1);
    if (ptr2 == NULL) {
        free(data);
        return res;
    } else {
        data = ptr2;
    }
    data[counter] = '\0';
    res.size = counter;
    res.data = data;
    return res;
}


