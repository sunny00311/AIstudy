#ifndef TOPIC_H
#define TOPIC_H

#include <string>
using namespace std;

class Topic
{
private:
    string name;
    bool completed;

public:
    Topic(string name = "");

    string getName() const;
    bool isCompleted() const;

    void setName(string n);
    void markCompleted();
    void resetStatus();

    void display() const;
};

#endif
