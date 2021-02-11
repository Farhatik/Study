#include <stdio.h>
#include <stdint.h>
#include <ctype.h>

int main() {
    int c;
    int64_t sum = 0;
    while ((c = getchar_unlocked()) != EOF) {
        if (isdigit(c) != 0) {
            sum += (c - 48);   
        }
    }
    printf("%ld\n", sum);
    return 0;
}