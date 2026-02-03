# COP4610 Parallel Forking Assignment

**Course**: COP4610 - Operating Systems (FIU)  
**Assignment**: Parallel Forking Assignment  
**Points**: 100 points total  
**Due Date**: [Check Canvas for due date]

## Assignment Overview

This assignment implements parallel execution in C using `fork()` to create child processes. Each child performs a different computational task and communicates results back to the parent process using inter-process communication (IPC).

## Assignment Requirements

### Part 1: Write the Program (55 pts)
- **User Input**: Program asks for number `n` (1-4) to determine child processes
- **Parent Message**: Parent displays message before creating children
- **Child Tasks**: Each child performs a unique computational task
- **IPC Communication**: Children send results to parent (no direct printing)
- **Parent Coordination**: Parent waits for all children and displays results
- **Compilation**: Code must compile successfully

### Part 2: Video Walkthrough (45 pts)
- **Task Explanation & Design Rationale** (10 pts)
- **Bugs & Debugging** (5 pts)
- **Online Resource or AI Use** (5 pts)
- **Communication Method Explained** (5 pts)
- **Diagram of Processes** (5 pts)
- **Live Code Demo** (5 pts)
- **Performance Comparison** (10 pts)
- **Peer Review** (10 pts)

## File Structure

```
Parallel_Forking_Assignment/
├── README.md                    # This file
├── parallel_forking.c           # Main source code
├── compilation_guide.md         # How to compile and run
├── video_walkthrough_guide.md   # Video recording checklist
├── process_diagram.md           # Process/IPC diagram
└── sample_output.txt            # Expected output examples
```

## Quick Start

1. **Compile on Ocelot**:
   ```bash
   gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm
   ```

2. **Run the program**:
   ```bash
   ./parallel_forking 4
   ```

3. **Record your video** following the walkthrough guide

## Assignment Tasks

The program implements 4 unique computational tasks:

1. **Prime Counting**: Count primes ≤ 300,000
2. **Pi Approximation**: Leibniz series (~30M iterations)
3. **Matrix Multiplication**: 140×140 matrix multiply and sum
4. **Numerical Integration**: Integrate sin(x) on [0,π] with 60M slices

## Key Features

- **Process Management**: Uses `fork()` to create child processes
- **IPC**: One pipe per child for communication
- **Error Handling**: Comprehensive error checking
- **Timing**: Microsecond precision timing with `CLOCK_MONOTONIC`
- **Clean Output**: Parent-only printing, structured result display

## Grading Rubric Alignment

**Compiles successfully**  
**Creates exactly n children (1-4)**  
**Each child performs unique task**  
**Children don't print (parent only)**  
**IPC method chosen and explained**  
**Error handling implemented**  
**Process diagram provided**  
**Timing discussion included**  
**Live demo recorded**  
**Peer review completed**

## Submission Checklist

- [ ] Source code (`parallel_forking.c`) uploaded
- [ ] Video walkthrough recorded and uploaded
- [ ] All rubric points covered in video
- [ ] Code tested on Ocelot (FIU Linux system)
- [ ] Peer review completed
- [ ] Self-check completed using course checklist

---

*This assignment demonstrates mastery of process creation, inter-process communication, and parallel programming concepts in C.*
