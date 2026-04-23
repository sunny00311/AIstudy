# ⚡ Quick Start Guide

## 🚀 Get Running in 5 Minutes

### Step 1: Install Dependencies

**Windows (with MinGW):**

```bash
# Install MinGW from: https://www.mingw-w64.org/
# Then download libcurl: https://curl.se/download.html
```

**Linux (Ubuntu/Debian):**

```bash
sudo apt-get update
sudo apt-get install build-essential libcurl4-openssl-dev
```

**macOS:**

```bash
brew install curl
```

### Step 2: Compile the Project

**Option A: Using Makefile (Linux/macOS)**

```bash
cd project2/
make
```

**Option B: Using Build Script (Windows)**

```bash
build.bat
```

**Option C: Using Build Script (Linux/macOS)**

```bash
chmod +x build.sh
./build.sh
```

**Option D: Manual Compilation (Works on all platforms)**

```bash
g++ -std=c++17 -I. -o study_planner main.cpp core/*.cpp models/*.cpp utils/*.cpp -lcurl
```

### Step 3: Run the Application

**Linux/macOS:**

```bash
./study_planner
```

**Windows:**

```bash
study_planner.exe
```

### Step 4: Complete First-Time Setup (Optional: For AI Features)

1. Get Gemini API Key:
   - Visit: https://aistudio.google.com/apikey
   - Create new API key
   - Copy the key

2. Configure API key:
   - Open `core/StudyManager.cpp`
   - Find line: `AIService aiService("YOUR_GEMINI_API_KEY");`
   - Replace with your actual key
   - Recompile

## 📖 Basic Usage

```
1. Start with "Add a new subject" (e.g., "Math", "History")
2. Add topics under each subject
3. Track progress by marking topics complete
4. Use AI features to generate plans and summaries
5. Press 10 to exit (data is auto-saved)
```

## 🆘 Command Reference

| Command             | Action                        |
| ------------------- | ----------------------------- |
| `make`              | Build project using Makefile  |
| `make clean`        | Remove build files            |
| `make rebuild`      | Full rebuild                  |
| `./build.sh`        | Build on Linux/macOS          |
| `build.bat`         | Build on Windows              |
| `./study_planner`   | Run application (Linux/macOS) |
| `study_planner.exe` | Run application (Windows)     |

## ⚠️ Common Issues

**"libcurl not found"**

- Install: `sudo apt-get install libcurl4-openssl-dev` (Linux)
- Or: `brew install curl` (macOS)

**"g++: command not found"**

- Install GCC: `sudo apt-get install build-essential`
- Or download MinGW (Windows)

**Compilation fails with ANSI color codes**

- ANSI codes work on modern terminals (most Linux/macOS)
- Windows 10+ supports them natively
- For older Windows: use WSL or Git Bash

## 📝 Example Session

```
$ ./study_planner

▶ Enter choice: 1
  Subject name: Data Structures

▶ Enter choice: 3
  Subject name: Data Structures
  Topic name: Linked Lists

▶ Enter choice: 5
  [Shows progress: 0% complete]

▶ Enter choice: 4
  Subject name: Data Structures
  Topic name: Linked Lists
  ✓ Topic marked as completed!

▶ Enter choice: 5
  [Shows progress: 100% complete]

▶ Enter choice: 10
  ✓ Exiting...
```

---

**Next Steps:** Read `README.md` for detailed documentation

**Happy Studying! 📚🚀**
