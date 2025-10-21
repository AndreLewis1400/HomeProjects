#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 10
#define INCREMENTS_PER_THREAD 100000

int counter = 0; // Shared counter
pthread_mutex_t counter_mutex; // Mutex declaration 

void* increment_counter(void* threadid) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        // Lock the mutex before accessing the counter
        pthread_mutex_lock(&counter_mutex);
        
        counter++; // Incrementing the shared counter - now protected!
        
        // Unlock the mutex after updating
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Initialize the mutex
    pthread_mutex_init(&counter_mutex, NULL);

    printf("=== Mutex Solution to Race Condition ===\n");
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
        printf("SUCCESS! Mutex prevented race condition.\n");
    } else {
        printf("ERROR! Counter is incorrect.\n");
    }
    
    // Clean up mutex
    pthread_mutex_destroy(&counter_mutex);
    
    return 0;
}
