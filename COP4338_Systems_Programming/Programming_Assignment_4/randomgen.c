#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: The program expects one command-line argument which is the length of randomly generated string\n");
        return 1;
    }
    
    int n = atoi(argv[1]);
    srand(time(NULL));
    
    for (long l = 0; l < n; l++) {
        putchar('a' + rand() % 26);
    }
    
    return 0;
} 