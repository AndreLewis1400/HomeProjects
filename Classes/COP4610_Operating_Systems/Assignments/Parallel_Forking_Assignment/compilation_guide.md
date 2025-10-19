# Compilation and Testing Guide - COP4610 Parallel Forking Assignment

## Compilation on Ocelot (FIU Linux System)

### Prerequisites
- Access to FIU's Ocelot system
- `gcc` compiler with C99 support
- Math library (`-lm` flag)

### Compilation Command
```bash
gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm
```

### Compilation Flags Explained
- **`-O2`**: Optimization level 2 for better performance
- **`-Wall`**: Enable all common warnings
- **`-Wextra`**: Enable additional warnings
- **`-lm`**: Link with math library (required for `sin()`, `pow()`, `M_PI`)

### Expected Compilation Output
```bash
$ gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm
$ echo $?
0
```
*No warnings or errors should appear*

## Testing the Program

### Basic Usage
```bash
./parallel_forking <n>
```
Where `n` is the number of child processes (1-4)

### Test Cases

#### Test 1: Single Child Process
```bash
$ ./parallel_forking 1
[parent] Starting Parallel Forking with 1 child(ren)
[parent] All children finished. Results:
  child #0 | task: Count primes (<= 300k)      | result: 25997.000000 | time: 0.123 s | status: 0
[parent] Wall-clock elapsed: 0.125 s
```

#### Test 2: Two Child Processes
```bash
$ ./parallel_forking 2
[parent] Starting Parallel Forking with 2 child(ren)
[parent] All children finished. Results:
  child #0 | task: Count primes (<= 300k)      | result: 25997.000000 | time: 0.123 s | status: 0
  child #1 | task: Leibniz pi (~30M iters)     | result: 3.141593     | time: 0.456 s | status: 0
[parent] Wall-clock elapsed: 0.458 s
```

#### Test 3: All Four Child Processes
```bash
$ ./parallel_forking 4
[parent] Starting Parallel Forking with 4 child(ren)
[parent] All children finished. Results:
  child #0 | task: Count primes (<= 300k)      | result: 25997.000000 | time: 0.123 s | status: 0
  child #1 | task: Leibniz pi (~30M iters)     | result: 3.141593     | time: 0.456 s | status: 0
  child #2 | task: Matmul sum (N=140)          | result: 1960000.000  | time: 0.789 s | status: 0
  child #3 | task: Integrate sin [0,pi] (60M)  | result: 2.000000     | time: 0.234 s | status: 0
[parent] Wall-clock elapsed: 0.791 s
```

### Error Handling Tests

#### Invalid Number of Children
```bash
$ ./parallel_forking 0
Error: Number of children must be between 1 and 4
Usage: ./parallel_forking <n>
  n: Number of child processes to create (1-4)
  Each child performs a unique computational task

$ ./parallel_forking 5
Error: Number of children must be between 1 and 4
Usage: ./parallel_forking <n>
  n: Number of child processes to create (1-4)
  Each child performs a unique computational task
```

#### Missing Arguments
```bash
$ ./parallel_forking
Usage: ./parallel_forking <n>
  n: Number of child processes to create (1-4)
  Each child performs a unique computational task
```

## Expected Results Validation

### Task 1: Prime Counting (≤ 300,000)
- **Expected Result**: ~25,997 primes
- **Validation**: This is the actual count of primes ≤ 300,000
- **Performance**: Should complete in 0.1-0.2 seconds

### Task 2: Pi Approximation (Leibniz Series)
- **Expected Result**: ~3.141593 (accurate to 6 decimal places)
- **Validation**: Leibniz series converges to π/4
- **Performance**: Should complete in 0.4-0.6 seconds

### Task 3: Matrix Multiplication (140×140)
- **Expected Result**: Large positive number (depends on initialization)
- **Validation**: Sum of all elements in result matrix
- **Performance**: Should complete in 0.7-1.0 seconds (most time-consuming)

### Task 4: Numerical Integration (sin(x) from 0 to π)
- **Expected Result**: ~2.000000 (exact value is 2)
- **Validation**: ∫₀^π sin(x) dx = [-cos(x)]₀^π = 2
- **Performance**: Should complete in 0.2-0.3 seconds

## Performance Analysis

### Timing Characteristics
- **Wall-clock time** ≈ **max(child_times)** + **overhead**
- **Overhead** includes: fork() calls, pipe creation, IPC communication, process scheduling
- **CPU-bound tasks** show good parallelization benefits
- **Memory-intensive tasks** (matrix multiplication) may show cache effects

### Expected Performance Patterns
1. **Matrix multiplication** typically takes the longest (cache misses)
2. **Pi calculation** is moderate (simple floating-point operations)
3. **Integration** is fast (tight loop, good cache locality)
4. **Prime counting** varies (branch-heavy, depends on CPU)

## Debugging Tips

### Common Issues
1. **Compilation errors**: Ensure `-lm` flag is included
2. **Segmentation faults**: Check array bounds in matrix operations
3. **Hanging processes**: Verify pipe ends are properly closed
4. **Incorrect results**: Validate mathematical formulas

### Debug Compilation
```bash
gcc -g -O0 -Wall -Wextra -o parallel_forking_debug parallel_forking.c -lm
gdb ./parallel_forking_debug
```

### Memory Leak Check
```bash
valgrind --leak-check=full ./parallel_forking 4
```

## Submission Checklist

Before submitting, verify:
- [ ] Code compiles without warnings on Ocelot
- [ ] All test cases (1-4 children) work correctly
- [ ] Error handling works for invalid inputs
- [ ] Results are mathematically correct
- [ ] No memory leaks (valgrind clean)
- [ ] Video walkthrough is recorded
- [ ] All rubric points are covered

## File Transfer to Ocelot

### Using SCP
```bash
scp parallel_forking.c username@ocelot.fiu.edu:~/
```

### Using SFTP
```bash
sftp username@ocelot.fiu.edu
put parallel_forking.c
```

### Compilation on Ocelot
```bash
ssh username@ocelot.fiu.edu
gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm
./parallel_forking 4
```

---

*This guide ensures your program works correctly on FIU's Ocelot system and meets all assignment requirements.*
