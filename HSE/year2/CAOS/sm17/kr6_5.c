#include <stdio.h>
#include <stdint.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>
//#include <linux/limits.h>
#include <strings.h>

int main(int argc, char * argv[]) {
    int64_t sz = strtoll(argv[2], NULL, 10);
    DIR * dp = opendir(argv[1]);
    char * path = argv[1];
    int64_t sum = 0;
    int64_t max = -1;
    struct dirent * dirp;
    char buf1[10000];
    int f = 0;
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
            continue;
        }

        if (dirp->d_type != DT_REG) {
            continue;
        }
        size_t p_s = strlen(argv[1]);
        size_t dn_s = strlen(dirp->d_name);
        char * buf = malloc(p_s + dn_s + 2);
        strcpy(buf, path);
        buf[p_s] = '/';
         strcpy(buf + p_s + 1, dirp->d_name);
        struct stat st_bf;
        stat(buf, &st_bf);
        sum += st_bf.st_size;
        if (st_bf.st_size > max) {
            max = st_bf.st_size;
            strcpy(buf1, dirp->d_name);
        } if (st_bf.st_size == max) {
            if (strcmp(buf1, dirp->d_name) > 0) {
                strcpy(buf1, dirp->d_name);
            }
        }
        if (sum > sz) {
            f = 1;
        }
        free(buf);
    }
    if (f) {
        printf("%s\n", buf1);
    }
    return 0;
}