#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>


int main(int argc, char * argv[]) {
    time_t t;
    int y = strtol(argv[1], NULL, 10);
    int m = strtol(argv[2], NULL, 10);
    // struct tm buf = {0, 0, 0, 1, m - 1, y - 1900};
    time(&t);
    struct tm * buf = localtime(&t);
    buf->tm_year = y - 1900; buf->tm_mon = m - 1; 
    buf->tm_mday = 1;
    mktime(buf);
    int sumt = 0;
    int pm = buf->tm_mon;
    while (buf->tm_mon == pm) {
        // printf("%d %d\n", buf->tm_mday, buf->tm_wday);
        int wd = buf->tm_wday;
        buf->tm_mday++;
        mktime(buf);
        if (wd == 0 || wd == 6) { continue; } 
        if (wd == 5) {sumt -= 2;}
        sumt += 8;
    }
    printf("%d\n", sumt);
    return 0;
}