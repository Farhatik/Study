#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <inttypes.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h> 
#include <limits.h>
// #include <linux/limits.h>

//задача с сема 186

enum { SZ = 10000 };

int main(int argc, char * argv[]) {
    char * dir_p = getenv("XDG_RUNTIME_DIR");
    if (dir_p == NULL) {
        dir_p = getenv("TMPDIR");
    }
    int fd;
    srand(time(NULL));
    int r = rand();
    char name_f[SZ];
    char pathname[PATH_MAX];
    sprintf(name_f, "/%d.py", r);
    if (dir_p == NULL) {
        strcpy(pathname, "/tmp");
    } else {
        strcpy(pathname, dir_p);
    }
    strcat(pathname + strlen(pathname), name_f);
    fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0700);
    dprintf(fd, "#!/usr/bin/python3\n");
    dprintf(fd, "import os\n");
    dprintf(fd, "print(");
    for (int i = 1; i < argc; ++i) {
        if (i != 1) {
            dprintf(fd, " * ");
        }
        dprintf(fd, "%s", argv[i]);
    }
    dprintf(fd, ")\n");
    dprintf(fd, "os.remove(\"%s\")\n", pathname);
    close(fd);
    execlp(pathname, pathname, NULL);
    return 0;
}