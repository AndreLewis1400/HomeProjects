/*
 * COP4610 - Operating Systems Principles
 * Programming Assignment 4: Banker's Algorithm
 * 
 * Name: Andre Lewis
 * Panther ID: 6222923
 * 
 * Description: This program implements the Banker's Algorithm for deadlock
 * avoidance. It manages resource allocation for 5 customers and 4 resource types,
 * ensuring the system always remains in a safe state.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Global constants
#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4

// Global data structures
int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

// Function prototypes
void initialize_available(int argc, char *argv[]);
void initialize_maximum(const char *filename);
void initialize_allocation_and_need();
bool is_safe();
bool request_resources(int customer_id, int request[]);
void release_resources(int customer_id, int release[]);
void display_state();
void print_array(const char *name, int *arr, int size);
void print_matrix(const char *name, int matrix[][NUMBER_OF_RESOURCES], int rows);

int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != NUMBER_OF_RESOURCES + 1) {
        printf("Usage: %s <r1> <r2> <r3> <r4>\n", argv[0]);
        printf("Example: %s 10 5 7 8\n", argv[0]);
        return 1;
    }
    
    printf("Welcome to the Banker's Algorithm Simulation\n");
    printf("Initializing system with resources:\n");
    
    // Initialize available resources from command line
    initialize_available(argc, argv);
    printf("Available: [");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("%d", available[i]);
        if (i < NUMBER_OF_RESOURCES - 1) printf(", ");
    }
    printf("]\n");
    
    // Initialize maximum from file
    printf("Reading maximum request file...\n");
    initialize_maximum("maximum.txt");  // Default filename, can be changed
    printf("Maximum requests initialized.\n");
    
    // Initialize allocation and need arrays
    initialize_allocation_and_need();
    
    // Main command loop
    char command[100];
    printf("\nEnter commands (RQ, RL, *, or exit):\n");
    
    while (1) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }
        
        // Remove newline
        command[strcspn(command, "\n")] = 0;
        
        // Parse and execute commands
        if (strcmp(command, "exit") == 0) {
            printf("Exiting...\n");
            break;
        } else if (strcmp(command, "*") == 0) {
            display_state();
        } else if (command[0] == 'R' && command[1] == 'Q') {
            // Request command: RQ customer_id r1 r2 r3 r4
            int customer_id;
            int request[NUMBER_OF_RESOURCES];
            
            if (sscanf(command, "RQ %d %d %d %d %d", 
                      &customer_id, &request[0], &request[1], 
                      &request[2], &request[3]) == 5) {
                if (customer_id >= 0 && customer_id < NUMBER_OF_CUSTOMERS) {
                    if (request_resources(customer_id, request)) {
                        printf("Request granted. System is in a safe state.\n");
                    } else {
                        printf("Request denied. System would be left in an unsafe state.\n");
                    }
                } else {
                    printf("Error: Invalid customer ID. Must be 0-%d.\n", NUMBER_OF_CUSTOMERS - 1);
                }
            } else {
                printf("Error: Invalid RQ command format. Use: RQ <customer_id> <r1> <r2> <r3> <r4>\n");
            }
        } else if (command[0] == 'R' && command[1] == 'L') {
            // Release command: RL customer_id r1 r2 r3 r4
            int customer_id;
            int release[NUMBER_OF_RESOURCES];
            
            if (sscanf(command, "RL %d %d %d %d %d", 
                      &customer_id, &release[0], &release[1], 
                      &release[2], &release[3]) == 5) {
                if (customer_id >= 0 && customer_id < NUMBER_OF_CUSTOMERS) {
                    release_resources(customer_id, release);
                    printf("Resources released successfully.\n");
                } else {
                    printf("Error: Invalid customer ID. Must be 0-%d.\n", NUMBER_OF_CUSTOMERS - 1);
                }
            } else {
                printf("Error: Invalid RL command format. Use: RL <customer_id> <r1> <r2> <r3> <r4>\n");
            }
        } else {
            printf("Error: Unknown command. Use RQ, RL, *, or exit.\n");
        }
    }
    
    return 0;
}

// Initialize available array from command line arguments
void initialize_available(int argc, char *argv[]) {
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] = atoi(argv[i + 1]);
        if (available[i] < 0) {
            printf("Error: Resource values must be non-negative.\n");
            exit(1);
        }
    }
}

// Initialize maximum array from file
void initialize_maximum(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Cannot open file '%s'\n", filename);
        exit(1);
    }
    
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            if (fscanf(file, "%d", &maximum[i][j]) != 1) {
                printf("Error: Invalid file format or insufficient data.\n");
                fclose(file);
                exit(1);
            }
        }
    }
    
    fclose(file);
}

// Initialize allocation and need arrays
void initialize_allocation_and_need() {
    // Initially, no resources are allocated
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            allocation[i][j] = 0;
            // need = maximum - allocation
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

// Safety algorithm to check if system is in safe state
bool is_safe() {
    int work[NUMBER_OF_RESOURCES];
    bool finish[NUMBER_OF_CUSTOMERS];
    
    // Initialize work = available
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        work[i] = available[i];
    }
    
    // Initialize finish[i] = false for all i
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        finish[i] = false;
    }
    
    // Find a customer i such that:
    // finish[i] == false and need[i] <= work
    bool found = true;
    while (found) {
        found = false;
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
            if (!finish[i]) {
                // Check if need[i] <= work
                bool can_allocate = true;
                for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                
                if (can_allocate) {
                    // Customer i can complete: work = work + allocation[i]
                    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
    }
    
    // Check if all customers finished
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (!finish[i]) {
            return false;  // System is unsafe
        }
    }
    
    return true;  // System is safe
}

// Request resources for a customer
bool request_resources(int customer_id, int request[]) {
    // Step 1: Check if request <= need[customer_id]
    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
        if (request[j] > need[customer_id][j]) {
            printf("Error: Request exceeds need.\n");
            return false;
        }
    }
    
    // Step 2: Check if request <= available
    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
        if (request[j] > available[j]) {
            printf("Error: Request exceeds available resources.\n");
            return false;
        }
    }
    
    // Step 3: Tentatively allocate resources
    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
        available[j] -= request[j];
        allocation[customer_id][j] += request[j];
        need[customer_id][j] -= request[j];
    }
    
    // Step 4: Check if system is safe
    bool safe = is_safe();
    
    if (!safe) {
        // Rollback: restore previous state
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            available[j] += request[j];
            allocation[customer_id][j] -= request[j];
            need[customer_id][j] += request[j];
        }
        return false;
    }
    
    return true;  // Request granted, system is safe
}

// Release resources from a customer
void release_resources(int customer_id, int release[]) {
    // Validate release doesn't exceed allocation
    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
        if (release[j] > allocation[customer_id][j]) {
            printf("Warning: Release exceeds allocation. Releasing only allocated amount.\n");
            release[j] = allocation[customer_id][j];
        }
    }
    
    // Release resources
    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
        available[j] += release[j];
        allocation[customer_id][j] -= release[j];
        need[customer_id][j] += release[j];  // need = max - allocation
    }
}

// Display current system state
void display_state() {
    printf("\n=== System State ===\n");
    
    printf("Available: [");
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        printf("%d", available[i]);
        if (i < NUMBER_OF_RESOURCES - 1) printf(", ");
    }
    printf("]\n\n");
    
    printf("Maximum:\n");
    print_matrix("Maximum", maximum, NUMBER_OF_CUSTOMERS);
    
    printf("\nAllocation:\n");
    print_matrix("Allocation", allocation, NUMBER_OF_CUSTOMERS);
    
    printf("\nNeed:\n");
    print_matrix("Need", need, NUMBER_OF_CUSTOMERS);
    
    printf("\n");
}

// Helper function to print a 1D array
void print_array(const char *name, int *arr, int size) {
    printf("%s: [", name);
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// Helper function to print a 2D matrix
void print_matrix(const char *name, int matrix[][NUMBER_OF_RESOURCES], int rows) {
    for (int i = 0; i < rows; i++) {
        printf("Customer %d: [", i);
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            printf("%d", matrix[i][j]);
            if (j < NUMBER_OF_RESOURCES - 1) printf(", ");
        }
        printf("]\n");
    }
}

