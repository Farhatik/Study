#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>


int imull_overflow(int64_t a, int64_t b, int64_t *res) {
    uint64_t u_a = *(uint64_t*)(&a);
    uint64_t u_b = *(uint64_t*)(&b);
    // uint64_t u_a = a, u_b = b;
    uint64_t u_res = u_a * u_b;
    *res = (int64_t)u_res;
    if (u_b == 0) {
        if ((u_res) == 0) {
            return 0;
        } else {
            return 1;
        }
    }
    // int64_t abs_a = a, abs_b = b, abs_res = *res;
    if (*res == INT64_MIN && b == -1) {
        return 1;
    }
    if (*res / b != a) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    FILE *myfile;
    FILE *ans;
    myfile = fopen ("tests2.txt", "r");
    ans = fopen("test_ans2.txt", "w");
    for (size_t i = 0; i < 1000; ++i) {
        int64_t a, b;
        int64_t res = 0;
        int64_t answer = 0;
        fscanf(myfile, "%"SCNd64"%"SCNd64, &a, &b);
        int my_c = imull_overflow(a, b, &answer);
        int c = __builtin_mul_overflow(a, b, &res);
        if (c == my_c && res == answer) {
            fprintf(ans, "OK_________________________________________________________\n%d\t%"PRId64" %"PRId64" %"PRId64"  \n%d\t%"PRId64"\n", c, a, b, res, my_c, answer);
        } else {
            fprintf(ans, "FASLE*****************\n%d\t%"PRId64" %"PRId64" %"PRId64"  \n%d\t%"PRId64"\n", c, a, b, res, my_c, answer);

        }
    }
    fclose(myfile);
    fclose(ans);
    return 0;
}