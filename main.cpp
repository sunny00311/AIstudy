#include <iostream>
#include <string>
#include <limits>
#include "core/StudyManager.h"
using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

void displayMainMenu();
void handleAddSubject(StudyManager &manager);
void handleAddTopic(StudyManager &manager);
void handleMarkCompleted(StudyManager &manager);
void handleGeneratePlan(StudyManager &manager);
void handleExplainTopic(StudyManager &manager);
void handleSummarizeNotes(StudyManager &manager);
void enterToContinue();
string getInput(const string &prompt);
int getIntInput(const string &prompt);

int main()
{
    StudyManager manager;
    int choice = 0;

    cout << "\033[2J\033[1;1H";

    cout << BLUE << BOLD << "\n";
    cout << "╔══════════════════════════════════════════════════════════╗\n";
    cout << "║                                                          ║\n";
    cout << "║    🎓  AI-POWERED STUDY PLANNER & EXPLAINER   🎓        ║\n";
    cout << "║                                                          ║\n";
    cout << "║    Powered by Gemini API | C++ Console Application      ║\n";
    cout << "║                                                          ║\n";
    cout << "╚══════════════════════════════════════════════════════════╝\n"
         << RESET;
    enterToContinue();

    while (true)
    {
        displayMainMenu();
        choice = getIntInput("Enter your choice");

        switch (choice)
        {
        case 1:
            handleAddSubject(manager);
            break;

        case 2:
            manager.displayAllSubjects();
            enterToContinue();
            break;

        case 3:
            handleAddTopic(manager);
            break;

        case 4:
            handleMarkCompleted(manager);
            break;

        case 5:
            manager.showProgress();
            enterToContinue();
            break;

        case 6:
            handleGeneratePlan(manager);
            break;

        case 7:
            handleExplainTopic(manager);
            break;

        case 8:
            handleSummarizeNotes(manager);
            break;

        case 9:
            manager.displayPlan();
            enterToContinue();
            break;

        case 10:
            cout << GREEN << BOLD << "\n  Saving data and exiting...\n"
                 << RESET;
            manager.saveData();
            cout << GREEN << "  Goodbye! Keep studying! 👋\n\n"
                 << RESET;
            return 0;

        default:
            cout << RED << "  ✗ Invalid choice. Please try again.\n"
                 << RESET;
            enterToContinue();
        }
    }

    return 0;
}

void displayMainMenu()
{
    cout << "\033[2J\033[1;1H";

    cout << CYAN << BOLD << "\n╔════════════════════════════════════════════╗\n";
    cout << "║           MAIN MENU                        ║\n";
    cout << "╚════════════════════════════════════════════╝\n"
         << RESET;

    cout << CYAN << "\n  1. " << RESET << "Add a new subject\n";
    cout << CYAN << "  2. " << RESET << "Display all subjects and topics\n";
    cout << CYAN << "  3. " << RESET << "Add topic to a subject\n";
    cout << CYAN << "  4. " << RESET << "Mark topic as completed\n";
    cout << CYAN << "  5. " << RESET << "Show progress tracking\n";
    cout << CYAN << "  6. " << RESET << "Generate AI study plan\n";
    cout << CYAN << "  7. " << RESET << "Explain a topic (AI)\n";
    cout << CYAN << "  8. " << RESET << "Summarize notes (AI)\n";
    cout << CYAN << "  9. " << RESET << "View last generated plan\n";
    cout << CYAN << "  10." << RESET << " Exit\n";
    cout << CYAN << "\n────────────────────────────────────────────\n"
         << RESET;
}

void handleAddSubject(StudyManager &manager)
{
    cout << "\n";
    string name = getInput("Enter subject name");

    if (manager.addSubject(name))
    {
        cout << GREEN << "  ✓ Subject '" << name << "' added successfully!\n"
             << RESET;
    }
    else
    {
        cout << RED << "  ✗ Failed to add subject.\n"
             << RESET;
    }

    enterToContinue();
}

void handleAddTopic(StudyManager &manager)
{
    cout << "\n";
    manager.displayAllSubjects();

    string subjectName = getInput("Enter subject name");
    string topicName = getInput("Enter topic name");

    if (manager.addTopic(subjectName, topicName))
    {
        cout << GREEN << "  ✓ Topic '" << topicName << "' added to '" << subjectName << "'!\n"
             << RESET;
    }
    else
    {
        cout << RED << "  ✗ Failed to add topic.\n"
             << RESET;
    }

    enterToContinue();
}

void handleMarkCompleted(StudyManager &manager)
{
    cout << "\n";
    manager.displayAllSubjects();

    string subjectName = getInput("Enter subject name");
    string topicName = getInput("Enter topic name");

    if (manager.markTopicCompleted(subjectName, topicName))
    {
        cout << GREEN << "  ✓ Topic marked as completed!\n"
             << RESET;
    }
    else
    {
        cout << RED << "  ✗ Failed to mark topic as completed.\n"
             << RESET;
    }

    enterToContinue();
}

void handleGeneratePlan(StudyManager &manager)
{
    cout << "\n";
    cout << YELLOW << "  Make sure you have added subjects first!\n"
         << RESET;

    int days = getIntInput("Enter number of study days");

    if (manager.generateStudyPlan(days))
    {
        cout << GREEN << "  ✓ Study plan generated successfully!\n"
             << RESET;
        manager.displayPlan();
    }
    else
    {
        cout << RED << "  ✗ Failed to generate study plan.\n"
             << RESET;
    }

    enterToContinue();
}

void handleExplainTopic(StudyManager &manager)
{
    cout << "\n";
    string topic = getInput("Enter topic name to explain");

    manager.explainTopic(topic);

    enterToContinue();
}

void handleSummarizeNotes(StudyManager &manager)
{
    cout << "\n";
    cout << YELLOW << "  Enter your notes (press Enter twice to finish):\n"
         << RESET;

    string notes;
    string line;
    int emptyLineCount = 0;

    while (getline(cin, line))
    {
        if (line.empty())
        {
            emptyLineCount++;
            if (emptyLineCount >= 2)
                break;
        }
        else
        {
            emptyLineCount = 0;
        }
        notes += line + "\n";
    }

    if (!notes.empty())
    {
        manager.summarizeNotes(notes);
    }
    else
    {
        cout << RED << "  ✗ No notes provided.\n"
             << RESET;
    }

    enterToContinue();
}

void enterToContinue()
{
    cout << "\n"
         << YELLOW << "Press Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string getInput(const string &prompt)
{
    cout << YELLOW << "  " << prompt << ": " << RESET;
    string input;
    getline(cin, input);
    return input;
}

int getIntInput(const string &prompt)
{
    cout << YELLOW << "  " << prompt << ": " << RESET;
    int value;

    while (!(cin >> value))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << RED << "  ✗ Invalid input. Please enter a number.\n"
             << RESET;
        cout << YELLOW << "  " << prompt << ": " << RESET;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}
