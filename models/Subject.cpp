#include "Subject.h"
#include <iostream>
#include <iomanip>
using namespace std;

Subject::Subject(string name) : name(name) {}

string Subject::getName() const
{
    return name;
}

vector<Topic> &Subject::getTopics()
{
    return topics;
}

const vector<Topic> &Subject::getTopics() const
{
    return topics;
}

void Subject::addTopic(const Topic &topic)
{
    topics.push_back(topic);
}

int Subject::getCompletedCount() const
{
    int count = 0;
    for (const auto &topic : topics)
    {
        if (topic.isCompleted())
        {
            count++;
        }
    }
    return count;
}

double Subject::getProgressPercentage() const
{
    if (topics.empty())
    {
        return 0.0;
    }
    return (static_cast<double>(getCompletedCount()) / topics.size()) * 100.0;
}

void Subject::display() const
{
    cout << "\n  Subject: " << name << endl;
    cout << "  Progress: " << fixed << setprecision(1) << getProgressPercentage() << "%" << endl;
    cout << "  Topics:" << endl;

    if (topics.empty())
    {
        cout << "    (No topics added yet)" << endl;
    }
    else
    {
        for (const auto &topic : topics)
        {
            topic.display();
        }
    }
}
