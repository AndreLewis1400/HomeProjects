/*
 * Complete Example: Parallel Processing with IPC
 * Demonstrates all concepts: fork, pipes, timing, error handling
 * 
 * Compile: gcc -o complete_example complete_example.c
 * Run: ./complete_example
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// Result structure for IPC
typedef struct {
    char task_name[32];
    int result;
    double time_seconds;
    int status;
} Result;

// Simple computational tasks
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n-1);
}

int sum_squares(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i * i;
    }
    return sum;
}

// Child task function
void child_task(int child_id, int write_fd) {
    Result result;
    struct timespec start, end;
    
    // Initialize result
    result.status = 0;
    
    // Start timing
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        perror("clock_gettime failed");
        result.status = -1;
        write(write_fd, &result, sizeof(result));
        exit(1);
    }
    
    // Perform task based on child ID
    switch (child_id) {
        case 0:
            strcpy(result.task_name, "Fibonacci(20)");
            result.result = fibonacci(20);
            break;
        case 1:
            strcpy(result.task_name, "Factorial(10)");
            result.result = factorial(10);
            break;
        case 2:
            strcpy(result.task_name, "Sum of squares(100)");
            result.result = sum_squares(100);
            break;
        default:
            strcpy(result.task_name, "Unknown task");
            result.result = -1;
            result.status = -1;
            break;
    }
    
    // End timing
    if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
        perror("clock_gettime failed");
        result.status = -1;
    } else {
        result.time_seconds = (end.tv_sec - start.tv_sec) + 
                             (end.tv_nsec - start.tv_nsec) / 1e9;
    }
    
    // Send result to parent
    if (write(write_fd, &result, sizeof(result)) != sizeof(result)) {
        perror("write failed");
        exit(1);
    }
    
    close(write_fd);
    exit(0);
}

int main() {
    printf("=== Complete Parallel Processing Example ===\n");
    
    const int num_children = 3;
    int pipes[num_children][2];
    
    // Create pipes
    for (int i = 0; i < num_children; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe failed");
            return 1;
        }
    }
    
    printf("Created %d pipes for communication\n", num_children);
    
    // Start timing
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Create child processes
    for (int i = 0; i < num_children; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("fork failed");
            return 1;
        }
        else if (pid == 0) {
            // Child process
            child_task(i, pipes[i][1]);
        }
        else {
            printf("Created child %d with PID %d\n", i, pid);
        }
    }
    
    // Parent process: Close write ends
    for (int i = 0; i < num_children; i++) {
        close(pipes[i][1]);
    }
    
    // Read results from children
    printf("\nResults from children:\n");
    printf("Child | Task                | Result    | Time (s) | Status\n");
    printf("------|---------------------|-----------|----------|-------\n");
    
    for (int i = 0; i < num_children; i++) {
        Result result;
        ssize_t bytes_read = read(pipes[i][0], &result, sizeof(result));
        
        if (bytes_read != sizeof(result)) {
            fprintf(stderr, "Error reading from child %d\n", i);
            continue;
        }
        
        printf("%-5d | %-19s | %-9d | %8.3f | %d\n", 
               i, result.task_name, result.result, result.time_seconds, result.status);
        
        close(pipes[i][0]);
    }
    
    // Wait for all children
    for (int i = 0; i < num_children; i++) {
        int status;
        pid_t child_pid = wait(&status);
        if (child_pid == -1) {
            perror("wait failed");
        } else {
            printf("Child %d finished with status %d\n", child_pid, WEXITSTATUS(status));
        }
    }
    
    // Calculate total time
    clock_gettime(CLOCK_MONOTONIC, &end);
    double total_time = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("\nTotal wall-clock time: %.3f seconds\n", total_time);
    printf("✓ All children completed successfully!\n");
    
    return 0;
}
