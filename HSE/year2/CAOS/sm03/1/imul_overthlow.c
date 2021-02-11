#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>


int imull_overflow(int64_t a, int64_t b, int64_t *res) {
    uint64_t u_a = a, u_b = b;
    int f = 0;
    int64_t sign = 0; 
    if ((a > 0 && b > 0) || (a < 0 && b < 0)) {
        sign = 1;
    } else {
        sign = -1;
    }
    if (a < 0) {
        u_a /= 2;
    }
    if (b < 0) {
        u_b /= 2;
    }
    uint64_t u_res = u_a * u_b;
    
    if ((u_res <= INT64_MAX && sign > 0) || (u_res <= ((uint64_t)1 + INT64_MAX) && sign < 0)) {
        f = 0;
    }  else {
        f = 1;
    }
    if (u_res > INT64_MAX) {
        u_res /= 2;
    }
    *res = (int64_t)u_res * sign;
    return f;
}
int main() {
    FILE *myfile;
    myfile = fopen ("tests.txt", "r");
    for (size_t i = 0; i < 100; ++i) {
        int64_t a, b;
        int64_t res = 0;
        fscanf("%"SCNd64"%"SCNd64, &a, &b);
    }
    scanf("%"SCNd64"%"SCNd64, &a, &b);
    // int64_t copy_a = a;
    // int64_t copy_b = b;
    int64_t res = 0;
    // int c = imull_overflow(a, b, &res);
    // printf("%"PRId64"\n%d\n", res, c);
    int64_t right_res
    return 0;
}