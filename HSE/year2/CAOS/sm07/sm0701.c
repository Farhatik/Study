#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct  
{
    const char * name;
    double (*f)(double);
} Func;

static Func const FunctionTable[] = {
    {"sin", &sin},
    {"cos", &cos},
    {"log", &log},
    {"exp", &exp},
    {"tan", &tan},
    {"sqrt", &sqrt}
};

enum{SIZE_TABLE = 6, SIZE = 100000};

int main() {
    char name_func[SIZE];
    double x;
    while (scanf("%100000s%lf", name_func, &x) == 2) {
        int f = 0;
        for (int i = 0; i < SIZE_TABLE; ++i) {
            if (strcmp(FunctionTable[i].name, name_func) == 0) {
                printf("%a\n", FunctionTable[i].f(x));
                f = 1;
                break;
            }
        }
        if (f) {
            continue;
        }
        printf("nan\n");
    }
    return 0;
}