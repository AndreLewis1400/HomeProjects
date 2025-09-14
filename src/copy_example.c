#include <stdio.h>
#include <string.h>

int main() {
    // 1. Array Copy
    int source_array[] = {1, 2, 3, 4, 5};
    int dest_array[5];
    
    // Method 1: Using loop
    printf("1. Array copy using loop:\n");
    for (int i = 0; i < 5; i++) {
        dest_array[i] = source_array[i];
    }
    
    // Print result
    printf("Copied array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", dest_array[i]);
    }
    printf("\n\n");

    // 2. String Copy
    char source_str[] = "Hello, World!";
    char dest_str[20];
    
    // Method 2: Using strcpy
    printf("2. String copy using strcpy:\n");
    strcpy(dest_str, source_str);
    printf("Original: %s\n", source_str);
    printf("Copied  : %s\n\n");

    // 3. Memory Copy
    int numbers[] = {10, 20, 30, 40, 50};
    int copied_numbers[5];
    
    // Method 3: Using memcpy
    printf("3. Memory copy using memcpy:\n");
    memcpy(copied_numbers, numbers, sizeof(numbers));
    
    printf("Copied numbers: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", copied_numbers[i]);
    }
    printf("\n");

    return 0;
} 