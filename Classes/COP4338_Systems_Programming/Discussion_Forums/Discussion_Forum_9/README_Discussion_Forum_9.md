# Discussion Forum 9: Multithreading - Race Conditions and Mutexes

This directory contains the implementation for Discussion Forum 9, demonstrating race conditions in multithreaded programs and how mutexes solve them.

## Assignment Overview

The program simulates a bank account with concurrent deposit and withdraw operations using pthreads. The goal is to demonstrate:
1. **Race conditions** when multiple threads access shared data without synchronization
2. **Mutex solutions** to prevent data corruption
3. **The importance of thread synchronization** in concurrent programming

## Files

- `bank.c` - Original version with race conditions
- `main_fixed.c` - Fixed version with mutex locks
- `Makefile_multithreading` - Compilation rules
- `test_race_conditions.sh` - Test script for experiments

## Program Logic

### Initial Balance: $10,000

Each thread pair (deposit + withdraw) should result in **no net change**:
- **Deposit thread**: Adds $100 × 100 times = +$10,000
- **Withdraw thread**: Subtracts $100 × 100 times = -$10,000
- **Net result**: +$10,000 - $10,000 = $0 change

### Expected Final Balance: $10,000

## Race Condition Problem

### Original Version (`bank.c`)
```c
void* deposit(void* arg) {
    for(int i = 0; i < 100; i++)
        balance += (int)arg;  // Race condition here!
}

void* withdraw(void* arg) {
    for(int i = 0; i < 100; i++)
        balance -= (int)arg;  // Race condition here!
}
```

**Problem**: Multiple threads can read and write `balance` simultaneously, leading to:
- Lost updates
- Inconsistent final balance
- Data corruption

### Fixed Version (`main_fixed.c`)
```c
void* deposit(void* arg) {
    for(int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);   // Lock before access
        balance += (int)arg;
        pthread_mutex_unlock(&mutex); // Unlock after access
    }
}

void* withdraw(void* arg) {
    for(int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);   // Lock before access
        balance -= (int)arg;
        pthread_mutex_unlock(&mutex); // Unlock after access
    }
}
```

**Solution**: Mutex locks ensure only one thread can access `balance` at a time.

## Compilation

```bash
make -f Makefile_multithreading
```

This creates:
- `bank` - Original version with race conditions
- `bank_fixed` - Fixed version with mutex locks

## Testing

### Quick Test
```bash
# Test race condition (may show different results)
for i in {1..3}; do echo "Run $i:"; ./bank 100; done

# Test fixed version (should always show 10000)
for i in {1..3}; do echo "Run $i:"; ./bank_fixed 100; done
```

### Full Experiment
```bash
./test_race_conditions.sh
```

This runs the complete experiment as specified in the assignment:
1. `./bank` (default) - 5 times
2. `./bank 100` - 5 times  
3. `./bank 1000` - 5 times
4. `./bank 10000` - 5 times
5. Same tests with `./bank_fixed`

## Expected Results

### Race Condition Version (`bank`)
- **Inconsistent results**: Final balance may vary
- **Corrupted data**: Balance ≠ $10,000
- **Higher thread counts**: More corruption likely

### Fixed Version (`bank_fixed`)
- **Consistent results**: Final balance always $10,000
- **No corruption**: Proper synchronization
- **Thread-safe**: Works with any number of threads

## Key Learning Points

1. **Race Conditions**: When multiple threads access shared data simultaneously
2. **Critical Sections**: Code sections that must be executed atomically
3. **Mutex Locks**: Synchronization primitives to protect shared resources
4. **Thread Safety**: Ensuring programs work correctly with concurrent execution
5. **Debugging Concurrent Code**: Race conditions can be intermittent and hard to reproduce

## Common Race Condition Scenarios

1. **Read-Modify-Write**: `balance += 100` is not atomic
2. **Lost Updates**: Two threads read the same value, modify it, and write back
3. **Inconsistent State**: Partial updates visible to other threads

## Best Practices

1. **Identify shared resources**: Variables accessed by multiple threads
2. **Use appropriate synchronization**: Mutexes, semaphores, or other primitives
3. **Minimize critical sections**: Keep locked code as short as possible
4. **Test thoroughly**: Race conditions can be intermittent
5. **Document thread safety**: Clearly indicate which functions are thread-safe

## Assignment Requirements

1. ✅ **Compile with pthread**: `gcc -o bank bank.c -pthread -w`
2. ✅ **Run experiments**: Test with different thread counts
3. ✅ **Record results**: Document corrupted vs. correct balances
4. ✅ **Implement mutex solution**: Add locks to prevent race conditions
5. ✅ **Compare results**: Show before/after with mutex locks
6. ✅ **Share findings**: Discuss with classmates

This implementation demonstrates the fundamental concepts of multithreading, race conditions, and synchronization in systems programming. 