# Discussion Forum 2: 2D Array Initialization and Function Use in C

## Assignment Description

The following C program creates a two-dimensional array of integers of size 40 by 50 where each cell at row index i and column index j stores the value of ((i+1)*(j+1)):

```c
#include <stdio.h>
void main(void){
    int array[40][50];
    for(int i = 0; i < 40; i++)
        for(int j = 0; j < 50; j++)
            array[i][j] = (i+1) * (j+1);
    printf("%d", your_function(array));
}
```

## Discussion Points

1. **What does the code do?**
   - It initializes a 2D array `array[40][50]` such that each element at position `[i][j]` is set to `(i+1)*(j+1)`.
   - For example, `array[0][0] = 1*1 = 1`, `array[1][2] = 2*3 = 6`, etc.

2. **What is `your_function(array)` supposed to do?**
   - The code is incomplete: it calls a function named `your_function` with the array as an argument.
   - A common discussion question is: *What should `your_function` do?* For example, it could:
     - Compute the sum of all elements in the array.
     - Find the maximum or minimum value.
     - Print the array in a certain format.

3. **How would you implement `your_function` to sum all elements?**
   ```c
   int your_function(int arr[40][50]) {
       int sum = 0;
       for (int i = 0; i < 40; i++)
           for (int j = 0; j < 50; j++)
               sum += arr[i][j];
       return sum;
   }
   ```
   - This function iterates through all elements and returns their sum.

4. **How do you pass a 2D array to a function in C?**
   - You must specify the second dimension (number of columns) in the function parameter, e.g., `int arr[40][50]` or `int arr[][50]`.

5. **What is the output if you use the sum function?**
   - The output will be the sum of all products `(i+1)*(j+1)` for `i` from 0 to 39 and `j` from 0 to 49.

## Sample Complete Program

```c
#include <stdio.h>

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
```

## Discussion Questions for Peers
- What other operations could `your_function` perform on the array?
- How would you modify the code to work for arrays of different sizes?
- What are the memory implications of large 2D arrays in C?

## Author

- Andre Lewis
- Florida International University (FIU)
- COP4338 Systems Programming 