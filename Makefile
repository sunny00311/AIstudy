CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I.

LDFLAGS := -lcurl

TARGET := study_planner

SOURCES := \
	main.cpp \
	core/StudyManager.cpp \
	core/AIService.cpp \
	core/FileHandler.cpp \
	models/Subject.cpp \
	models/Topic.cpp \
	models/StudyPlan.cpp \
	utils/Parser.cpp

OBJECTS := $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete → ./$(TARGET)"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

debug: CXXFLAGS += -g
debug: rebuild

.PHONY: all clean rebuild run debug
