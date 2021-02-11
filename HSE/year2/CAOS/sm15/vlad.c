#include <stdio.h>
#include <inttypes.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h> 
#include <stdbool.h>


int file_d;
int64_t file_size;
int open_file(int argc, char *argv[]) {
    file_d = open(argv[1], O_RDONLY);
    if (file_d == 1) {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return 1;
    }
    struct stat file_stat;
    if (fstat(file_d, &file_stat) == -1) {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return 1;
    }
    file_size = file_stat.st_size;
    return file_d;
}


int64_t max_page_size = 1, cur_fragment = 0;
void find_max_mmap_size() {
    while (true) {
        void *mp = mmap(NULL, max_page_size * getpagesize(), PROT_READ, MAP_PRIVATE, file_d, 0);
        if (mp == MAP_FAILED) {
            max_page_size -= 1;
            cur_fragment = max_page_size * getpagesize();
            break;
        }
        if (max_page_size * getpagesize() >= file_size) {
            cur_fragment = file_size;
            break;
        }
        max_page_size++;
    }
    //
    max_page_size = 4;
    cur_fragment = getpagesize() * max_page_size;
}

int64_t sum_ = 0;
int32_t result = 0, shift = 0, i = 0;
void decode(char *data) {
    while (true) {
        if (i == cur_fragment) {
            //printf("breaked with i=%d\n", i);
            i = 0;
            break;
        }
        //printf("i = %d, %ld\n", i, max_page_size * getpagesize());
        const char byte= data[i];
        result |= (byte & 0x7f) << shift;
        shift += 7;
        if ((0x80 & byte) == 0) {
            if (shift < 32 && (byte & 0x40) != 0) {
                sum_ += result | (~0 << shift);
                // printf("%d\n", result | (~0 << shift));
                result = 0; shift = 0; i++;
                continue;
            }
            sum_ += result;
            // printf("%d\n", result);
            result = 0; shift = 0; i++;
            continue;
            
        }
        i++;
    }
}

int main(int argc, char*argv[]) {
    if (open_file(argc, argv) == 1) return 1;
    printf("%" PRId64 "\n", file_size);

    find_max_mmap_size();
    printf("%" PRId64 "\n", cur_fragment);

    int64_t alr_mmaped = 0;
    while (alr_mmaped < file_size) {
        void *mp = mmap(NULL, cur_fragment, PROT_READ, MAP_PRIVATE, file_d, alr_mmaped);
        char *data = mp;
        printf("\nnew fragment, alr = %lld, cur_frg = %lld\n", alr_mmaped, cur_fragment);
        decode(data);
        munmap(mp, cur_fragment);


        alr_mmaped += cur_fragment;
        bool flag = false;
        while (max_page_size * getpagesize() >= file_size - alr_mmaped) {
            max_page_size--;
            flag = true;
        }
        if (flag) max_page_size++;
        cur_fragment = max_page_size * getpagesize();
        if (file_size - alr_mmaped < cur_fragment)
        cur_fragment = file_size - alr_mmaped;
    }
    printf("%" PRId64 "\n", sum_);
    return 0;
}