# GitHub Repository Setup Guide

## 🎯 **Goal**: Push your FIU coursework to GitHub repository `AndreLewis1400/HomeProjects`

## 📋 **Current Status**
- ✅ Local repository is organized and committed
- ✅ All FIU classes are properly structured in `Classes/` directory
- ✅ COP4610 Parallel Forking assignment is ready
- ❌ GitHub repository needs to be created/configured

## 🚀 **Step-by-Step Setup**

### **Option 1: Create Repository on GitHub (Recommended)**

1. **Go to GitHub.com** and sign in to your account
2. **Click the "+" icon** in the top right corner
3. **Select "New repository"**
4. **Repository settings**:
   - **Repository name**: `HomeProjects`
   - **Description**: `FIU Academic Coursework - Operating Systems, Data Structures, Programming, and Data Mining`
   - **Visibility**: Private (recommended for academic work)
   - **DO NOT** initialize with README, .gitignore, or license (we already have these)
5. **Click "Create repository"**

### **Option 2: SSH Key Setup (if needed)**

If you get permission denied errors, you need to add your SSH key to GitHub:

1. **Copy your public key**:
   ```bash
   cat ~/.ssh/id_ed25519.pub
   ```

2. **Add to GitHub**:
   - Go to GitHub.com → Settings → SSH and GPG keys
   - Click "New SSH key"
   - Paste your public key
   - Give it a title like "MacBook Pro - FIU Coursework"
   - Click "Add SSH key"

### **Option 3: Use Personal Access Token (Alternative)**

If SSH doesn't work, use HTTPS with a Personal Access Token:

1. **Create Personal Access Token**:
   - GitHub.com → Settings → Developer settings → Personal access tokens → Tokens (classic)
   - Click "Generate new token (classic)"
   - Select scopes: `repo` (full control of private repositories)
   - Copy the token (you won't see it again!)

2. **Update remote URL**:
   ```bash
   git remote set-url origin https://github.com/AndreLewis1400/HomeProjects.git
   ```

3. **Push with token**:
   ```bash
   git push -u origin main
   ```
   - Username: `AndreLewis1400`
   - Password: `[paste your personal access token]`

## 📁 **Repository Structure (Already Organized)**

Your repository is already perfectly organized:

```
HomeProjects/
├── Classes/                          # All FIU coursework
│   ├── COP4610_Operating_Systems/    # Operating Systems
│   │   ├── Assignments/
│   │   │   └── Parallel_Forking_Assignment/
│   │   │       ├── parallel_forking.c    # Your assignment
│   │   │       ├── README.md
│   │   │       └── [supporting files]
│   │   ├── Labs/
│   │   ├── Projects/
│   │   └── Code_Examples/
│   ├── COP4338_Systems_Programming/  # Systems Programming
│   ├── COP3530_Data_Structures/      # Data Structures
│   ├── COP3350_Programming_1/        # Programming 1
│   ├── CAP4770_Data_Mining/          # Data Mining
│   └── FIU_Quick_Reference.md
├── README.md                         # Main repository overview
└── .gitignore                       # C/C++ development ignore rules
```

## 🎓 **COP4610 Assignment Ready**

Your Parallel Forking assignment is complete and ready:

- **File**: `Classes/COP4610_Operating_Systems/Assignments/Parallel_Forking_Assignment/parallel_forking.c`
- **Features**: 
  - ✅ Process creation with `fork()`
  - ✅ IPC using pipes
  - ✅ 4 unique computational tasks
  - ✅ Error handling
  - ✅ Performance timing
  - ✅ Clean, commented code

## 🔧 **Commands to Run After GitHub Setup**

Once your GitHub repository is created:

```bash
# Navigate to your project directory
cd /Users/andrelewis/HomeProjects/COP4610_Operating_Systems

# Verify remote is set correctly
git remote -v

# Push to GitHub
git push -u origin main
```

## 📚 **Benefits of This Organization**

- **Professional**: Clean, academic structure
- **Scalable**: Easy to add new FIU classes
- **Organized**: Each class has consistent structure
- **Complete**: All assignments, labs, projects organized
- **FIU-Ready**: Meets academic standards

## 🎯 **Next Steps**

1. **Create the GitHub repository** (Option 1 above)
2. **Set up authentication** (Option 2 or 3 above)
3. **Push your code** with the commands above
4. **Share your repository** with professors/classmates as needed

## 📞 **Need Help?**

If you encounter any issues:
1. Check that the repository name is exactly `HomeProjects`
2. Verify your GitHub username is `AndreLewis1400`
3. Make sure you have the correct permissions
4. Try the Personal Access Token method if SSH fails

---

**Your FIU coursework is professionally organized and ready for GitHub! 🎓**
