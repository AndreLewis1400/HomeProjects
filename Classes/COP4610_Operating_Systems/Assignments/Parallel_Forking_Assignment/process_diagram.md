# Process/IPC Diagram - Parallel Forking Assignment

## Visual Process Flow Diagram

```
                    PARENT PROCESS
                    ┌─────────────────┐
                    │  main()         │
                    │  - Parse args   │
                    │  - Create pipes │
                    │  - fork() loop  │
                    └─────────────────┘
                           │
                    ┌──────┼──────┐
                    │      │      │
                    ▼      ▼      ▼
            ┌─────────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐
            │ CHILD 0 │ │ CHILD 1 │ │ CHILD 2 │ │ CHILD 3 │
            │         │ │         │ │         │ │         │
            │ Primes  │ │ Pi Calc │ │ Matrix  │ │ Integr. │
            │ ≤300k   │ │ ~30M    │ │ 140×140 │ │ sin(x)  │
            │         │ │ iters   │ │ mult.   │ │ 60M     │
            └─────────┘ └─────────┘ └─────────┘ └─────────┘
                    │      │      │      │
                    ▼      ▼      ▼      ▼
            ┌─────────┐ ┌─────────┐ ┌─────────┐ ┌─────────┐
            │ PIPE 0  │ │ PIPE 1  │ │ PIPE 2  │ │ PIPE 3  │
            │ [0] [1] │ │ [0] [1] │ │ [0] [1] │ │ [0] [1] │
            └─────────┘ └─────────┘ └─────────┘ └─────────┘
                    │      │      │      │
                    ▼      ▼      ▼      ▼
            ┌─────────────────────────────────────────────┐
            │           PARENT PROCESS                    │
            │  - Close write ends                        │
            │  - Read results from each pipe             │
            │  - wait() for all children                 │
            │  - Display formatted output                 │
            └─────────────────────────────────────────────┘
```

## IPC Communication Flow

### 1. Pipe Creation
```c
int pipes[4][2];
for (int i = 0; i < num_children; i++) {
    pipe(pipes[i]);  // Creates pipe[i][0] (read) and pipe[i][1] (write)
}
```

### 2. Child Process Communication
```c
// Child closes read end, keeps write end
close(pipes[child_id][0]);

// Child writes Result struct
Result result = {
    .task_name = "Count primes (<= 300k)",
    .result = 25997.0,
    .time_seconds = 0.123,
    .status = 0
};
write(pipes[child_id][1], &result, sizeof(result));
```

### 3. Parent Process Communication
```c
// Parent closes write ends, keeps read ends
for (int i = 0; i < num_children; i++) {
    close(pipes[i][1]);
}

// Parent reads from each pipe
for (int i = 0; i < num_children; i++) {
    Result result;
    read(pipes[i][0], &result, sizeof(result));
    // Process and display result
}
```

## Result Structure

```c
typedef struct {
    char task_name[64];    // Task description
    double result;         // Computed result
    double time_seconds;   // Execution time
    int status;           // Success/error status
} Result;
```

## Process Synchronization

### Fork Sequence
1. **Parent**: Creates pipes for all children
2. **Parent**: Calls `fork()` in loop to create children
3. **Children**: Execute their assigned tasks
4. **Children**: Write results to pipes and exit
5. **Parent**: Reads results from all pipes
6. **Parent**: Calls `wait()` to synchronize with all children

### Timing
- **Child Timing**: Each child measures its own execution time using `CLOCK_MONOTONIC`
- **Parent Timing**: Parent measures total wall-clock time from start to finish
- **Performance**: Wall-clock time ≈ max(child_times) + fork/IPC overhead

## Key Design Decisions

### 1. One Pipe Per Child
- **Advantage**: No interleaving of results
- **Advantage**: Simple synchronization
- **Trade-off**: More file descriptors

### 2. Struct-Based Communication
- **Advantage**: Type-safe data transfer
- **Advantage**: Single read/write operation
- **Advantage**: Includes timing and status information

### 3. Parent-Only Output
- **Advantage**: Clean, formatted output
- **Advantage**: No race conditions in printing
- **Requirement**: Meets assignment specification

### 4. Error Handling
- **Pipe Creation**: Check for pipe() failure
- **Fork**: Check for fork() failure
- **IPC**: Check read/write return values
- **Timing**: Check clock_gettime() success

## Expected Output Format

```
[parent] Starting Parallel Forking with 4 child(ren)
[parent] All children finished. Results:
  child #0 | task: Count primes (<= 300k)      | result: 25997.000000 | time: 0.123 s | status: 0
  child #1 | task: Leibniz pi (~30M iters)     | result: 3.141593     | time: 0.456 s | status: 0
  child #2 | task: Matmul sum (N=140)          | result: 1960000.000  | time: 0.789 s | status: 0
  child #3 | task: Integrate sin [0,pi] (60M)  | result: 2.000000     | time: 0.234 s | status: 0
[parent] Wall-clock elapsed: 0.791 s
```

---

*This diagram illustrates the complete process flow and IPC communication pattern used in the Parallel Forking assignment.*
