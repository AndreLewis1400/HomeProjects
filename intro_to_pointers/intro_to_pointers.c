#include <stdio.h>
#include <limits.h>


// Function to perform arithmetic operations
// Returns 0 if all OK, 1 if sum overflow, 2 if diff overflow, 3 if division by zero
// op1, op2: input integers
// sum, diff, prod, quo: pointers to store results
int arithmetic(int op1, int op2, int* sum, int* diff, int* prod, int* quo) {
    // Check for sum overflow
    if (((op2 > 0) && (op1 > INT_MAX - op2)) || ((op2 < 0) && (op1 < INT_MIN - op2))) {
        return 1; // Error code 1: sum overflow
    }
    *sum = op1 + op2;

    // Check for diff overflow
    if (((op2 < 0) && (op1 > INT_MAX + op2)) || ((op2 > 0) && (op1 < INT_MIN + op2))) {
        return 2; // Error code 2: difference overflow
    }
    *diff = op1 - op2;

    *prod = op1 * op2; // For simplicity, not checking for product overflow

    if (op2 == 0) {
        return 3; // Error code 3: division by zero
    }
    *quo = op1 / op2;

    return 0; // No error
}

int main() {
    int op1, op2;
    int sum, diff, prod, quo;

    // Prompt user for input
    printf("Enter two integers: ");
    if (scanf("%d %d", &op1, &op2) != 2) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    // Call arithmetic function and handle errors
    int error = arithmetic(op1, op2, &sum, &diff, &prod, &quo);
    if (error == 1) {
        printf("Error: Sum overflow.\n");
    } else if (error == 2) {
        printf("Error: Difference overflow.\n");
    } else if (error == 3) {
        printf("Error: Division by zero.\n");
    } else {
        // Print results if no error
        printf("Sum: %d\n", sum);
        printf("Difference: %d\n", diff);
        printf("Product: %d\n", prod);
        printf("Quotient: %d\n", quo);
    }
    return 0;
}