#include <stdio.h>
#include <string.h>

int mystrcmp(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if ((unsigned int)(*str1) < (unsigned int)(*str2)) {
            return -1;
        } else if ((unsigned int)(*str1) > (unsigned int)(*str2)) {
            return 1;
        } else {
            str1++; str2++;
        }    
    }
    int result = 1;
    if (!(*str1) && !(*str2)) {
        result = 0;
    }
    if (!(*str1) && (*str2)) {
        result = -1;
    }
    return result;
}

void checker(char * s1, char * s2) { 
if (strcmp(s1, s2) > 0 &&  mystrcmp(s1, s2) > 0) {
        printf("TRUE\n %d %d\n", mystrcmp(s1, s2), strcmp(s1, s2));
    } else if (strcmp(s1, s2) == 0 &&  mystrcmp(s1, s2) == 0) {
        printf("TRUE\n %d %d\n", mystrcmp(s1, s2), strcmp(s1, s2));
    } else if (strcmp(s1, s2) < 0 &&  mystrcmp(s1, s2) < 0) {
        printf("TRUE\n %d %d\n", mystrcmp(s1, s2), strcmp(s1, s2));
    } else {
        printf("FALSE\n %d %d\n", mystrcmp(s1, s2), strcmp(s1, s2));
    }
}

int main() {
    char s1[1000];
    char s2[1000];
    scanf("%s%s", s1, s2);
    char s11[4] = {1, 1, '\0'}; 
    char s12[4] = {1, -1, '\0'};
    checker(s1, s2);
    return 0;
}