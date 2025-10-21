# Discussion Forum 6: Line Sorting Program

This program reads multiple lines from stdin, sorts them alphabetically, and prints them in sorted order. It supports both case-sensitive and case-insensitive sorting.

## Features

- **Case-sensitive sorting** (default behavior)
- **Case-insensitive sorting** (with `-i` flag)
- **Memory management** with proper allocation and deallocation
- **Error handling** for memory allocation failures
- **Help system** with usage information

## Files

- `discussion_forum_6.c`: Main source file
- `Makefile`: Build instructions
- `README_discussion_forum_6.md`: This documentation

## How to Build

```bash
make
```

## How to Run

### Case-sensitive sorting (default):
```bash
./discussion_forum_6
```

### Case-insensitive sorting:
```bash
./discussion_forum_6 -i
```

### Help:
```bash
./discussion_forum_6 -h
./discussion_forum_6 --help
```

## Usage Examples

### Input from keyboard:
```bash
./discussion_forum_6
# Type lines, press Ctrl+D (Unix) or Ctrl+Z (Windows) when done
```

### Input from file:
```bash
cat input.txt | ./discussion_forum_6
```

### Input from echo:
```bash
echo -e "Zebra\napple\nBanana\ncat" | ./discussion_forum_6
```

## Test Cases

Run the built-in tests:
```bash
make test
```

This will demonstrate both case-sensitive and case-insensitive sorting.

## Program Structure

1. **`read_lines()`**: Reads lines from stdin and stores them in dynamically allocated memory
2. **`write_lines()`**: Prints the sorted lines
3. **`compare_strings()`**: Case-sensitive string comparison for qsort
4. **`compare_strings_ignore_case()`**: Case-insensitive string comparison for qsort
5. **`main()`**: Handles command-line arguments and orchestrates the sorting process

## Memory Management

- Each line is dynamically allocated using `malloc()`
- Memory is properly freed at the end using `free()`
- Error handling for memory allocation failures

## Author

- Andre Lewis
- Florida International University (FIU)
- COP4338 Systems Programming 