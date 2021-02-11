#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char * argv[]) {
    int dx = 0;
    int f = 0;
    uint64_t temp;
    uint64_t sum = 0;
    if (argc == 1) {
        printf("%lx\n", sum);
        return 0;
    }
    while (argv[1][dx] != '\0') {
            if (argv[1][dx] != ',' && f) {
                dx++;
                continue;
            }
            if (sscanf(argv[1] + dx + f, "%lo", &temp) != 1) {
                break;
            };
            if (!(sum & 1LLU << (temp - 1))) sum += (1LLU << (temp - 1));
            dx++;
            f = 1;
        }
    printf("%lx\n", sum);
    return 0;
}