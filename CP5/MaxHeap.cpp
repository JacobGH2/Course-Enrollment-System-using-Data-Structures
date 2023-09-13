#include "MaxHeap.h"

MaxHeap::MaxHeap() {}

void MaxHeap::insert(const string &id, int priority) {
    // Create a Student struct with the provided ID and priority
    Student student(id, priority);
    
    // Insert the student into the heap
    data.push_back(student);
    heapify_up(data.size() - 1);
}


void MaxHeap::increase_key(string id, int new_priority) {
    int index = find_student_index(id);
    if (index != -1) {
        data[index].priority += new_priority;
        heapify_up(index);
    }
}

Student MaxHeap::extract_max() {
    if (data.empty()) {
        throw runtime_error("Heap is empty.");
    }

    Student max = data[0];
    data[0] = data.back();
    data.pop_back();
    heapify_down(0);

    return max;
}

Student MaxHeap::get_max() const {
    if (data.empty()) {
        throw runtime_error("Heap is empty.");
    }
    return data[0];
}

int MaxHeap::size() const {
    return data.size();
}

void MaxHeap::heapify_up(int index) {
    while (index > 0 && data[parent(index)].priority < data[index].priority) {
        swap(data[parent(index)], data[index]);
        index = parent(index);
    }
}

void MaxHeap::heapify_down(int index) {
    int max_index = index;
    int left = left_child(index);
    int right = right_child(index);

    if (left < size() && data[left].priority > data[max_index].priority) {
        max_index = left;
    }

    if (right < size() && data[right].priority > data[max_index].priority) {
        max_index = right;
    }

    if (index != max_index) {
        swap(data[index], data[max_index]);
        heapify_down(max_index);
    }
}

int MaxHeap::parent(int index) const {
    return (index - 1) / 2;
}

int MaxHeap::left_child(int index) const {
    return 2 * index + 1;
}

int MaxHeap::right_child(int index) const {
    return 2 * index + 2;
}

int MaxHeap::find_student_index(string id) const {
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].id == id) {
            return i;
        }
    }
    return -1;
}

void MaxHeap::remove(const string &id) {
    int index = -1;
    for (int i = 0; i < data.size(); i++) {
        if (data[i].id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        return; // Student not found in the heap
    }

    // Swap the element to be removed with the last element
    swap(data[index], data[data.size() - 1]);

    // Remove the last element
    data.pop_back();

    // Rebalance the heap by calling heapify_down and heapify_up on the swapped index
    heapify_down(index);
    heapify_up(index);
}