# Labs

This directory contains laboratory exercises and hands-on work for COP4610 Operating Systems.

## Lab Structure

Each lab should follow this structure:
```
Lab_X/
├── README.md              # Lab instructions and objectives
├── exercises/             # Individual lab exercises
├── solutions/             # Solution code (if provided)
├── data/                  # Test data and input files
├── reports/               # Lab reports and analysis
└── resources/             # Reference materials and tools
```

## Lab Objectives

### Lab 1: System Calls and Process Creation
**Objectives:**
- Understand system calls and their usage
- Learn process creation with fork() and exec()
- Practice signal handling and process monitoring
- Use debugging tools (GDB, strace)

**Topics Covered:**
- Process creation and termination
- System call tracing
- Signal handling
- Process monitoring tools

**Tools Used:**
- Linux command line
- GCC compiler
- GDB debugger
- strace system call tracer

### Lab 2: Memory Management
**Objectives:**
- Understand memory allocation and deallocation
- Learn about memory leaks and how to detect them
- Practice with virtual memory concepts
- Use memory profiling tools

**Topics Covered:**
- Dynamic memory allocation (malloc, free)
- Memory leak detection
- Virtual memory concepts
- Memory profiling with valgrind

**Tools Used:**
- valgrind memory profiler
- Memory monitoring tools
- GCC with debugging symbols

### Lab 3: File I/O and System Programming
**Objectives:**
- Master file operations and system calls
- Understand file descriptors and permissions
- Practice directory operations
- Learn about file system internals

**Topics Covered:**
- File operations (open, read, write, close)
- File descriptors and permissions
- Directory operations
- File system monitoring

**Tools Used:**
- Linux system calls
- File system utilities
- Permission management tools

### Lab 4: Inter-Process Communication
**Objectives:**
- Understand IPC mechanisms
- Practice with pipes and shared memory
- Learn synchronization techniques
- Implement producer-consumer patterns

**Topics Covered:**
- Pipes and named pipes
- Shared memory segments
- Message queues
- Synchronization primitives

**Tools Used:**
- POSIX IPC mechanisms
- Synchronization libraries
- Process monitoring tools

## Lab Guidelines

### Preparation
1. **Read the lab instructions** thoroughly before starting
2. **Review relevant course materials** and system call documentation
3. **Set up your development environment** with required tools
4. **Understand the objectives** and expected outcomes

### During the Lab
1. **Follow the step-by-step instructions** carefully
2. **Test your code** with provided test cases
3. **Use debugging tools** when encountering issues
4. **Document your observations** and any problems encountered

### Lab Reports
Each lab should include:
- **Objective**: What you were trying to accomplish
- **Procedure**: Steps you followed
- **Results**: What you observed and measured
- **Analysis**: Interpretation of results
- **Conclusion**: Key learnings and insights

### Code Requirements
- **Clean, readable code** with proper comments
- **Proper error handling** for system calls
- **Testing with various inputs** and edge cases
- **Documentation** of any assumptions or limitations

## Common Lab Exercises

### Process Management
```c
// Example: Process creation and monitoring
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
    } else if (pid > 0) {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        wait(NULL);
        printf("Child process completed\n");
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}
```

### Memory Management
```c
// Example: Memory allocation and leak detection
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory
    int *arr = malloc(1000 * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
        return 1;
    }
    
    // Use the memory
    for (int i = 0; i < 1000; i++) {
        arr[i] = i;
    }
    
    // Free memory (comment out to create a leak)
    free(arr);
    
    return 0;
}
```

### File Operations
```c
// Example: File I/O operations
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }
    
    const char *message = "Hello, Operating Systems!\n";
    ssize_t bytes_written = write(fd, message, strlen(message));
    
    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return 1;
    }
    
    close(fd);
    printf("Wrote %zd bytes to file\n", bytes_written);
    
    return 0;
}
```

## Debugging Tips

### Using GDB
```bash
# Compile with debugging symbols
gcc -g -o program program.c

# Start GDB
gdb ./program

# Set breakpoints
(gdb) break main
(gdb) break line_number

# Run the program
(gdb) run

# Step through code
(gdb) step
(gdb) next

# Examine variables
(gdb) print variable_name
(gdb) info locals
```

### Using Valgrind
```bash
# Check for memory leaks
valgrind --leak-check=full ./program

# Check for memory errors
valgrind --tool=memcheck ./program

# Profile memory usage
valgrind --tool=massif ./program
```

### Using strace
```bash
# Trace system calls
strace ./program

# Trace specific system calls
strace -e trace=open,read,write ./program

# Save trace to file
strace -o trace.log ./program
```

## Lab Environment

### Required Software
- **Operating System**: Linux (Ubuntu, CentOS, or similar)
- **Compiler**: GCC (GNU Compiler Collection)
- **Debugger**: GDB (GNU Debugger)
- **Memory Tools**: Valgrind
- **System Tools**: strace, ltrace, perf

### Useful Commands
```bash
# System information
uname -a
cat /proc/version
cat /proc/cpuinfo

# Process monitoring
ps aux
top
htop

# Memory information
free -h
cat /proc/meminfo

# File system
df -h
du -sh *
```

---

For specific lab instructions, see the individual lab directories.
