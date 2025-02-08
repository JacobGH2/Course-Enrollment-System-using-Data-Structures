#include "EnrollmentManager.h"

EnrollmentManager::EnrollmentManager(const string &semester, const string &prereq_file, const string &schedule_file) {
    this->semester = semester;
    if (!pr_check(prereq_file)) {
        throw(std::invalid_argument("invalid prerequisite file"));
    }

    ifstream schedules(schedule_file);
    string line;
    while (getline(schedules, line)) {
        istringstream iss(line);
        string id;
        string schedule_file;
        iss >> id >> schedule_file;

        // changed to not use student_schedules map (wasn't used outside of here and commented out function)
        ScheduleChecker schedule_checker(prereq_file ,schedule_file);
        if (!schedule_checker.checkSchedule()) {
            throw(std::invalid_argument("invalid schedule file"));
        } 
    }
}

void EnrollmentManager::process_enrollment_file(const string& enrollment_file) {
    ifstream file(enrollment_file);
    if (!file.is_open()) {
        cerr << "Failed to open " << enrollment_file << "." << endl;
        return;
    }

    string line;
    string current_course;
    while (getline(file, line)) {
        istringstream iss(line);
        string command;
        iss >> command;

        if (command == "newlist") {
            iss >> current_course;
            waitlists[current_course] = MaxHeap();
        } else if (command == "add") {
            string bnumber, course;
            int priority;
            iss >> bnumber >> course >> priority;

            waitlists[course].insert(bnumber, priority);
        } else if (command == "promote") {
            string bnumber, course;
            int priority;
            iss >> bnumber >> course >> priority;

            waitlists[course].increase_key(bnumber, priority);
        } else if (command == "enroll") {
            iss >> current_course;
            string enrolled_student = waitlists[current_course].extract_max().id;
            
            if (!enrolled_student.empty()) {
                cout << "Enrolling student " << enrolled_student << " in course " << current_course << endl;
            }

            for (auto& entry : waitlists) {
                
                entry.second.remove(enrolled_student);
            }
        }
    }
}

/*void EnrollmentManager::load_student_schedules(const string& prereq_file, const string& schedules_file) {
    ifstream file(schedules_file);
    if (!file.is_open()) {
        cerr << "Failed to open " << schedules_file << "." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string id, schedule_file;
        iss >> id >> schedule_file;

        ScheduleChecker schedule_checker(prereq_file ,schedule_file);
        student_schedules[id] = schedule_checker;
    }
} */