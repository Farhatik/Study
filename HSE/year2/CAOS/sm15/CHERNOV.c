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
        return a;
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
    if (ptr != MAP_FAILED) {
        x.ptr = ptr; x.sz = sz; x.entire = 1;
        return x;
    }
    int n = 1;
    size_t psz = getpagesize();
    ptr = mmap(NULL, n * psz, PROT_READ, MAP_SHARED, fd, offset);
    while (ptr != MAP_FAILED) {
        munmap(ptr, n * psz);
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

    struct MyMap maxsz = getmaxmmap(fd, sz);
    printf("%u\n%u\n", sz, maxsz.sz);

    if (maxsz.entire) {
        char * st = maxsz.ptr;
        char * end = st + sz;
        printf("%"PRId64"\n", decode_file(st, end).sf);
    } else {
        int64_t sumfile = 0;   size_t offset = 0;
        struct DecFile df;  df.sf = 0;
        int offset_st = 0;  char * st;  char * end; 
        void * ptr;
        while (offset + maxsz.sz < sz) {
            ptr = mmap(NULL, maxsz.sz, PROT_READ, MAP_SHARED, fd, offset);
            st = ptr + offset_st;
            end = ptr + maxsz.sz;
            df = decode_file(st, end);
            sumfile += df.sf;
            // printf("offset_st = %d, offset = %u, sumfile = %ld\n", offset_st, offset, sumfile);
            if (df.num.ptr == NULL) {
                int after = getpagesize();
                if (offset + maxsz.sz + after > sz) {
                    after = sz - offset - maxsz.sz;
                }
                void * ptr2 = mmap(NULL, after, PROT_READ, MAP_SHARED, fd, offset + maxsz.sz);
                struct MyNum x = decode_num2(df.num.shift, df.num.res, ptr2, ptr2 + after);
                sumfile += x.x;
                // printf("%d\n", x.x);
                offset_st = x.shift;
                munmap(ptr2, after);
            } else {
                offset_st = 0;
            }
            munmap(ptr, maxsz.sz);
            offset += maxsz.sz;
        }
        ptr = mmap(NULL, sz - offset, PROT_READ, MAP_SHARED, fd, offset);
        st = offset_st + ptr; end = ptr + (sz - offset);
        df = decode_file(st, end);
        munmap(ptr, sz - offset);
        sumfile += df.sf;
        printf("%"PRId64"\n", sumfile);
    }

    return 0;
}