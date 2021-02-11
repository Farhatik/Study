#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <stdlib.h>


int compare(const void * i, const void * j, void * buffer) {
    wchar_t * buf1 = (wchar_t*)(buffer);
    wchar_t * buf2 =  (wchar_t*)(buffer);
    int i1 = *(int*)(i);
    int j1 = *(int*)(j);

    return wcscmp(buf1 + i1, buf2 + j1);
}

int main() {
    setlocale(LC_ALL, "");
    wchar_t buffer[1000000];
    wint_t c;
    size_t str_size = 0;
    while ((c = getwchar()) != WEOF) {
        if (!iswspace(c)) {
            buffer[str_size] = c;
            str_size++;
        }
    }
    buffer[str_size] = WCHAR_MAX;
    size_t buf_num[str_size];
    str_size++;
    buffer[str_size] = '\0';
    for (size_t i = 0; i < str_size; ++i) {
        buf_num[i] = i;
    }
    qsort_r(buf_num, str_size, sizeof(str_size), compare, buffer);
    for (size_t i = 0; i < str_size; ++i) {
        if (buffer[(str_size -1  + buf_num[i]) % str_size] != WCHAR_MAX) {
            wprintf(L"%lc", buffer[(str_size + buf_num[i] - 1) % str_size]);
        } else {
            wprintf(L"%lc", L'#');
        }
    }
    wprintf(L"%lc", L'\n');
}