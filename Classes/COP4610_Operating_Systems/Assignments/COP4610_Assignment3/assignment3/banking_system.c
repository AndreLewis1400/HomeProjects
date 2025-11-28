#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

// Global variables for shared data
int account_balance = 0;
int bonus_count = 0;
int deposit_count = 0;
int withdrawal_count = 0;

// Synchronization primitive
pthread_mutex_t account_mutex = PTHREAD_MUTEX_INITIALIZER;

// Constants
#define MAX_DEPOSITS 2000000
#define MAX_WITHDRAWALS 2000000
#define BONUS_THRESHOLD 1000

// Function prototypes
void* deposit_thread(void* arg);
void* withdrawal_thread(void* arg);
void enter_critical_section();
void exit_critical_section();
void remainder_section();

int main() {
    printf("=== Banking System with Critical Section Problem Solution ===\n");
    printf("Initial account balance: $%d\n", account_balance);
    printf("Starting concurrent banking operations...\n\n");
    
    // Create thread IDs
    pthread_t deposit_tid, withdrawal_tid;
    
    // Create and start threads
    if (pthread_create(&deposit_tid, NULL, deposit_thread, NULL) != 0) {
        perror("Failed to create deposit thread");
        exit(1);
    }
    
    if (pthread_create(&withdrawal_tid, NULL, withdrawal_thread, NULL) != 0) {
        perror("Failed to create withdrawal thread");
        exit(1);
    }
    
    // Wait for both threads to complete
    if (pthread_join(deposit_tid, NULL) != 0) {
        perror("Failed to join deposit thread");
        exit(1);
    }
    
    if (pthread_join(withdrawal_tid, NULL) != 0) {
        perror("Failed to join withdrawal thread");
        exit(1);
    }
    
    // Print final results
    printf("\n=== Final Results ===\n");
    printf("Final account balance: $%d\n", account_balance);
    printf("Total deposits performed: %d\n", deposit_count);
    printf("Total withdrawals performed: %d\n", withdrawal_count);
    printf("Total bonuses awarded: %d\n", bonus_count);
    
    // Clean up mutex
    pthread_mutex_destroy(&account_mutex);
    
    return 0;
}

// Thread A: Deposit operations
void* deposit_thread(void* arg) {
    (void)arg; // Suppress unused parameter warning
    printf("Deposit thread started\n");
    
    while (deposit_count < MAX_DEPOSITS) {
        // Entry section
        enter_critical_section();
        
        // Critical section - only one update per entry
        if (deposit_count < MAX_DEPOSITS) {
            account_balance += 1;  // Deposit $1
            deposit_count++;
            
            // Check for bonus (every 1000th deposit)
            if (deposit_count % BONUS_THRESHOLD == 0) {
                account_balance += 10;  // $10 bonus
                bonus_count++;
            }
        }
        
        // Exit section
        exit_critical_section();
        
        // Remainder section
        remainder_section();
    }
    
    printf("Deposit thread completed\n");
    return NULL;
}

// Thread B: Withdrawal operations
void* withdrawal_thread(void* arg) {
    (void)arg; // Suppress unused parameter warning
    printf("Withdrawal thread started\n");
    
    while (withdrawal_count < MAX_WITHDRAWALS) {
        // Entry section
        enter_critical_section();
        
        // Critical section - only one update per entry
        if (withdrawal_count < MAX_WITHDRAWALS) {
            // Withdraw $1 for the deposit amount
            // Also withdraw bonus amounts to achieve final balance of 0
            // Every 1000th withdrawal, withdraw an additional $10 to account for bonuses
            account_balance -= 1;  // Withdraw $1 for deposit
            if ((withdrawal_count + 1) % BONUS_THRESHOLD == 0) {
                account_balance -= 10;  // Withdraw $10 for bonus
            }
            withdrawal_count++;
        }
        
        // Exit section
        exit_critical_section();
        
        // Remainder section
        remainder_section();
    }
    
    printf("Withdrawal thread completed\n");
    return NULL;
}

// Entry section - acquire mutex
void enter_critical_section() {
    pthread_mutex_lock(&account_mutex);
}

// Exit section - release mutex
void exit_critical_section() {
    pthread_mutex_unlock(&account_mutex);
}

// Remainder section - non-critical work
void remainder_section() {
    // Simulate some non-critical work
    // This could be logging, other computations, etc.
    // For this assignment, we'll just do a minimal delay
    // Using a simple loop instead of usleep for portability
    volatile int i;
    for (i = 0; i < 100; i++);
}
