/*
 * Process Creation Example
 * 
 * This example demonstrates basic process creation using fork() and exec()
 * 
 * Compile: gcc -o process_creation main.c
 * Run: ./process_creation
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    pid_t pid;
    int status;
    
    printf("Parent process: PID = %d\n", getpid());
    printf("About to create child process...\n\n");
    
    // Create a child process
    pid = fork();
    
    if (pid == -1) {
        // Error occurred
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d, Parent PID = %d\n", 
               getpid(), getppid());
        
        // Execute a command in the child process
        printf("Child: Executing 'ls -l' command...\n");
        execl("/bin/ls", "ls", "-l", NULL);
        
        // If execl returns, there was an error
        perror("execl failed");
        exit(EXIT_FAILURE);
    }
    else {
        // Parent process
        printf("Parent: Created child process with PID = %d\n", pid);
        printf("Parent: Waiting for child to complete...\n");
        
        // Wait for child process to complete
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }
        
        // Check how the child process terminated
        if (WIFEXITED(status)) {
            printf("Parent: Child process exited with status %d\n", 
                   WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)) {
            printf("Parent: Child process was killed by signal %d\n", 
                   WTERMSIG(status));
        }
        
        printf("Parent: Child process completed\n");
    }
    
    printf("Process %d: Exiting\n", getpid());
    return EXIT_SUCCESS;
}
