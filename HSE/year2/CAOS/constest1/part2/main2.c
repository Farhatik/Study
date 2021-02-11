#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    uint32_t a, b = 0;
    scanf("%u%u", &a, &b);
    
    uint32_t a_k = a / 2;
    uint32_t b_k = b / 2;
    
    uint32_t a_r = a % 2;
    uint32_t b_r = b % 2;
    
    uint32_t result = a_k + b_k + ((a_r + b_r) / 2);
    
    printf("%u\n", result);
    return 0;
}