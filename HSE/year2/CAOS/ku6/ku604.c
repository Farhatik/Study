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
#include <math.h>
#include <limits.h>
#include <float.h>


int compare(const void * x1, const void * x2)   {
    if (*(double*)x1 < *(double*)x2) {
        return -1;
    } else if (*(double*)x1 == *(double*)x2) {
        return 0;
    } else {
        return 1;
    }
}


int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "few args\n");
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "open: %s\n", strerror(errno));
        exit(1);
    }
    struct stat stb;
    if (fstat(fd, &stb) < 0) {
        exit(1);
    };
    size_t sz = stb.st_size;
    if (sz != stb.st_size) {
        fprintf(stderr, "file is too big\n"); 
        exit(1);
    }
    if (!sz) {
        printf("0\n");
        return 0;   
    }
    double x = 0;
    int qty = sz / sizeof(x);

    double res = 0;

    void * ptr = mmap(NULL, sz, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
    if (ptr == MAP_FAILED) {
        fprintf(stderr, "map: %s\n", strerror(errno)); 
        exit(1);
    }
    close(fd);
    double *s1 = ptr + qty/10 * sizeof(x);
    double *s2 = ptr + sz - qty/10 * sizeof(x);
    qsort(s1, qty - 2 * qty/10, sizeof(res), compare);
    int k = qty - 2 * qty/10;
    for (double * i = s1 + k/10; i != s2 - k/10; ++i) {
        res += *i;
    }

    printf("%.10g\n", res/(double)(qty - 2 * qty/10 - 2 * k/10));
    munmap(ptr, sz);
    
    return 0;
}