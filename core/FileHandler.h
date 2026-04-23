#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "../models/Subject.h"
#include "../models/StudyPlan.h"
using namespace std;

class FileHandler
{
private:
    string dataDirectory;
    string subjectsFile;
    string progressFile;
    string planFile;

public:
    FileHandler(const string &dataDir = "data");

    bool saveSubjects(const vector<Subject> &subjects);
    bool loadSubjects(vector<Subject> &subjects);

    bool savePlan(const StudyPlan &plan);
    bool loadPlan(StudyPlan &plan);

    bool fileExists(const string &filename);
    void initializeDataDirectory();
};

#endif
