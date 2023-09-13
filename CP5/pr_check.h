#ifndef __PR_CHECK
#define __PR_CHECK

#include <vector>
#include <list>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>
#include <iterator>
#include <algorithm>
#include <deque>
#include <queue>

using namespace std;

string getKey(int value, const map<string, int> &map);

void printAdjList(const vector<list<int>> &list, const map<string, int> &map, int dir);

int DFS(int sourceVertex, deque<int> &stack, vector<int> &graySet, vector<int> &blackSet, map<string, int> &map, vector<list<int>> &adjVecForward);

int BFS(int source, int max_length, vector<list<int>> &adjVecForward);

int pr_check(string inputFile);

#endif