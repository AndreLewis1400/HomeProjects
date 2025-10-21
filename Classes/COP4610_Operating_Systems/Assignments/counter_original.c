#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_THREADS 10
#define INCREMENTS_PER_THREAD 100000

int counter = 0; // Shared counter
pthread_mutex_t counter_mutex; // Mutex declaration 
sem_t counter_sem; // Semaphore declaration 

void* increment_counter(void* threadid) {
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
        counter++; // Incrementing the shared counter
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create multiple threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", counter); // Print the final counter value
    return 0;
}
