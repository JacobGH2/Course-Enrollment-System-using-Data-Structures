#ifndef __EMANAGER
#define __EMANAGER

#include "pr_check.h"
#include "ScheduleChecker.h"
#include "MaxHeap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

using namespace std;

class EnrollmentManager {
public:
    EnrollmentManager(const string& semester, const string& prereq_file, const string& schedules_file);
    void process_enrollment_file(const string& enrollment_file);

private:
    map<string, MaxHeap> waitlists;
    map<string, ScheduleChecker> student_schedules;
    string semester;

    void load_student_schedules(const string& prereq_file, const string& schedules_file);
};

#endif