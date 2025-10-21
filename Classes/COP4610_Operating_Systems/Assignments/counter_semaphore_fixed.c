#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 10
#define INCREMENTS_PER_THREAD 100000

int counter = 0; // Shared counter
sem_t counter_sem; // Semaphore declaration 

void* increment_counter(void* threadid) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        // Wait (decrement) the semaphore
        sem_wait(&counter_sem);
        
        counter++; // Incrementing the shared counter - now protected!
        
        // Signal (increment) the semaphore
        sem_post(&counter_sem);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the semaphore with a value of 1 (acts like a mutex)
    sem_init(&counter_sem, 0, 1);

    printf("=== Semaphore Solution to Race Condition ===\n");
    printf("Expected final value: %d\n", NUM_THREADS * INCREMENTS_PER_THREAD);

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", counter); // Print the final counter value
    
    if (counter == NUM_THREADS * INCREMENTS_PER_THREAD) {
        printf("SUCCESS! Semaphore prevented race condition.\n");
    } else {
        printf("ERROR! Counter is incorrect.\n");
    }
    
    // Clean up semaphore
    sem_destroy(&counter_sem);
    
    return 0;
}
