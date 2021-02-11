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
        // printf("%d\n", a.x);
        first = a.ptr;
        sumfile += a.x;
    }
    df.sf = sumfile;
    df.num = a;
    return df;
}


struct MyMap getmaxmmap(int fd, size_t sz) {
    size_t offset = 0;
    void * ptr = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, offset);
    struct MyMap x; x.ptr = NULL; x.entire = 0;
    // if (ptr != MAP_FAILED) {
    //     x.ptr = ptr; x.sz = sz; x.entire = 1;
    //     return x;
    // }
    int n = 1;
    size_t psz = 4 * getpagesize();
    // ptr = mmap(NULL, n * psz, PROT_READ, MAP_SHARED, fd, offset);
    // while (ptr != MAP_FAILED) {
    //     munmap(ptr, n * sz);
    //     n++;
    //     ptr = mmap(NULL, n * psz, PROT_READ, MAP_SHARED, fd, offset);
    // };
    x.sz = psz;
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

    struct MyMap maxsz = getmaxmmap(fd, sz);
    printf("%u\n%u\n", sz, maxsz.sz);

    if (maxsz.entire) {
        char * st = maxsz.ptr;
        char * end = st + sz;
        printf("%"PRId64"\n", decode_file(st, end).sf);
    } else {
        int64_t temp = sz;   int64_t sumfile = 0;   size_t offset = 0;
        struct DecFile df;  df.sf = 0;
        int f = 0;  char * st;  char * end; 

        while (offset + maxsz.sz < sz) {
            printf("temp = %d, f = %d, offset = %u, sumfile = %ld\n", temp, f,   offset, sumfile);

            void * ptrtemp = mmap(NULL, maxsz.sz, PROT_READ, MAP_SHARED, fd, offset);
            st = ptrtemp + f;
            end = ptrtemp + maxsz.sz;
            printf("!!!!!!!!!!!!!!!!!!\n");

            struct DecFile tempdf = decode_file(st, end);
            printf("tempdf = %ld\n", tempdf.sf);
            sumfile += tempdf.sf;
            // return 0;
            printf("****sumfile = %ld*****\n",sumfile);
            if (tempdf.num.ptr == NULL) {
                int after = getpagesize();
                if (offset + maxsz.sz + getpagesize() > sz) {
                    after = temp - maxsz.sz;
                }

                void * ptrtemp2 = mmap(NULL, after, PROT_READ, MAP_SHARED, fd, offset + maxsz.sz);

                st = ptrtemp2; end = ptrtemp2 + after;

                struct MyNum y = decode_num2(df.num.shift, df.num.res, st, end);
                sumfile += y.x;
                f = y.shift;
                printf("%d\n", y.x);
                munmap(ptrtemp2, after);
            } else {
                f = 0;
            }

            munmap(ptrtemp, maxsz.sz);
            offset += maxsz.sz;
            temp -= maxsz.sz;
        }
        offset -= maxsz.sz;

        if (temp < maxsz.sz) {
            temp = temp + maxsz.sz;
            void * ptrtemp5 = mmap(NULL, temp, PROT_READ, MAP_SHARED, fd, offset);
            st = ptrtemp5 + f; end = ptrtemp5 + temp;
            sumfile += decode_file(st, end).sf;
            munmap(ptrtemp5, temp);
            printf("f = %d, temp = %d, offset = %u, sumfile = %ld\n", f, temp, offset, sumfile);
        } 

        printf("%"PRId64"\n", sumfile);
    }
    close(fd);
    return 0;
}