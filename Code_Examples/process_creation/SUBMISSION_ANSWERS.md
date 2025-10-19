# COP4610 Assignment Submission

## Code Segment Analysis

```c
pid_t pid;
pid = fork();
if (pid == 0) { /* child process */
    fork();
    thread_create( . . .);
}
fork();
```

## Answers

### Question 1: How many unique processes are created?

**Answer: 6 unique processes**

**Explanation:**
1. **Initial process**: 1 process (parent)
2. **First fork()**: Creates 1 child process (total: 2 processes)
3. **Second fork()** (inside if block): Creates 1 grandchild process (total: 3 processes)  
4. **Third fork()** (outside if block): Creates 3 new processes (total: 6 processes)

**Final count: 6 total unique processes** (including the original parent)

### Question 2: How many unique threads are created?

**Answer: 2 unique threads**

**Explanation:**
- The `thread_create()` call is inside the `if (pid == 0)` block
- This means only child processes execute it
- The child process creates 1 thread
- The grandchild process also executes the if block and creates 1 thread
- **Total: 2 threads created**

## Process Tree

```
Original Parent (PID: X)
├── Child 1 (PID: Y) - creates 1 thread
│   ├── Grandchild (PID: Z) - creates 1 thread  
│   └── Child 1's child (PID: A)
├── Parent's child (PID: B)
└── Grandchild's child (PID: C)
```

## Verification

The program `fork_analysis.c` demonstrates this behavior and confirms:
- **6 unique processes total** (including original parent)
- **2 unique threads created** (1 in child, 1 in grandchild)

## Files Created

1. `fork_analysis.c` - Working C program demonstrating the code
2. `Makefile` - Compilation instructions
3. `FORK_ANALYSIS.md` - Detailed analysis
4. `SUBMISSION_ANSWERS.md` - This submission document

## Compilation and Testing

```bash
gcc -Wall -Wextra -std=c99 -pthread -o fork_analysis fork_analysis.c
./fork_analysis
```

**Student: Andre Lewis**  
**Course: COP4610 Operating Systems**  
**Assignment: Process Forking Analysis**
