#include <stdio.h>
#include <stdlib.h>
 
#define ERROR_FILE_OPEN -3

// argv[1] -- дескриптор, argv[2] -- число строк, argv[3] -- число стобцов
int main(int argc, char* argv[]) {
    FILE *input = NULL;
    int number;
 
    input = fopen(argv[1], "rb");
    if (input == NULL) {
        printf("Error opening file");
        exit(ERROR_FILE_OPEN);
    }
    
    int counter = 1;
    while (fread(&number, sizeof(int), 1, input)) {
        printf("%d\t", number);
        if (counter % atoi(argv[3]) == 0) printf("\n");
        counter++;
    }
 
    fclose(input);
}
