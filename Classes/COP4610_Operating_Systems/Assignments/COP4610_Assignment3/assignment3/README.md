# Programming Assignment 3: Critical Section Problem Solution

## Overview
This program implements a solution to the critical section problem using pthreads and mutex synchronization for concurrent banking operations.

## Implementation Details

### Threading (8 points)
- Uses `pthread_create()` to create two threads (deposit and withdrawal)
- Uses `pthread_join()` to wait for thread completion
- Proper thread lifecycle management

### Deposit Logic (10 points)
- Thread A performs up to 2,000,000 deposit operations
- Each deposit adds $1 to account balance
- Bonus tracking: Every 1000th deposit awards a $10 bonus
- Accurate bonus counting and reporting

### Withdrawal Logic (10 points)
- Thread B performs exactly 2,000,000 withdrawal operations
- Each withdrawal removes $1 from account balance
- Only withdraws when account balance > 0

### Synchronization (10 points)
- Uses `pthread_mutex_t` for synchronization
- Mutex protects shared variables: `account_balance`, `bonus_count`, `deposit_count`, `withdrawal_count`

### Critical Section Structure (10 points)
- Clear separation of entry, critical, exit, and remainder sections
- Only one update per critical section entry
- Proper mutex locking/unlocking

### Bonus Tracking (5 points)
- Accurately counts bonuses awarded
- Reports total bonus count in final output

## Critical Section Properties

### Mutual Exclusion
- Only one thread can access shared data at a time
- Mutex ensures atomic access to critical section

### Progress
- Threads not in critical section don't prevent others from entering
- No deadlock conditions

### Bounded Waiting
- Threads will eventually get access to critical section
- No indefinite waiting due to mutex fairness

## Compilation and Execution

```bash
make
./banking_system
```

## Expected Output
- Initial and final account balance
- Total deposits and withdrawals performed
- Total bonuses awarded
- Thread completion messages
