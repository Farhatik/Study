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
    int ret = -1;
    for (int i = 1; i < argc; ++i) {
        ret = -1;
        if (access(argv[i], F_OK) < 0) {
            printf("%d\n", ret);
            continue;
        };
        int fd = open(argv[i], O_RDONLY);
        //printf("%s\n", argv[i]);
        if (fd < 0) {
            printf("%d\n", ret);
            continue;
        }
        struct stat stb;
        if (fstat(fd, &stb) < 0) {
            printf("%d\n", ret);
            continue;  
        };
        size_t sz = stb.st_size;
        //printf("%d\n", sz);
        if (sz != stb.st_size) {
            printf("%d\n", ret);
            continue;   
        }
        ret = 0;
        if (sz == 0) {
            printf("%d\n", ret);
            continue;
        }
        void * ptr = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, 0);
        if (ptr == MAP_FAILED) {
            printf("%d\n", ret);
            continue; 
        }
        const unsigned char *st_f = ptr;
        const unsigned char *end_f = ptr + sz;
        for (;st_f != end_f; ++st_f) {
            //printf("%c", *st_f);
            if ((*st_f)== '\n') ret++;
        }
        if (*(--st_f) != '\n') {
            ret++;
        }
        printf("%d\n", ret);
    }
    return 0;
}