#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

uint32_t satsum(uint32_t v1, uint32_t v2) {
    uint32_t res;
    if (__builtin_add_overflow(v1, v2, &res)) {
        res = ~0;
    }
    return res;
};
