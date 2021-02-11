#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
int main()
{
    int64_t a, b;
    int width;
    scanf("%ld%ld%d", &a, &b, &width);
    printf("%*s", width, " ");
    for (int64_t i = a; i < b; ++i) {
        printf("%*ld", width + 1, i);
        if (i != b - 1) {
        }
    }
    printf("\n");
    for (int64_t i = a; i < b; ++i) {
        printf("%*ld", width, i);
        for (int64_t j = a; j < b; ++j) {
            if (j != b - 1) {
                int64_t product = i * j;
                printf("%*ld", width + 1, product);
            } else {
                int64_t product = i * j;
                printf("%*ld", width + 1, product);
            }
        }
        printf("\n");
    }
    return 0;
}