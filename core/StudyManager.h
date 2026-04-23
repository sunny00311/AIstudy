#ifndef STUDYMANAGER_H
#define STUDYMANAGER_H

#include <vector>
#include <string>
#include "../models/Subject.h"
#include "../models/StudyPlan.h"
#include "AIService.h"
#include "FileHandler.h"
using namespace std;

class StudyManager
{
private:
    vector<Subject> subjects;
    StudyPlan currentPlan;
    AIService aiService;
    FileHandler fileHandler;

    int findSubject(const string &name);
    int findTopic(int subjectIndex, const string &topicName);

public:
    StudyManager();

    bool addSubject(const string &name);
    bool addTopic(const string &subjectName, const string &topicName);
    bool markTopicCompleted(const string &subjectName, const string &topicName);

    double getOverallProgress() const;
    void showProgress() const;

    bool generateStudyPlan(int days);
    bool explainTopic(const string &topic);
    bool summarizeNotes(const string &notes);

    void displayAllSubjects() const;
    void displayPlan() const;

    bool saveData();
    bool loadData();

    const vector<Subject> &getSubjects() const;
    const StudyPlan &getPlan() const;
};

#endif
