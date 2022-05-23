CXX := g++
CXXFLAGS := -g -Wall --std=c++11
GTESTINCL := -I /usr/include/gtest/  
GTESTLIBS := -lgtest -lgtest_main  -lpthread
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: rh
tests: llrec-test stack-test heap-test

# generic rule for .cpp files
board.o : board.cpp board.h vehicle.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
heur.o : heur.cpp heur.h board.h vehicle.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
move.o : move.cpp move.h board.h heur.h vehicle.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
solver.o : solver.cpp solver.h move.h board.h heur.h vehicle.h
	$(CXX) $(CXXFLAGS) -c $< -o $@
rh : rh.cpp board.o heur.o move.o solver.o
	$(CXX) $(CXXFLAGS) $^ -o $@

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------
llrec.o : llrec.cpp llrec.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

llrec-test : llrec-test.cpp llrec.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# used to test own test cases
rec-tests : llrec-test
	$(VALGRIND) ./llrec-test llrec-tests/llrec-test1.in llrec-tests/llrec-test2.in llrec-tests/llrec-test3.in
#	$(VALGRIND) ./llrec-test llrec-tests/llrec-test2.in llrec-tests/llrec-test3.in llrec-tests/llrec-test4.in
#	$(VALGRIND) ./llrec-test llrec-tests/llrec-test3.in llrec-tests/llrec-test4.in llrec-tests/llrec-test5.in
#	$(VALGRIND) ./llrec-test llrec-tests/llrec-test4.in llrec-tests/llrec-test5.in llrec-tests/llrec-test6.in
#	$(VALGRIND) ./llrec-test llrec-tests/llrec-test5.in llrec-tests/llrec-test6.in llrec-tests/llrec-test1.in
#	$(VALGRIND) ./llrec-test llrec-tests/llrec-test6.in llrec-tests/llrec-test1.in llrec-tests/llrec-test2.in

#-----------------------------------------------------
# ADD target(s) to build your stack-test executable
#-----------------------------------------------------
stack-test : stack-test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
stack : stack-test
	$(VALGRIND) ./stack-test

#	target for test heap.h
heap-test : heap-test.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^
heap : heap-test
	$(VALGRIND) ./heap-test
	

clean:
	rm -f *.o rh llrec-test stack-test heap-test*~

.PHONY: clean 
