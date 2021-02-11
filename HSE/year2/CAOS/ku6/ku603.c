#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <math.h>

    
int main(int argc, char * argv[]) {
    if (argc != 4) {
        fprintf(stderr, "few args\n");
        exit(1);
    }
    int rows = strtol(argv[2], NULL, 10);
    int cols = strtol(argv[3], NULL, 10);
    
    size_t sz = rows * cols * sizeof(double);

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        fprintf(stderr, "open: %s\n", strerror(errno));
        exit(1);
    }
    if (ftruncate(fd, sz) == -1)
    {
        fprintf(stderr, "Cannot set size for file: %s\n", strerror(errno));
        return 1;
    }
    
    void * ptr = mmap(NULL, sz, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        fprintf(stderr, "map: %s\n", strerror(errno)); 
        exit(1);
    }
    double * * mat = malloc(rows*sizeof(*mat));
    if (mat == NULL) {
        fprintf(stderr, "malloc for mat: %s\n", strerror(errno)); 
        exit(1);
    }
    
    for (int i = 0 ; i < rows; ++i) {
        double * temp = malloc(cols*sizeof(**mat));
        mat[i] = temp;
    }
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] = 2*sin((double)i) + 4 * cos(((double)j) / 2.0);
        }
    }

    size_t offset = 0;
    for (size_t i = 0; i < rows; ++i) {
        memcpy(ptr + offset, mat[i], cols * sizeof(*mat[i]));
        offset += cols * sizeof(*mat[i]);
        free(mat[i]);
    }
    free(mat);
    close(fd);
    munmap(ptr, sz);
    
    return 0;
}