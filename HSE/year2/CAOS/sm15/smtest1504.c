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



struct MyNum 
{
    int64_t x;
    char * ptr;
};

void decode(char * first, char * end) {
    int64_t result = 0, shift = 0;
    for  (;first != end; ++first) {
        unsigned char byte = *first;
        result |= (byte & 0x7f) << shift;
        shift += 7;
        if ((0x80 & byte) == 0) {
            if (shift < 32 && (byte & 0x40) != 0) {
                printf("%ld\n",  result | ((0xFFFFFFFF) << shift));
            }
            return printf("%ld\n", result);
            shift = 0;
            result = 0;
        }
    }
}


int main(int argc, char * argv[]) {
    if (argc < 2) {
        return 0;
    }
    int fd = open(argv[1], O_RDONLY);
    struct stat buf;
    fstat(fd, &buf);
    size_t sz = buf.st_size;
    void * ptr = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, 0);
    char * st = ptr;
    char * end = st + sz;
    char b = *st;
    decode(st, end);



    return 0;
}