# Discussion Forum 8: I/O in C - Solutions

This directory contains solutions for the Discussion Forum 8 problems on C I/O operations.

## Problems Solved

### Problem 1: CSV to TXT Conversion with Scientific Notation
**File**: `csv_to_txt_converter.c`
- Converts CSV format (comma-separated) to TXT format (tab-delimited)
- Uses `%-25e` format specifier for scientific notation with left alignment
- Each cell is exactly 25 characters wide
- Input: integers from stdin
- Output: formatted table to stdout

**Usage**:
```bash
./csv_to_txt_converter
# Enter: 1,2,3,4,5,6
```

### Problem 2: File I/O Enhancement
**File**: `file_io_converter.c`
- Reads from `input.csv` file
- Writes formatted output to `output.txt` file
- Uses `fscanf` and `fprintf` for file operations
- Same formatting as Problem 1 but with file I/O

**Usage**:
```bash
# Create input.csv with your data first
./file_io_converter
```

### Problem 3: printf Output Analysis
**File**: `printf_analysis.c`
- Analyzes the complex printf statement:
  ```c
  printf("%05d,,,%-7.2f,,,%7.2e,,,%x,,,%0,,,%10.5s.", 31, 11.0/3, 11.0/3, 31, 31, "umbrella");
  ```

**Format Specifiers Explained**:
1. `%05d` - 5-digit width, zero-padded, right-aligned integer
2. `%-7.2f` - 7-char width, left-aligned float with 2 decimal places
3. `%7.2e` - 7-char width, right-aligned scientific notation
4. `%x` - hexadecimal representation
5. `%0` - Invalid format specifier (prints literally)
6. `%10.5s` - 10-char width, right-aligned string (max 5 chars)

**Expected Output**:
```
00031,,,3.67   ,,, 3.67e+00,,,1f,,,%0,,,     umbre.
```

## Fixed Date Scanner
**File**: `date_scanner_fixed.c`
- Fixed the original date scanner code
- **Bug Fix**: Case 6 now returns "Jun" instead of "Jan"
- Added date validation function
- Improved buffer sizes and error handling
- Supports both `mm/dd/yyyy` and `day monthname year` formats

## Compilation
```bash
make all          # Compile all programs
make clean        # Remove compiled files
make test         # Run tests
```

## Key Learning Points

1. **Format Specifiers**: Understanding `%d`, `%f`, `%e`, `%x`, `%s` and their modifiers
2. **File I/O**: Using `fopen`, `fscanf`, `fprintf`, `fclose`
3. **Input Validation**: Checking return values and validating data
4. **Buffer Management**: Proper string handling and buffer sizes
5. **Error Handling**: Graceful handling of file operations and invalid input 