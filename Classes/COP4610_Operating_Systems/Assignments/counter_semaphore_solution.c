/*
 * COP4610 Operating Systems - Multithreading Assignment
 * Semaphore Solution to Race Condition
 * 
 * This program fixes the race condition using semaphores.
 * A semaphore with value 1 acts like a mutex, allowing only one thread
 * to access the critical section at a time.
 * 
 * Compile: gcc -pthread -o counter_semaphore_solution counter_semaphore_solution.c
 * Run: ./counter_semaphore_solution
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Global shared variable
int counter = 0;

// Semaphore declaration
sem_t counter_sem;

// Number of threads and iterations
#define NUM_THREADS 5
#define ITERATIONS 100000

// Function that each thread will execute
void* increment_counter(void* arg) {
    int thread_id = *(int*)arg;
    
    printf("Thread %d starting...\n", thread_id);
    
    for (int i = 0; i < ITERATIONS; i++) {
        // Wait (decrement) the semaphore
        sem_wait(&counter_sem);
        
        // Critical section - now protected by semaphore
        counter++;  // This is now atomic from the thread's perspective
        
        // Signal (increment) the semaphore
        sem_post(&counter_sem);
    }
    
    printf("Thread %d finished. Final counter value: %d\n", thread_id, counter);
    return NULL;
}

int main() {
    printf("=== Semaphore Solution to Race Condition ===\n");
    printf("COP4610 Operating Systems Assignment\n\n");
    
    // Initialize the semaphore with a value of 1 (acts like a mutex)
    sem_init(&counter_sem, 0, 1);
    
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    printf("Starting %d threads, each incrementing counter %d times...\n", 
           NUM_THREADS, ITERATIONS);
    printf("Expected final value: %d\n", NUM_THREADS * ITERATIONS);
    printf("Using semaphore to prevent race condition!\n\n");
    
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
        printf("SUCCESS! Semaphore prevented race condition. Counter is correct!\n");
    } else {
        printf("ERROR! Something went wrong.\n");
    }
    
    // Clean up semaphore
    sem_destroy(&counter_sem);
    
    return 0;
}
