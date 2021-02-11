#include <stdio.h>
#include <stdint.h>

enum { BASE_SIGN = 31, LEFT_EXP = 1, RIGHT_EXP = 24, BASE_MANT = 9 };

union Float 
{
    float f;
    uint32_t n;
};

int main() {
    union Float x;
    while (scanf("%f", &x.f) != EOF) {
        uint32_t sign = x.n >> BASE_SIGN;
        uint32_t exp = (x.n << LEFT_EXP) >> RIGHT_EXP;
        uint32_t mant = (x.n << BASE_MANT) >> BASE_MANT;
        printf("%u %u %x\n", sign, exp, mant);
    }
    return 0;
}