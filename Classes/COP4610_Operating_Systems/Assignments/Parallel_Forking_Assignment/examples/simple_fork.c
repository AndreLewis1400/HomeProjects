/*
 * Simple Fork Example
 * Demonstrates basic process creation with fork()
 * 
 * Compile: gcc -o simple_fork simple_fork.c
 * Run: ./simple_fork
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("=== Simple Fork Example ===\n");
    printf("Before fork: PID = %d, PPID = %d\n", getpid(), getppid());
    
    // Create a child process
    pid_t pid = fork();
    
    if (pid == -1) {
        // Error occurred
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child: PID = %d, Parent PID = %d\n", getpid(), getppid());
        printf("Child: I'm doing some work...\n");
        sleep(2); // Simulate work
        printf("Child: Work done! Exiting.\n");
        return 42; // Child exits with status 42
    }
    else {
        // Parent process
        printf("Parent: Created child with PID = %d\n", pid);
        printf("Parent: Waiting for child to finish...\n");
        
        int status;
        pid_t child_pid = wait(&status);
        
        printf("Parent: Child %d finished with status %d\n", 
               child_pid, WEXITSTATUS(status));
        printf("Parent: All done!\n");
    }
    
    return 0;
}
