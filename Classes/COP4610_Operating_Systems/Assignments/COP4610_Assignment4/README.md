# COP4610 - Programming Assignment 4: Banker's Algorithm

## Overview
This program implements the Banker's Algorithm for deadlock avoidance in operating systems. It manages resource allocation for 5 customers and 4 resource types, ensuring the system always remains in a safe state.

## Compilation
```bash
make
# or
gcc -Wall -Wextra -std=c11 -g -o banker banker.c
```

## Execution
```bash
./banker <r1> <r2> <r3> <r4>
# Example:
./banker 10 5 7 8
```

## Commands
- `RQ customer_id r1 r2 r3 r4` - Request resources
- `RL customer_id r1 r2 r3 r4` - Release resources
- `*` - Display system state
- `exit` - Quit program

## File Structure
- `banker.c` - Main program implementation
- `maximum.txt` - File containing maximum resource requests for each customer
- `Makefile` - Build configuration
- `README.md` - This file

## Data Structures
- `available[NUMBER_OF_RESOURCES]` - Currently available resources
- `maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]` - Maximum resources each customer needs
- `allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]` - Currently allocated resources
- `need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES]` - Remaining resources needed (need = max - allocation)

## Safety Algorithm
The program uses the Banker's safety algorithm to ensure the system never enters an unsafe state that could lead to deadlock. Before granting any request, it:
1. Validates the request doesn't exceed need
2. Validates the request doesn't exceed available
3. Tentatively allocates resources
4. Checks if system remains safe
5. Grants or denies the request based on safety check

## Example Usage
```
$ ./banker 10 5 7 8
Welcome to the Banker's Algorithm Simulation
Initializing system with resources:
Available: [10, 5, 7, 8]
Reading maximum request file...
Maximum requests initialized.

Enter commands (RQ, RL, *, or exit):
> RQ 0 3 1 2 1
Request granted. System is in a safe state.
> *
=== System State ===
Available: [7, 4, 5, 7]
...
> exit
Exiting...
```

