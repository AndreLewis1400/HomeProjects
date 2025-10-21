#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

// Global counter for threads
int thread_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Thread function
void* thread_function(void* arg __attribute__((unused))) {
    pthread_mutex_lock(&mutex);
    thread_count++;
    printf("Thread %d created in process %d\n", thread_count, getpid());
    pthread_mutex_unlock(&mutex);
    
    // Keep thread alive for a moment
    sleep(1);
    return NULL;
}

int main() {
    printf("=== COP4610 Process Forking Analysis ===\n");
    printf("Initial process PID: %d\n", getpid());
    printf("\n");
    
    pid_t pid;
    
    // First fork
    printf("1. First fork() call\n");
    pid = fork();
    
    if (pid == 0) { /* child process */
        printf("Child process %d: Inside if block\n", getpid());
        
        // Second fork (only in child)
        printf("2. Second fork() call (child only)\n");
        pid_t pid2 = fork();
        
        if (pid2 == 0) {
            printf("Grandchild process %d created\n", getpid());
        } else {
            printf("Child process %d continues after second fork\n", getpid());
        }
        
        // Thread creation (only in child and grandchild)
        printf("3. thread_create() call\n");
        pthread_t thread;
        if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
            perror("pthread_create failed");
            exit(1);
        }
        
        // Wait for thread to complete
        pthread_join(thread, NULL);
        
    } else {
        printf("Parent process %d: Child created with PID %d\n", getpid(), pid);
    }
    
    // Third fork (executed by all processes)
    printf("4. Third fork() call (all processes)\n");
    pid_t pid3 = fork();
    
    if (pid3 == 0) {
        printf("New child process %d created by third fork\n", getpid());
    } else {
        printf("Process %d continues after third fork\n", getpid());
    }
    
    // Wait for all child processes
    int status;
    while (wait(&status) > 0);
    
    printf("\nProcess %d terminating\n", getpid());
    return 0;
}
