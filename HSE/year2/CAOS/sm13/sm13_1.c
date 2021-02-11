#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdint.h>
#include <inttypes.h>

enum { SB = 100, SECINDAY = 86400 };

int main() {
    char buf[SB];
    int32_t cur = 0;
    while (scanf("%"SCNd32, &cur) == 1) {
        if (__builtin_mul_overflow(cur, SECINDAY, &cur)) {
            printf("OVERFLOW\n");
            continue;
        }
        time_t t_cur = time(NULL);
        if (__builtin_add_overflow(t_cur, cur, &t_cur)) {
            printf("OVERFLOW\n");
            continue;
        }
        struct tm * local = localtime(&t_cur);
        if (local == NULL) {
            printf("OVERFLOW\n");
            continue;
        }
        strftime(buf, SB, "%F", local);
        puts(buf);
    }
    return 0;
}