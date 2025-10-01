# Ocelot Connection Guide - FIU COP4610

## What is Ocelot?

Ocelot is FIU's Linux server system where you need to compile and test your COP4610 assignments. It's required for this course because it provides the proper Linux environment with all the necessary tools.

## Getting Ocelot Access

### Option 1: Use Existing FIU Credentials
If you have FIU credentials from previous classes:
- **Username**: Your FIU Panther ID (usually starts with letters)
- **Password**: Your FIU password
- **Server**: `ocelot.fiu.edu`

### Option 2: Get New Ocelot Access
If you don't have Ocelot access yet:
1. **Contact FIU IT Help Desk**: (305) 348-2284
2. **Visit**: [FIU IT Support](https://it.fiu.edu/)
3. **Request**: Ocelot server access for COP4610
4. **Provide**: Your Panther ID and course information

## Connecting to Ocelot

### Method 1: SSH (Recommended)
```bash
ssh your_panther_id@ocelot.fiu.edu
```

### Method 2: SFTP (For file transfer)
```bash
sftp your_panther_id@ocelot.fiu.edu
```

### Method 3: SCP (For file copying)
```bash
scp parallel_forking.c your_panther_id@ocelot.fiu.edu:~/
```

## Step-by-Step Process

### 1. Transfer Your Code to Ocelot
```bash
# From your local machine, navigate to the assignment directory
cd /Users/andrelewis/HomeProjects/COP4610_Operating_Systems/Classes/COP4610_Operating_Systems/Assignments/Parallel_Forking_Assignment/

# Copy the file to Ocelot
scp parallel_forking.c your_panther_id@ocelot.fiu.edu:~/
```

### 2. Connect to Ocelot
```bash
ssh your_panther_id@ocelot.fiu.edu
```

### 3. Compile on Ocelot
```bash
# Once connected to Ocelot
gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm
```

### 4. Test the Program
```bash
# Test with different numbers of children
./parallel_forking 1
./parallel_forking 2
./parallel_forking 3
./parallel_forking 4

# Test error handling
./parallel_forking 0
./parallel_forking 5
```

### 5. Record Your Video
- Use screen recording software (OBS, QuickTime, etc.)
- Show the compilation and execution on Ocelot
- Follow the video walkthrough guide

## Alternative: Local Testing (Not for Submission)

If you want to test locally first (but you still need to submit from Ocelot):

### On macOS (Your current system)
```bash
# Navigate to the assignment directory
cd /Users/andrelewis/HomeProjects/COP4610_Operating_Systems/Classes/COP4610_Operating_Systems/Assignments/Parallel_Forking_Assignment/

# Compile locally
gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm

# Test locally
./parallel_forking 4
```

## Troubleshooting

### Connection Issues
- **"Connection refused"**: Check if you have Ocelot access
- **"Permission denied"**: Verify your username/password
- **"Host not found"**: Check your internet connection

### Compilation Issues
- **"command not found"**: Make sure you're on Ocelot (Linux system)
- **"No such file"**: Check if the file was transferred correctly
- **Math library errors**: Ensure you're using the `-lm` flag

### Runtime Issues
- **Segmentation fault**: Check for array bounds in matrix operations
- **Hanging processes**: Verify pipe ends are properly closed
- **Incorrect results**: Validate mathematical formulas

## Getting Help

### FIU Resources
1. **IT Help Desk**: (305) 348-2284
2. **SCIS Lab**: Engineering Center (EC)
3. **Professor Office Hours**: Check Canvas
4. **TA Support**: Available for lab assistance

### Online Resources
- **FIU IT Support**: https://it.fiu.edu/
- **Canvas**: Your course page
- **MyFIU**: Student portal

## Important Notes

- **Ocelot is required** for COP4610 assignments
- **Local testing is fine** for development, but final submission must be from Ocelot
- **Keep your credentials secure** - don't share them
- **Test early and often** - don't wait until the last minute

## Quick Commands Reference

```bash
# Connect to Ocelot
ssh your_panther_id@ocelot.fiu.edu

# Transfer file
scp parallel_forking.c your_panther_id@ocelot.fiu.edu:~/

# Compile
gcc -O2 -Wall -Wextra -o parallel_forking parallel_forking.c -lm

# Run
./parallel_forking 4

# Check if running
ps aux | grep parallel_forking

# Exit Ocelot
exit
```

---

*This guide will help you connect to Ocelot and successfully compile/test your COP4610 assignment.*
