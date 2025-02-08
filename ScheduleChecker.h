#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class ScheduleChecker {
public:
    ScheduleChecker(const string &prereqFile, const string &scheduleFile);
    ScheduleChecker(); // added because map requires default constructor for [] operands, should never be called
    void loadFiles(const std::string &prereqFile, const std::string &scheduleFile);
    bool checkSchedule();

private:
    bool checkDuplicateCourses(const string &course);
    bool checkMaxCoursesPerSemester(const string &semester);
    bool checkPrerequisites(const string &course);
    
    unordered_map<string, string> prerequisites;
    unordered_map<string, int> semesterCounts;
    unordered_set<string> takenCourses;
    vector<pair<string, string>> schedule;
};