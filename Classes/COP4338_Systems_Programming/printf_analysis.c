#include <stdio.h>

int main() {
    printf("Analysis of printf statement:\n");
    printf("printf(\"%%05d,,,%%-7.2f,,,%%7.2e,,,%%x,,,%%%%,,%%10.5s.\", 31, 11.0/3, 11.0/3, 31, \"umbrella\");\n\n");
    
    printf("Let's break down each format specifier:\n\n");
    
    // Test each format specifier individually
    printf("1. %%05d with 31: ");
    printf("%05d", 31);
    printf(" (5-digit width, zero-padded, right-aligned)\n");
    
    printf("2. %%-7.2f with 11.0/3 (≈3.67): ");
    printf("%-7.2f", 11.0/3);
    printf(" (7-char width, left-aligned, 2 decimal places)\n");
    
    printf("3. %%7.2e with 11.0/3 (≈3.67): ");
    printf("%7.2e", 11.0/3);
    printf(" (7-char width, right-aligned, scientific notation, 2 decimal places)\n");
    
    printf("4. %%x with 31: ");
    printf("%x", 31);
    printf(" (hexadecimal representation of 31 = 1F)\n");
    
    printf("5. %%0 with 31: ");
    printf("%%0");
    printf(" (invalid format specifier - prints %%0 literally)\n");
    
    printf("6. %%10.5s with \"umbrella\": ");
    printf("%10.5s", "umbrella");
    printf(" (10-char width, right-aligned, max 5 characters from string)\n\n");
    
    printf("Complete output:\n");
    printf("%05d,,,%-7.2f,,,%7.2e,,,%x,,,%%0,,,%10.5s.\n", 31, 11.0/3, 11.0/3, 31, "umbrella");
    
    return 0;
} 