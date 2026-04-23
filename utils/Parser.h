#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
using namespace std;

class Parser
{
public:
    static vector<string> parseStudyPlan(const string &response);

    static vector<string> parseSummaryBullets(const string &response);

    static vector<string> split(const string &text, const string &delimiter);
};

#endif
