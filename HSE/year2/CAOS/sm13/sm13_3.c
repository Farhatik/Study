#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>


int main(int argc, char * argv[]) {
    int fd open(argv[1], O_WRDONLY);
    close(fd);
    return 0;
}