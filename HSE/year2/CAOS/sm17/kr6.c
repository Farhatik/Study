//https://github.com/hseos/hseos-course/tree/master/2017/14-files3 
//Читал и изучал тут

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
#include <dlfcn.h>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        fprintf(stderr, "few argsn\n");
        exit(1);
    }

    
    void * pr_handle = NULL;
    void * cur_handle = NULL; 
    float x;
    float (*libfunc)(float);
    sscanf(argv[1], "%f", &x);

    if (argc == 2) {
        printf("%.6g\n", x);
        return 0;
    }


    for (int i  = 0 ; i < argc / 2 - 1; ++i) {
        if (strcmp(argv[2*i + 2], "-") == 0) {
            cur_handle = pr_handle;
        } else {
            if ((cur_handle = dlopen(argv[2*i + 2], RTLD_LAZY)) == NULL) {
                continue;
            }
        }
        pr_handle = cur_handle;

        void * sym = dlsym(cur_handle, argv[2*i + 3]);
        if (sym == NULL) {
            continue;
        }
        libfunc = sym;

        x = libfunc(x);
        // if (dlclose(cur_handle) < 0) {
        //     exit(1);
        // }
    };    
    printf("%.6g\n", x);
    return 0;
}