# Programming Assignment 3: Bucket Sort in C

This directory contains the implementation of a bucket sort algorithm for sorting strings alphabetically using linked lists.

## Assignment Overview

The program implements a bucket sort algorithm that:
- Takes command-line arguments as bucket boundaries
- Reads words from standard input (stdin)
- Sorts words into appropriate buckets based on alphabetical order
- Prints each non-empty bucket with its contents

## Program Requirements

### Input Format
- **Command-line arguments**: Must be provided in alphabetical order
- **Standard input**: Words separated by spaces, terminated by EOF (Ctrl+D)

### Output Format
- Each non-empty bucket is printed with format: `bucket #: word1 word2 word3...`
- Words within each bucket are space-separated
- Only non-empty buckets are displayed

### Error Handling
- **No CLAs**: "bucketsort: Fatal error! There must be at-least one CLA."
- **Non-alphabetical CLAs**: "bucketsort: Fatal error! CLAs must be entered in alphabetical order"

## Implementation Details

### Data Structures
```c
typedef struct node {
    char* string;
    struct node* next;
} node;

typedef struct bucket {
    char* min_word;
    node* head;
} bucket;
```

### Key Functions
1. **`insert_after()`**: Inserts a new node after a given node in a linked list
2. **`insert_into_bucket()`**: Finds the appropriate bucket and inserts a word in sorted order
3. **`main()`**: Handles command-line arguments, reads input, and manages the sorting process

### Algorithm
1. **Initialize buckets**: Create bucket array with command-line arguments as boundaries
2. **Validate input**: Check that CLAs are in alphabetical order
3. **Read input**: Parse words from stdin using `strtok()`
4. **Sort words**: For each word, find appropriate bucket and insert in sorted order
5. **Print results**: Display all non-empty buckets with their contents

## Usage Examples

### Test Case 1: No Command-Line Arguments
```bash
echo "test" | ./bucketsort
# Output: bucketsort: Fatal error! There must be at-least one CLA.
```

### Test Case 2: Non-alphabetical CLAs
```bash
echo "test" | ./bucketsort strawberry blackberry
# Output: bucketsort: Fatal error! CLAs must be entered in alphabetical order
```

### Test Case 3: Valid Input
```bash
echo "This is a simple example with 8 words." | ./bucketsort apple carrot kiwi pineapple watermelon
# Output:
# Next word is This
# Next word is is
# Next word is a
# Next word is simple
# Next word is example
# Next word is with
# Next word is 8
# Next word is words.
# bucket 0: 8 a
# bucket 2: example is
# bucket 4: simple This
# bucket 5: with words.
```

### Test Case 4: Another Valid Input
```bash
echo "I'd rather go shopping than go to the gym!" | ./bucketsort mango
# Output:
# Next word is I'd
# Next word is rather
# Next word is go
# Next word is shopping
# Next word is than
# Next word is go
# Next word is to
# Next word is the
# Next word is gym!
# bucket 0: go go gym! I'd
# bucket 1: rather shopping than the to
```

## Compilation

```bash
make -f Makefile_bucketsort
```

## Testing

```bash
make -f Makefile_bucketsort test
```

## Files

- `bucketsort.c`: Main implementation
- `Makefile_bucketsort`: Compilation rules
- `ag-bucketsort/`: Autograder files
- `COP4338_PA3_Bucket Sort.pdf`: Assignment specification

## Key Learning Points

1. **Linked Lists**: Implementation and manipulation of linked list data structures
2. **Memory Management**: Proper allocation and deallocation of dynamic memory
3. **String Handling**: Using `strtok()`, `strdup()`, and `strcasecmp()`
4. **Command-Line Arguments**: Processing and validating argc/argv
5. **Error Handling**: Graceful error messages and program termination
6. **Bucket Sort Algorithm**: Understanding and implementing the bucket sort concept 