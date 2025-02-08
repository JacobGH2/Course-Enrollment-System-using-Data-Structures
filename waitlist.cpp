#include "pr_check.h"
#include "EnrollmentManager.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: ./waitlist <semester> <prereqfile> <schedsfile> <enrollmentfile>" << std::endl;
        return 1;
    }

    string semester = argv[1];
    string prereq_file = argv[2];
    string schedules_file = argv[3];
    string enrollment_file = argv[4];

    try {
        EnrollmentManager manager(semester, prereq_file, schedules_file);
        manager.process_enrollment_file(enrollment_file);
    } catch (const runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}