#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <inttypes.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void print_m(int * buf, int cnt) {
    for (size_t i = 0; i < cnt; ++i) {
        printf("%d ", buf[i]); 
    }
    printf("\n");
}

int main(int argc, char * argv[]) {
    //argv[0] - name_of_pr
    //argv[1] == N - чисо параллеьно запускаемых процессов
    //argv[2] == F - имя выходного файла
    //argv[3] == A_0  начальное хначение
    //argv[4] == D - разность прогресии
    //argv[5] == K – число чисел для генерации каждым процессом.
    if (argc != 6) {
        fprintf(stderr, "few args\n");
        exit(1);
    } 
    int n = strtol(argv[1],NULL, 10);
    int a0 = strtol(argv[3],NULL, 10);
    int d = strtol(argv[4],NULL, 10);
    int k = strtol(argv[5],NULL, 10);
    int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    for (int i = 0; i < n ; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            int fd = open(argv[2], O_WRONLY);
            if (fd < 0) {
                fprintf(stderr, "open: %s\n", strerror(errno));
                exit(1);
            }
            for (int j = 0; j < k ; ++j) {
                int x =  a0 + d * ((j * n) + i);
                if (lseek(fd, ((j * n) + i) * sizeof(x), SEEK_SET) < 0) {
                    fprintf(stderr, "lseek: %s\n", strerror(errno));
                    exit(1);
                }
                int need_wr = sizeof(x);
                    while (need_wr > 0) {
                        need_wr -=write(fd, &x, need_wr);
                        
                    };
                    // printf("%d %d %d %d %d\n", fd, i, j, ((j * n) + i), x);
                    // fflush(stdout);
            }
            close(fd);
            exit(0);
        }
    }
    for (int i = 0; i < n; ++i) {
        wait(NULL);
    }
    close(fd);
    return 0;
}