#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 5000
#define MAX_LEN 1000

char* lineptr[MAX_LINES];
int ignore_case = 0; // 0 = case-sensitive, 1 = case-insensitive

int read_lines(void) {
    char line[MAX_LEN];
    int nline = 0;
    while (fgets(line, MAX_LEN, stdin)) {
        int len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        lineptr[nline] = (char*) malloc((len + 1) * sizeof(char));
        if (lineptr[nline] == NULL)
            return -1;
        strcpy(lineptr[nline++], line);
    }
    return nline;
}

void write_lines(int len) {
    for (int i = 0; i < len; i++)
        printf("%s\n", lineptr[i]);
}

int compare_strings(const void* first, const void* second) {
    const char** first_string_pointer = (const char**)first;
    const char** second_string_pointer = (const char**)second;
    return strcmp(*first_string_pointer, *second_string_pointer);
}

int compare_strings_ignore_case(const void* first, const void* second) {
    const char** first_string_pointer = (const char**)first;
    const char** second_string_pointer = (const char**)second;
    
    // Use strcasecmp if available, otherwise implement manually
    #ifdef _WIN32
        // Windows does not have strcasecmp, use _stricmp
        return _stricmp(*first_string_pointer, *second_string_pointer);
    #else
        return strcasecmp(*first_string_pointer, *second_string_pointer);
    #endif
}

void print_usage(const char* program_name) {
    printf("Usage: %s [-i]\n", program_name);
    printf("  -i: Ignore case when sorting (case-insensitive)\n");
    printf("  Default: Case-sensitive sorting\n");
    printf("\nExample:\n");
    printf("  %s          # Case-sensitive sort\n", program_name);
    printf("  %s -i       # Case-insensitive sort\n", program_name);
}

int main(int argc, char* argv[]) {
    int number_of_lines;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            ignore_case = 1;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else {
            printf("Error: Unknown argument '%s'\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    if ((number_of_lines = read_lines()) < 0) {
        printf("Error: cannot store input stream in the memory!\n");
        return 1;
    }
    
    printf("# of lines: %d.\n", number_of_lines);
    printf("Sorting mode: %s\n", ignore_case ? "Case-insensitive" : "Case-sensitive");

    if (ignore_case)
        qsort(lineptr, (size_t)number_of_lines, sizeof(char*), compare_strings_ignore_case);
    else
        qsort(lineptr, (size_t)number_of_lines, sizeof(char*), compare_strings);

    write_lines(number_of_lines);

    for (int i = 0; i < number_of_lines; i++)
        free(lineptr[i]);
    
    return 0;
} 