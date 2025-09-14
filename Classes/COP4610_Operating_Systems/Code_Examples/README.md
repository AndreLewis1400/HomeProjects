# Code Examples

This directory contains example code and demonstrations for COP4610 Operating Systems concepts.

## Example Categories

### Process Management
- Process creation and termination
- Signal handling
- Process monitoring
- Job control

### Memory Management
- Dynamic memory allocation
- Memory leak detection
- Virtual memory concepts
- Memory mapping

### File Systems
- File operations
- Directory traversal
- File permissions
- System calls

### Synchronization
- Thread creation and management
- Mutexes and condition variables
- Semaphores
- Deadlock prevention

### Inter-Process Communication
- Pipes and named pipes
- Shared memory
- Message queues
- Sockets

## Example Structure

Each example follows this structure:
```
example_name/
├── README.md              # Example description and usage
├── main.c                 # Main source file
├── Makefile              # Build configuration
├── test_data/            # Test input files
└── output/               # Expected output examples
```

## Quick Start

### Compiling Examples
```bash
# Navigate to an example directory
cd process_creation/

# Compile the example
make

# Run the example
./process_creation
```

### Running with Debugging
```bash
# Compile with debugging symbols
make debug

# Run with GDB
gdb ./process_creation

# Run with valgrind
valgrind --leak-check=full ./process_creation
```

## Example Descriptions

### Process Creation
**File**: `process_creation/main.c`
**Description**: Demonstrates process creation using fork() and exec()
**Key Concepts**: Process lifecycle, system calls, process hierarchy

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Child: PID = %d\n", getpid());
        execl("/bin/ls", "ls", "-l", NULL);
    } else if (pid > 0) {
        // Parent process
        printf("Parent: PID = %d, Child PID = %d\n", getpid(), pid);
        wait(NULL);
        printf("Child completed\n");
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}
```

### Memory Management
**File**: `memory_management/main.c`
**Description**: Shows proper memory allocation and deallocation
**Key Concepts**: malloc/free, memory leaks, error handling

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Allocate memory
    char *buffer = malloc(1024);
    if (buffer == NULL) {
        perror("malloc failed");
        return 1;
    }
    
    // Use memory
    strcpy(buffer, "Hello, Memory Management!");
    printf("%s\n", buffer);
    
    // Free memory
    free(buffer);
    buffer = NULL;  // Prevent dangling pointer
    
    return 0;
}
```

### File Operations
**File**: `file_operations/main.c`
**Description**: Demonstrates file I/O operations
**Key Concepts**: File descriptors, system calls, error handling

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    // Open file for writing
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open failed");
        return 1;
    }
    
    // Write data
    const char *data = "Hello, File System!\n";
    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("write failed");
        close(fd);
        return 1;
    }
    
    // Close file
    close(fd);
    printf("Wrote %zd bytes\n", bytes_written);
    
    return 0;
}
```

### Thread Synchronization
**File**: `thread_sync/main.c`
**Description**: Shows thread creation and synchronization
**Key Concepts**: pthreads, mutexes, thread safety

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    
    // Create threads
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);
    
    // Wait for threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    printf("Final counter value: %d\n", counter);
    
    return 0;
}
```

## Build Instructions

### Basic Compilation
```bash
# Single file compilation
gcc -o program program.c

# Multiple files
gcc -o program file1.c file2.c file3.c

# With debugging symbols
gcc -g -o program program.c

# With optimization
gcc -O2 -o program program.c
```

### Threaded Programs
```bash
# Compile with pthread support
gcc -pthread -o program program.c

# Or use -lpthread
gcc -o program program.c -lpthread
```

### Makefile Example
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -pthread

TARGET = example
SOURCES = main.c helper.c
OBJECTS = $(SOURCES:.c=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
```

## Testing Examples

### Running Tests
```bash
# Run basic functionality test
./example

# Test with different inputs
echo "test input" | ./example

# Test with file input
./example < input.txt

# Test output redirection
./example > output.txt
```

### Debugging Tests
```bash
# Run with GDB
gdb ./example
(gdb) run
(gdb) break main
(gdb) step

# Check for memory leaks
valgrind --leak-check=full ./example

# Trace system calls
strace ./example
```

## Common Issues and Solutions

### Compilation Errors
```bash
# Undefined reference to pthread functions
# Solution: Add -pthread flag
gcc -pthread -o program program.c

# Missing header files
# Solution: Install development packages
sudo apt-get install build-essential

# Permission denied
# Solution: Check file permissions
chmod +x program
```

### Runtime Errors
```bash
# Segmentation fault
# Solution: Use GDB to debug
gdb ./program
(gdb) run
(gdb) bt  # backtrace

# Memory leaks
# Solution: Use valgrind
valgrind --leak-check=full ./program

# File not found
# Solution: Check file paths and permissions
ls -la filename
```

## Performance Considerations

### Optimization Flags
```bash
# Basic optimization
gcc -O2 -o program program.c

# Aggressive optimization
gcc -O3 -o program program.c

# Size optimization
gcc -Os -o program program.c
```

### Profiling
```bash
# Compile with profiling
gcc -pg -o program program.c

# Run and generate profile
./program
gprof program gmon.out

# Use perf for detailed profiling
perf record ./program
perf report
```

## Resources

### Documentation
- `man 2 <system_call>` - System call documentation
- `man 3 <function>` - Library function documentation
- `/usr/include/` - Header files

### Online Resources
- [Linux System Programming](https://man7.org/tlpi/)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [GNU C Library Documentation](https://www.gnu.org/software/libc/manual/)

### Tools
- **Compiler**: GCC with various optimization flags
- **Debugger**: GDB for debugging
- **Memory Tools**: Valgrind for memory analysis
- **Profiler**: perf, gprof for performance analysis
- **System Monitor**: top, htop, ps for process monitoring

---

For specific examples, see the individual example directories.
