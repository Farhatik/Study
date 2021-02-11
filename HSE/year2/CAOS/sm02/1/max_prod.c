#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main()
{
    uint32_t c;
    uint32_t max2, max;
    max2 = 0;
    max = 0;
    while (scanf("%u", &c) == 1) {
        if (c > max) {
            max2 = max;
            max = c;
        } else if (c > max2) {
            max2 = c;
        }
    }
    uint32_t max_product = max2 * max;
    printf("%u\n", max_product);
    return 0;
}