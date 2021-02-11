#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int32_t satsum(int32_t v1, int32_t v2) {
    uint32_t res = (~(uint32_t)0) >> 1;
    int32_t answer = 0;
    if (__builtin_add_overflow(v1, v2, &answer)) {
        if (v1 < 0) {
            return (int32_t)(~res);
        } else {
            return (int32_t)res;
        }
    } else {
        return v1 + v2;
    }
}
