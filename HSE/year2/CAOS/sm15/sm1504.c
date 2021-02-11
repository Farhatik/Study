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
#include <inttypes.h>


struct MyNum 
{
    int32_t x;
    char * ptr;
    int res;
    int shift;
};

struct DecFile 
{
    struct MyNum num;
    int64_t sf;
};

struct MyMap 
{
    size_t sz;
    void * ptr;
    int entire;
};

struct MyNum decode_num(char * first, char * end) {
    int32_t result = 0, shift = 0;
    struct MyNum a;
    a.ptr = NULL;
    for (;first != end; ++first) {
        unsigned char byte = *first;
        result |= (byte & 0x7f) << shift;
        shift += 7;
        if ((0x80 & byte) == 0) {
            a.ptr = ++first;
            if (shift < 32 && (byte & 0x40) != 0) {
                a.x = result | ((0xFFFFFFFF) << shift);
                // printf("%d\n", a.x);
                return a;
            }
            a.x = result;
            return a;
        }
    }
    a.ptr = NULL;
    a.shift = shift;
    a.res = result;
    return a;
}


struct MyNum decode_num2(int shift, int result, char * first, char * end) {
        struct MyNum a;
        int offset = 0;
        for (;first != end; ++first) {
            offset++;
            unsigned char byte = *first;
            result |= (byte & 0x7f) << shift;
            shift += 7;
            if ((0x80 & byte) == 0) {
                a.ptr = ++first;
                if (shift < 32 && (byte & 0x40) != 0) {
                    a.x = result | ((0xFFFFFFFF) << shift);
                    a.shift = offset;
                    return a;
                }
                a.shift = offset;
                a.x = result;
                return a;
            }
        }
}

struct DecFile decode_file(char * first, char * end) {
    struct DecFile df;
    int64_t sumfile = 0;
    struct MyNum a;
    while (first != end) {
        a = decode_num(first, end);
        if (a.ptr == NULL) {
            break;
        }
        first = a.ptr;
        sumfile += a.x;
        // printf("%d\n", a.x);
        // printf("sumfile = %ld\n", sumfile);
    }
    df.sf = sumfile;
    df.num = a;
    return df;
}


struct MyMap getmaxmmap(int fd, size_t sz) {
    size_t offset = 0;
    void * ptr = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, offset);
    struct MyMap x; x.ptr = NULL; x.entire = 0;
    if (ptr != MAP_FAILED) {
        x.ptr = ptr; x.sz = sz; x.entire = 1;
        return x;
    }
    int n = 1;
    size_t psz = getpagesize();
    ptr = mmap(NULL, n * psz, PROT_READ, MAP_SHARED, fd, offset);
    while (ptr != MAP_FAILED) {
        munmap(ptr, n * sz);
        n++;
        ptr = mmap(NULL, n * psz, PROT_READ, MAP_SHARED, fd, offset);
    };
    x.sz = (n - 1) * psz;
    x.entire = 0;
    return x;
}



int main(int argc, char * argv[]) {
    if (argc < 2) {
        return 0;
    }
    int fd = open(argv[1], O_RDONLY);
    struct stat buf;
    fstat(fd, &buf);
    size_t sz = buf.st_size;
    if (!sz) {
        printf("0\n0\n0\n");
        return 0;
    }
    // size_t psz = getpagesize();

    // while (void * ptr = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, offset); 
    struct MyMap maxsz = getmaxmmap(fd, sz);
    printf("%u\n%u\n", sz, maxsz.sz);
    if (maxsz.entire) {
        char * st = maxsz.ptr;
        char * end = st + sz;
        // printf("********************************\n");
        printf("%"PRId64"\n", decode_file(st, end).sf);
    } else {
        size_t temp = sz;
        int64_t sumfile = 0;
        size_t offset = 0;
        struct DecFile df; df.sf = 0;
        int f = 0;
        char * st; char * end; 
        while (temp > 0) {
            temp -= maxsz.sz;
            void * ptrtemp = mmap(NULL, maxsz.sz, PROT_READ, MAP_SHARED, fd, offset);
            if (!f) {st = ptrtemp;}
            else {
                st = ptrtemp + f;
            }
            end = st + maxsz.sz;
            struct DecFile tempdf = decode_file(st, end);
             sumfile += tempdf.num.x;
            if (tempdf.num.ptr == NULL) {
                void * ptrtemp = mmap(NULL, getpagesize(), PROT_READ, MAP_SHARED, fd, offset + maxsz.sz);
                st = ptrtemp; end = st + getpagesize();
                struct MyNum y = decode_num2(df.num.shift, df.num.res, st, end);
                sumfile += y.x;
                f = y.shift;
            }
            // printf("%"PRId64"\n", sumfile);
            munmap(ptrtemp, maxsz.sz);
            offset += maxsz.sz;
        }
        offset -= maxsz.sz;
        if (temp != 0) {
            temp += maxsz.sz;
            void * ptrtemp = mmap(NULL, temp, PROT_READ, MAP_SHARED, fd, offset);
            char * st = ptrtemp; char * end = st + temp;
            sumfile += decode_file(st, end).sf;
            munmap(ptrtemp, temp);
        } 
        printf("%"PRId64"\n", sumfile);
    }
    close(fd);
    return 0;
}