# Assignments

This directory contains all programming assignments for COP4610 Operating Systems.

## Assignment Structure

Each assignment should follow this structure:
```
Assignment_X/
├── README.md              # Assignment description and instructions
├── src/                   # Source code files
├── include/               # Header files
├── tests/                 # Test files and test data
├── docs/                  # Documentation and reports
├── Makefile              # Build configuration
└── submission/           # Files ready for submission
```

## Assignment Guidelines

### Code Requirements
- **Language**: C/C++ (unless otherwise specified)
- **Compiler**: GCC with C99 or C++11 standard
- **Platform**: Linux/Unix environment
- **Documentation**: Comprehensive comments and README files

### Build Instructions
Each assignment should include:
1. A `Makefile` for easy compilation
2. Clear build instructions in the README
3. Dependencies and requirements listed
4. Test instructions and expected output

### Submission Requirements
1. **Source Code**: All `.c` and `.h` files
2. **Documentation**: README with build/run instructions
3. **Testing**: Evidence that code works correctly
4. **Clean Code**: No temporary files or build artifacts

### Grading Criteria
- **Functionality**: Code works as specified
- **Code Quality**: Clean, readable, well-commented code
- **Documentation**: Clear instructions and explanations
- **Testing**: Proper testing and validation
- **Efficiency**: Reasonable performance and resource usage

## Assignment Topics

### Process Management
- Process creation and termination
- Process scheduling algorithms
- Context switching simulation
- Process state management

### Memory Management
- Virtual memory simulation
- Page replacement algorithms (LRU, FIFO, etc.)
- Memory allocation strategies
- Memory leak detection

### File Systems
- File operations and system calls
- Directory structure implementation
- Disk space management
- File permissions and security

### Synchronization
- Producer-consumer problems
- Dining philosophers problem
- Reader-writer problems
- Deadlock detection and prevention

### Inter-Process Communication
- Pipes and named pipes
- Shared memory segments
- Message queues
- Sockets and network communication

## Development Tips

### Debugging
```bash
# Compile with debugging symbols
gcc -g -Wall -o program program.c

# Run with GDB
gdb ./program

# Check for memory leaks
valgrind --leak-check=full ./program

# Trace system calls
strace ./program
```

### Testing
- Test with various input sizes and edge cases
- Verify correct system call usage
- Check for memory leaks and buffer overflows
- Validate output format and correctness

### Performance
- Use appropriate data structures
- Minimize system call overhead
- Implement efficient algorithms
- Profile and optimize critical sections

## Resources

### System Calls Reference
- `man 2 <system_call>` - System call documentation
- `man 3 <function>` - Library function documentation
- `/usr/include/` - Header files for system calls

### Useful Commands
```bash
# Process information
ps aux | grep <program>
top -p <pid>

# Memory usage
cat /proc/<pid>/status
pmap <pid>

# File system
ls -la /proc/<pid>/fd/
lsof -p <pid>
```

---

For specific assignment instructions, see the individual assignment directories.
