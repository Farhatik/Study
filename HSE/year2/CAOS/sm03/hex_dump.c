#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <ctype.h>

enum { BASE = 4, SIZE_OCTET = 8 };

int main() {
    int x_i;
    int counter_octets = 0;
    uint32_t sum_x_i = 0;
    int count_bytes = BASE;
    while (scanf("%x", &x_i) == 1) {
        if (count_bytes == BASE) {
            count_bytes = 0;
            continue;
        }

        counter_octets++;
        sum_x_i <<= SIZE_OCTET;
        sum_x_i += x_i;
        
        if (counter_octets % BASE == 0) {
            printf("%"PRIu32"\n", sum_x_i);
            count_bytes++;
        }

    }

    return 0;
}