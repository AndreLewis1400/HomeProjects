/*
 * Timing Example
 * Demonstrates how to measure execution time
 * 
 * Compile: gcc -o timing_example timing_example.c
 * Run: ./timing_example
 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

// Simple function to simulate work
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

int main() {
    printf("=== Timing Example ===\n");
    
    // Method 1: Using clock_gettime() (recommended)
    printf("\n1. Using clock_gettime():\n");
    struct timespec start, end;
    
    clock_gettime(CLOCK_MONOTONIC, &start);
    int primes = count_primes(10000);
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    double elapsed = (end.tv_sec - start.tv_sec) + 
                     (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("   Found %d primes in %.6f seconds\n", primes, elapsed);
    
    // Method 2: Using clock() (less precise)
    printf("\n2. Using clock():\n");
    clock_t start_clock = clock();
    count_primes(10000);
    clock_t end_clock = clock();
    
    double cpu_time = ((double)(end_clock - start_clock)) / CLOCKS_PER_SEC;
    printf("   CPU time: %.6f seconds\n", cpu_time);
    
    // Method 3: Using gettimeofday() (deprecated but still used)
    printf("\n3. Using gettimeofday():\n");
    struct timeval start_tv, end_tv;
    gettimeofday(&start_tv, NULL);
    count_primes(10000);
    gettimeofday(&end_tv, NULL);
    
    double elapsed_tv = (end_tv.tv_sec - start_tv.tv_sec) + 
                        (end_tv.tv_usec - start_tv.tv_usec) / 1e6;
    
    printf("   Elapsed time: %.6f seconds\n", elapsed_tv);
    
    // Demonstrate timing precision
    printf("\n4. Timing precision test:\n");
    clock_gettime(CLOCK_MONOTONIC, &start);
    usleep(1000); // Sleep for 1 millisecond
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    double sleep_time = (end.tv_sec - start.tv_sec) + 
                        (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("   Sleep time: %.6f seconds (expected ~0.001)\n", sleep_time);
    
    return 0;
}
