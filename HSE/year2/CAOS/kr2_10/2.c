#include <stdint.h>
#include <stdio.h>

size_t process_2(const char *str, const char *range) {
    char low = range[0];
    char up = range[2];
    size_t count = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= low && str[i]<= up) {
            count++;
        } else {
            break;
        }
    }
    return count;
}

// int main() {
//     char s[100000];
//     scanf("%s", s);
//     s[7] = '\0';
//     char k[3] = {'a', 'b', 'c'};
//     printf("%ld", process_2(s, k));
//     return 0;
// }