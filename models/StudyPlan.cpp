#include "StudyPlan.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

StudyPlan::StudyPlan()
{
    time_t now = time(0);
    tm *timeinfo = localtime(&now);

    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    generatedDate = string(buffer);
}

const vector<string> &StudyPlan::getDailyPlan() const
{
    return dailyPlan;
}

string StudyPlan::getGeneratedDate() const
{
    return generatedDate;
}

void StudyPlan::addDay(const string &day)
{
    dailyPlan.push_back(day);
}

void StudyPlan::clearPlan()
{
    dailyPlan.clear();
}

bool StudyPlan::isEmpty() const
{
    return dailyPlan.empty();
}

void StudyPlan::display()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════╗\n";
    cout << "║      GENERATED STUDY PLAN              ║\n";
    cout << "╚════════════════════════════════════════╝\n\n";

    if (isEmpty())
    {
        cout << "  No study plan generated yet.\n";
        return;
    }

    cout << "  Generated: " << generatedDate << "\n\n";

    for (size_t i = 0; i < dailyPlan.size(); ++i)
    {
        cout << "  " << dailyPlan[i] << "\n";
    }
    cout << "\n";
}
