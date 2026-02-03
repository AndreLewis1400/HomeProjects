# CPU Scheduling Algorithms Assignment
## COP4610 Operating Systems - FIU

### Assignment Overview
This assignment implements and compares three CPU scheduling algorithms:
1. **FCFS (First-Come, First-Served)**
2. **SJF (Shortest Job First)**
3. **Round Robin**

### Files
- `cpu_scheduling.c` - Main implementation file
- `Makefile` - Build configuration
- `README.md` - This documentation
- `test_cases.md` - Sample test cases

### Compilation and Execution

#### On Ocelot:
```bash
# Compile the program
gcc -Wall -Wextra -std=c99 -O2 -o cpu_scheduling cpu_scheduling.c

# Or use the Makefile
make

# Run the program
./cpu_scheduling
```

#### Alternative compilation:
```bash
# Simple compilation
gcc -o cpu_scheduling cpu_scheduling.c

# With debugging
gcc -g -o cpu_scheduling cpu_scheduling.c
```

### Program Features

#### Input
- Number of processes (maximum 10)
- For each process:
  - Process name
  - Arrival time
  - Burst time
- Time quantum for Round Robin

#### Output
- Detailed results for each algorithm showing:
  - Process execution order
  - Completion time
  - Turnaround time
  - Waiting time
  - Response time
- Average metrics for comparison

### Algorithm Implementations

#### 1. FCFS (First-Come, First-Served)
- Processes are executed in order of arrival
- No preemption
- Simple but can cause convoy effect

#### 2. SJF (Shortest Job First)
- Always executes the shortest available job
- Non-preemptive version implemented
- Optimal for minimizing average waiting time

#### 3. Round Robin
- Each process gets equal time slice (quantum)
- Preemptive scheduling
- Good for time-sharing systems

### Sample Test Case

#### Input:
```
Number of processes: 4
Process 1: P1, Arrival: 0, Burst: 8
Process 2: P2, Arrival: 1, Burst: 4
Process 3: P3, Arrival: 2, Burst: 9
Process 4: P4, Arrival: 3, Burst: 5
Time quantum: 2
```

#### Expected Results:
- **FCFS**: P1 → P2 → P3 → P4
- **SJF**: P1 → P2 → P4 → P3 (when P1 arrives, it's the only one)
- **Round Robin**: P1(2) → P2(2) → P3(2) → P4(2) → P1(2) → P2(2) → P4(2) → P1(2) → P1(2) → P3(2) → P3(2) → P3(2) → P3(2) → P3(1)

### Performance Metrics

#### Waiting Time
- Time a process waits in ready queue
- Waiting Time = Turnaround Time - Burst Time

#### Turnaround Time
- Total time from arrival to completion
- Turnaround Time = Completion Time - Arrival Time

#### Response Time
- Time from arrival to first execution
- Important for interactive systems

### Assignment Requirements

#### Code Requirements:
- Implement all three algorithms
- Calculate performance metrics
- Compare algorithm performance
- Handle edge cases (no processes, single process)
- Clear, commented code

#### Deliverables:
- Working C program that compiles on Ocelot
- Video explanation of code
- Resources used during development
- Performance analysis and reflection
- Peer feedback

### Testing on Ocelot

#### Before Submission:
1. **Compile test**: `gcc -o cpu_scheduling cpu_scheduling.c`
2. **Run test**: `./cpu_scheduling`
3. **Verify output**: Check all three algorithms produce results
4. **Edge case test**: Try with 1 process, 0 processes
5. **Performance test**: Use provided test cases

#### Common Issues:
- **Segmentation fault**: Check array bounds and null pointers
- **Infinite loop**: Verify Round Robin queue management
- **Wrong results**: Check algorithm logic and time calculations

### Code Structure

```c
// Process structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int first_execution;
} Process;

// Main functions
void fcfs_scheduling();           // FCFS implementation
void sjf_scheduling();            // SJF implementation  
void round_robin_scheduling();    // Round Robin implementation
void calculate_metrics();         // Performance calculations
void print_results();             // Output formatting
```

### Performance Analysis

#### Expected Results:
- **FCFS**: Simple but may have high waiting times
- **SJF**: Optimal average waiting time but requires burst time knowledge
- **Round Robin**: Fair scheduling, good response times

#### Trade-offs:
- **FCFS**: Simple but poor performance with varying burst times
- **SJF**: Optimal but not practical (requires future knowledge)
- **Round Robin**: Good balance of fairness and performance

### Submission Checklist

- [ ] Code compiles without warnings on Ocelot
- [ ] All three algorithms implemented correctly
- [ ] Performance metrics calculated accurately
- [ ] Code is well-commented and documented
- [ ] Test cases produce expected results
- [ ] Video explanation recorded
- [ ] Resources documented
- [ ] Performance analysis completed
- [ ] Peer feedback provided

### Resources Used

- Operating System Concepts (Silberschatz)
- CPU Scheduling Algorithms lecture notes
- FIU COP4610 course materials
- C programming reference

### Author
Andre Lewis - COP4610 Operating Systems
