#!/bin/bash

echo "Building Study Planner..."
echo ""

g++ -std=c++17 -I. -o study_planner \
    main.cpp \
    core/StudyManager.cpp \
    core/AIService.cpp \
    core/FileHandler.cpp \
    models/Subject.cpp \
    models/Topic.cpp \
    models/StudyPlan.cpp \
    utils/Parser.cpp \
    -lcurl -Wall -Wextra

if [ $? -eq 0 ]; then
    echo ""
    echo "✓ [SUCCESS] Build complete!"
    echo "  Run with: ./study_planner"
else
    echo ""
    echo "✗ [ERROR] Build failed!"
    echo ""
    echo "Make sure you have installed:"
    echo "  Ubuntu/Debian: sudo apt-get install build-essential libcurl4-openssl-dev"
    echo "  macOS:         brew install curl"
    echo ""
fi
