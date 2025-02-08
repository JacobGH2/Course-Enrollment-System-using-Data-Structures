OBJ = obj
CFLAGS = --std=c++17

# tests

all_tests: pr_test sch_test waitlist_test

pr_test: pr_check
	./pr_check testFiles/prereq1.txt

sch_test: sch_check
	./sch_check testFiles/prereq1.txt testFiles/schedule1.txt

waitlist_test: waitlist
	./waitlist 2023Fall testFiles/prereq1.txt testFiles/schedule1.txt testFiles/enroll1.txt

# pr_check targets
pr_check: ${OBJ}/pr_user.o ${OBJ}/pr_check.o
	g++ ${CFLAGS} ${OBJ}/pr_user.o  ${OBJ}/pr_check.o -o $@ -g

${OBJ}/pr_user.o: pr_user.cpp
	g++ -c  ${CFLAGS} pr_user.cpp -o $@ -g

${OBJ}/pr_check.o: pr_check.cpp pr_check.h
	g++ -c  ${CFLAGS} pr_check.cpp -o $@ -g

debug pr: pr_check
	gdb pr_check

# sch_check targets

sch_check: ${OBJ}/sch_check.o ${OBJ}/ScheduleChecker.o ${OBJ}/pr_check.o
	g++ ${CFLAGS} ${OBJ}/sch_check.o ${OBJ}/ScheduleChecker.o ${OBJ}/pr_check.o -o $@ -g

${OBJ}/sch_check.o: sch_check.cpp
	g++ -c ${CFLAGS} sch_check.cpp -o $@ -g

${OBJ}/ScheduleChecker.o: ScheduleChecker.cpp ScheduleChecker.h
	g++ -c ${CFLAGS} ScheduleChecker.cpp -o $@ -g

debug_sch_check: sch_check
	gdb sch_check

# waitlist targets

waitlist: ${OBJ}/waitlist.o ${OBJ}/ScheduleChecker.o ${OBJ}/pr_check.o ${OBJ}/EnrollmentManager.o ${OBJ}/MaxHeap.o
	g++ ${CFLAGS} ${OBJ}/waitlist.o ${OBJ}/ScheduleChecker.o ${OBJ}/pr_check.o ${OBJ}/EnrollmentManager.o ${OBJ}/MaxHeap.o -o $@ -g

${OBJ}/waitlist.o: waitlist.cpp
	g++ -c ${CFLAGS} waitlist.cpp -o $@ -g

${OBJ}/EnrollmentManager.o: EnrollmentManager.cpp EnrollmentManager.h pr_check.h ScheduleChecker.h MaxHeap.h
	g++ -c ${CFLAGS} EnrollmentManager.cpp -o $@ -g

${OBJ}/MaxHeap.o: MaxHeap.cpp MaxHeap.h
	g++ -c ${CFLAGS} MaxHeap.cpp -o $@ -g


debug_waitlist: waitlist
	gdb --args waitlist Fall2023 testFiles/prereq1.txt testFiles/WLschedules1.txt testFiles/enroll1.txt

clean:
	rm -f ${OBJ}/*.o pr_check sch_check waitlist