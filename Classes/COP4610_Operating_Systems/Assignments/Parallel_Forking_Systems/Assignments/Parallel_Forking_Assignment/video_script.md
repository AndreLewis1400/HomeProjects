# COP4610 Parallel Forking Assignment - Video Script

## Video Overview
- **Duration**: 3-5 minutes
- **Format**: Mediasite with PowerPoint slides + live demo
- **Total Points**: 45 points
- **Requirements**: Cover all 8 rubric sections

---

## Slide 1: Introduction (15 seconds)
**Script**: "Hi, I'm [Your Name] and this is my COP4610 Parallel Forking assignment. I'll be demonstrating parallel execution in C using fork() and inter-process communication."

**Visual**: Title slide with your name, course, and assignment title

---

## Slide 2: Task Explanation & Design Rationale (45-60 seconds)
**Script**: 
"I chose these 4 computational tasks because they're CPU-bound with varied instruction mixes, perfect for demonstrating parallel speedup versus single process execution. I constrained n to be between 1 and 4 so each child runs a unique task as required by the assignment.

Each task has different computational characteristics:
- Prime counting is branch-heavy with many conditional statements
- Pi approximation uses simple floating-point operations
- Matrix multiplication is cache-intensive and memory-bound
- Integration is a tight loop with trigonometric functions

This variety helps show how different types of workloads benefit from parallelization."

**Visual**: 
- List of 4 tasks with their characteristics
- Diagram showing CPU-bound vs I/O-bound tasks

---

## Slide 3: Bugs & Debugging (30-45 seconds)
**Script**:
"One major bug I encountered was forgetting to close unused pipe ends, which caused the program to hang. The fix was to close all unrelated file descriptors in both parent and child before compute and write operations.

Another bug was reading fewer bytes than sizeof(Result). I fixed this by checking the exact byte count returned by read() to ensure complete data transfer.

These debugging experiences taught me the importance of proper resource management in system programming."

**Visual**: 
- Code snippet showing pipe closing
- Before/after comparison of bug fixes

---

## Slide 4: Online Resource or AI Use (30 seconds)
**Script**:
"I used ChatGPT to help design the struct-based IPC system and per-child pipe architecture. The AI suggested using CLOCK_MONOTONIC for timing and helped with the Result struct design. This collaboration improved the robustness and maintainability of my code."

**Visual**: 
- Brief screenshot of ChatGPT conversation (blur sensitive parts)
- Highlight the key suggestions that were implemented

---

## Slide 5: Communication Method Explained (30-45 seconds)
**Script**:
"Each child has its own dedicated pipe for communication. Children write a packed Result struct containing task name, numeric result, execution time, and status. The parent reads once per child to avoid interleaving and maintains clean separation of concerns. Children do not print anything; only the parent handles all I/O, which prevents race conditions and ensures clean output formatting."

**Visual**: 
- Diagram showing one pipe per child
- Result struct layout
- Data flow arrows

---

## Slide 6: Diagram of Processes (30-45 seconds)
**Script**:
"Here's the process flow diagram. The parent creates pipes for each child, then forks children in a loop. Each child performs its assigned task and writes results to its dedicated pipe. The parent reads from all pipes, displays the results, and waits for all children to complete using wait()."

**Visual**: 
- Process flow diagram with parent at top
- 4 arrows pointing to children
- Pipes connecting back to parent
- Label the wait() synchronization

---

## Slide 7: Live Code Demo (60-90 seconds)
**Script**:
"Now let's see the program in action. I'll compile it with the required flags, then run it with 4 children to show all tasks executing in parallel."

**Live Demo**:
```bash
gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm
./parallel_forking 4
```

**Script Continued**:
"Notice the results: π is approximately 3.141593, the integral of sin(x) from 0 to π equals 2, and we found 25,997 primes. The matrix multiplication produces a large sum as expected."

**Visual**: 
- Terminal showing compilation
- Terminal showing execution and results
- Highlight the expected values

---

## Slide 8: Performance Comparison (60-90 seconds)
**Script**:
"Let's analyze the performance. The wall-clock time of 0.499 seconds is approximately equal to the maximum child execution time of 0.499 seconds plus a small overhead. This overhead includes scheduler time, fork() system calls, and IPC communication.

The CPU intensity varies by task: prime testing is branch-heavy, pi series uses simple floating-point operations, matrix multiplication is cache-intensive, and integration is a tight loop with trigonometric functions. This demonstrates how fork/IPC overhead and CPU intensity affect parallel performance."

**Visual**: 
- Performance table showing individual times vs wall-clock
- Bar chart comparing task execution times
- Overhead breakdown

---

## Slide 9: Peer Review (30 seconds)
**Script**:
"I reviewed [Peer's Name]'s video and learned about their approach to [specific task]. One suggestion I had was [constructive feedback]. I watched their entire video and found their explanation of [specific concept] particularly helpful."

**Visual**: 
- Brief mention of peer review process
- Key learning points from peer's work

---

## Slide 10: Conclusion (15 seconds)
**Script**:
"This assignment demonstrates mastery of process creation, IPC, and parallel programming concepts in C. Thank you for watching."

**Visual**: 
- Summary of key concepts learned
- Contact information if needed

---

## Technical Setup Notes

### Mediasite Recording:
- **Resolution**: 1080p minimum
- **Audio**: Clear microphone, minimal background noise
- **Duration**: 3-5 minutes total
- **Screen sharing**: Show terminal and slides

### PowerPoint Tips:
- **Keep slides simple**: Don't overcrowd with text
- **Use visuals**: Diagrams, code snippets, performance charts
- **Consistent formatting**: Same font, colors, layout
- **Practice transitions**: Smooth flow between slides

### Word Document Talking Points:
- **Print out**: Have a physical copy for reference
- **Highlight key points**: Mark important sections
- **Time markers**: Note approximate timing for each section
- **Backup plan**: Have notes ready if technology fails

### Demo Preparation:
- **Test everything**: Compile and run program beforehand
- **Have backup**: Multiple terminal windows ready
- **Clear screen**: Clean desktop, close unnecessary apps
- **Practice**: Run through the demo several times

---

## Rubric Checklist

- [ ] Task explanation & design rationale (10 pts)
- [ ] Bugs & debugging (5 pts)
- [ ] Online resource or AI use (5 pts)
- [ ] Communication method explained (5 pts)
- [ ] Diagram of processes (5 pts)
- [ ] Live code demo (5 pts)
- [ ] Performance comparison (10 pts)
- [ ] Peer review (10 pts)

**Total: 45 points**

---

*This script ensures you hit every rubric requirement while maintaining a professional presentation flow.*
