#include <iostream>
#include "ScheduleChecker.h"
#include "pr_check.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./sch_check <prereqfile> <schedulefile>" << endl;
        return 1;
    }

    if(!pr_check(argv[1])) {
        return 0;
    }

    ScheduleChecker checker(argv[1], argv[2]);
    checker.checkSchedule();

    return 0;
}