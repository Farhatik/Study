#include <stdio.h>
#include <string.h>


void normalize_path(char *buf) {

    // ??????? наверное, можно записать просто (buf)
    // char * ptr = buf + 1;
    if (buf == NULL || *buf == '\0') {
        return;
    }

    char * ptr = buf + 1;
    char * prev_ptr = buf;
    
    if (*ptr == '\0') {
        return;
    }

    
    while (*ptr) {
        if (*prev_ptr != *ptr || *ptr != '/') {
            ++prev_ptr; ++ptr;
            *prev_ptr = *(ptr - 1);
        } else {
            ptr++;
        }
    }
    *(++prev_ptr) = '\0';

}

// int main() {
//     char str[1000];
//     scanf("%s", str);
//     char new_str[11] = {'*', '-', '\0'};
//     normalize_path(new_str);
//     normalize_path(str);
//     printf("%s\n", new_str);
//         printf("%s\n", str);

//     return 0;
// }