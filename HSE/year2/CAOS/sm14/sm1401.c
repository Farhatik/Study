//Пользовался семинарами Белякова https://github.com/hseos/hseos-course/tree/master/2017/13-files2

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

int main(int argc, char * argv[]) {
    uint64_t size_all_files = 0;
    
    if (argc != 2) {
        fprintf(stderr, "NO PATH");
        return 1;
    }

    DIR *dp;
    if ((dp = opendir(argv[1])) == NULL) {
        fprintf(stderr, "Can't open directory");
        exit(1);
    };

    struct dirent * dirp;
    while ((dirp = readdir(dp)) != NULL) {
        struct stat statbuf;
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
            continue;
        }
        uint64_t pd_s = strlen(argv[1]);
        uint64_t dn_s = strlen(dirp->d_name);
        char * buf = malloc(pd_s + dn_s + 2);
        if (buf == NULL) {
            continue;
        }
        strcpy(buf, argv[1]);
        buf[pd_s] = '/';
        strcpy(buf + pd_s + 1, dirp->d_name);
        buf[pd_s + dn_s + 1] = '\0';
        if (stat(buf, &statbuf) == -1 || (!S_ISREG(statbuf.st_mode)) ||
            (getuid() != statbuf.st_uid) || (!isupper(dirp->d_name[0]))) {
            free(buf);
            continue;
        }
        size_all_files += (uint64_t)statbuf.st_size;
        free(buf);
    }
    printf("%"PRIu64"\n", size_all_files);
    if (closedir(dp) != 0) {
        fprintf(stderr, "Can't close directory");
        exit(1);
    };
    return 0;
}