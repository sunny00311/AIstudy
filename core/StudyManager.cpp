#include "StudyManager.h"
#include <iostream>
#include <iomanip>
using namespace std;

StudyManager::StudyManager() : aiService("YOUR_GEMINI_API_KEY"), fileHandler("data")
{
    loadData();
}

int StudyManager::findSubject(const string &name)
{
    for (size_t i = 0; i < subjects.size(); ++i)
    {
        if (subjects[i].getName() == name)
        {
            return i;
        }
    }
    return -1;
}

int StudyManager::findTopic(int subjectIndex, const string &topicName)
{
    if (subjectIndex < 0 || subjectIndex >= (int)subjects.size())
    {
        return -1;
    }

    auto &topics = subjects[subjectIndex].getTopics();
    for (size_t i = 0; i < topics.size(); ++i)
    {
        if (topics[i].getName() == topicName)
        {
            return i;
        }
    }
    return -1;
}

bool StudyManager::addSubject(const string &name)
{
    if (name.empty())
    {
        cout << "Subject name cannot be empty." << endl;
        return false;
    }

    if (findSubject(name) != -1)
    {
        cout << "Subject '" << name << "' already exists." << endl;
        return false;
    }

    subjects.push_back(Subject(name));
    saveData();
    return true;
}

bool StudyManager::addTopic(const string &subjectName, const string &topicName)
{
    if (topicName.empty())
    {
        cout << "Topic name cannot be empty." << endl;
        return false;
    }

    int index = findSubject(subjectName);
    if (index == -1)
    {
        cout << "Subject '" << subjectName << "' not found." << endl;
        return false;
    }

    if (findTopic(index, topicName) != -1)
    {
        cout << "Topic '" << topicName << "' already exists in this subject." << endl;
        return false;
    }

    subjects[index].addTopic(Topic(topicName));
    saveData();
    return true;
}

bool StudyManager::markTopicCompleted(const string &subjectName, const string &topicName)
{
    int subIndex = findSubject(subjectName);
    if (subIndex == -1)
    {
        cout << "Subject '" << subjectName << "' not found." << endl;
        return false;
    }

    int topIndex = findTopic(subIndex, topicName);
    if (topIndex == -1)
    {
        cout << "Topic '" << topicName << "' not found in subject '" << subjectName << "'." << endl;
        return false;
    }

    subjects[subIndex].getTopics()[topIndex].markCompleted();
    saveData();
    return true;
}

double StudyManager::getOverallProgress() const
{
    if (subjects.empty())
    {
        return 0.0;
    }

    double totalProgress = 0.0;
    for (const auto &subject : subjects)
    {
        totalProgress += subject.getProgressPercentage();
    }

    return totalProgress / subjects.size();
}

void StudyManager::showProgress() const
{
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║      PROGRESS TRACKING                 ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";

    if (subjects.empty())
    {
        cout << "  No subjects added yet.\n\n";
        return;
    }

    cout << "  Overall Progress: " << fixed << setprecision(1) << getOverallProgress() << "%\n";
    cout << "  ────────────────────────────────────────\n\n";

    for (const auto &subject : subjects)
    {
        int completed = subject.getCompletedCount();
        int total = subject.getTopics().size();
        double percentage = subject.getProgressPercentage();

        cout << "  " << subject.getName() << ": " << completed << "/" << total
             << " (" << fixed << setprecision(1) << percentage << "%)\n";
    }
    cout << "\n";
}

bool StudyManager::generateStudyPlan(int days)
{
    if (days <= 0)
    {
        cout << "Number of days must be positive." << endl;
        return false;
    }

    if (subjects.empty())
    {
        cout << "Add at least one subject before generating a plan." << endl;
        return false;
    }

    string subjectsList;
    for (size_t i = 0; i < subjects.size(); ++i)
    {
        subjectsList += subjects[i].getName();
        if (i < subjects.size() - 1)
        {
            subjectsList += ", ";
        }
    }

    cout << "\nGenerating study plan... Please wait.\n";

    string planResponse = aiService.generateStudyPlan(subjectsList, days);

    currentPlan.clearPlan();

    stringstream ss(planResponse);
    string line;

    while (getline(ss, line))
    {
        if (!line.empty())
        {
            if (line.find("Day ") != string::npos || line.find("day ") != string::npos)
            {
                currentPlan.addDay(line);
            }
        }
    }

    if (currentPlan.isEmpty())
    {
        stringstream ss2(planResponse);
        while (getline(ss2, line))
        {
            if (!line.empty())
            {
                currentPlan.addDay(line);
            }
        }
    }

    fileHandler.savePlan(currentPlan);
    return true;
}

bool StudyManager::explainTopic(const string &topic)
{
    if (topic.empty())
    {
        cout << "Topic name cannot be empty." << endl;
        return false;
    }

    cout << "\nFetching explanation for '" << topic << "'... Please wait.\n";

    string explanation = aiService.explain(topic);

    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║      TOPIC EXPLANATION                 ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << "Topic: " << topic << "\n\n";
    cout << explanation << "\n";

    return true;
}

bool StudyManager::summarizeNotes(const string &notes)
{
    if (notes.empty())
    {
        cout << "Notes cannot be empty." << endl;
        return false;
    }

    cout << "\nSummarizing notes... Please wait.\n";

    string summary = aiService.summarize(notes);

    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║      NOTES SUMMARY                     ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";
    cout << summary << "\n";

    return true;
}

void StudyManager::displayAllSubjects() const
{
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║      ALL SUBJECTS AND TOPICS           ║\n";
    cout << "╚════════════════════════════════════════╝\n";

    if (subjects.empty())
    {
        cout << "\n  (No subjects added yet)\n\n";
        return;
    }

    for (const auto &subject : subjects)
    {
        subject.display();
    }
    cout << "\n";
}

void StudyManager::displayPlan() const
{
    const_cast<StudyPlan &>(currentPlan).display();
}

bool StudyManager::saveData()
{
    return fileHandler.saveSubjects(subjects);
}

bool StudyManager::loadData()
{
    return fileHandler.loadSubjects(subjects);
}

const vector<Subject> &StudyManager::getSubjects() const
{
    return subjects;
}

const StudyPlan &StudyManager::getPlan() const
{
    return currentPlan;
}
