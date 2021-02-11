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

void copy_file(int in_fd, int out_fd) {
    int readed = 0;
    int wrote = 0;

    char buf[SBUF];
    while ((readed = read(in_fd, buf, SBUF)) > 0) {
        int need_written = readed;
        int written = 0;
        while (need_written > 0) {
            wrote = write(out_fd, buf + written, need_written);
            need_written -= wrote;
            written += wrote;
        }
    }
}

// int main() {
//     copy_file(0, 1);
//     return 0;
// }