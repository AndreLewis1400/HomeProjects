#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

int process_count = 0;
int thread_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_function(void* arg __attribute__((unused))) {
    pthread_mutex_lock(&mutex);
    thread_count++;
    printf("  -> Thread %d created in process %d\n", thread_count, getpid());
    pthread_mutex_unlock(&mutex);
    sleep(1);
    return NULL;
}

int main() {
    printf("=== DETAILED PROCESS TRACE ===\n");
    printf("Initial process PID: %d\n", getpid());
    process_count = 1;
    printf("Process count: %d\n\n", process_count);
    
    pid_t pid;
    
    // First fork
    printf("1. FIRST FORK() - Original process %d\n", getpid());
    pid = fork();
    
    if (pid == 0) { 
        // CHILD PROCESS
        printf("   -> Child process %d created\n", getpid());
        process_count++;
        printf("   -> Process count: %d\n", process_count);
        
        // Second fork (only in child)
        printf("2. SECOND FORK() - Child process %d\n", getpid());
        pid_t pid2 = fork();
        
        if (pid2 == 0) {
            // GRANDCHILD PROCESS
            printf("      -> Grandchild process %d created\n", getpid());
            process_count++;
            printf("      -> Process count: %d\n", process_count);
            
            // Thread creation in grandchild
            printf("3. THREAD_CREATE() - Grandchild process %d\n", getpid());
            pthread_t thread;
            if (pthread_create(&thread, NULL, thread_function, NULL) == 0) {
                pthread_join(thread, NULL);
            }
            
        } else {
            // CHILD CONTINUES
            printf("      -> Child process %d continues\n", getpid());
            
            // Thread creation in child
            printf("3. THREAD_CREATE() - Child process %d\n", getpid());
            pthread_t thread;
            if (pthread_create(&thread, NULL, thread_function, NULL) == 0) {
                pthread_join(thread, NULL);
            }
        }
        
    } else {
        // PARENT PROCESS
        printf("   -> Parent process %d continues\n", getpid());
    }
    
    // Third fork (ALL processes execute this)
    printf("4. THIRD FORK() - Process %d\n", getpid());
    pid_t pid3 = fork();
    
    if (pid3 == 0) {
        printf("   -> New child process %d created by third fork\n", getpid());
        process_count++;
        printf("   -> Process count: %d\n", process_count);
    } else {
        printf("   -> Process %d continues after third fork\n", getpid());
    }
    
    // Wait for all child processes
    int status;
    while (wait(&status) > 0);
    
    printf("\nProcess %d terminating (final count: %d processes, %d threads)\n", 
           getpid(), process_count, thread_count);
    return 0;
}
