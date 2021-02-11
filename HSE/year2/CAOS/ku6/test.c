#include <sys/stat.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    DIR *dir = opendir(argv[1]);
    int64_t sizeLimit = strtoll(argv[2], NULL, 10);
    int64_t size = 0, mxSize = 0;
    struct stat info;
    char name[1024];

    if (dir != NULL) {
        struct dirent *data = readdir(dir);
        while (data) {
            char buf[PATH_MAX + 1];
            snprintf(buf, PATH_MAX, "%s/%s", argv[1], data->d_name);
            if (lstat(buf, &info) == 0 && S_ISREG(info.st_mode) && !S_ISLNK(info.st_mode)) {
                size += info.st_size;
                if (info.st_size > mxSize) {
                    mxSize = info.st_size;
                    strcpy(name, data->d_name);
                } else if (info.st_size == mxSize) {
                    if (strcmp(name, data->d_name) > 0) {
                        strcpy(name, data->d_name);
                    }
                }
            }
            data = readdir(dir);
        }
        closedir(dir);
    }
    
    if (size <= sizeLimit) {
        printf("%"PRId64"\n", size);
    } else {
        printf("%s\n", name);
    }

    return 0;
}