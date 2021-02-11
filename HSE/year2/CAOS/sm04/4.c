#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>
#include <stdlib.h>



uint32_t fixed_mul(uint32_t a, uint32_t b, int n){
    if (n == 0) {
        uint32_t res;
        if (__builtin_mul_overflow(a, b, &res)) {
            res = UINT32_MAX;
        }
        return res;
    } else {
        uint64_t res = (uint64_t)a * (uint64_t)b;
        if ((res & (1ULL << (n - 1))) == 0) {
            res >>= n;
        } else {
            int f = 1;
            for (uint32_t i = 0; i <= (n - 1); ++i) {
                if ((res & (1ULL << i)) != 0) {
                    f = 0;
                }
            }
            if (f == 1) {
                res >>= n - 1;
            } else {
                res >>= n;
                res += 1;
            }

        };
        if (res > UINT32_MAX) {
            res = UINT32_MAX;
        }
        return res;
    }
};

// int main() {
//     uint32_t a, b;
//     int n;
//     scanf("%x%x%d", &a, &b, &n);
//     uint32_t res = fixed_mul(a, b, n);
//     printf("%x\n", res);
//     return 0;
// }
