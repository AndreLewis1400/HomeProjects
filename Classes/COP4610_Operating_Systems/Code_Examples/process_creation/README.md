# Process Creation Example

This example demonstrates basic process creation using the `fork()` and `exec()` system calls.

## Description

The program creates a child process using `fork()`, then the child process executes a command using `execl()`. The parent process waits for the child to complete using `waitpid()`.

## Key Concepts

- **Process Creation**: Using `fork()` to create new processes
- **Process Execution**: Using `exec()` family functions to run programs
- **Process Synchronization**: Using `wait()` family functions to wait for child processes
- **Process Termination**: Understanding how processes terminate and exit status

## System Calls Used

- `fork()` - Creates a new process
- `execl()` - Executes a program in the current process
- `waitpid()` - Waits for a specific child process to terminate
- `getpid()` - Gets the current process ID
- `getppid()` - Gets the parent process ID

## Compilation and Execution

### Basic Usage
```bash
# Compile the program
make

# Run the program
make run

# Or run directly
./process_creation
```

### Debugging
```bash
# Compile with debugging symbols
make debug

# Run with GDB
make debug-run

# Run with system call tracing
make trace

# Run with memory checking
make memcheck
```

## Expected Output

```
Parent process: PID = 12345
About to create child process...

Parent: Created child process with PID = 12346
Parent: Waiting for child to complete...
Child process: PID = 12346, Parent PID = 12345
Child: Executing 'ls -l' command...
total 8
-rwxr-xr-x 1 user user 12345 Sep 13 10:30 process_creation
-rw-r--r-- 1 user user   456 Sep 13 10:30 main.c
-rw-r--r-- 1 user user   123 Sep 13 10:30 Makefile
Parent: Child process exited with status 0
Parent: Child process completed
Process 12345: Exiting
```

## Code Explanation

### Process Creation
```c
pid = fork();
```
- Creates a new process by duplicating the current process
- Returns 0 in the child process, child's PID in the parent process, or -1 on error

### Child Process Execution
```c
if (pid == 0) {
    // Child process code
    execl("/bin/ls", "ls", "-l", NULL);
}
```
- The child process executes the `ls -l` command
- `execl()` replaces the current process image with a new program

### Parent Process Waiting
```c
waitpid(pid, &status, 0);
```
- The parent process waits for the specific child process to terminate
- `status` contains information about how the child terminated

## Common Issues and Solutions

### Fork Failed
- **Cause**: System resource limits or insufficient memory
- **Solution**: Check system limits with `ulimit -a`

### Exec Failed
- **Cause**: Program not found or permission denied
- **Solution**: Verify the program path and permissions

### Wait Failed
- **Cause**: Invalid process ID or process already waited for
- **Solution**: Check the process ID and ensure it's a child process

## Learning Exercises

1. **Modify the program** to execute different commands
2. **Add error handling** for all system calls
3. **Create multiple child processes** and wait for all of them
4. **Implement signal handling** for Ctrl+C interruption
5. **Add process monitoring** to show process states

## Related Examples

- Signal handling
- Process groups and sessions
- Job control
- Inter-process communication

## References

- `man 2 fork` - fork() system call documentation
- `man 2 exec` - exec() family functions documentation
- `man 2 wait` - wait() family functions documentation
- `man 2 getpid` - getpid() and getppid() documentation
