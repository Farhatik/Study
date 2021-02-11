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
    if (argc != 2) {
        exit(1);
    }
    void * handle;
    if ((handle = dlopen("/lib/libm.so.6", RTLD_LAZY)) == NULL) {
        exit(1);
    }; 
    double x;
    double (*libfunc)(double);
    void * sym = dlsym(handle, argv[1]);
    if (sym == NULL) {
        exit(1);
    }
    libfunc = sym; 
    while (scanf("%lf", &x) == 1) {
        printf("%.10g\n", libfunc(x));
    }
    if (dlclose(handle) < 0) {
        exit(1);
    };
    return 0;
}
