#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>


int main(int argc, char * argv[]) {
    for (int i = 1; i < argc; ++i) {
        char * eptr = NULL; 
        errno = 0;
        long value = strtol(argv[i], &eptr, 10);
        if (errno || *eptr || !*argv[i]) {
            printf("%d\n", -1);
        } else {
            if (value == (int8_t)value) {
                printf("%d\n", 1);
            } else if (value == (int16_t)value) {
                printf("%d\n", 2);
            } else if (value == (int32_t)value){
                printf("%d\n", 4);
            } else {
                printf("%d\n", -1);
            }
        }
    }
}