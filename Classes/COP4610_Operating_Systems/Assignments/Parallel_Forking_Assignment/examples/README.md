# Learning Examples - Process Management & IPC

This directory contains simple examples that demonstrate the key concepts from your COP4610 Parallel Forking assignment.

## Examples Overview

### 1. `simple_fork.c` - Basic Process Creation
**What it teaches**: How `fork()` creates new processes
**Key concepts**:
- Process creation with `fork()`
- Parent vs child process execution
- Process synchronization with `wait()`
- Exit status handling

**Run it**:
```bash
make simple_fork
./simple_fork
```

### 2. `simple_pipe.c` - Basic Inter-Process Communication
**What it teaches**: How processes communicate using pipes
**Key concepts**:
- Pipe creation with `pipe()`
- File descriptor management
- Data flow between processes
- Proper pipe cleanup

**Run it**:
```bash
make simple_pipe
./simple_pipe
```

### 3. `timing_example.c` - Performance Measurement
**What it teaches**: How to measure execution time accurately
**Key concepts**:
- `clock_gettime()` for precise timing
- `clock()` for CPU time measurement
- `gettimeofday()` (deprecated but still used)
- Timing precision and accuracy

**Run it**:
```bash
make timing_example
./timing_example
```

### 4. `error_handling.c` - Robust Error Handling
**What it teaches**: How to handle errors in system programming
**Key concepts**:
- Checking return values from system calls
- Using `perror()` for error messages
- Proper resource cleanup on errors
- Memory and file error handling

**Run it**:
```bash
make error_handling
./error_handling
```

### 5. `complete_example.c` - Full Parallel Processing
**What it teaches**: How to combine all concepts into a working program
**Key concepts**:
- Multiple process creation
- Struct-based IPC communication
- Performance measurement
- Comprehensive error handling
- Process synchronization

**Run it**:
```bash
make complete_example
./complete_example
```

## How to Use These Examples

### Compile All Examples
```bash
make all
```

### Run All Examples
```bash
make test
```

### Clean Up
```bash
make clean
```

### Get Help
```bash
make help
```

## Learning Path

1. **Start with `simple_fork.c`** - Understand basic process creation
2. **Move to `simple_pipe.c`** - Learn inter-process communication
3. **Try `timing_example.c`** - Understand performance measurement
4. **Study `error_handling.c`** - Learn robust error handling
5. **Examine `complete_example.c`** - See how everything fits together

## Key Takeaways

### Process Management
- **fork()** creates a copy of the current process
- **Child process** gets PID 0, **parent** gets child's PID
- **wait()** synchronizes parent and child processes
- **exit()** terminates a process with a status code

### Inter-Process Communication
- **Pipes** are unidirectional communication channels
- **pipe_fd[0]** is read end, **pipe_fd[1]** is write end
- **Always close unused ends** to prevent hanging
- **Check return values** of read/write operations

### Performance Measurement
- **clock_gettime(CLOCK_MONOTONIC)** is most accurate
- **Wall-clock time** measures real elapsed time
- **CPU time** measures actual processing time
- **Timing precision** varies by system and method

### Error Handling
- **Always check return values** from system calls
- **perror()** provides descriptive error messages
- **Clean up resources** on error conditions
- **Use meaningful exit codes** for debugging

## Common Pitfalls to Avoid

1. **Forgetting to close pipe ends** - Causes hanging processes
2. **Not checking return values** - Misses error conditions
3. **Memory leaks** - Always free what you allocate
4. **Zombie processes** - Always wait for children
5. **Race conditions** - Be careful with shared resources

## Next Steps

1. **Modify the examples** - Try changing the tasks or adding features
2. **Experiment with timing** - Compare different timing methods
3. **Add more error handling** - Make the programs more robust
4. **Try different IPC methods** - Shared memory, message queues
5. **Study your main assignment** - See how these concepts apply

## Understanding Your Main Assignment

Your `parallel_forking.c` program uses all these concepts:

- **fork()** creates multiple child processes
- **pipes** enable communication between parent and children
- **clock_gettime()** measures execution time
- **Comprehensive error handling** makes it robust
- **wait()** synchronizes all processes

These examples help you understand each piece before seeing how they work together in the complete program.

---

*Use these examples to deepen your understanding of process management and IPC concepts!*
