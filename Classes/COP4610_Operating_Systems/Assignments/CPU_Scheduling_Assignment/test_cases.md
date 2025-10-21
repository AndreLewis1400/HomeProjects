# CPU Scheduling Test Cases
## COP4610 Operating Systems Assignment

### Test Case 1: Basic Example
**Input:**
```
Number of processes: 4
P1: Arrival=0, Burst=8
P2: Arrival=1, Burst=4  
P3: Arrival=2, Burst=9
P4: Arrival=3, Burst=5
Time quantum: 2
```

**Expected FCFS Results:**
- P1: Completion=8, Turnaround=8, Waiting=0, Response=0
- P2: Completion=12, Turnaround=11, Waiting=7, Response=7
- P3: Completion=21, Turnaround=19, Waiting=10, Response=10
- P4: Completion=26, Turnaround=23, Waiting=18, Response=18

**Expected SJF Results:**
- P1: Completion=8, Turnaround=8, Waiting=0, Response=0
- P2: Completion=12, Turnaround=11, Waiting=7, Response=7
- P4: Completion=17, Turnaround=14, Waiting=9, Response=9
- P3: Completion=26, Turnaround=24, Waiting=15, Response=15

### Test Case 2: Same Arrival Time
**Input:**
```
Number of processes: 3
P1: Arrival=0, Burst=5
P2: Arrival=0, Burst=3
P3: Arrival=0, Burst=8
Time quantum: 2
```

**Expected FCFS Results:**
- P1: Completion=5, Turnaround=5, Waiting=0, Response=0
- P2: Completion=8, Turnaround=8, Waiting=5, Response=5
- P3: Completion=16, Turnaround=16, Waiting=8, Response=8

**Expected SJF Results:**
- P2: Completion=3, Turnaround=3, Waiting=0, Response=0
- P1: Completion=8, Turnaround=8, Waiting=3, Response=3
- P3: Completion=16, Turnaround=16, Waiting=8, Response=8

### Test Case 3: Different Arrival Times
**Input:**
```
Number of processes: 5
P1: Arrival=0, Burst=3
P2: Arrival=2, Burst=6
P3: Arrival=4, Burst=4
P4: Arrival=6, Burst=5
P5: Arrival=8, Burst=2
Time quantum: 2
```

### Test Case 4: Single Process
**Input:**
```
Number of processes: 1
P1: Arrival=0, Burst=10
Time quantum: 3
```

**Expected Results (all algorithms):**
- P1: Completion=10, Turnaround=10, Waiting=0, Response=0

### Test Case 5: Long vs Short Jobs
**Input:**
```
Number of processes: 4
P1: Arrival=0, Burst=1
P2: Arrival=0, Burst=10
P3: Arrival=0, Burst=1
P4: Arrival=0, Burst=10
Time quantum: 1
```

**Analysis:**
- FCFS: P1→P2→P3→P4 (convoy effect)
- SJF: P1→P3→P2→P4 (optimal for short jobs)
- Round Robin: Alternates between all processes

### Test Case 6: Edge Case - No Processes
**Input:**
```
Number of processes: 0
```

**Expected:** Program should handle gracefully

### Test Case 7: Large Time Quantum
**Input:**
```
Number of processes: 3
P1: Arrival=0, Burst=5
P2: Arrival=1, Burst=3
P3: Arrival=2, Burst=4
Time quantum: 10
```

**Expected:** Round Robin behaves like FCFS

### Test Case 8: Small Time Quantum
**Input:**
```
Number of processes: 3
P1: Arrival=0, Burst=5
P2: Arrival=1, Burst=3
P3: Arrival=2, Burst=4
Time quantum: 1
```

**Expected:** Round Robin provides good response times

### Performance Analysis

#### Algorithm Comparison:
1. **FCFS**: Simple, fair, but can have high waiting times
2. **SJF**: Optimal average waiting time, but requires future knowledge
3. **Round Robin**: Good response times, fair scheduling

#### Metrics to Compare:
- Average Waiting Time
- Average Turnaround Time  
- Average Response Time
- Throughput (processes completed per unit time)

#### When to Use Each:
- **FCFS**: Batch systems, simple implementation
- **SJF**: When burst times are known, batch systems
- **Round Robin**: Time-sharing systems, interactive applications

### Testing Instructions

1. **Compile the program:**
   ```bash
   gcc -o cpu_scheduling cpu_scheduling.c
   ```

2. **Run each test case:**
   ```bash
   ./cpu_scheduling
   ```

3. **Verify results match expected values**

4. **Check edge cases:**
   - Single process
   - No processes
   - Same arrival times
   - Very large/small time quantum

5. **Performance analysis:**
   - Compare average metrics
   - Identify which algorithm performs best for each scenario
   - Explain trade-offs

### Common Issues to Check

1. **Array bounds**: Ensure no segmentation faults
2. **Queue management**: Round Robin queue operations
3. **Time calculations**: Verify all metrics are correct
4. **Edge cases**: Handle empty queues, single processes
5. **Memory management**: No memory leaks

### Expected Output Format

```
=== CPU Scheduling Algorithms Comparison ===
COP4610 Operating Systems Assignment

Enter number of processes (max 10): 4

Enter process details:

Process 1:
  Name: P1
  Arrival Time: 0
  Burst Time: 8

Process 2:
  Name: P2
  Arrival Time: 1
  Burst Time: 4

Process 3:
  Name: P3
  Arrival Time: 2
  Burst Time: 9

Process 4:
  Name: P4
  Arrival Time: 3
  Burst Time: 5

=== Simulation Results ===

1. FCFS (First-Come, First-Served) Scheduling:

FCFS Results:
Process Arrival Burst Completion Turnaround Waiting Response
------- ------- ----- ---------- ---------- ------- --------
P1      0       8     8          8          0       0
P2      1       4     12         11         7       7
P3      2       9     21         19         10      10
P4      3       5     26         23         18      18

Average Waiting Time: 8.75
Average Turnaround Time: 15.25
Average Response Time: 8.75
```
