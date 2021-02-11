#include <stdio.h>
#include <stdint.h>

enum { BASE_SIGN = 31, LEFT_EXP = 1, RIGHT_EXP = 24, BASE_MANT = 9, MANT_SZ = 23 };

union Float 
{
    float f;
    uint32_t n;
};

float float_round(float value, int prec) {
    union Float x; x.f = value;

        uint32_t exp = (x.n << LEFT_EXP) >> RIGHT_EXP;
        uint32_t mant = (x.n << BASE_MANT) >> BASE_MANT;
        // printf("%f\n", x.f);
        if (!mant) {
            if (!exp) {
                return x.f;
            } else if (exp == 0xFF) {
                return x.f;
            }
        } else if (!exp) {
            return x.f;
        }
        if (exp && exp != 0xFF) {
            if (prec == 23) return x.f;
            x.n = x.n >> (MANT_SZ - prec - 1);
            // printf("%f\n", x.f);
            int r = x.n % 2;
            x.n = x.n >> 1;
            x.n += r;
            x.n = x.n << (MANT_SZ - prec);
            return x.f;
        }
        return x.f;
} 



// int main() {
//     union Float x;
//     // scanf("%f", x.f);
//     printf("%f\n", float_round(1.3892822265625, 3));
//     return 0;
// }