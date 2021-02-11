#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


int main(int argc, char * argv[]) {
    uint max_sz = 0;
    uint temp;
    uint sz = 0;
    while (scanf("%u", &temp) == 1) {
        if (temp > max_sz) {
            max_sz = temp;
        }
        sz += temp + (sz + temp) % temp;
    }
    if (sz == 0) {
        max_sz = 1;
        sz = 1;
    }
    if (sz % max_sz != 0) {
        sz += max_sz - sz % max_sz;
    }
    printf("%u %u\n", sz, max_sz);
    return 0;
}