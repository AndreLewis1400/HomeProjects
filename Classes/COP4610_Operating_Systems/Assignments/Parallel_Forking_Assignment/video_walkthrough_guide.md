# Video Walkthrough Guide - COP4610 Parallel Forking Assignment

## Video Requirements (3-5 minutes, 45 points total)

### 1. Task Explanation & Design Rationale (10 pts)
**What to say:**
- "I chose these 4 tasks because they're CPU-bound with varied instruction mixes, perfect for demonstrating parallel speedup vs single process execution"
- "I constrained n≤4 so each child runs a unique task as required by the assignment"
- "Each task has different computational characteristics: prime counting is branch-heavy, pi approximation is simple floating-point, matrix multiplication is cache-intensive, and integration is a tight loop with trigonometric functions"

**Time: 45-60 seconds**

### 2. Bugs & Debugging (5 pts)
**What to demonstrate:**
- "One major bug I encountered was forgetting to close unused pipe ends, which caused blocking"
- "The fix was to close all unrelated file descriptors in both parent and child before compute/write operations"
- "Another bug was reading fewer bytes than sizeof(Result); I fixed this by checking the exact byte count returned by read()"

**Show on screen:**
- Brief code snippet showing pipe closing
- Error handling in read/write operations

**Time: 30-45 seconds**

### 3. Online Resource or AI Use (5 pts)
**What to show:**
- "I used ChatGPT to help design the struct-based IPC system and per-child pipe architecture"
- "The AI suggested using CLOCK_MONOTONIC for timing and helped with the Result struct design"
- Show a brief clip of your ChatGPT conversation (blur sensitive parts)

**Time: 30 seconds**

### 4. Communication Method Explained (5 pts)
**What to explain:**
- "Each child has its own dedicated pipe for communication"
- "Children write a packed Result struct containing task name, numeric result, execution time, and status"
- "The parent reads once per child to avoid interleaving and maintains clean separation of concerns"
- "Children do not print anything; only the parent handles all I/O"

**Time: 30-45 seconds**

### 5. Diagram of Processes (5 pts)
**What to draw:**
- Simple box diagram: Parent at top with 4 arrows pointing down to Child0, Child1, Child2, Child3
- Each arrow back represents a pipe (child writes → parent reads)
- Label the wait() call on parent
- Show the Result struct flowing through pipes

**Time: 30-45 seconds**

### 6. Live Code Demo (5 pts)
**What to record:**
```bash
# Show compilation
gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm

# Show execution
./parallel_forking 4

# Discuss expected results:
# - π ≈ 3.14159
# - ∫sin(x) from 0 to π ≈ 2.0
# - Prime count for 300k should be around 25,997
# - Matrix sum will be a large positive number
```

**Time: 60-90 seconds**

### 7. Performance Comparison (10 pts)
**What to analyze:**
- "The wall-clock time should be approximately equal to the maximum child execution time plus overhead"
- "Overhead includes scheduler time, fork() system calls, and IPC communication"
- "CPU intensity varies: prime testing is branch-heavy, pi series is simple FP operations, matrix multiplication is cache-intensive, and integration is a tight loop with trigonometric functions"
- "This demonstrates how fork/IPC overhead and CPU intensity affect parallel performance"

**Show on screen:**
- Output with timing data
- Point out the relationship between individual times and wall-clock time

**Time: 60-90 seconds**

### 8. Peer Review (10 pts)
**What to mention:**
- "I reviewed [peer's name]'s video and learned about their approach to [specific task]"
- "One suggestion I had was [constructive feedback]"
- "I watched their entire video and found their explanation of [specific concept] particularly helpful"

**Time: 30 seconds**

## Video Recording Tips

### Technical Setup
- **Screen Recording**: Use OBS, QuickTime, or similar
- **Audio**: Clear microphone, minimal background noise
- **Resolution**: 1080p minimum
- **Duration**: 3-5 minutes total

### Content Organization
1. **Introduction** (15 seconds): "Hi, I'm [name] and this is my COP4610 Parallel Forking assignment"
2. **Main Content** (3-4 minutes): Follow the 8 sections above
3. **Conclusion** (15 seconds): "This demonstrates mastery of process creation, IPC, and parallel programming"

### Recording Checklist
- [ ] Test audio levels before recording
- [ ] Have code ready to show on screen
- [ ] Prepare diagram on paper or digital tool
- [ ] Test compilation and execution beforehand
- [ ] Have ChatGPT conversation ready to show (briefly)
- [ ] Practice timing for each section

### Post-Recording
- [ ] Check audio quality
- [ ] Verify all rubric points are covered
- [ ] Ensure video is 3-5 minutes
- [ ] Upload to Canvas or required platform
- [ ] Complete peer review

## Self-Check Before Submitting

Use the course checklist and verify:
- [ ] Code compiles without warnings
- [ ] Creates exactly n children (1-4)
- [ ] Each child performs unique task
- [ ] Parent-only printing (no child output)
- [ ] IPC method chosen and explained
- [ ] Error handling implemented
- [ ] Process diagram provided
- [ ] Timing discussion included
- [ ] Live demo recorded
- [ ] Peer review completed

---

*This guide ensures you hit every rubric requirement and demonstrate mastery of the assignment objectives.*
