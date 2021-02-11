#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>



int main(int argc, char * argv[]) {
    if (argc < 4) {
        fprintf(stderr, "few arguments\n");
        exit(1);
    }
    if (argc > 4) {
        fprintf(stderr, "many arguments\n");
        exit(1);
    }
    int64_t line1 = strtoll(argv[2], NULL, 10);
    int64_t line2 = strtoll(argv[3], NULL, 10);
    if (line1 >= line2) {
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
    }
    int offset;
    int length;



    mmap(NULL, length, PROT_READ, MAP_SHARED, fd, offset);
    return 0;
}