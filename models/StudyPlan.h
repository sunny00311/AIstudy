#ifndef STUDYPLAN_H
#define STUDYPLAN_H

#include <vector>
#include <string>
using namespace std;

class Content
{
public:
    virtual ~Content() = default;
    virtual void display() = 0;
};

class StudyPlan : public Content
{
private:
    vector<string> dailyPlan;
    string generatedDate;

public:
    StudyPlan();

    const vector<string> &getDailyPlan() const;
    string getGeneratedDate() const;

    void addDay(const string &day);
    void clearPlan();
    bool isEmpty() const;

    void display() override;
};

#endif
