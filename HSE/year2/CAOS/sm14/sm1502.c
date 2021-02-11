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

struct Point 
{
    int x;
    int y;
};

uint32_t CUR = 0;

void print_mat(int * * mat, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (j != 0) {
                printf("\t%d", mat[i][j]);
            } else {
                printf("%d", mat[i][j]);
            }
        }
        printf("\n");
    }
}

struct Point fill_part(char * name_part, struct Point cur_pos, int num, int sign, int * * mat) {
    if (num <= 0) {
        return cur_pos;
    }
    // print_mat(mat, 3, 5);
    for (int i = 0; i < num; ++i) {

        mat[cur_pos.x][cur_pos.y] = ++CUR;
        // printf("cur_pos.x -- %d\tcur_ps.y -- %d\n", cur_pos.x, cur_pos.y);
        // printf("CUR -- %d\n", CUR);
        if (strcmp(name_part, "row") == 0) {
            if (i != num - 1) cur_pos.y += sign;
        } else if (strcmp(name_part, "col") == 0) {
            if (i != num - 1) cur_pos.x += sign;
        }
    }
    // print_mat(mat, 10, 10);
    // printf("*********************************************\n");
    return cur_pos;
}

    
int main(int argc, char * argv[]) {
    if (argc != 4) {
        fprintf(stderr, "few args\n");
        exit(1);
    }
    int rows = strtol(argv[2], NULL, 10);
    int cols = strtol(argv[3], NULL, 10);
    
    size_t sz = rows * cols * sizeof(int);

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        fprintf(stderr, "open: %s\n", strerror(errno));
        exit(1);
    }
    if (ftruncate(fd, sz) == -1)
    {
        fprintf(stderr, "Cannot set size for file: %s\n", strerror(errno));
        return 1;
    }
    
    void * ptr = mmap(NULL, sz, PROT_READ| PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        fprintf(stderr, "map: %s\n", strerror(errno)); 
        exit(1);
    }
    int * * mat = malloc(rows*sizeof(*mat));
    if (mat == NULL) {
        fprintf(stderr, "malloc for mat: %s\n", strerror(errno)); 
        exit(1);
    }
    for (int i = 0 ; i < rows; ++i) {
        int * temp = malloc(cols*sizeof(**mat));
        mat[i] = temp;
    }
    int dx = cols;
    int dy = rows;
    int sign_x = 1;
    int sign_y = 1;
    struct Point p;
    p.x = 0; p.y = 0;
    while (dx > 0 && dy > 0) {
        p = fill_part("row", p, dx, sign_x, mat);
        p.x += sign_y;
        dy--;
        p = fill_part("col", p, dy, sign_y, mat);

        p.y -= sign_x;
        dx--;
        sign_x *= -1;
        sign_y *= -1;
    }

    size_t offset = 0;
    for (size_t i = 0; i < rows; ++i) {
        //printf("%d\n", *mat[i]);
        memcpy(ptr + offset, mat[i], cols * sizeof(*mat[i]));
        offset += cols * sizeof(*mat[i]);
        free(mat[i]);
    }
    free(mat);
    close(fd);
    munmap(ptr, sz);
    return 0;
}
