# COP4610 Process Forking Analysis

## Assignment Code Analysis

```c
pid_t pid;
pid = fork();
if (pid == 0) { /* child process */
    fork();
    thread_create( . . .);
}
fork();
```

## Process Creation Analysis

### Step-by-Step Execution:

1. **Initial State**: 1 process (Parent)

2. **First fork()**: Creates 1 child process
   - Total processes: 2 (Parent + Child)

3. **Second fork()** (inside if block, child only):
   - Only the child process executes this
   - Creates 1 grandchild process
   - Total processes: 3 (Parent + Child + Grandchild)

4. **Third fork()** (outside if block):
   - **ALL processes** execute this fork
   - Parent creates 1 new child
   - Child creates 1 new child  
   - Grandchild creates 1 new child
   - Total processes: 6 (Original 3 + 3 new children)

## Thread Creation Analysis

### thread_create() Execution:
- Only executed by the **child process** (inside the if block)
- Creates **1 thread** in the child process
- The grandchild process also executes the if block, so it also creates **1 thread**

### Total Thread Count: **2 threads**

## Final Answer

**How many unique processes are created?**
- **Answer: 6 unique processes** (including the original parent)
- Total processes at end: 6 unique processes

**How many unique threads are created?**
- **Answer: 2 unique threads**
- 1 thread in the child process
- 1 thread in the grandchild process

## Process Tree Visualization

```
Original Parent (PID: X)
├── Child 1 (PID: Y) - creates thread
│   ├── Grandchild (PID: Z) - creates thread
│   └── Child 1's child (PID: A)
├── Parent's child (PID: B)
└── Grandchild's child (PID: C)
```

## Compilation and Execution

```bash
# Compile
gcc -Wall -Wextra -std=c99 -pthread -o fork_analysis fork_analysis.c

# Run
./fork_analysis
```

## Key Concepts Demonstrated

1. **Process Forking**: Each fork() creates a new process
2. **Conditional Execution**: if (pid == 0) ensures code runs only in child
3. **Thread Creation**: pthread_create() creates threads within processes
4. **Process Tree**: Understanding parent-child relationships
5. **Concurrent Execution**: Multiple processes and threads running simultaneously
