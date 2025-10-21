/*
 * COP4610 Parallel Forking Assignment
 * FIU - Operating Systems
 * 
 * This program demonstrates parallel execution using fork() and IPC.
 * Each child process performs a unique computational task and sends
 * results back to the parent via pipes.
 * 
 * Compile: gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm
 * Run: ./parallel_forking <n> where n is 1-4
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <errno.h>

// Result structure for IPC communication
typedef struct {
    char task_name[64];
    double result;
    double time_seconds;
    int status;
} Result;

// Function prototypes
int count_primes(int limit);
double leibniz_pi(int iterations);
double matrix_multiply_sum(int size);
double integrate_sin(int slices);
void child_task(int child_id, int write_fd);
void parent_task(int num_children, int pipes[][2]);
void print_usage(const char *program_name);

// Global task names
const char* TASK_NAMES[] = {
    "Count primes (<= 300k)",
    "Leibniz pi (~30M iters)",
    "Matmul sum (N=140)",
    "Integrate sin [0,pi] (60M)"
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    int num_children = atoi(argv[1]);
    if (num_children < 1 || num_children > 4) {
        fprintf(stderr, "Error: Number of children must be between 1 and 4\n");
        print_usage(argv[0]);
        return 1;
    }
    
    // Create pipes for each child
    int pipes[4][2];
    for (int i = 0; i < num_children; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            return 1;
        }
    }
    
    printf("[parent] Starting Parallel Forking with %d child(ren)\n", num_children);
    
    // Create child processes
    for (int i = 0; i < num_children; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("fork");
            return 1;
        }
        else if (pid == 0) {
            // Child process
            child_task(i, pipes[i][1]);
            exit(0);
        }
    }
    
    // Parent process
    parent_task(num_children, pipes);
    
    return 0;
}

void child_task(int child_id, int write_fd) {
    // Close read end of pipe (we don't need it in child)
    // The write_fd is already the write end, so we just close the read end
    // Note: We can't access pipes array here, so we'll close it in parent
    
    Result result;
    struct timespec start, end;
    
    // Initialize result structure
    strncpy(result.task_name, TASK_NAMES[child_id], sizeof(result.task_name) - 1);
    result.task_name[sizeof(result.task_name) - 1] = '\0';
    result.status = 0;
    
    // Start timing
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        perror("clock_gettime");
        result.status = -1;
        write(write_fd, &result, sizeof(result));
        exit(1);
    }
    
    // Perform task based on child ID
    switch (child_id) {
        case 0:
            result.result = count_primes(300000);
            break;
        case 1:
            result.result = leibniz_pi(30000000);
            break;
        case 2:
            result.result = matrix_multiply_sum(140);
            break;
        case 3:
            result.result = integrate_sin(60000000);
            break;
        default:
            result.status = -1;
            break;
    }
    
    // End timing
    if (clock_gettime(CLOCK_MONOTONIC, &end) == -1) {
        perror("clock_gettime");
        result.status = -1;
    } else {
        result.time_seconds = (end.tv_sec - start.tv_sec) + 
                             (end.tv_nsec - start.tv_nsec) / 1e9;
    }
    
    // Send result to parent
    if (write(write_fd, &result, sizeof(result)) != sizeof(result)) {
        perror("write");
        exit(1);
    }
    
    close(write_fd);
    exit(0);
}

void parent_task(int num_children, int pipes[][2]) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    // Close write ends of pipes (parent doesn't write to children)
    for (int i = 0; i < num_children; i++) {
        close(pipes[i][1]);
    }
    
    // Close read ends of unused pipes (if num_children < 4)
    for (int i = num_children; i < 4; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
    
    // Wait for all children and collect results
    printf("[parent] All children finished. Results:\n");
    
    for (int i = 0; i < num_children; i++) {
        Result result;
        ssize_t bytes_read = read(pipes[i][0], &result, sizeof(result));
        
        if (bytes_read != sizeof(result)) {
            fprintf(stderr, "Error reading from child %d\n", i);
            continue;
        }
        
        printf("  child #%d | task: %-30s | result: %12.6f | time: %8.3f s | status: %d\n",
               i, result.task_name, result.result, result.time_seconds, result.status);
        
        close(pipes[i][0]);
    }
    
    // Wait for all children to complete
    for (int i = 0; i < num_children; i++) {
        int status;
        wait(&status);
    }
    
    // Calculate total wall-clock time
    clock_gettime(CLOCK_MONOTONIC, &end);
    double wall_time = (end.tv_sec - start.tv_sec) + 
                       (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("[parent] Wall-clock elapsed: %.3f s\n", wall_time);
}

// Task 1: Count primes up to limit
int count_primes(int limit) {
    int count = 0;
    for (int i = 2; i <= limit; i++) {
        int is_prime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) count++;
    }
    return count;
}

// Task 2: Approximate pi using Leibniz series
double leibniz_pi(int iterations) {
    double pi = 0.0;
    for (int i = 0; i < iterations; i++) {
        pi += pow(-1, i) / (2 * i + 1);
    }
    return pi * 4;
}

// Task 3: Matrix multiplication and sum
double matrix_multiply_sum(int size) {
    // Allocate matrices
    double **A = calloc(size, sizeof(double*));
    double **B = calloc(size, sizeof(double*));
    double **C = calloc(size, sizeof(double*));
    
    if (!A || !B || !C) {
        perror("calloc");
        return -1;
    }
    
    for (int i = 0; i < size; i++) {
        A[i] = calloc(size, sizeof(double));
        B[i] = calloc(size, sizeof(double));
        C[i] = calloc(size, sizeof(double));
        
        if (!A[i] || !B[i] || !C[i]) {
            perror("calloc");
            return -1;
        }
    }
    
    // Initialize matrices with simple values
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            A[i][j] = (i + j) % 10;
            B[i][j] = (i - j + 10) % 10;
        }
    }
    
    // Matrix multiplication
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    // Sum all elements
    double sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sum += C[i][j];
        }
    }
    
    // Free memory
    for (int i = 0; i < size; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    
    return sum;
}

// Task 4: Numerical integration of sin(x) from 0 to pi
double integrate_sin(int slices) {
    double dx = M_PI / slices;
    double sum = 0.0;
    
    for (int i = 0; i < slices; i++) {
        double x = i * dx;
        sum += sin(x) * dx;
    }
    
    return sum;
}


void print_usage(const char *program_name) {
    printf("Usage: %s <n>\n", program_name);
    printf("  n: Number of child processes to create (1-4)\n");
    printf("  Each child performs a unique computational task\n");
}
