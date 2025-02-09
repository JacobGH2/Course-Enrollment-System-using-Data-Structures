Project completed by Jacob Helhoski, Wilson Yang, and Ira Cheng

## Functionality

This project uses data structures to validate course schedules.

The provided makefile can compile and run the three test programs.

1.  ```pr_test``` - Valiidate prerequisites in a course catalog. Graphs are stored in an adjacency list representation, and a depth-first search is performed, finding any circular dependencies, and invalidating the schedule if one is found.
    
2.   ```sch_test``` - Validate a particular schedule. Detects courses being taken multiple times, exceeding the semester limit, or lacking prerequisites. Uses a hashmap-like structure to performs checks.
   
3.  ```waitlist_test``` - Processes enrollment instructions for multiple students. Creates waitlists for courses, implemented as a priority queue/max-heap.

# Notes

My implementation of the prereq checker uses two graphs. In one, the adjacency list shows a courses prerequisites. In the other, the adjacency list show courses that the course is a prerequisite FOR. This helps in DFS, where I need to find vertices with no "parents", but also find the "children" of those vertices.

Disable printing out of prereq checker graphs by commenting out lines around line 152 in pr_check.cpp.
