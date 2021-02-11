#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct Funct {
    char
}


uint32_t fixed_mul(uint32_t a, uint32_t b, int n){
    if (n == 0) {
        uint32_t res;
        if (__builtin_mul_overflow(a, b, &res)) {
            res = UINT32_MAX;
        }
        return res;
    } else {
        uint64_t res = (uint64_t)a * (uint64_t)b;
        if (res == 0) {
            return res;
        }
        int f_mid = 1;
        for (int i = 0; i < n - 1; ++i) {
            if (a & (1 << i)) {
                f_mid = 0;
            }
        }
        res = res >> (n - 1);
        if (f_mid) {
            if (res % 2 == 1) {
                res >>= 1;
                if (res > INT32_MAX) {
                    return INT32_MAX;
                }
                return res + res % 2;
            } 
            if (res % 2 == 0) {
                res >>= 1;
                if (res > INT32_MAX) {
                    return INT32_MAX; 
                }
                return res;
            }
        } else {
            res >>= 1;
            if (res > INT32_MAX) {
                return INT32_MAX;
            }
            return res + 1;
        }
    }
    return 0;   
}

// int main() {
//     uint32_t a, b;
//     int n;
//     scanf("%x%x%d", &a, &b, &n);
//     uint32_t res = fixed_mul(a, b, n);
//     printf("%x\n", res);
//     return 0;
// }