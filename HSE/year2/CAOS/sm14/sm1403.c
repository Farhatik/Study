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
#include <linux/limits.h>
#include <strings.h>

int compare(const void * a, const void * b) {
    const char * x1 = *(const char **)a;
    const char * x2 = *(const char **)b;
    return strcasecmp(x1, x2);
}


struct ListDirs 
{
    size_t qty;
    char * * ptrs;
};

struct ListDirs getdirs(DIR *dp, char * path) {
    char * * bufptrs = NULL;
    size_t qty = 0;
    struct dirent * dirp = NULL;
    while ((dirp = readdir(dp)) != NULL) {
        if ((strcmp(dirp->d_name, ".") == 0) || (strcmp(dirp->d_name, "..") == 0)) {
            continue;
        }
        if (dirp->d_type != DT_DIR) {
            continue;
        }
        size_t dn_s = strlen(dirp->d_name);
        qty++;
        bufptrs = realloc(bufptrs, qty * sizeof(*bufptrs));
        char * temp = malloc(dn_s + 1);
        strcpy(temp, dirp->d_name);
        bufptrs[qty - 1] = temp;
        
    }
    struct ListDirs data;
    data.qty = qty;
    data.ptrs = bufptrs;
    if (qty != 0) {
        qsort(data.ptrs, data.qty, sizeof(*data.ptrs), compare);
    }
    // closedir(dp);
    return data;
}



int mydopath(char * fullpath, int off_set ) {
    if (strlen(fullpath) > PATH_MAX - 1) {
        return -1;
    }
    DIR * dp = opendir(fullpath);

    if (dp == NULL) {
        return -1;
    }
    if (off_set) {
        printf("cd %s\n", fullpath + off_set);
    }
    struct ListDirs data = getdirs(dp, fullpath);
    closedir(dp);
    if (data.qty == 0) {
        return 1;
    }
    for (size_t i = 0; i < data.qty; ++i) {
        size_t fp_s = strlen(fullpath);
        fullpath[fp_s] = '/';
        strcpy(fullpath + fp_s + 1, data.ptrs[i]);
        // printf("fullpath = %s\n", fullpath);
        //printf("fullpath = %s\n", fullpath strlen(data.ptrs[i]));
        int res = mydopath(fullpath, fp_s + 1);
        fullpath[fp_s] = '\0';
        off_set = 1;
        if (off_set && (res != -1)) {
            printf("cd ..\n");
            }
        free(data.ptrs[i]);
    }
    return 0;
}
 
int main(int argc, char * argv[]) {
    char * fullpath = malloc(10*PATH_MAX);
    strcpy(fullpath, argv[1]);
    int off_set = 0;
    mydopath(fullpath, off_set);
    free(fullpath);
    return 0;
}
