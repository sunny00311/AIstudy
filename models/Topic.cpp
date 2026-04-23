#include "Topic.h"
#include <iostream>
using namespace std;

Topic::Topic(string name) : name(name), completed(false) {}

string Topic::getName() const
{
    return name;
}

bool Topic::isCompleted() const
{
    return completed;
}

void Topic::setName(string n)
{
    name = n;
}

void Topic::markCompleted()
{
    completed = true;
}

void Topic::resetStatus()
{
    completed = false;
}

void Topic::display() const
{
    string status = completed ? "[✓]" : "[ ]";
    cout << "    " << status << " " << name << endl;
}
