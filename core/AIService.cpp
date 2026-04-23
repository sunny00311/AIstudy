#include "AIService.h"
#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;
string AIService::extractText(const string &response)
{
    string key = "\"text\":";
    size_t pos = response.find(key);

    if (pos == string::npos)
        return "text field not found";

    pos += key.length();

    while (pos < response.size() &&
           (response[pos] == ' ' || response[pos] == '\"'))
    {
        pos++;
    }

    string result;
    bool escape = false;

    for (size_t i = pos; i < response.size(); i++)
    {
        char c = response[i];

        if (escape)
        {
            result += c;
            escape = false;
        }
        else if (c == '\\')
        {
            escape = true; 
        }
        else if (c == '\"')
        {
            break; 
        }
        else
        {
            result += c;
        }
    }

    return result;
}

// Standalone extractText (backup)
string extractText(const string &response)
{
    string key = "\"text\":";
    size_t pos = response.find(key);

    if (pos == string::npos)
        return "text field not found";

    pos += key.length();

    // Skip spaces and quotes
    while (pos < response.size() &&
           (response[pos] == ' ' || response[pos] == '\"'))
    {
        pos++;
    }

    string result;
    bool escape = false;

    for (size_t i = pos; i < response.size(); i++)
    {
        char c = response[i];

        if (escape)
        {
            result += c;
            escape = false;
        }
        else if (c == '\\')
        {
            escape = true; // handle escaped chars
        }
        else if (c == '\"')
        {
            break; // end of string
        }
        else
        {
            result += c;
        }
    }

    return result;
}


AIService::AIService(const string &key) : apiKey(key)
{
    endpoint = "https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent";
}

string AIService::makeAPICall(const string &prompt)
{
   string API_KEY = "AIzaSyCmt5R8mZ8RKzcVbfzkbjlgQaM6kHtQSmA";

   
    string command =
        "curl -s \"https://generativelanguage.googleapis.com/v1beta/models/gemini-3-flash-preview:generateContent\" "
        "-H \"x-goog-api-key: " +
        API_KEY + "\" "
                  "-H \"Content-Type: application/json\" "
                  "-X POST "
"-d \"{\\\"contents\\\":[{\\\"parts\\\":[{\\\"text\\\":\\\"" + prompt + "\\\"}]}]}\"";

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        cerr << "Failed to run curl\n";
        return "";
    }

    char buffer[512];
    string response;

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        response += buffer;
    }

    pclose(pipe);

    string text = extractText(response);

    
    return text;
}

string AIService::generateStudyPlan(const string &subjects, int days)
{
    stringstream prompt;
    prompt << "Generate a " << days << "-day study plan for the following subjects: " << subjects
           << "\n\nFormat the response exactly as:\nDay 1: [specific topics to study]\nDay 2: [specific topics to study]\n"
           << "and so on...\n\nProvide only the day-by-day plan without any additional explanation.";

    string response = makeAPICall(prompt.str());

    // For demonstration, return mock response if API fails
    if (response.find("\"text\"") == string::npos && response.length() < 100)
    {
        stringstream mockPlan;
        mockPlan << "Day 1: Introduction to " << subjects << " - concepts and fundamentals\n";
        mockPlan << "Day 2: Deep dive into core topics\n";
        mockPlan << "Day 3: Practice problems and applications\n";
        mockPlan << "Day 4: Review and consolidation\n";
        mockPlan << "Day 5: Final revision and self-assessment\n";
        for (int i = 6; i <= days; ++i)
        {
            mockPlan << "Day " << i << ": Advanced topics and practice\n";
        }
        return mockPlan.str();
    }

    return response;
}

string AIService::explain(const string &topic)
{
    stringstream prompt;
    prompt << "Explain the topic '" << topic << "' in simple, beginner-friendly language. "
           << "Keep the explanation concise (3-4 paragraphs) and avoid technical jargon where possible.";

    string response = makeAPICall(prompt.str());

    // Mock response for demonstration
    if (response.find("\"text\"") == string::npos)
    {
        stringstream mockExplanation;
        mockExplanation << "Explanation of " << topic << ":\n\n";
        mockExplanation << "This is a fundamental concept in computer science and programming. "
                        << "It helps us understand how systems work together.\n\n";
        mockExplanation << "Key points:\n";
        mockExplanation << "1. It involves breaking down complex problems\n";
        mockExplanation << "2. It uses systematic approaches\n";
        mockExplanation << "3. It's essential for modern software development\n";
        return mockExplanation.str();
    }

    return response;
}

string AIService::summarize(const string &text)
{
    stringstream prompt;
    prompt << "Summarize the following text into 5 concise bullet points:\n\n"
           << text
           << "\n\nProvide only the 5 bullet points, numbered 1-5, without any additional text.";

    string response = makeAPICall(prompt.str());

    // Mock response for demonstration
    if (response.find("\"text\"") == string::npos)
    {
        stringstream mockSummary;
        mockSummary << "1. Main concept identified and understood\n";
        mockSummary << "2. Key details extracted from source material\n";
        mockSummary << "3. Important relationships and connections noted\n";
        mockSummary << "4. Supporting examples and evidence gathered\n";
        mockSummary << "5. Summary conclusion and key takeaways highlighted\n";
        return mockSummary.str();
    }

    return response;
}
