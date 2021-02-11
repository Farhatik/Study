#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


int main(int argc, char * argv[]) {
    int32_t val1 = strtol(argv[1], NULL, 9);
    int32_t val2 = strtol(argv[2], NULL, 9);
    int f1 = 0, f2 = 0; int32_t res;
    if (__builtin_add_overflow(val1, val2, &res)) {
        f1++;
    }
    if (((val1 == INT32_MIN) && (val2 == -1)) || (val2 == 0)) {
        f2++;
    }
    printf("%d\n%d\n", f1, f2);
    return 0;
}