#include <stdio.h>

int main() {
    char str[15] = "helloXworld!";
    // p points to the letter 'o' in "helloXworld!" (str[4] = 'o')
    char* p = &str[4];

    // Use temporary variables to avoid unsequenced modification/access
    long diff = p - str;           // 4
    int l_minus_a = p[-2] - 'a';   // 11
    char k = p[3] - 4;             // 'k'
    char before = *(p--);          // 'o', then p points to str[3]
    char after = *(++p);           // p back to str[4], value is 'o'

    printf("%ld %d %c %c %c", diff, l_minus_a, k, before, after);
    // Predicted output: 4 11 k o o
    return 0;
} 