#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

int main() {
    int32_t a, b;
    scanf("%"SCNd32"%"SCNd32, &a, &b);
    if (a == INT32_MIN && b == 1) {
        printf("%"PRId32"\n", INT32_MIN);
        return 0;
    }
    if (a == 0) {
        printf("%d\n", 0);
        return 0;
    }
    if (b == 1) {
        printf("%"PRId32"\n", a);
        return 0;
    }
    int64_t right_border;
    int64_t left_border;
    int64_t r = a % b;
    if (a == b) {
        printf("%"SCNd32"\n", a);
        return 0;
    }
    if (a > 0) {
        right_border = (int64_t)a + (b - r);
        left_border = (int64_t)a - r;
    } else {
        right_border = (int64_t)a - r;
        left_border = (int64_t)a - (b + r);
    }
    if (left_border >= INT32_MIN && right_border <= INT32_MAX) {
        if ((a - left_border) < (right_border - a)) {
            printf("%"PRId64"\n", left_border);
            return 0;
        } else {
            printf("%"PRId64"\n", right_border);
            return 0;
        }
    }
    if (left_border < INT32_MIN) {
        printf("%"PRId64"\n", right_border);
        return 0;
    }
    if (right_border > INT32_MAX) {
        printf("%"PRId64"\n", left_border);
        return 0;
    }
    return 0;
}