#include <stdio.h>
#include <stdint.h>

enum { D24 = 16777216, D25 = 33554432, D26 = 67108864 };
enum { D27 = 134217728, D28 = 268435456, D29 = 536870912, D30 = 1073741824 };
union Num 
{
    uint32_t u;
    int32_t i;
};

int main() {
    union Num x;
    
    while (scanf("%u", &x.u) == 1) {

        if (x.u <= D24) {
            printf("%d\n", 1);
        } else if (x.u <= D25) {
            if (x.u % 2 == 0) {
                printf("%d\n", 1);
            } else {
                printf("%d\n", 0);
            }
        } else if (x.u <= D26) {
            if (x.u % 4 == 0) {
                printf("%d\n", 1);
            } else {
                printf("%d\n", 0);
            }
        } else if (x.u <= D27) {
            if (x.u % 8 == 0) {
                printf("%d\n", 1);
            } else {
                printf("%d\n", 0);
            }
        } else if (x.u <= D28) {
            if (x.u % 16 == 0) {
                printf("%d\n", 1);
            } else {
                printf("%d\n", 0);
            }
        } else if (x.u <= D29) {
            if (x.u % 32 == 0) {
                printf("%d\n", 1);
            } else {
                printf("%d\n", 0);
            }
        }  else if (x.u <= D30) {
            if (x.u % 64 == 0) {
                printf("%d\n", 1);
            } else {
                printf("%d\n", 0);
            }
        } else {
            if (x.u % 128 == 0) {
                printf("%d\n", 1);
            } else {
                printf("%d\n", 0);
            }
        }
    }
    return 0;
}