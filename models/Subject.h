#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <string>
#include "Topic.h"
using namespace std;

class Subject
{
private:
    string name;
    vector<Topic> topics;

public:
    Subject(string name = "");

    string getName() const;
    vector<Topic> &getTopics();
    const vector<Topic> &getTopics() const;

    void addTopic(const Topic &topic);
    int getCompletedCount() const;
    double getProgressPercentage() const;

    void display() const;
};

#endif
