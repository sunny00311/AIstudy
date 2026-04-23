#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
using namespace std;

FileHandler::FileHandler(const string &dataDir) : dataDirectory(dataDir)
{
    subjectsFile = dataDirectory + "/subjects.txt";
    progressFile = dataDirectory + "/progress.txt";
    planFile = dataDirectory + "/plan.txt";
    initializeDataDirectory();
}

void FileHandler::initializeDataDirectory()
{
#ifdef _WIN32
    mkdir(dataDirectory.c_str());
#else
    mkdir(dataDirectory.c_str(), 0755);
#endif
}

bool FileHandler::fileExists(const string &filename)
{
    ifstream file(filename);
    return file.good();
}

bool FileHandler::saveSubjects(const vector<Subject> &subjects)
{
    ofstream file(subjectsFile);

    if (!file.is_open())
    {
        cerr << "Error: Could not open " << subjectsFile << " for writing" << endl;
        return false;
    }

    for (const auto &subject : subjects)
    {
        file << "[SUBJECT]" << subject.getName() << endl;

        for (const auto &topic : subject.getTopics())
        {
            file << "TOPIC|" << topic.getName() << "|"
                 << (topic.isCompleted() ? "1" : "0") << endl;
        }
    }

    file.close();
    return true;
}

bool FileHandler::loadSubjects(vector<Subject> &subjects)
{
    ifstream file(subjectsFile);

    if (!file.is_open())
    {
        return true;
    }

    string line;
    Subject *currentSubject = nullptr;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        if (line.find("[SUBJECT]") == 0)
        {
            if (currentSubject != nullptr)
            {
                subjects.push_back(*currentSubject);
            }
            string subjectName = line.substr(9);
            currentSubject = new Subject(subjectName);
        }
        else if (line.find("TOPIC|") == 0 && currentSubject != nullptr)
        {
            size_t firstPipe = line.find('|');
            size_t secondPipe = line.find('|', firstPipe + 1);

            if (firstPipe != string::npos && secondPipe != string::npos)
            {
                string topicName = line.substr(firstPipe + 1, secondPipe - firstPipe - 1);
                bool completed = stoi(line.substr(secondPipe + 1)) == 1;

                Topic t(topicName);
                if (completed)
                {
                    t.markCompleted();
                }
                currentSubject->addTopic(t);
            }
        }
    }

    if (currentSubject != nullptr)
    {
        subjects.push_back(*currentSubject);
        delete currentSubject;
    }

    file.close();
    return true;
}

bool FileHandler::savePlan(const StudyPlan &plan)
{
    ofstream file(planFile);

    if (!file.is_open())
    {
        cerr << "Error: Could not open " << planFile << " for writing" << endl;
        return false;
    }

    file << "GENERATED: " << plan.getGeneratedDate() << endl;
    file << "---" << endl;

    for (const auto &day : plan.getDailyPlan())
    {
        file << day << endl;
    }

    file.close();
    return true;
}

bool FileHandler::loadPlan(StudyPlan &plan)
{
    ifstream file(planFile);

    if (!file.is_open())
    {
        return true;
    }

    string line;
    bool skipHeader = false;

    while (getline(file, line))
    {
        if (line.find("GENERATED:") == 0 || line == "---" || line.empty())
        {
            skipHeader = true;
            continue;
        }

        if (!line.empty())
        {
            plan.addDay(line);
        }
    }

    file.close();
    return true;
}
