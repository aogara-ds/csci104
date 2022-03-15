CXX := g++
CXXFLAGS := -g -Wall --std=c++11
GTESTINCL := -I /usr/include/gtest/  
GTESTLIBS := -lgtest -lgtest_main  -lpthread
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: labellist-test

check: hw1-checkpt run-check

labellist-test: labellist-test.o labellist.o
	$(CXX) $(CXXFLAGS) $^ -o $@
# generic rule for .cpp files
labellist.o : labellist.cpp labellist.h 
labellist-test.o : labellist-test.cpp labellist.h

hw1-checkpt: hw1-checkpt.cpp labellist.o
	$(CXX) $(CXXFLAGS) $(GTESTINCL) $^ -o $@ $(GTESTLIBS)

run-check:
	./hw1-checkpt

clean:
	rm -f *.o labellist-test hw1-checkpt *~

valgrind:
	$(VALGRIND) ./labellist-test
	
.PHONY: clean run-check