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

enum { MAX_BYTES = 64 };
struct MyType 
{
    unsigned char buf[MAX_BYTES];
};

int main(int argc, char * argv[]) {
    if (argc <= 3) {
        return 0;
    }
    char * name_lib = argv[1];
    void * handle;
    //"/lib32/libc.so.6"
    if ((handle = dlopen(name_lib ,RTLD_LAZY)) == NULL) {
        exit(1);
    }; 
    const char * name_func = argv[2];
    char * sign_func = argv[3];
    unsigned char arg_func[MAX_BYTES];

    int argc_func = strlen(sign_func) - 1; 

    int offset = 0;

    for (int i = 1; i <= argc_func; ++i) {
        int bytes = 0;
        if (sign_func[i] == 'i') {
            bytes = sizeof(int);
            int x = strtol(argv[i + 3], NULL, 10); 
            memcpy(arg_func + offset, &x, bytes);
        }
        if (sign_func[i] == 'd') {
            bytes = sizeof(double);
            double x = strtod(argv[i + 3], NULL); 
            memcpy(arg_func + offset, &x, bytes);
        }
        if (sign_func[i] == 's') {
            bytes = sizeof(char *);
            memcpy(arg_func + offset, &argv[i + 3], bytes);
        }
        offset += bytes;
    }

    void * sym = dlsym(handle, name_func);
    if (sym == NULL) {
        exit(1);
    };

    if (argc_func == 0) {
        if (*argv[3] == 'v') {
            ((void (*)()) sym)();
        }
        if (*argv[3] == 'i') {
            int res = ((int (*)()) sym)();
            printf("%d\n", res);
        }
        if (*argv[3] == 'd') {
            double res  = ((double (*)()) sym)();
            printf("%.10g\n", res);
        }
        if (*argv[3] == 's') {
            char * res = ((char* (*)()) sym)();
            printf("%s\n", res);
        }
    } else {
        struct MyType args;
        memcpy(args.buf, arg_func, offset); 
        if (*argv[3] == 'v') {
            ((void (*)(struct MyType)) sym)(args);
        }
        if (*argv[3] == 'i') {
            int res = ((int (*)(struct MyType)) sym)(args);
            printf("%d\n", res);
        }
        if (*argv[3] == 'd') {
            double res  = ((double (*)(struct MyType)) sym)(args);
            printf("%.10g\n", res);
        }
        if (*argv[3] == 's') {
            char * res = ((char* (*)(struct MyType)) sym)(args);
            printf("%s\n", res);
        }
    }
    return 0;
}

