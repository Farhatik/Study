#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
int main() {
    int32_t a;
    uint32_t b;
    scanf("%d%u", &a, &b);
    int32_t c = INT32_MAX;
    int64_t temp = INT64_MAX;
    for (int32_t i = INT32_MAX; i > INT32_MIN; --i) {
        if ((int64_t)i % (int64_t)b == 0) {
            if (temp > llabs((int64_t)a - (int64_t)b)) {
                c = i;
            }
        }
    }
    printf("%d\n", c);
    return 0;
}
