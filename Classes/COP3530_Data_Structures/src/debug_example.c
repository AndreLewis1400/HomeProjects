#include <stdio.h>

int sum_array(int arr[], int size) {
    int sum = 0;
    // Deliberate bug: loop goes one element too far
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = 5;
    
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    int result = sum_array(numbers, size);
    printf("Sum of array elements: %d\n", result);
    
    return 0;
} 