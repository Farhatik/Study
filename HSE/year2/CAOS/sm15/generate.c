#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
 
int main(int argc, char const* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Not enough arguments\n");
        return 0;
    }
 
    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
    if (fd < 0) {
        fprintf(stderr, "Failed to open file\n");
        return 0;
    }
    srand((unsigned)time(NULL));
 
    int n;
    intmax_t sum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int32_t value;
        value = rand() ^ rand() << 16;
        sum += value;
        int32_t Value = value;
        bool More;
        do {
            uint8_t Byte = Value & 0x7f;
            Value >>= 7;
            More =
                !((((Value == 0) && ((Byte & 0x40) == 0)) ||
                   ((Value == -1) && ((Byte & 0x40) != 0))));
            if (More) Byte |= 0x80;
            write(fd, &Byte, 1);
        } while (More);
    }
    printf("%jd\n", sum);
 
    return 0;
}