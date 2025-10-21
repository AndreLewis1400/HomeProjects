/*
 * COP4610 Operating Systems - Multithreading Assignment
 * Mutex Solution to Race Condition
 * 
 * This program fixes the race condition using pthread mutex locks.
 * Only one thread can access the critical section at a time.
 * 
 * Compile: gcc -pthread -o counter_mutex_solution counter_mutex_solution.c
 * Run: ./counter_mutex_solution
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Global shared variable
int counter = 0;

// Mutex declaration
pthread_mutex_t counter_mutex;

// Number of threads and iterations
#define NUM_THREADS 5
#define ITERATIONS 100000

// Function that each thread will execute
void* increment_counter(void* arg) {
    int thread_id = *(int*)arg;
    
    printf("Thread %d starting...\n", thread_id);
    
    for (int i = 0; i < ITERATIONS; i++) {
        // Lock the mutex before accessing the counter
        pthread_mutex_lock(&counter_mutex);
        
        // Critical section - now protected by mutex
        counter++;  // This is now atomic from the thread's perspective
        
        // Unlock the mutex after updating
        pthread_mutex_unlock(&counter_mutex);
    }
    
    printf("Thread %d finished. Final counter value: %d\n", thread_id, counter);
    return NULL;
}

int main() {
    printf("=== Mutex Solution to Race Condition ===\n");
    printf("COP4610 Operating Systems Assignment\n\n");
    
    // Initialize the mutex
    pthread_mutex_init(&counter_mutex, NULL);
    
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    printf("Starting %d threads, each incrementing counter %d times...\n", 
           NUM_THREADS, ITERATIONS);
    printf("Expected final value: %d\n", NUM_THREADS * ITERATIONS);
    printf("Using mutex locks to prevent race condition!\n\n");
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }
    
    printf("\n=== Final Results ===\n");
    printf("Expected counter value: %d\n", NUM_THREADS * ITERATIONS);
    printf("Actual counter value: %d\n", counter);
    printf("Lost increments: %d\n", (NUM_THREADS * ITERATIONS) - counter);
    
    if (counter == NUM_THREADS * ITERATIONS) {
        printf("SUCCESS! Mutex prevented race condition. Counter is correct!\n");
    } else {
        printf("ERROR! Something went wrong.\n");
    }
    
    // Clean up mutex
    pthread_mutex_destroy(&counter_mutex);
    
    return 0;
}
