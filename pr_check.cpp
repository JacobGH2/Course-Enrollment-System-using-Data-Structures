#include "pr_check.h"

using namespace std;


string getKey(int value, const map<string, int> &map) {
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->second == value) {
            return it->first;
        }
    }
    return NULL;
}

void printAdjList(const vector<list<int>> &list, const map<string, int> &map, int dir) {
    for (int i = 0; i < list.size(); i++) {
        cout << "Vertex: " << getKey(i, map);
        if (dir == 0) {
            cout << "  Prereqs: ";
        } else {
            cout << "  Prereq for: ";
        }
        for (auto it = list.at(i).begin(); it != list.at(i).end(); it++) {
            cout << "  " << getKey(*it, map);
        }
        cout << endl;
    }
}

int DFS(int sourceVertex, deque<int> &stack, vector<int> &graySet, vector<int> &blackSet, map<string, int> &map, vector<list<int>> &adjVecForward) {
    
    stack.push_front(sourceVertex);
    
    while (!stack.empty()) {
        int currentV = stack.front();   // get most recent vertex off of stack
        stack.pop_front();

        if (find(graySet.begin(), graySet.end(), currentV) == graySet.end() && find(blackSet.begin(), blackSet.end(), currentV) == blackSet.end()) {
            graySet.push_back(currentV);                // if the vertex hasn't been "discovered" before, add it to the gray, discovered set
        }
        
        // add successor courses to stack if undiscovered white, ignore if black, and state circ. dependency if gray
        int numWhite = 0;
        for (auto it = adjVecForward.at(currentV).begin(); it != adjVecForward.at(currentV).end(); it++) {
            // check is vertex has been "discovered"
            if (find(graySet.begin(), graySet.end(), *it) != graySet.end()) {
                cout << "Prerequisites invalid: Circular dependency from " << getKey(currentV, map) << " -> " << getKey(*it, map) << endl;
                return 1;
            } 
            if (find(blackSet.begin(), blackSet.end(), *it) == blackSet.end()) {
                numWhite++;         // increase every time a new undiscovered vertex is found
                stack.push_front(currentV);
                stack.push_front(*it);
            }
        }
        
        if (numWhite == 0) {        // now, if no new vertices, the vertex has "reached the end of its path", and it can be marked as completed (black)
            blackSet.push_back(currentV);
            for (int i = 0; i < graySet.size(); i++) {      // removed from gray set as well
                if (graySet.at(i) == currentV) {
                    graySet.erase(graySet.begin() + i);
                    break;
                }                               // this procedure is called on every vertex in the graph in the pr_check function through a for-loop
            }
        }
    }
    
    
    return 0;
}

int BFS(int source, int max_length, vector<list<int>> &adjVecForward) {
    int pathSizes[adjVecForward.size()]; // array of path sizes (indexed by mapping)
    pathSizes[source] = 0;
    queue<int> frontierQueue;
    frontierQueue.push(source);
    vector<int> discoveredSet;
    discoveredSet.push_back(source);

    int currentV = 0;
    while (!frontierQueue.empty()) {
        currentV = frontierQueue.front();
        frontierQueue.pop();
        for (auto it = adjVecForward.at(currentV).begin(); it != adjVecForward.at(currentV).end(); it++) {
            if (find(discoveredSet.begin(), discoveredSet.end(), *it) == discoveredSet.end()) {
                frontierQueue.push(*it);
                discoveredSet.push_back(*it);
                pathSizes[*it] = pathSizes[currentV] + 1;  // update pathSizes
                if (pathSizes[*it] > max_length) {
                    cout << "Prerequisites invalid: course sequence greater than 6" << endl;
                    return 1;
                }
            }
        }
    }
    
    return 0;
}

int pr_check(string inputFile) {
    vector<list<int>> adjVecForward;
    vector<list<int>> adjVecBackward;
    map<string, int> map;
    
    int nextCourseIndex = 0;
    
    ifstream inFile;
    inFile.open(inputFile);
    string line;
    // create graph from file
    while (getline(inFile, line)) {
        string course;
        vector<string> prereqs;
        istringstream iss(line);
        iss >> course;
        string temp;
        while (!iss.eof()) {
            iss >> temp;
            prereqs.push_back(temp);
        }

        // course
        if (map.find(course) == map.end()) {
            map.insert(pair<string, int>(course, nextCourseIndex));
            nextCourseIndex++;
            
            list<int> newList;
            adjVecBackward.push_back(newList);
            adjVecForward.push_back(newList);
        }
        // prereqs
        for(int i = 0; i < prereqs.size(); i++) {
            
            string currPrereq = prereqs.at(i);
            // add prereq to map/vec if not already in them
            if (map.find(currPrereq) == map.end()) {
                map.insert(pair<string, int>(currPrereq, nextCourseIndex));
                nextCourseIndex++;

                list<int> newList;
                adjVecBackward.push_back(newList);
                adjVecForward.push_back(newList);
            }
            adjVecForward.at(map[currPrereq]).push_back(map[course]);
            // add course as adjacent to prereqs
            adjVecBackward.at(map[course]).push_back(map[currPrereq]);
        }
    }

    // now have adjacency list of ints mapped to by courses
    
    printAdjList(adjVecBackward, map, 0);           // COMMENT OUT THESE FOUR LINES TO DISABLE PRINTING
    cout << endl;
    printAdjList(adjVecForward, map, 1);
    cout << endl;
    
    // find circular dependencies (DFS)
    deque<int> stack;
    vector<int> graySet;
    vector<int> blackSet;
    
    for (int i = 0; i < adjVecBackward.size(); i++) {
        if (adjVecBackward.at(i).size() == 0) {
            goto validCourse;
        }
    }
    cout << "Prerequisites invalid: all courses have prerequisites" << endl;
    goto invalid;
    
    validCourse:
    for (int i = 0; i < adjVecBackward.size(); i++) {
        int foundDep = DFS(i, stack, graySet, blackSet, map, adjVecForward);
        if (foundDep) {goto invalid;}
    }


    
    // BST length test
    
    for (int i = 0; i < adjVecBackward.size(); i++) {
        if (adjVecBackward.at(i).size() == 0) {
            if (BFS(i, 5, adjVecForward)) {
                goto invalid;
            }
        }
    }
    
    cout << "Prerequisites valid: no circular dependencies or sequences greater than 6 semesters" << endl;
    return 1;

    invalid:
    
    return 0;
}