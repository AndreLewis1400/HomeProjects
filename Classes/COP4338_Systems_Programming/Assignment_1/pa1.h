#ifndef PA1_H 
#define PA1_H 

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_palindrome(char *line){ //function to check if the line is a palindrome
    int len = strlen(line); //get the length of the line
    for(int i = 0; i < len/2; i++){
        if (line[i] != line[len-i-1]){ //if the characters do not match, return 0
            return 0;
        }
    }
    return 1; //if we made it through the loop, it's a palindrome
}

int is_singleton(char *line){ //function to check if the line is a singleton
    int len = strlen(line); //get the length of the line
    if (len == 0){
        return 0; //empty string is not a singleton
    }  
    char first = line[0]; //get the first character
    for(int i = 1; i < len; i++){
        if(line[i] != first){ //if any character is different from the first, not a singleton
            return 0;
        }
    }
    return 1; //if we made it through the loop, all characters are the same
}

int is_arithmetic(char *line){ //function to check if the line is an arithmetic sequence
    int len = strlen(line); //get the length of the line
    if (len < 2){
        return 0; //less than 2 characters is not an arithmetic sequence
    }

    // Find first letter
    int start = 0;
    while (start < len && !isalpha(line[start])){ //find the first letter
        start++; //increment the start index
    }
    if (start >= len - 1){
        return 0;  //if the start index is greater than the length of the line, not an arithmetic sequence
    }
    char prev = tolower(line[start]); //get the first letter
    for (int i = start + 1; i < len; i++) { //check each letter
        if (!isalpha(line[i])){ //if the character is not a letter, continue
            continue;
        }
        char curr = tolower(line[i]); //get the current letter
        if (curr != prev + 1){ //if the current letter is not the next letter, not an arithmetic sequence
            return 0;  //if the current letter is not the next letter, not an arithmetic sequence
        }
        prev = curr; //set the previous letter to the current letter
    }
    return 1;
}

int is_reverse_arithmetic(char *line){ //function to check if the line is a reverse arithmetic sequence
    int len = strlen(line); //get the length of the line
    if (len < 2){
        return 0; //less than 2 characters is not a reverse arithmetic sequence
    }
    
    // Find first letter
    int start = 0;
    while (start < len && !isalpha(line[start])){ //find the first letter
        start++; //increment the start index
    }
    if (start >= len - 1){
        return 0;  //if the start index is greater than the length of the line, not a reverse arithmetic sequence
    }
    
    char prev = tolower(line[start]);
    for (int i = start + 1; i < len; i++) {
        if (!isalpha(line[i])){ //if the character is not a letter, continue
            continue;
        }
        char curr = tolower(line[i]); //get the current letter
        if (curr != prev - 1){ //if the current letter is not the previous letter, not a reverse arithmetic sequence
            return 0;  //if the current letter is not the previous letter, not a reverse arithmetic sequence
        }
        prev = curr; //set the previous letter to the current letter
    }
    return 1;
}

int is_balanced_tripartite(char *line){ //function to check if the line is a balanced tripartite sequence
    int len = strlen(line); //get the length of the line
    if (len % 3 != 0){
        return 0; //if the length is not divisible by 3, not a balanced tripartite sequence
    }
    int part_len = len / 3; //get the length of each part
    
    // Check first part against second part AND third part
    for(int i = 0; i < part_len; i++){
        // Compare with second part
        if(line[i] != line[i + part_len]){
            return 0;
        }
        // Compare with third part
        if(line[i] != line[i + 2 * part_len]){
            return 0;
        }
    }
    return 1; //if we made it through all checks, it's a balanced tripartite sequence
}

int is_balanced_bipartite(char *line){ //function to check if the line is a balanced bipartite sequence
    int len = strlen(line); //get the length of the line
    if (len % 2 != 0){
        return 0; //if the length is not divisible by 2, not a balanced bipartite sequence
    }
    int half_len = len / 2; //get the length of each part
    for(int i = 0; i < half_len; i++){ //check each part
        if(line[i] != line[i + half_len]) //if the difference is not the same, not a balanced bipartite sequence
            return 0;
    }
    return 1; //if we made it through the loop, it's a balanced bipartite sequence
}

#endif // PA1_H