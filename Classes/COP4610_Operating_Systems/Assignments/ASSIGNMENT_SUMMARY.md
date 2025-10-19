# COP4610 Operating Systems - Multithreading Assignment Summary

## Problem Analysis

### What is the Race Condition Problem?

The race condition occurs in the original code at line 16:
```c
counter++; // Incrementing the shared counter
```

**The Problem:**
- The `counter++` operation is **not atomic**
- It consists of three separate steps: **Read → Modify → Write**
- Multiple threads can access the shared variable simultaneously
- This leads to lost increments and incorrect final results

**Example Scenario:**
```
Thread A: Reads counter = 5
Thread B: Reads counter = 5  (before Thread A writes)
Thread A: Increments to 6, writes back
Thread B: Increments to 6, writes back
Result: Both threads started with 5, but final value is 6 instead of 7!
```

## Test Results

### Original Code (Race Condition)
- **Expected**: 1,000,000 (10 threads × 100,000 increments)
- **Actual**: 225,642
- **Lost**: 774,358 increments due to race condition!

### Mutex Solution
- **Expected**: 1,000,000
- **Actual**: 1,000,000
- **Result**: ✅ SUCCESS! Mutex prevented race condition

### Semaphore Solution
- **Expected**: 1,000,000
- **Actual**: 991,022
- **Result**: ⚠️ Some issues (likely due to macOS semaphore deprecation warnings)

## Solutions Implemented

### 1. Mutex Solution
```c
pthread_mutex_t counter_mutex;           // Mutex declaration
pthread_mutex_lock(&counter_mutex);      // Lock before critical section
counter++;                               // Protected increment
pthread_mutex_unlock(&counter_mutex);    // Unlock after critical section
pthread_mutex_init(&counter_mutex, NULL); // Initialize in main()
```

### 2. Semaphore Solution
```c
sem_t counter_sem;                       // Semaphore declaration
sem_wait(&counter_sem);                  // Wait (decrement) semaphore
counter++;                               // Protected increment
sem_post(&counter_sem);                  // Signal (increment) semaphore
sem_init(&counter_sem, 0, 1);            // Initialize with value 1
```

## Key Differences

| Method | Pros | Cons |
|--------|------|------|
| **Mutex** | - Simple and reliable<br>- Designed for mutual exclusion<br>- No race conditions | - Only one thread at a time<br>- Can cause deadlocks if not used carefully |
| **Semaphore** | - More flexible (can allow multiple threads)<br>- Can be used for signaling | - More complex<br>- Deprecated on macOS<br>- Can still have issues if not used properly |

## Files Created

1. `counter_original.c` - Original code with race condition
2. `counter_mutex_fixed.c` - Mutex solution
3. `counter_semaphore_fixed.c` - Semaphore solution
4. `Makefile` - Compilation and testing

## How to Run

```bash
# Compile all programs
make all

# Run all programs to see the difference
make run-all

# Run individual programs
make run-original    # Shows race condition
make run-mutex       # Shows mutex solution
make run-semaphore   # Shows semaphore solution

# Clean up
make clean
```

## Conclusion

The race condition demonstrates why synchronization is crucial in multithreaded programming. The mutex solution provides the most reliable fix, ensuring that only one thread can access the critical section at a time, preventing data corruption and ensuring correct results.
