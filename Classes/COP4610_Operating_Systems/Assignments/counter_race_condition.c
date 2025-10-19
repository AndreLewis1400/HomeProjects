/*
 * COP4610 Operating Systems - Multithreading Assignment
 * Race Condition Example
 * 
 * This program demonstrates a race condition in a multithreaded counter.
 * Multiple threads increment a shared counter variable without synchronization.
 * 
 * Compile: gcc -pthread -o counter_race_condition counter_race_condition.c
 * Run: ./counter_race_condition
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Global shared variable
int counter = 0;

// Number of threads and iterations
#define NUM_THREADS 5
#define ITERATIONS 100000

// Function that each thread will execute
void* increment_counter(void* arg) {
    int thread_id = *(int*)arg;
    
    printf("Thread %d starting...\n", thread_id);
    
    for (int i = 0; i < ITERATIONS; i++) {
        // This is the critical section - RACE CONDITION HERE!
        counter++;  // Read, modify, write operation - not atomic!
    }
    
    printf("Thread %d finished. Final counter value: %d\n", thread_id, counter);
    return NULL;
}

int main() {
    printf("=== Race Condition Demonstration ===\n");
    printf("COP4610 Operating Systems Assignment\n\n");
    
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    printf("Starting %d threads, each incrementing counter %d times...\n", 
           NUM_THREADS, ITERATIONS);
    printf("Expected final value: %d\n", NUM_THREADS * ITERATIONS);
    printf("Actual result will likely be less due to race condition!\n\n");
    
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
        printf("Lucky! No race condition occurred this time.\n");
    } else {
        printf("Race condition detected! Counter is incorrect.\n");
    }
    
    return 0;
}
