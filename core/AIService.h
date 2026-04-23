#ifndef AISERVICE_H
#define AISERVICE_H

#include <string>

using namespace std;

class AIService
{
private:
    string apiKey;
    string endpoint;

    string extractText(const string &response);
    string makeAPICall(const string &prompt);

public:
    AIService(const string &key = "YOUR_GEMINI_API_KEY");

    string generateStudyPlan(const string &subjects, int days);
    string explain(const string &topic);
    string summarize(const string &text);
};

#endif
