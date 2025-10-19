#include <stdio.h>

int main() {
    int value;
    int first = 1;  // Flag to track if this is the first value in a row
    
    printf("CSV to TXT Converter with Scientific Notation\n");
    printf("Enter integers separated by commas (Ctrl+D to end):\n");
    
    while (scanf("%d", &value) == 1) {
        // Print the value in scientific notation with left alignment and 25-char width
        printf("%-25e", (double)value);
        
        // Check if next character is a comma (new value in same row)
        int next_char = getchar();
        if (next_char == ',') {
            // Continue on same line
            first = 0;
        } else if (next_char == '\n') {
            // End of row
            printf("\n");
            first = 1;
        } else if (next_char == EOF) {
            // End of input
            printf("\n");
            break;
        }
    }
    
    return 0;
} 