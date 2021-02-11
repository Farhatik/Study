#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char * argv[]) {
    uint64_t size_of_all_files = 0;
    for (int i = 1; i < argc; ++i) {
        if (!access(argv[i], F_OK)) {
            continue;
        }
        struct stat f;
        stat(argv[i], &f);
        if (!S_ISREG(f.st_mode)) {
            continue;
        }
        if (S_ISLNK(f.st_mode)) {
            continue;
        }
        if (f.st_nlink != 1) {
            continue;
        }
        size_of_all_files += f.st_size;
    }
    printf("%"PRIu64"\n", size_of_all_files);
    return 0;
}