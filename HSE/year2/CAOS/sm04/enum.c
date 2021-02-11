#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

union MyFloat 
{   
    float f;
    uint32_t u;
};

enum { SIGN_BITES = 31, KILL_SIGN = 1, EXP_BITES = 24, MANT_BITES = 9 };

FPClass fpclassf(float value, int *psign) 
{
    union MyFloat x;
    x.f = value;
    uint32_t exp = (x.u << KILL_SIGN) >> EXP_BITES;
    uint32_t sign = x.u >> SIGN_BITES;
    *psign = (int)sign;
    uint32_t mant = (x.u << MANT_BITES) >> MANT_BITES;
    if (!mant) {
        if (!exp) {
            return FFP_ZERO;
        } else if (exp == 0xFF) {
            return FFP_INF;
        }
    } else if (!exp) {
            return FFP_DENORMALIZED;
    }
    if (exp && exp != 0xFF) {
        return FFP_NORMALIZED;
    }
    *psign = 0;
    return FFP_NAN;
}