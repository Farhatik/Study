#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
enum { BASE = 7, N = 1000 };


void free_buf(char *buf, int size) {
    for (int i = 0; i < size; ++i) {
        buf[i] = '0';
    }
}

void print_buf(char *buf, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%c ", buf[i]);
    }
    printf("\n");
}

int isdigit_7(int c) {
    return c >= '0'&& c <= '6';
}
int main() {
    char buf_main[N];
    char buf_frac[N];
    free_buf(buf_main, N);
    free_buf(buf_frac, N);
    int c;
    while((c = getchar()) != EOF) {
        long double answer = 0;
        if (!isdigit_7(c)) {
            if (c == '.') {
                int j = 0;
                while (isdigit_7(c = getchar())) {
                    buf_frac[j] = c;
                    j++;
                }
                int deg_frac = 1;
                for (int k = 0; k < j; ++k) {
                    long double prod = 1;
                    for (int l = 0; l < deg_frac; ++l) {
                        prod *= BASE;
                    }
                    answer += ((long double)1)/prod * (buf_frac[k] - 48);
                    deg_frac++;
                }
                printf("%.10Lg\n", answer);
                continue;
            } else {
                continue;
            }
        } else {
            buf_main[0] = c;
        }
        int i = 1;
        while (isdigit_7((c = getchar()))) {
            buf_main[i] = c;
            i++;
        }

        long double mult_main = 1;
        for (int k = 0; k < i; ++k) {
            answer += ((long double)((buf_main[i - k - 1]) - 48)) * mult_main;
            mult_main *= BASE;
        }
        if (c != '.') {
            printf("%.10Lg\n", answer);
            free_buf(buf_main, N);
            continue;
        } 
        int j = 0;
        while (isdigit_7(c = getchar())) {
            buf_frac[j] = c;
            j++;
        }
        int deg_frac = 1;
        for (int k = 0; k < j; ++k) {
            long double prod = 1;
            for (int l = 0; l < deg_frac; ++l) {
                prod *= BASE;
            }
            answer += ((long double)1)/prod * (buf_frac[k] - 48);
            deg_frac++;
        } 
        printf("%.10Lg\n", answer);
    }
    return 0;
}