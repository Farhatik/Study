#include <endian.h>
#include <fcntl.h>
#include <memory.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char * argv[]) {
    int yyy, mmm;
    sscanf(argv[1], "%d", &yyy);
    sscanf(argv[2], "%d", &mmm);
    yyy -= 1900;
    mmm -= 1;
    struct tm tmp; tmp.tm_mon = mmm; tmp.tm_year = yyy;
    tmp.tm_mday = 0;
    mktime(&tmp);
    int h = 0;
    for (size_t i = 1; i <= 35; ++i) {
        mktime(&tmp);
        if (tmp.tm_wday == 5) {
            h += 6;
        } 
        if (tmp.tm_wday <= 4 && tmp.tm_wday >= 1) {
            h += 8;
        }
        tmp.tm_mday +=1;
    }
    printf("%d", h);
}