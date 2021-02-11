#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

char *getline2(FILE *f) {
    int c = getc(f);
    if (c == EOF) {
        return NULL;
    }
    char * ptr = malloc(2);
    if (!ptr) {
        return NULL;
    }
    int64_t size = 1;
    int64_t capacity = 2;
    while (c != EOF && c != '\n'){
        size++;
        if (size > capacity) {
            capacity *= 2;
            ptr = realloc(ptr, capacity);
            if (!ptr) {
                free(ptr);
                return NULL;
            }
        }
        ptr[size - 2] = c;
        c = getc(f);
    }
    if (c == '\n') {
        size++;
        ptr[size - 2] = c;;
        c = getc(f);
    }
    ptr[size - 1] = '\0';
    return ptr;
}

int main() {
    char * buf = malloc(1);
    buf[0] = 'c';
    FILE *f;
    f = fopen("input", "r");
    char * s = getline2(f);
    // scanf("%s", s);
    if (!s) {
        printf("NULL\n");
        return 0;
    }
    for (int i = 0; s[i]; ++i) {
        printf("%c", s[i]);
    }
    printf("\n");
    free(s);
    return 0;
}