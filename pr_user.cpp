#include "pr_check.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << "Usage: ./pr_check <prereqfile>" << endl;
    }
    
    pr_check(argv[1]);
    
    return 0;
}