#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    int64_t x, b;
    scanf("%ld%ld", &x, &b);
    int64_t sum = 0;
    while (x != 0) {
        int64_t temp = x % b;
        if (temp > 0) {
            sum += temp;
        } else {
            sum -= temp;
        }
        x = x / b;
    }
    printf("%ld\n", sum);
    return 0;
}