#include <wchar.h>
#include <wctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <locale.h>

int main() {
    wchar_t c;
    setlocale (LC_ALL, "");
    // assert (rl != 0);
    int low_qty = 0;
    int up_qty = 0;
    int dig_qty = 0;
    while ((c = getwchar()) != WEOF) {
        if (iswdigit(c)) {
            dig_qty += 1;
        } else if (iswlower(c)) {
            low_qty += 1;
        } else if (iswupper(c)) {
            up_qty += 1;
        }
    }
    printf("%d\n", dig_qty);
    printf("%d\n", up_qty);
    printf("%d\n", low_qty);
    return 0;
}