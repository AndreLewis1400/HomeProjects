#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

// Global arrays to track unique processes and threads
int unique_processes[10] = {0};
int unique_threads[10] = {0};
int process_index = 0;
int thread_index = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_function(void* arg __attribute__((unused))) {
    pthread_mutex_lock(&mutex);
    unique_threads[thread_index++] = getpid();
    printf("THREAD CREATED in process %d\n", getpid());
    pthread_mutex_unlock(&mutex);
    sleep(1);
    return NULL;
}

int main() {
    printf("=== PRECISE ANALYSIS ===\n");
    printf("Original process PID: %d\n", getpid());
    unique_processes[process_index++] = getpid();
    
    pid_t pid;
    
    // First fork
    printf("\n1. FIRST FORK()\n");
    pid = fork();
    
    if (pid == 0) { 
        // CHILD PROCESS
        printf("Child process %d created\n", getpid());
        unique_processes[process_index++] = getpid();
        
        // Second fork (only in child)
        printf("\n2. SECOND FORK()\n");
        pid_t pid2 = fork();
        
        if (pid2 == 0) {
            // GRANDCHILD PROCESS
            printf("Grandchild process %d created\n", getpid());
            unique_processes[process_index++] = getpid();
            
            // Thread creation in grandchild
            printf("\n3. THREAD_CREATE() in grandchild\n");
            pthread_t thread;
            if (pthread_create(&thread, NULL, thread_function, NULL) == 0) {
                pthread_join(thread, NULL);
            }
            
        } else {
            // CHILD CONTINUES
            printf("Child process %d continues\n", getpid());
            
            // Thread creation in child
            printf("\n3. THREAD_CREATE() in child\n");
            pthread_t thread;
            if (pthread_create(&thread, NULL, thread_function, NULL) == 0) {
                pthread_join(thread, NULL);
            }
        }
        
    } else {
        // PARENT PROCESS
        printf("Parent process %d continues\n", getpid());
    }
    
    // Third fork (ALL processes execute this)
    printf("\n4. THIRD FORK()\n");
    pid_t pid3 = fork();
    
    if (pid3 == 0) {
        printf("New child process %d created by third fork\n", getpid());
        unique_processes[process_index++] = getpid();
    } else {
        printf("Process %d continues after third fork\n", getpid());
    }
    
    // Wait for all child processes
    int status;
    while (wait(&status) > 0);
    
    // Print summary (only from original process)
    if (getpid() == unique_processes[0]) {
        printf("\n=== FINAL SUMMARY ===\n");
        printf("Unique Processes:\n");
        for (int i = 0; i < process_index; i++) {
            printf("  %d. PID %d\n", i+1, unique_processes[i]);
        }
        printf("Total unique processes: %d\n", process_index);
        printf("Total unique threads: %d\n", thread_index);
    }
    
    return 0;
}
