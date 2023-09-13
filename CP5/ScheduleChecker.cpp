#include "ScheduleChecker.h"

ScheduleChecker::ScheduleChecker(const string &prereqFile, const string &scheduleFile) {
    ifstream prereqFileStream(prereqFile);
    ifstream scheduleFileStream(scheduleFile);
    string line;

    // Read the prerequisites
    while (getline(prereqFileStream, line)) {
        istringstream inputFile(line);
        string course, prereq;
        inputFile >> course >> prereq;
        prerequisites[course] = prereq;
    }

    // Read the schedule
    while (getline(scheduleFileStream, line)) {
        istringstream inputFile(line);
        string course, semester;
        inputFile >> course >> semester;
        schedule.emplace_back(course, semester);
    }

    // Sort the schedule by year and semester
    sort(schedule.begin(), schedule.end(), [](const auto &a, const auto &b) {
        string semesterOrder = "SpringSummerFall";
        return (a.second.substr(0, 4) < b.second.substr(0, 4)) ||
                (a.second.substr(0, 4) == b.second.substr(0, 4) &&
                semesterOrder.find(a.second.substr(4)) < semesterOrder.find(b.second.substr(4)));
    });
}

// Reads new prerequisites and schedule files
void ScheduleChecker::loadFiles(const string &prereqFile, const string &scheduleFile) {
    prerequisites.clear();
    takenCourses.clear();
    semesterCounts.clear();
    schedule.clear();

    ifstream prereqFileStream(prereqFile);
    ifstream scheduleFileStream(scheduleFile);
    string line;

    // Read the prerequisites
    while (getline(prereqFileStream, line)) {
        istringstream inputFile(line);
        string course, prereq;
        inputFile >> course >> prereq;
        prerequisites[course] = prereq;
    }

    // Read the schedule
    while (getline(scheduleFileStream, line)) {
        istringstream inputFile(line);
        string course, semester;
        inputFile >> course >> semester;
        schedule.emplace_back(course, semester);
    }

    // Sort the schedule by year and semester
    sort(schedule.begin(), schedule.end(), [](const auto &a, const auto &b) {
        string semesterOrder = "SpringSummerFall";
        return (a.second.substr(0, 4) < b.second.substr(0, 4)) ||
                (a.second.substr(0, 4) == b.second.substr(0, 4) &&
                semesterOrder.find(a.second.substr(4)) < semesterOrder.find(b.second.substr(4)));
    });
}

// Checks if a course was taken in the previous semesters
bool ScheduleChecker::checkDuplicateCourses(const string &course) {
    if (takenCourses.count(course)) {
        cout << "Error: Schedule includes the same course more than once." << endl;
        return true;
    }
    takenCourses.insert(course);
    return false;
}

// Checks if a there are more than 3 courses in a semester
bool ScheduleChecker::checkMaxCoursesPerSemester(const string &semester) {
    semesterCounts[semester]++;
    if (semesterCounts[semester] > 3) {
        cout << "Error: Schedule proposes too many courses in a semester." << endl;
        return true;
    }
    return false;
}

// Checks if a course is already taken
bool ScheduleChecker::checkPrerequisites(const string &course) {
    if (prerequisites.count(course)) {
        string prereq = prerequisites[course];
        if (!takenCourses.count(prereq)) {
            cout << "Error: Schedule proposes to take a course before its prerequisite." << endl;
            return true;
        }
    }
    return false;
}

// Checks for errors in the schedule, utlitizes above functions
bool ScheduleChecker::checkSchedule() {
    // Check if the schedule is valid
    for (const auto &[course, semester] : schedule) {
        if (checkDuplicateCourses(course) || checkMaxCoursesPerSemester(semester) || checkPrerequisites(course)) {
            // REMOVE RIGHT AFTER
            cout << "Schedule not valid." << endl;
            return false;
        }
    }

    cout << "Schedule is valid." << endl;
    return true;
}

// Constructor needed for map [] operands to compile, will not be called
ScheduleChecker::ScheduleChecker() {

}