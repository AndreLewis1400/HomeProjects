# Discussion Forum 6: Line Sorting Program

## Assignment Description

Rewrite a C program that receives multiple lines from stdin, sorts them alphabetically, and prints them in sorted order. The program should allow an optional command-line argument "-i" to ignore case when sorting. The default behavior should remain case-sensitive.

## Problem Statement

**Original Program:** Sorts lines case-sensitively (uppercase comes before lowercase)

**Enhanced Requirements:**
- Add `-i` flag for case-insensitive sorting
- Maintain default case-sensitive behavior
- Handle command-line arguments properly
- Provide help functionality

## Solution

### Key Features Implemented

1. **Case-sensitive sorting** (default behavior)
2. **Case-insensitive sorting** (with `-i` flag)
3. **Flexible argument parsing** (can place `-i` anywhere)
4. **Help system** (`-h` or `--help`)
5. **Error handling** for invalid arguments
6. **Memory management** with proper allocation/deallocation
7. **Cross-platform compatibility** (Windows/Linux/macOS)

### Files

- `discussion_forum_6.c` - Main source file
- `Makefile` - Build instructions and test targets
- `README.md` - This documentation
- `test_input.txt` - Sample test data

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

### Interactive input:
```bash
./discussion_forum_6
# Type lines, press Ctrl+D (Unix) or Ctrl+Z (Windows) when done
```

### Input from file:
```bash
cat test_input.txt | ./discussion_forum_6
```

### Input from echo:
```bash
printf "Zebra\napple\nBanana\ncat\n" | ./discussion_forum_6
```

## Test Cases

Run the built-in tests:
```bash
make test
```

This demonstrates both sorting modes:
- **Case-sensitive:** "Banana" comes before "apple"
- **Case-insensitive:** "apple" comes before "Banana"

## Program Structure

### Functions

1. **`read_lines()`** - Reads lines from stdin and stores them in dynamically allocated memory
2. **`write_lines()`** - Prints the sorted lines
3. **`compare_strings()`** - Case-sensitive string comparison for qsort
4. **`compare_strings_ignore_case()`** - Case-insensitive string comparison for qsort
5. **`print_usage()`** - Displays help information
6. **`main()`** - Handles command-line arguments and orchestrates the sorting process

### Key Implementation Details

- **Global flag:** `ignore_case` determines sorting behavior
- **Memory management:** Each line is dynamically allocated and properly freed
- **Cross-platform:** Uses `strcasecmp` on Unix/Linux, `_stricmp` on Windows
- **Error handling:** Reports memory allocation failures and invalid arguments

## Memory Management

- Each line is dynamically allocated using `malloc()`
- Memory is properly freed at the end using `free()`
- Error handling for memory allocation failures
- No memory leaks

## Testing

The program includes comprehensive testing:
- Built-in test cases in Makefile
- Support for file input testing
- Interactive testing capabilities

## Author

- **Name:** Andre Lewis
- **Institution:** Florida International University (FIU)
- **Course:** COP4338 Systems Programming
- **Assignment:** Discussion Forum 6

## Course Information

- **Course:** COP4338 Systems Programming
- **Topic:** Command-line arguments and string sorting
- **Skills Demonstrated:** C programming, memory management, argument parsing, string manipulation 