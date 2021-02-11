// https://www.geeksforgeeks.org/how-to-compute-mod-of-a-big-number/
// ф-ия деления
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <math.h>
#include <pthread.h>

struct Temp 
{
    char * num;
    int k;
    int res;
};


void* func(void * ptr) {
    char * arg = ((struct Temp*)ptr)->num;
    int k = ((struct Temp*)ptr)->k;
    int res = 0;
    for (int i = 0; i < strlen(arg); i++) {
        res = (res* 10 + (int)arg[i] - '0') % k;
    }
    ((struct Temp*)ptr)->res = res;
    return ptr;
}


int main(int argc, char * argv[]) {
    if (argc <= 2) {
        printf("0\n");
        return 0;
    }
    pthread_t threads[argc - 2];
    
    struct Temp x;
    x.k = strtoll(argv[1], NULL, 10);
    struct Temp xs[argc - 2];
    int max = 0;
    for (int i = 2; i < argc; ++i) {
        xs[i - 2].num = argv[i];
        xs[i - 2].k = x.k;
        pthread_create(&threads[i - 2], NULL, func, &xs[i-2]);
    }


    for (int i = 0; i < argc - 2; ++i) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < argc - 2; ++i) {
        if (xs[i].res > max) {
            max = xs[i].res;
        }
    }

    printf("%d\n", max);

    return 0;
}