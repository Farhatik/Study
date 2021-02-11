#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>

int main() {
    uint64_t sum_space = 0;
    char buf[5000];
    while (fgets(buf, 5000, stdin)) {
        uint64_t a, b;
        sscanf(buf, "%"SCNx64"-%"SCNx64, &a, &b);
        sum_space += b - a;
    }
    printf("%"PRIu64"\n", sum_space);
    return 0;
}