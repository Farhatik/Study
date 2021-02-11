

#include <stdio.h>
#include <stdlib.h>
 

int main(int argc, char* argv[]) {
    FILE *output = NULL;
    double number;
    output = fopen(argv[1], "wb");
    while (scanf("%lf", &number) > 0) {
        fwrite(&number, sizeof(number), 1, output);
    }
    fclose(output);
}