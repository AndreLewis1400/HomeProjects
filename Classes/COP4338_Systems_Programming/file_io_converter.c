#include <stdio.h>

int main() {
    FILE *input_file, *output_file;
    int value;
    int first = 1;
    
    // Open input file
    input_file = fopen("input.csv", "r");
    if (input_file == NULL) {
        printf("Error: Cannot open input.csv\n");
        return 1;
    }
    
    // Open output file
    output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        printf("Error: Cannot create output.txt\n");
        fclose(input_file);
        return 1;
    }
    
    printf("Converting input.csv to output.txt with scientific notation...\n");
    
    while (fscanf(input_file, "%d", &value) == 1) {
        // Write the value in scientific notation with left alignment and 25-char width
        fprintf(output_file, "%-25e", (double)value);
        
        // Check if next character is a comma (new value in same row)
        int next_char = fgetc(input_file);
        if (next_char == ',') {
            // Continue on same line
            first = 0;
        } else if (next_char == '\n') {
            // End of row
            fprintf(output_file, "\n");
            first = 1;
        } else if (next_char == EOF) {
            // End of input
            fprintf(output_file, "\n");
            break;
        }
    }
    
    fclose(input_file);
    fclose(output_file);
    printf("Conversion complete! Check output.txt\n");
    
    return 0;
} 