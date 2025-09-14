#include <stdio.h>
#include <string.h>

// Function to find the last occurrence of needle in haystack
int find_last_occurrence(char needle[], char haystack[]) {
    int haystack_len = strlen(haystack);
    int needle_len = strlen(needle);
    
    // If needle is longer than haystack, it can't be found
    if (needle_len > haystack_len) {
        return -1;
    }
    
    // Start from the end of haystack minus needle length
    for (int i = haystack_len - needle_len; i >= 0; i--) {
        int match = 1;
        // Check if needle matches at this position
        for (int j = 0; j < needle_len; j++) {
            if (haystack[i + j] != needle[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return -1;  // Needle not found
}

// Function to find the first occurrence of needle in haystack
int find_first_occurrence(char needle[], char haystack[]) {
    int haystack_len = strlen(haystack);
    int needle_len = strlen(needle);
    
    // If needle is longer than haystack, it can't be found
    if (needle_len > haystack_len) {
        return -1;
    }
    
    // Check each possible starting position in haystack
    for (int i = 0; i <= haystack_len - needle_len; i++) {
        int match = 1;
        // Check if needle matches at this position
        for (int j = 0; j < needle_len; j++) {
            if (haystack[i + j] != needle[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            return i;
        }
    }
    return -1;  // Needle not found
}

int main() {
    // Test cases
    char haystack1[] = "Hello world, Hello again";
    char needle1[] = "Hello";
    char haystack2[] = "Programming in C is fun";
    char needle2[] = "in";
    char haystack3[] = "abcabcabc";
    char needle3[] = "abc";
    
    // Test find_first_occurrence
    printf("Testing find_first_occurrence:\n");
    printf("Haystack: '%s', Needle: '%s'\n", haystack1, needle1);
    printf("First occurrence at index: %d\n\n", find_first_occurrence(needle1, haystack1));
    
    printf("Haystack: '%s', Needle: '%s'\n", haystack2, needle2);
    printf("First occurrence at index: %d\n\n", find_first_occurrence(needle2, haystack2));
    
    // Test find_last_occurrence
    printf("Testing find_last_occurrence:\n");
    printf("Haystack: '%s', Needle: '%s'\n", haystack1, needle1);
    printf("Last occurrence at index: %d\n\n", find_last_occurrence(needle1, haystack1));
    
    printf("Haystack: '%s', Needle: '%s'\n", haystack3, needle3);
    printf("Last occurrence at index: %d\n", find_last_occurrence(needle3, haystack3));
    
    return 0;
} 