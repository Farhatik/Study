/*#include <unistd.h>

void read_print_file(int in_fd) {
    unsigned char buffer[4096];
    ssize_t read_int, write_out, counter_of_writing = 0;
    while ((read_int = read(in_fd, buffer, 4096)) > 0) {

        printf("%s\n", buffer);
    }

    return;
}

int main(int argc, char *argv[]) {
    read_print_file(argv[1]);
    return 0;
}*/

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
