/*
 * COP4610 CPU Scheduling Algorithms Assignment
 * FIU - Operating Systems
 * 
 * This program implements and compares three CPU scheduling algorithms:
 * 1. FCFS (First-Come, First-Served)
 * 2. SJF (Shortest Job First)
 * 3. Round Robin
 * 
 * Compile: gcc -o cpu_scheduling cpu_scheduling.c
 * Run: ./cpu_scheduling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 10
#define MAX_NAME_LENGTH 20

// Process structure
typedef struct {
    char name[MAX_NAME_LENGTH];
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int first_execution;
} Process;

// Global variables
Process processes[MAX_PROCESSES];
int num_processes = 0;

// Function prototypes
void input_processes();
void fcfs_scheduling();
void sjf_scheduling();
void round_robin_scheduling(int quantum);
void calculate_metrics(Process p[], int n);
void print_results(Process p[], int n, char* algorithm_name);
void reset_processes();
void sort_by_arrival_time();
void sort_by_burst_time();

// Main function
int main() {
    printf("=== CPU Scheduling Algorithms Comparison ===\n");
    printf("COP4610 Operating Systems Assignment\n\n");
    
    // Get process information from user
    input_processes();
    
    printf("\n=== Simulation Results ===\n\n");
    
    // FCFS Scheduling
    printf("1. FCFS (First-Come, First-Served) Scheduling:\n");
    fcfs_scheduling();
    print_results(processes, num_processes, "FCFS");
    reset_processes();
    
    // SJF Scheduling
    printf("\n2. SJF (Shortest Job First) Scheduling:\n");
    sjf_scheduling();
    print_results(processes, num_processes, "SJF");
    reset_processes();
    
    // Round Robin Scheduling
    printf("\n3. Round Robin Scheduling:\n");
    int quantum;
    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);
    round_robin_scheduling(quantum);
    print_results(processes, num_processes, "Round Robin");
    
    printf("\n=== Assignment Complete ===\n");
    return 0;
}

// Input process information
void input_processes() {
    printf("Enter number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &num_processes);
    
    if (num_processes > MAX_PROCESSES) {
        printf("Error: Maximum %d processes allowed\n", MAX_PROCESSES);
        exit(1);
    }
    
    printf("\nEnter process details:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("  Name: ");
        scanf("%s", processes[i].name);
        printf("  Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("  Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        
        // Initialize other fields
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = 0;
        processes[i].first_execution = -1;
    }
}

// FCFS Scheduling Algorithm
void fcfs_scheduling() {
    // Sort processes by arrival time
    sort_by_arrival_time();
    
    int current_time = 0;
    
    for (int i = 0; i < num_processes; i++) {
        // If process hasn't arrived yet, wait
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        // Set response time (first execution time - arrival time)
        processes[i].response_time = current_time - processes[i].arrival_time;
        processes[i].first_execution = current_time;
        
        // Execute process
        current_time += processes[i].burst_time;
        
        // Set completion time
        processes[i].completion_time = current_time;
        
        // Calculate turnaround time and waiting time
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

// SJF Scheduling Algorithm
void sjf_scheduling() {
    int current_time = 0;
    int completed = 0;
    int shortest_index;
    
    while (completed < num_processes) {
        shortest_index = -1;
        int shortest_burst = 999999;
        
        // Find the shortest job that has arrived
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && 
                processes[i].remaining_time > 0 && 
                processes[i].burst_time < shortest_burst) {
                shortest_burst = processes[i].burst_time;
                shortest_index = i;
            }
        }
        
        // If no process is ready, advance time
        if (shortest_index == -1) {
            current_time++;
            continue;
        }
        
        // Set response time if first execution
        if (processes[shortest_index].first_execution == -1) {
            processes[shortest_index].response_time = current_time - processes[shortest_index].arrival_time;
            processes[shortest_index].first_execution = current_time;
        }
        
        // Execute the shortest job
        current_time += processes[shortest_index].burst_time;
        processes[shortest_index].remaining_time = 0;
        processes[shortest_index].completion_time = current_time;
        
        // Calculate turnaround time and waiting time
        processes[shortest_index].turnaround_time = processes[shortest_index].completion_time - processes[shortest_index].arrival_time;
        processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;
        
        completed++;
    }
}

// Round Robin Scheduling Algorithm
void round_robin_scheduling(int quantum) {
    int current_time = 0;
    int completed = 0;
    int queue[MAX_PROCESSES];
    int front = 0, rear = 0;
    
    // Initialize queue with processes that have arrived
    for (int i = 0; i < num_processes; i++) {
        if (processes[i].arrival_time <= current_time) {
            queue[rear++] = i;
        }
    }
    
    while (completed < num_processes) {
        if (front == rear) {
            // No processes in queue, advance time
            current_time++;
            // Add any new processes that have arrived
            for (int i = 0; i < num_processes; i++) {
                if (processes[i].arrival_time == current_time) {
                    queue[rear++] = i;
                }
            }
            continue;
        }
        
        int current_process = queue[front++];
        
        // Set response time if first execution
        if (processes[current_process].first_execution == -1) {
            processes[current_process].response_time = current_time - processes[current_process].arrival_time;
            processes[current_process].first_execution = current_time;
        }
        
        // Execute for quantum or remaining time, whichever is smaller
        int execution_time = (processes[current_process].remaining_time < quantum) ? 
                            processes[current_process].remaining_time : quantum;
        
        current_time += execution_time;
        processes[current_process].remaining_time -= execution_time;
        
        // Add any new processes that arrived during execution
        for (int i = 0; i < num_processes; i++) {
            if (processes[i].arrival_time <= current_time && 
                processes[i].remaining_time > 0 && 
                i != current_process) {
                // Check if process is already in queue
                int in_queue = 0;
                for (int j = front; j < rear; j++) {
                    if (queue[j] == i) {
                        in_queue = 1;
                        break;
                    }
                }
                if (!in_queue) {
                    queue[rear++] = i;
                }
            }
        }
        
        // If process is not completed, add it back to queue
        if (processes[current_process].remaining_time > 0) {
            queue[rear++] = current_process;
        } else {
            // Process completed
            processes[current_process].completion_time = current_time;
            processes[current_process].turnaround_time = processes[current_process].completion_time - processes[current_process].arrival_time;
            processes[current_process].waiting_time = processes[current_process].turnaround_time - processes[current_process].burst_time;
            completed++;
        }
    }
}

// Calculate performance metrics
void calculate_metrics(Process p[], int n) {
    float avg_waiting_time = 0, avg_turnaround_time = 0, avg_response_time = 0;
    
    for (int i = 0; i < n; i++) {
        avg_waiting_time += p[i].waiting_time;
        avg_turnaround_time += p[i].turnaround_time;
        avg_response_time += p[i].response_time;
    }
    
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    avg_response_time /= n;
    
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Response Time: %.2f\n", avg_response_time);
}

// Print results
void print_results(Process p[], int n, char* algorithm_name) {
    printf("\n%s Results:\n", algorithm_name);
    printf("Process\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\tResponse\n");
    printf("-------\t-------\t-----\t----------\t----------\t-------\t--------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               p[i].name, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time,
               p[i].waiting_time, p[i].response_time);
    }
    
    calculate_metrics(p, n);
}

// Reset processes for next algorithm
void reset_processes() {
    for (int i = 0; i < num_processes; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = 0;
        processes[i].first_execution = -1;
    }
}

// Sort processes by arrival time
void sort_by_arrival_time() {
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Sort processes by burst time (for SJF)
void sort_by_burst_time() {
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
