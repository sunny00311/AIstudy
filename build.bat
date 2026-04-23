@echo off

echo Building Study Planner...
echo.

g++ -std=c++17 -I. -o study_planner.exe ^
    main.cpp ^
    core/StudyManager.cpp ^
    core/AIService.cpp ^
    core/FileHandler.cpp ^
    models/Subject.cpp ^
    models/Topic.cpp ^
    models/StudyPlan.cpp ^
    utils/Parser.cpp ^
    -lcurl -Wall -Wextra

if %ERRORLEVEL% equ 0 (
    echo.
    echo [SUCCESS] Build complete!
    echo Run with: study_planner.exe
) else (
    echo.
    echo [ERROR] Build failed!
    echo Make sure you have:
    echo - MinGW/GCC installed (g++ in PATH)
    echo - libcurl development headers installed
    echo.
    pause
)

pause
