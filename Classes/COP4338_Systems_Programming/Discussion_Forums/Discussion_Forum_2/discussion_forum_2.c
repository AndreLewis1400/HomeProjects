#include <stdio.h>

// Function to sum all elements in a 40x50 array
int your_function(int arr[40][50]) {
    int sum = 0;
    for (int i = 0; i < 40; i++)
        for (int j = 0; j < 50; j++)
            sum += arr[i][j];
    return sum;
}

int main(void) {
    int array[40][50];
    for (int i = 0; i < 40; i++)
        for (int j = 0; j < 50; j++)
            array[i][j] = (i+1) * (j+1);
    printf("%d\n", your_function(array));
    return 0;
} 