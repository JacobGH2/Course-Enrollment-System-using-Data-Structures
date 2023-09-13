Group 29

Jacob Helhoski jhelhos1 |
Wilson Yang wyang53 |
Ira Cheng icheng4

My implementation of the prereq checker uses two graphs. In one, the adjacency list shows a courses prerequisites. In the other, the adjacency list show courses that the course is a prerequisite FOR. This helps in DFS, where I need to find vertices with no "parents", but also find the "children" of those vertices.

Disable printing out of prereq checker graphs by commenting out lines around line 152 in pr_check.cpp.
