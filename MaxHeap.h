#pragma once

#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

struct Student {
    string id;
    int priority;

    Student(string id, int priority)
        : id(id), priority(priority) {}
};

class MaxHeap {
public:
    MaxHeap();

    void insert(const string& student, int priority);
    void increase_key(string id, int new_priority);
    Student extract_max();
    Student get_max() const;
    int size() const;
    void remove(const string &id);

private:
    vector<Student> data;

    void heapify_up(int index);
    void heapify_down(int index);
    int parent(int index) const;
    int left_child(int index) const;
    int right_child(int index) const;
    int find_student_index(string id) const;
};