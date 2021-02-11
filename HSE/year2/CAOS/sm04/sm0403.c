#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

int BASE = 4;

int get_bytes(int c) {
    for (int i = BASE - 1; i >= 0; --i) {
        if (((c & (1 << i)) >> i) == 0) {
            return BASE - i - 1;
        }
    }
    return BASE;
};

int get_bytes_rev(int c) {
    for (int i = 0; i < BASE; ++i) {
        if (((c & (1 << i)) >> i) == 0) {
            return BASE - i - 1;
        }
    }
    return BASE;
};
int main() {
    int c;
    int qty = 0;
    int first_point = 0;
    int f_first = 1;
    int last_point = 0;
    while ((c = getchar()) != EOF) {
        if ((c >= '0' && c <= '9') || (c >= 'a' && c <='e') || 
        (c >= 'A' && c <= 'E') || (c == 'f' || c == 'F')) {

            qty += 4;

            if (c == 'f' || c == 'F') {continue;} 
            if (c >= '0' && c <= '9') c -= '0';
            if (c >= 'a' && c <='e') c-= 'a' - 10;
            if (c >= 'A' && c <= 'E') c -= 'A' - 10;
            if (f_first) {
                first_point = qty - 4 + get_bytes(c);

                f_first = 0;
            }
            last_point = qty - 4 + get_bytes_rev(c);
        }
    }
    if (qty == 0) {
        return 0;
    }
    int side = sqrt(qty);
    int x1 = first_point / side;
    int y1 = first_point % side;

    int x2 = last_point / side;
    int y2 = last_point % side;
    if (side == 0) {
        return 0;
    }
    printf("%d %d %d %d %d\n", side, x1, y1, x2, y2);
    return 0;
}