# COP4610 Operating Systems

This repository contains coursework, assignments, and projects for COP4610: Operating Systems at FIU.

## Course Overview

COP4610 covers fundamental concepts of operating systems, including:
- Process management and scheduling
- Memory management and virtual memory
- File systems and storage
- Input/Output systems
- Inter-process communication
- Synchronization and deadlocks
- Security and protection

## Repository Structure

```
COP4610_Operating_Systems/
├── Assignments/           # Programming assignments and homework
├── Labs/                  # Laboratory exercises and hands-on work
├── Projects/              # Major projects and implementations
├── Notes/                 # Class notes and study materials
├── Resources/             # Reference materials and documentation
├── Code_Examples/         # Example code and demonstrations
└── README.md             # This file
```

## Assignments

### Assignment 1: Process Management
- **Description**: Implementation of process creation, scheduling, and management
- **Language**: C/C++
- **Topics**: Fork, exec, wait, process states, scheduling algorithms

### Assignment 2: Memory Management
- **Description**: Virtual memory simulation and page replacement algorithms
- **Language**: C/C++
- **Topics**: Paging, segmentation, page faults, LRU, FIFO algorithms

### Assignment 3: File Systems
- **Description**: Simple file system implementation
- **Language**: C/C++
- **Topics**: File operations, directory structures, disk management

### Assignment 4: Synchronization
- **Description**: Producer-consumer problem and synchronization primitives
- **Language**: C/C++ with POSIX threads
- **Topics**: Mutexes, semaphores, condition variables, deadlock prevention

## Labs

### Lab 1: System Calls and Process Creation
- **Objective**: Learn system calls for process management
- **Tools**: Linux command line, gcc, gdb
- **Exercises**: Process creation, signal handling, process monitoring

### Lab 2: Memory Management
- **Objective**: Understand memory allocation and management
- **Tools**: valgrind, memory profilers
- **Exercises**: Dynamic allocation, memory leaks, virtual memory

### Lab 3: File I/O and System Programming
- **Objective**: File operations and system programming
- **Tools**: Linux system calls, file descriptors
- **Exercises**: File reading/writing, directory operations, permissions

### Lab 4: Inter-Process Communication
- **Objective**: IPC mechanisms and synchronization
- **Tools**: Pipes, shared memory, message queues
- **Exercises**: Process communication, data sharing, synchronization

## Projects

### Project 1: Shell Implementation
- **Description**: Custom shell with job control and piping
- **Language**: C
- **Features**: Command parsing, process execution, job control, redirection

### Project 2: Thread Pool Implementation
- **Description**: Multi-threaded server with thread pool
- **Language**: C with POSIX threads
- **Features**: Thread management, task queuing, load balancing

### Project 3: File System Simulator
- **Description**: Simulation of a simple file system
- **Language**: C/C++
- **Features**: File operations, directory management, disk simulation

## Key Learning Outcomes

- **Process Management**: Understanding of process lifecycle, scheduling, and context switching
- **Memory Management**: Virtual memory concepts, paging, and memory allocation
- **File Systems**: File operations, directory structures, and storage management
- **Synchronization**: Thread safety, deadlock prevention, and IPC mechanisms
- **System Programming**: Low-level programming with system calls and kernel interfaces

## Development Environment

### Required Tools
- **Compiler**: GCC (GNU Compiler Collection)
- **Debugger**: GDB (GNU Debugger)
- **Memory Tools**: Valgrind for memory leak detection
- **System Monitoring**: top, htop, ps, strace
- **Version Control**: Git

### Compilation Commands
```bash
# Basic compilation
gcc -o program program.c

# With debugging symbols
gcc -g -o program program.c

# With threading support
gcc -pthread -o program program.c

# With optimization
gcc -O2 -o program program.c
```

### Debugging Commands
```bash
# Run with GDB
gdb ./program

# Memory leak detection
valgrind --leak-check=full ./program

# System call tracing
strace ./program
```

## Resources

### Textbooks
- "Operating System Concepts" by Silberschatz, Galvin, and Gagne
- "Advanced Programming in the UNIX Environment" by Stevens and Rago

### Online Resources
- [Linux System Programming](https://man7.org/tlpi/)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [GNU C Library Documentation](https://www.gnu.org/software/libc/manual/)

### Useful Commands
```bash
# Process management
ps aux                    # List all processes
top                       # Real-time process monitor
kill -9 <pid>            # Force kill process

# Memory information
free -h                   # Memory usage
cat /proc/meminfo        # Detailed memory info

# File system
df -h                     # Disk usage
du -sh *                 # Directory sizes
ls -la                    # Detailed file listing

# System information
uname -a                  # System information
cat /proc/version        # Kernel version
```

## Best Practices

### Code Organization
- Use meaningful variable and function names
- Add comprehensive comments
- Follow consistent indentation and formatting
- Implement proper error handling

### Testing and Debugging
- Test with various input scenarios
- Use debugging tools (GDB, Valgrind)
- Implement logging for troubleshooting
- Handle edge cases and error conditions

### Documentation
- Document all functions and their parameters
- Include usage examples
- Maintain README files for each project
- Keep notes on system behavior and observations

## Submission Guidelines

1. **Code Quality**: Clean, well-commented, and properly formatted code
2. **Documentation**: Include README files with build and run instructions
3. **Testing**: Demonstrate that your code works with provided test cases
4. **Git Usage**: Use meaningful commit messages and proper branching

---

For questions or issues, refer to the course materials or contact the instructor.
