# COP4338 Systems Programming

This directory contains assignments and projects for COP4338: Systems Programming at FIU.

## Course Overview

COP4338 covers systems programming concepts and implementations in C, including:
- Memory management and pointers
- Process control and inter-process communication
- File I/O and system calls
- Multithreading and synchronization
- Race conditions and debugging

## Projects & Assignments

### Assignment 1: Pattern Checker
- **Directory**: [`Assignment_1/`](Assignment_1/)
- **Description**: Pattern matching and validation program
- **Files**: Pattern checker implementation and related documentation

### Programming Assignment 3: Bucket Sort
- **Directory**: [`Programming Assignment 3/`](Programming%20Assignment%203/)
- **Description**: Implementation of bucket sort algorithm
- **Files**: 
  - `bucketsort.c`: Main implementation
  - `Makefile_bucketsort`: Build configuration
  - `README_Bucket_Sort.md`: Detailed documentation
  - `COP4338_PA3_Bucket Sort.pdf`: Assignment specification

### Programming Assignment 4: Advanced Systems Programming
- **Directory**: [`Programming_Assignment_4/`](Programming_Assignment_4/)
- **Description**: Advanced systems programming concepts
- **Files**: Implementation and documentation

### Discussion Forums
- **Directory**: [`Discussion_Forums/`](Discussion_Forums/)
- **Description**: Various discussion forum exercises and implementations

## Additional Exercises

### File I/O and Data Processing
- **`file_io_converter.c`**: File format conversion utility
- **`csv_to_txt_converter.c`**: CSV to text file converter
- **`date_scanner_fixed.c`**: Date parsing and validation

### Multithreading and Synchronization
- **`bank.c`** & **`bank_fixed`**: Banking simulation with race condition fixes
- **`discussion_forum_6.c`**: Multithreading examples
- **`test_race_conditions.sh`**: Race condition testing script
- **`Makefile_multithreading`**: Build configuration for multithreading projects

### Analysis and Debugging
- **`printf_analysis.c`**: Printf function analysis and examples
- **`main_fixed.c`**: Fixed version of main program

## Documentation

- **`README_Discussion_Forum_9.md`**: Discussion forum 9 documentation
- **`README_discussion_forum_6.md`**: Discussion forum 6 documentation
- **`README_Discussion_Forum_8.md`**: Discussion forum 8 documentation
- **`README_Bucket_Sort.md`**: Comprehensive bucket sort documentation

## Build Instructions

### Compiling C Programs
```bash
# Basic compilation
gcc -o program_name program_name.c

# With debugging symbols
gcc -g -o program_name program_name.c

# Using provided Makefiles
make -f Makefile_name
```

### Running Programs
```bash
# Execute compiled programs
./program_name

# Run with input files
./program_name < input.txt

# Run shell scripts
bash test_race_conditions.sh
```

## Key Learning Outcomes

- **Memory Management**: Understanding pointers, dynamic allocation, and memory leaks
- **Process Control**: Fork, exec, wait, and process synchronization
- **File Operations**: File I/O, permissions, and system calls
- **Multithreading**: Thread creation, synchronization, and race condition prevention
- **Debugging**: Using gdb, valgrind, and other debugging tools
- **System Programming**: Low-level programming concepts and Unix/Linux systems

---

For detailed documentation on specific assignments, see the README files in each subdirectory. 