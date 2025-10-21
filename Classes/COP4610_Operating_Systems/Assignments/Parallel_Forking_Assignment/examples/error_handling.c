/*
 * Error Handling Example
 * Demonstrates proper error handling in system programming
 * 
 * Compile: gcc -o error_handling error_handling.c
 * Run: ./error_handling
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

// Function to demonstrate error handling
int create_and_communicate() {
    int pipe_fd[2];
    
    // 1. Check pipe creation
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return -1;
    }
    printf("✓ Pipe created successfully\n");
    
    // 2. Check fork
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return -1;
    }
    printf("✓ Fork successful, child PID: %d\n", pid);
    
    if (pid == 0) {
        // Child process
        close(pipe_fd[0]); // Close read end
        
        char message[] = "Hello from child!";
        ssize_t bytes_written = write(pipe_fd[1], message, strlen(message) + 1);
        
        if (bytes_written == -1) {
            perror("write failed in child");
            close(pipe_fd[1]);
            exit(1);
        }
        
        if (bytes_written != strlen(message) + 1) {
            fprintf(stderr, "Warning: Partial write (%zd/%zu bytes)\n", 
                    bytes_written, strlen(message) + 1);
        }
        
        printf("✓ Child wrote %zd bytes\n", bytes_written);
        close(pipe_fd[1]);
        exit(0);
    } else {
        // Parent process
        close(pipe_fd[1]); // Close write end
        
        char buffer[100];
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
        
        if (bytes_read == -1) {
            perror("read failed in parent");
            close(pipe_fd[0]);
            return -1;
        }
        
        if (bytes_read == 0) {
            fprintf(stderr, "Error: No data received from child\n");
            close(pipe_fd[0]);
            return -1;
        }
        
        printf("✓ Parent read %zd bytes: '%s'\n", bytes_read, buffer);
        close(pipe_fd[0]);
        
        // Wait for child
        int status;
        pid_t child_pid = wait(&status);
        if (child_pid == -1) {
            perror("wait failed");
            return -1;
        }
        
        if (WIFEXITED(status)) {
            printf("✓ Child exited normally with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("✗ Child killed by signal %d\n", WTERMSIG(status));
        }
    }
    
    return 0;
}

// Function to demonstrate memory error handling
int memory_example() {
    printf("\n=== Memory Error Handling ===\n");
    
    // Allocate memory
    int *array = malloc(1000 * sizeof(int));
    if (array == NULL) {
        perror("malloc failed");
        return -1;
    }
    printf("✓ Memory allocated successfully\n");
    
    // Use the memory
    for (int i = 0; i < 1000; i++) {
        array[i] = i * i;
    }
    printf("✓ Memory used successfully\n");
    
    // Free memory
    free(array);
    printf("✓ Memory freed successfully\n");
    
    return 0;
}

// Function to demonstrate file error handling
int file_example() {
    printf("\n=== File Error Handling ===\n");
    
    // Try to open a non-existent file
    FILE *file = fopen("nonexistent.txt", "r");
    if (file == NULL) {
        perror("fopen failed (expected)");
        printf("✓ Error handling working correctly\n");
    } else {
        fclose(file);
    }
    
    // Try to create a file
    file = fopen("test_file.txt", "w");
    if (file == NULL) {
        perror("fopen failed");
        return -1;
    }
    
    if (fprintf(file, "Hello, World!\n") < 0) {
        perror("fprintf failed");
        fclose(file);
        return -1;
    }
    
    if (fclose(file) == EOF) {
        perror("fclose failed");
        return -1;
    }
    
    printf("✓ File operations successful\n");
    
    // Clean up
    if (unlink("test_file.txt") == -1) {
        perror("unlink failed");
    } else {
        printf("✓ File cleaned up\n");
    }
    
    return 0;
}

int main() {
    printf("=== Error Handling Example ===\n");
    
    // Test process communication
    if (create_and_communicate() == -1) {
        fprintf(stderr, "Process communication failed\n");
        return 1;
    }
    
    // Test memory handling
    if (memory_example() == -1) {
        fprintf(stderr, "Memory example failed\n");
        return 1;
    }
    
    // Test file handling
    if (file_example() == -1) {
        fprintf(stderr, "File example failed\n");
        return 1;
    }
    
    printf("\n✓ All examples completed successfully!\n");
    return 0;
}
