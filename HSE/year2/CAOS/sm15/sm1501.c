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
    if (argc != 2) {
        fprintf(stderr, "few arguments\n");
        exit(1);
    }
    int fd = open(argv[1], O_RDONLY);
        if (argc != 2) {
        fprintf(stderr, "open: %s\n", strerror(errno));
        exit(1);
    }
    struct stat stb;
    fstat(fd, &stb);
    size_t sz = stb.st_size;
    if (sz != stb.st_size) {
        fprintf(stderr, "file is too big\n"); 
        exit(1);
    }
    void * ptr = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        fprintf(stderr, "mmap: %s\n", strerror(errno));
        exit(1);
    }
    close(fd);
    double *s1 = ptr;
    double *s2 = ptr + sz;

    double count = 0;
    double sum = 0;
    for (; s1< s2; ++s1) {
        sum += *s1;
        count++;
    }

    printf("%a\n", sum/count);


    munmap(ptr, sz);


    return 0;
}