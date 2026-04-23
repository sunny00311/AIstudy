# 🎓 AI-Powered Study Planner & Explainer

A sophisticated C++ console application that helps students manage their studies using AI-powered features based on Google's Gemini API.

## 📋 Features

✅ **Subject & Topic Management**

- Add subjects and organize topics under each subject
- Track completion status of individual topics
- View all subjects with their topics in a structured format

✅ **Progress Tracking**

- Real-time progress percentage per subject
- Overall study progress tracking
- Visual progress indicators

✅ **AI-Powered Features** (Requires Gemini API Key)

- **Study Plan Generator**: Creates day-wise study plans for your subjects
- **Topic Explainer**: Get simple explanations for any topic
- **Notes Summarizer**: Convert lengthy notes into concise bullet points

✅ **Data Persistence**

- Automatic saving and loading of subjects/topics
- Study plans stored in text files in `data/` directory
- Seamless recovery on application restart

✅ **Beautiful CLI Interface**

- ANSI color-coded menu system
- Clear visual separators and formatting
- User-friendly prompts and feedback messages

## 🏗️ Architecture

```
User (CLI Menu)
    ↓
StudyManager (Controller)
    ↓
Models + AIService + FileHandler
    ↓
Gemini API (via libcurl)
```

### Class Structure

**Models:**

- `Content` - Abstract base class for displayable content
- `StudyPlan` - Inherits from `Content`, manages daily study plans
- `Topic` - Represents a study topic with completion status
- `Subject` - Contains multiple topics and tracks progress

**Core Services:**

- `StudyManager` - Main controller managing all operations
- `AIService` - Handles Gemini API communication
- `FileHandler` - Manages persistent data storage

**Utilities:**

- `Parser` - Parses AI responses into structured format

## 📁 Project Structure

```
project/
├── main.cpp                          # Entry point with colored CLI
├── Makefile                          # Build configuration
├── README.md                         # This file
│
├── core/
│   ├── StudyManager.h/cpp           # Main controller class
│   ├── AIService.h/cpp              # Gemini API integration
│   └── FileHandler.h/cpp            # Data persistence layer
│
├── models/
│   ├── Subject.h/cpp                # Subject model
│   ├── Topic.h/cpp                  # Topic model
│   └── StudyPlan.h/cpp              # Study plan with inheritance
│
├── utils/
│   └── Parser.h/cpp                 # Response parsing utilities
│
└── data/
    ├── subjects.txt                 # Persistent subject storage
    ├── plan.txt                     # Generated study plans
    └── progress.txt                 # Progress tracking
```

## 🚀 Compilation & Build

### Prerequisites

- **GCC/G++** (C++17 or later)
- **libcurl** development headers

### Installation of Dependencies

**On Ubuntu/Debian:**

```bash
sudo apt-get install build-essential libcurl4-openssl-dev
```

**On macOS (with Homebrew):**

```bash
brew install curl
```

**On Windows (with MinGW):**
Download libcurl from https://curl.se/download.html or use vcpkg:

```bash
vcpkg install curl:x64-windows
```

### Build Commands

```bash
# Build the project
make

# Run the application
./study_planner

# Clean build artifacts
make clean

# Rebuild from scratch
make rebuild
```

### Manual Compilation (if Makefile fails)

```bash
g++ -std=c++17 -I. -o study_planner \
    main.cpp \
    core/StudyManager.cpp \
    core/AIService.cpp \
    core/FileHandler.cpp \
    models/Subject.cpp \
    models/Topic.cpp \
    models/StudyPlan.cpp \
    utils/Parser.cpp \
    -lcurl
```

## 🔑 Gemini API Setup

### Get Your API Key

1. Visit [Google AI Studio](https://aistudio.google.com)
2. Click "Get API Key"
3. Create a new API key for your project
4. Copy your API key

### Configure the Application

Edit `core/AIService.cpp` and replace:

```cpp
AIService::AIService(const string& key) : apiKey(key) {
```

with your actual API key, or modify in `core/StudyManager.cpp`:

```cpp
AIService aiService("YOUR_ACTUAL_GEMINI_API_KEY");
```

## 📱 Usage Guide

### Starting the Application

```bash
./study_planner
```

### Menu Options

1. **Add a new subject** - Create a new subject (e.g., "Mathematics", "History")
2. **Display all subjects and topics** - View your complete study structure
3. **Add topic to a subject** - Add specific topics under a subject
4. **Mark topic as completed** - Track progress by marking topics done
5. **Show progress tracking** - View completion percentages
6. **Generate AI study plan** - Create a day-wise study plan (requires API key)
7. **Explain a topic (AI)** - Get AI-powered explanation (requires API key)
8. **Summarize notes (AI)** - Convert notes into bullet points (requires API key)
9. **View last generated plan** - Display the most recent study plan
10. **Exit** - Save data and close application

### Example Workflow

```
1. Add subject: "JavaScript"
2. Add topics: "Variables", "Functions", "Async/Await"
3. Mark "Variables" as completed
4. Generate study plan for 7 days
5. View plan and summary
6. Add more subjects and repeat
```

## 🎨 Color Scheme

- **CYAN**: Menu titles and options
- **GREEN**: Success messages
- **RED**: Error messages
- **YELLOW**: Warnings and input prompts
- **BLUE**: Headers and titles

## 🔒 OOP Design Highlights

### Encapsulation

- All data members are `private`
- Access through public getter/setter methods
- Clear separation of concerns

### Abstraction

- `AIService` completely hides API complexity
- `FileHandler` abstracts file I/O operations
- Users interact through high-level `StudyManager` interface

### Inheritance

- `StudyPlan` inherits from abstract `Content` class
- `Content` defines virtual `display()` method
- Demonstrates proper use of virtual functions

### Polymorphism

- Virtual method `display()` implemented in `StudyPlan`
- Extensible for future content types

## 📝 Data Files

The application automatically creates and manages:

- **subjects.txt** - Stores subjects and topics in custom format

  ```
  [SUBJECT]Mathematics
  TOPIC|Algebra|1
  TOPIC|Geometry|0
  ```

- **plan.txt** - Stores generated study plans
  ```
  GENERATED: 2024-04-12 15:30:45
  ---
  Day 1: Introduction to topics...
  Day 2: Deep dive...
  ```

## 🐛 Troubleshooting

### "libcurl not found"

- Ensure libcurl development headers are installed
- On Linux: `sudo apt-get install libcurl4-openssl-dev`

### API calls not working

- Verify your Gemini API key is correctly set
- Check internet connection
- Ensure API key has proper permissions

### Data not persisting

- Verify `data/` directory exists and is writable
- Check file permissions
- Ensure disk has available space

### Compilation errors

- Use C++17 or later: `g++ -std=c++17 ...`
- Include all source files in compilation
- Link libcurl library: `-lcurl`

## 📊 Code Quality

- ✅ Clean modular architecture
- ✅ Proper header/source separation
- ✅ Meaningful variable and function names
- ✅ Comprehensive comments for complex logic
- ✅ No global variables
- ✅ Small, focused functions
- ✅ Proper error handling

## 🎯 Future Enhancements

- [ ] SQLite database instead of text files
- [ ] Export study plans to PDF
- [ ] Interactive topic progress graphs
- [ ] Spaced repetition scheduling
- [ ] User authentication
- [ ] Cloud sync across devices
- [ ] Customizable color themes

## 📄 License

This project is provided as-is for educational purposes.

## 👤 Author

Created as a comprehensive demonstration of C++ OOP principles and clean architecture.

---

**Happy Studying! 🚀📚**
#   c p p _ p r o g r a m  
 