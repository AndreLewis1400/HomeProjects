#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_lowercase(char user_input[]);
double num_of_elements_n_array_of_int(int array[], int size);

int main() {
    char user_input[50];
    // Read the string from the user
    printf("Enter a string: ");
    scanf("%s", user_input);
    printf("You entered: %s\n", user_input);
    // Reverse the string
    printf("Reversed string: ");
    for (int i = strlen(user_input); i > 0; i--) {
        printf("%c", user_input[i-1]); 
    }
    printf("\n");
    printf("Number of lowercase letters: %d\n", count_lowercase(user_input));
    
    // Array of integers
    printf("Enter the number of elements in the array: ");
    int size;
    scanf("%d", &size);
    int array[size];
    for (int i = 0; i < size; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &array[i]);
    }
    printf("The average of the array is: %f\n", num_of_elements_n_array_of_int(array, size));
    return 0;
}

// Count the number of lowercase letters
int count_lowercase(char user_input[]) {
    int lowercase_count = 0;    
    for (int i = 0; i < strlen(user_input); i++) {
        if (islower(user_input[i])) {
            lowercase_count++;
        }
    }
    return lowercase_count;
}
// Calculate the average of the array
double num_of_elements_n_array_of_int(int array[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}
