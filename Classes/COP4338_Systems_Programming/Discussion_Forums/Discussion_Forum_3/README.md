# Discussion Forum 3: Sorting Fruit Names with Custom Comparators in C

## Assignment Description

Given a C program that sorts and prints a list of fruit names using a generic quicksort function and a function pointer for comparison, make the following modifications:

1. Change the program to sort the names in decreasing (reverse) order.
2. Change the program to sort the names after ignoring their case (case-insensitive sort).

## Original Code

The program uses a generic quicksort and passes `strcmp` as a function pointer to sort the names alphabetically (increasing order).

## Modifications

### 4.1 Sort in Decreasing Order
- Implement a comparison function that returns the negative of `strcmp`.
- Pass this function pointer to the sort routine.

### 4.2 Sort Ignoring Case
- Implement a comparison function that uses `strcasecmp` (or `_stricmp` on Windows) for case-insensitive comparison.
- Pass this function pointer to the sort routine.

## Sample Output

```
Original (increasing order):
Apple
Berries
Kiwi
Orange
Pineapple
Strawberry
apple
berries
kiwi
orange
pineapple
strawberry

Decreasing order:
strawberry
pineapple
orange
kiwi
berries
apple
Strawberry
Pineapple
Orange
Kiwi
Berries
Apple

Case-insensitive order:
Apple
apple
Berries
berries
Kiwi
kiwi
Orange
orange
Pineapple
pineapple
Strawberry
strawberry
```

## Discussion Points
- How does using a function pointer make the sort routine generic?
- Why does negating the result of `strcmp` reverse the sort order?
- What is the effect of using `strcasecmp` instead of `strcmp`?

## Author
- Andre Lewis
- Florida International University (FIU)
- COP4338 Systems Programming 