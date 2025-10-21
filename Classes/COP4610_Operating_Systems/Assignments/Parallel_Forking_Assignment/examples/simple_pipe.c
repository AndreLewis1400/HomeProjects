/*
 * Simple Pipe Example
 * Demonstrates inter-process communication with pipes
 * 
 * Compile: gcc -o simple_pipe simple_pipe.c
 * Run: ./simple_pipe
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    printf("=== Simple Pipe Example ===\n");
    
    // Create a pipe
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    printf("Created pipe: read_fd=%d, write_fd=%d\n", pipe_fd[0], pipe_fd[1]);
    
    // Create a child process
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process: Write to pipe
        printf("Child: Closing read end of pipe\n");
        close(pipe_fd[0]); // Close read end
        
        char message[] = "Hello from child process!";
        printf("Child: Writing message to pipe\n");
        
        if (write(pipe_fd[1], message, strlen(message) + 1) == -1) {
            perror("write failed");
            return 1;
        }
        
        printf("Child: Message sent, closing write end\n");
        close(pipe_fd[1]);
        return 0;
    }
    else {
        // Parent process: Read from pipe
        printf("Parent: Closing write end of pipe\n");
        close(pipe_fd[1]); // Close write end
        
        char buffer[100];
        printf("Parent: Waiting for message from child...\n");
        
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer));
        if (bytes_read == -1) {
            perror("read failed");
            return 1;
        }
        
        printf("Parent: Received %zd bytes: '%s'\n", bytes_read, buffer);
        close(pipe_fd[0]);
        
        // Wait for child to finish
        int status;
        wait(&status);
        printf("Parent: Child finished with status %d\n", WEXITSTATUS(status));
    }
    
    return 0;
}
