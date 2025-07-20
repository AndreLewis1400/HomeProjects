#include <stdio.h>
#include <string.h>
#include "pa1.h"
#define MAX_LENGTH 1000

int is_singleton(char *line); //function declarations
int is_palindrome(char *line); //function declarations
int is_arithmetic(char *line); //function declarations
int is_reverse_arithmetic(char *line); //function declarations
int is_balanced_tripartite(char *line); //function declarations
int is_balanced_bipartite(char *line); //function declarations

int main(void) {
    char line[MAX_LENGTH];
    while(fgets(line, MAX_LENGTH, stdin)) {  //read a line from stdin
        int len = strlen(line) - 1; //get the length of the line
        line[len] = '\0'; //null terminate the line
        
        if(is_singleton(line)) {
            printf("singleton\n");
        }
        else if(is_palindrome(line)) {
            printf("palindrome\n");
        }
        else if(is_arithmetic(line)) {
            printf("arithmetic\n");
        }
        else if(is_reverse_arithmetic(line)) {
            printf("reverse arithmetic\n");
        }
        else if(is_balanced_tripartite(line)) {
            printf("balanced tripartite\n");
        }
        else if(is_balanced_bipartite(line)) {
            printf("balanced bipartite\n");
        }
        else {
            printf("neither\n");
        }
        printf("\n");
    }
    return 0;
}    