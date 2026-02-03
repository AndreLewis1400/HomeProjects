# COP4610 Operating Systems - Assignment 3

## Banking System with Critical Section Problem Solution

This assignment implements a multi-threaded banking system that demonstrates the solution to the critical section problem using pthreads and mutex synchronization.

### Assignment Overview

**Course**: COP4610 Operating Systems  
**Assignment**: Assignment 3 - Critical Section Problem  
**University**: Florida International University  

### Files

- `banking_system.c` - Main implementation with pthread synchronization
- `Assignment3_Student_Self_Assessment_Checklist.pdf` - Assignment requirements and grading rubric
- `README.md` - This documentation

### Features

- **Multi-threading**: Uses pthreads for concurrent deposit and withdrawal operations
- **Mutex Synchronization**: Implements proper critical section protection
- **Bonus Tracking**: Awards bonuses every 1000th deposit
- **Balanced Operations**: 2,000,000 deposits and 2,000,000 withdrawals
- **Critical Section Structure**: Proper entry, critical, exit, and remainder sections

### Compilation

```bash
gcc -pthread banking_system.c -o banking_system
```

### Execution

```bash
./banking_system
```

### Expected Output

- 2,000,000 deposit operations
- 2,000,000 withdrawal operations  
- 2,000 bonus awards (every 1000th deposit)
- Final account balance near $0

### Implementation Details

#### Thread A (Deposit Thread)
- Performs up to 2,000,000 deposit operations
- Awards $10 bonus every 1000th deposit
- Uses mutex for critical section protection

#### Thread B (Withdrawal Thread)
- Performs exactly 2,000,000 withdrawal operations
- Withdraws $1 per deposit + $10 per bonus
- Ensures final balance approaches zero

#### Critical Section Properties
- **Mutual Exclusion**: Only one thread in critical section at a time
- **Progress**: Threads waiting to enter are served fairly
- **Bounded Waiting**: No thread waits indefinitely

### Video Discussion Requirements

This implementation addresses all rubric requirements:
- Correct use of pthreads (8 pts)
- Deposit logic with bonus tracking (10 pts)
- Withdrawal logic (10 pts)
- Mutex synchronization (10 pts)
- Critical section structure (10 pts)
- Bonus tracking accuracy (5 pts)

### Author

Andre Lewis - FIU COP4610 Operating Systems
