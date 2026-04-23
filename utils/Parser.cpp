#include "Parser.h"
using namespace std;

vector<string> Parser::split(const string &text, const string &delimiter)
{
    vector<string> result;
    size_t start = 0;
    size_t end = text.find(delimiter);

    while (end != string::npos)
    {
        result.push_back(text.substr(start, end - start));
        start = end + delimiter.length();
        end = text.find(delimiter, start);
    }

    result.push_back(text.substr(start));
    return result;
}

vector<string> Parser::parseStudyPlan(const string &response)
{
    vector<string> plan;
    vector<string> lines = split(response, "\n");

    for (const auto &line : lines)
    {
        if (line.find("Day ") != string::npos || line.find("day ") != string::npos)
        {
            if (!line.empty())
            {
                plan.push_back(line);
            }
        }
    }

    return plan;
}

vector<string> Parser::parseSummaryBullets(const string &response)
{
    vector<string> bullets;
    vector<string> lines = split(response, "\n");

    for (const auto &line : lines)
    {
        if (!line.empty() && (isdigit(line[0]) || line[0] == '-' || line[0] == '*'))
        {
            bullets.push_back(line);
        }
    }

    return bullets;
}
