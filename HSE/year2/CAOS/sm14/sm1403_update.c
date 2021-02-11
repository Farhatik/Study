//https://github.com/hseos/hseos-course/tree/master/2017/13-files2
//Читал конспекты 

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


int compare(const void * a, const void * b) {
    const char * x1 = *(const char **)a;
    const char * x2 = *(const char **)b;
    return strcasecmp(x1, x2);
}



void gotodir(char * path, char * namedir) {
    if (strlen(path) + strlen(namedir) + 1 > PATH_MAX - 1) {
        return;
    }
    if (namedir == NULL) {
        return;
    }
    char buf[PATH_MAX + 2];

    DIR * dp = opendir(path);
    if (dp == NULL) {
        return;
    }
    struct dirent * dirp = readdir(path);
    size_t start_sz = 7;
    size_t qty = 0;
    char * * temp_list = malloc(sizeof(*temp_list) * start_sz);
    if (dirp == NULL) {
        return;
    }
    while (dirp != NULL) {
        if (strcmp(dirp->d_name, "." == 0 || (strcmp("..", dirp->d_name == 0))  {
            continue;
        }
        if (dirp->d_type != DT_DIR) {
            continue;
        }
        if (qty + 1 > start_s) {
            temp_list = realloc(dirp->d_name, qty + 1)
        }

    }
    qsort(dirp)

    return 
}


int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "few args\n");
        exit(1);
    }

    
    return 0;
}